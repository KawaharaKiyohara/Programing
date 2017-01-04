/*!
 * @brief	���ԑ���n(���Ԓ�~)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillStop.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"

void MagicSkillStop::MagicSkillStopFinish::Update()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = blendRate - 4.0f * GameTime().GetFrameDeltaTime();
	

	if (blendRate < 0.0f) {
		//�I���B
		DeleteGO(this);
		MonochromeFilter().SetEnalbe(false);
	}
	else {
		MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
			//�v���C���[�������_�����O���ă}�X�N���쐬����B
			g_player->Render(renderContext);
			for (auto& e : g_enemyManager->GetEnemyList()) {
				e->Render(renderContext);
			}
		});
		MonochromeFilter().SetBlendRate(blendRate);
	}
}
MagicSkillStop::MagicSkillStop(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillStop::~MagicSkillStop()
{
}
void MagicSkillStop::OnChangeMagic()
{
}
void MagicSkillStop::OnStartMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	MotionBlur().SetEnable(true);
	MonochromeFilter().SetEnalbe(true);
	//�I�������������Ă��邩������Ȃ��̂ō폜�B
	DeleteGO(&m_finish);
//	MonochromeFilter().SetBlendRate(0.0f);
}
void MagicSkillStop::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	//�I���������Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^�B
	AddGO(0, &m_finish);
	//�����ł��}�X�N��`�悵�Ȃ��ƂP�t���[�������}�X�N���Ȃ���Ԃŕ`�悳��Ă��܂��B
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	MotionBlur().SetEnable(false);
}
void MagicSkillStop::OnUsingMagicSkill()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = min(1.0f, blendRate + 4.0f * GameTime().GetFrameDeltaTime());
	MonochromeFilter().SetBlendRate(blendRate);
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext){
		//�v���C���[�������_�����O���ă}�X�N���쐬����B
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
}

