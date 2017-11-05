#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "tkEngine/light/tkPointLight.h"
#include "GameCamera.h"
#include "GameOverControl.h"
#include "star.h"

//#define CLASH_DEBUB

Game::Game()
{
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	//���C�g��z�u�B
	CSkeleton ligLoc;
	ligLoc.Load(L"loc/light.tks");
	for (int i = 1; i < ligLoc.GetNumBones(); i++) {
		CBone* bone = ligLoc.GetBone(i);
		prefab::CPointLight* ptLig = NewGO<prefab::CPointLight>(0);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		ptLig->SetPosition(pos);
		ptLig->SetColor({
			200.0f,
			200.0f,
			100.0f,
			1.0f
		});
		ptLig->SetAttn({
			550.0f,
			3.0f,
			0.1f
		});
		m_pointLight.push_back(ptLig);
	}

	//�G��z�u
	CSkeleton enemyLoc;
	enemyLoc.Load(L"loc/enemy.tks");
	for (int i = 1; i < enemyLoc.GetNumBones(); i++) {
		CBone* bone = enemyLoc.GetBone(i);
		Enemy* enemy = NewGO <Enemy>(0);
		m_enemyList.push_back(enemy);
	
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		enemy->SetPosition(pos);
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"pathData/enemy0%d_path.tks", i);
		enemy->Init(moveFilePath);
	}
	//����z�u
	CSkeleton starLoc;
	starLoc.Load(L"loc/star.tks");
	for (int i = 1; i < starLoc.GetNumBones(); i++) {
		CBone* bone = starLoc.GetBone(i);
		Star* star = NewGO <Star>(0);

		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		star->SetPosition(pos);
		star->SetTags(enGameObject_Star);	//�^�O��ݒ�B
	}

}
bool Game::Start()
{
#ifndef CLASH_DEBUB
	
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 50.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 300.0f, 300.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().Update();

	m_player = NewGO<Player>(0, "Player");
	m_background = NewGO<Background>(0);
	m_gameCamera = NewGO<GameCamera>(0);
	//�V�[�����C�g���������B
	InitSceneLight();
	CVector3 dir = { 1.0f, -1.0f, -1.0f };
	dir.Normalize();
	GraphicsEngine().GetShadowMap().SetLightDirection(dir);
	m_bgmSource = NewGO<prefab::CSoundSource>(0);
	m_bgmSource->Init("sound/normalBGM.wav");
	m_bgmSource->Play(true);
#endif
	return true;
}
void Game::OnDestroy() 
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	for (auto pt : m_pointLight) {
		DeleteGO(pt);
	}
	for (auto enemy : m_enemyList) {
		DeleteGO(enemy);
	}
	DeleteGO(m_gameCamera);
	DeleteGO(m_bgmSource);
	//Star���폜�B
	FindGameObjectsWithTag(enGameObject_Star, [](IGameObject* go) {
		DeleteGO(go);
	});
	NewGO<Game>(0, "Game");
}
void Game::NotifyGameOver()
{
	m_isGameOver = true;
	m_player->NotifyGameOver();
	m_gameCamera->NotifyGameOver();
	//�Q�[���I�[�o�[������쐬�B
	m_gameOverControl = NewGO<GameOverControl>(0);
}
void Game::NotifyRestart()
{
	m_isGameOver = false;
	m_gameCamera->NotifyRestart();
	m_player->NotifyRestart();
	for (auto& enemy : m_enemyList) {
		enemy->NotifyRestart();
	}
	DeleteGO(m_gameOverControl);
}
void Game::Update()
{
#ifndef CLASH_DEBUB
	//�N���A����
	int coinCount = 0;
	FindGameObjectsWithTag(enGameObject_Star, [&](IGameObject* go) {
		coinCount++;
	});
	if (coinCount == 0) {
		//�S���̃R�C����������B
		TK_WARNING_MESSAGE_BOX("���肠�`");
		DeleteGO(this);
	}
#else
	if (Pad(0).IsTrigger(enButtonA)) {
		if (m_background == nullptr) {
			m_background = NewGO<Background>(0);
		}
		else {
			DeleteGO(m_background);
			m_background = nullptr;
		}
	}
#endif
}
void Game::Render(CRenderContext& rc)
{
}