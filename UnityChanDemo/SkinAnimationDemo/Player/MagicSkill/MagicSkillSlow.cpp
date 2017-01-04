/*!
 * @brief	���ԑ���n(����̑��x��x��)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillSlow.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "tkEngine/Sound/tkSoundSource.h"

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
	g_enemyManager->SetFrameDeltaTimeMul(0.3f);
	MotionBlur().SetEnable(true);
	SepiaFilter().SetEnalbe(true);
	//�I�������������Ă��邩������Ȃ��̂ō폜�B
	DeleteGO(&m_finish);
}
void MagicSkillSlow::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	MotionBlur().SetEnable(false);
	//�����ł��}�X�N��`�悵�Ȃ��ƂP�t���[�������}�X�N���Ȃ���Ԃŕ`�悳��Ă��܂��B
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	//�I���������Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^�B
	AddGO(0, &m_finish);
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

