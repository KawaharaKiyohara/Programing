/*!
 * @brief	���ԑ���n(����̑��x��x��)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillSlow.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "Scene/gameScene.h"
#include "Map/Sky.h"

void MagicSkillSlow::MagicSkillStopFinish::Update()
{
	float blendRate = SepiaFilter().GetBlendRate();
	blendRate = blendRate - 4.0f * GameTime().GetFrameDeltaTime();
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	if (blendRate < 0.0f) {
		//�I���B
		DeleteGO(this);
		SepiaFilter().SetEnalbe(false);
	}
	else {
		SepiaFilter().SetBlendRate(blendRate);
	}
}

MagicSkillSlow::MagicSkillSlow(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillSlow::~MagicSkillSlow()
{
}
void MagicSkillSlow::OnChangeMagic()
{
}
void MagicSkillSlow::OnStartMagic()
{
	//�ۓ������Đ�
	CSoundSource* s = NewGO<CSoundSource>(0);
	s->Init("Assets/Sound/heartbeat.wav");
	s->Play(false);
	const float deltaTimeMul = 0.3f;
	g_enemyManager->SetFrameDeltaTimeMul(deltaTimeMul);
	gameScene->GetSky()->SetFrameDeltaTimeMul(deltaTimeMul);
	SepiaFilter().SetEnalbe(true);
	
	auto pauseSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Pause();
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		pauseSound
	);
	
	//�I�������������Ă��邩������Ȃ��̂ō폜�B
	DeleteGO(&m_finish);
}
void MagicSkillSlow::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	gameScene->GetSky()->SetFrameDeltaTimeMul(1.0f);
	//�I���������Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^�B
	AddGO(0, &m_finish);
	//�����ł��}�X�N��`�悵�Ȃ��ƂP�t���[�������}�X�N���Ȃ���Ԃŕ`�悳��Ă��܂��B
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	
	auto resumeSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Play(s->GetLoopFlag());
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		resumeSound
	);
}
void MagicSkillSlow::OnUsingMagicSkill()
{
	float blendRate = SepiaFilter().GetBlendRate();
	blendRate = min(1.0f, blendRate + 4.0f * GameTime().GetFrameDeltaTime());
	SepiaFilter().SetBlendRate(blendRate);
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
}

