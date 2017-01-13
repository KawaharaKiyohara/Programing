#include "stdafx.h"
#include "GameScene.h"
#include "ScreenEffect/Fade.h"
#include "Common/CardDeck.h"
#include "Scene/TitleScene.h"
#include "tkEngine/Sound/tkSoundSource.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
	
}
GameScene::~GameScene()
{
	//HandsOn-3 BGM�̍Đ����~�߂�B
	DeleteGO(bgmSource);
}
void GameScene::OnDestroy()
{
	DeleteGO(&cardDeck);
	for (int i = 0; i < NUM_PLAYER; i++) {
		DeleteGO(&playerList[i]);
	}
}
bool GameScene::Start()
{
	switch (m_initState) {
	case enInitState_Init00:
		light.SetAmbinetLight(CVector3::One);
		//�J�������������B
		camera.SetPosition({ 0.0f, 0.0f, -700.0f });
		camera.SetNear(400.0f);
		camera.SetFar(1000.0f);
		camera.Update();
		
		AddGO(0, &cardDeck);
		textureBG = TextureResources().Load("Assets/sprite/BG.jpg");
		spriteBG.Init(textureBG);
		spriteBG.SetSize({ 1280, 720 });
		m_initState = enInitState_WaitInit;
		break;
	case enInitState_WaitInit:
		if (cardDeck.IsInited()) {
			return true;
		}
		break;
	}
	return false;
}
/*!
*@brief	���s����B
*/
bool GameScene::Judgement()
{
	if (playerList[0].GetCardList().empty()) {
		//�v���C���[0�̏���
		return true;
	}
	else if (playerList[1].GetCardList().empty()) {
		//COM�̏���
		return true;
	}
	return false;
}
void GameScene::Update()
{
	switch (gameStep) {
	case enGameStep_DealCards: {
		//HandsOn-2 BGM�̍Đ����J�n���邽�߂�CSoundSource�̃C���X�^���X�𐶐�����B
		bgmSource = NewGO<CSoundSource>(0);
		bgmSource->Init("Assets/sound/BGM.wav");
		bgmSource->Play(true);
		//�J�[�h��z��B
		int numPlayerNo = 0;
		while (true) {
			Card* card = cardDeck.GetUnuseCardRandom();
			if (card == NULL) {
				//�S���z��I������B
				break;
			}
			playerList[numPlayerNo].AddCard(card);
			numPlayerNo = (numPlayerNo + 1) % NUM_PLAYER;
		}
		for (int i = 0; i < NUM_PLAYER; i++) {
			AddGO(0, &playerList[i]);
			playerList[i].SetPlayerNo(i);
		}
		//�J�[�h�̈�������ɂȂ�v���C���[��ݒ�B
		playerList[0].SetTargetPlayer(&playerList[1]);
		playerList[1].SetTargetPlayer(&playerList[0]);
		g_fade->StartFadeIn();
		gameStep = enGameStep_WaitFadeIn;
	}break;
	case enGameStep_WaitFadeIn:
		if (!g_fade->IsExecute()) {
			//�܂��̓v���C���[�̎�ԁB
			playerList[0].ChangeState(Player::enStateSelectCard);
			gameStep = enGameStep_SelectPlayer;
		}
		break;
	case enGameStep_SelectPlayer:
		if (playerList[0].GetState() == Player::enStateIdle) {
			playerList[0].UpdateCardPosition();
			playerList[1].UpdateCardPosition();
			//�v���C���[�I���I���B
			if (Judgement()) {
				//�����������B
				gameStep = enGameStep_Over;
			}
			else {
				//COM�̎�ԁB
				playerList[1].ChangeState(Player::enStateSelectCard);
				gameStep = enGameStep_SelectCom;
			}
		}
		break;
	case enGameStep_SelectCom:
		if (playerList[1].GetState() == Player::enStateIdle) {
			//COM�I���I���B
			playerList[0].UpdateCardPosition();
			playerList[1].UpdateCardPosition();
			if (Judgement()) {
				//�����������B
				gameStep = enGameStep_Over;
			}
			else {
				//�v���C���[�̎�ԁB
				playerList[0].ChangeState(Player::enStateSelectCard);
				gameStep = enGameStep_SelectPlayer;
			}
		}
		break;
	case enGameStep_Over:
		MessageBox(NULL, "����", "�����", MB_OK);
		g_fade->StartFadeOut();
		gameStep = enGameStep_WaitFadeOut;
		break;
	case enGameStep_WaitFadeOut:
		if (!g_fade->IsExecute()) {
			//�^�C�g���ɖ߂�B
			DeleteGO(this);
			NewGO<TitleScene>(0);
		}
		break;
	}
}
void GameScene::Render(CRenderContext& rc)
{
	rc.SetRenderState(RS_ZWRITEENABLE, FALSE);
	spriteBG.Draw(rc);
	rc.SetRenderState(RS_ZWRITEENABLE, TRUE);
}