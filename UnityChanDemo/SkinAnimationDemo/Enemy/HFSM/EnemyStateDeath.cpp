/*!
 * @brief	��������ԁB
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDeath.h"
#include "ParticleParam.h"

/*!
 * @brief	�R���X�g���N�^�B
 */
EnemyStateDeath::EnemyStateDeath( Enemy* enemy ) :
	IEnemyState(enemy),
	timer(0.0f)
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
EnemyStateDeath::~EnemyStateDeath()
{
}
void EnemyStateDeath::Update() 
{
	enemy->PlayAnimation(Enemy::enAnimDeath);
	enemy->SetMoveSpeed(0.0f);
	timer += GameTime().GetFrameDeltaTime();
	if(timer > 1.0f){
		for (auto& p : particleEmitterList) {
			DeleteGO(p);
		}
		particleEmitterList.clear();
	}
}
void EnemyStateDeath::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
	CMatrix* m = enemy->FindBoneWorldMatrix("Bip001_Neck");
	if (m == NULL) {
		//���J���J��
		m = enemy->FindBoneWorldMatrix("spine");
	}
	if (m != NULL) {
		//�p�[�e�B�N���G�~�b�^�[��o�^�B
		for (SParicleEmitParameter& param : bloodEmitterParam) {
			CParticleEmitter* particleEmitter = NewGO<CParticleEmitter>(0);
			CVector3 pos;
			pos.Set(m->m[3][0], m->m[3][1], m->m[3][2]);
			particleEmitter->Init(g_random, g_camera->GetCamera(), param, pos);
			particleEmitterList.push_back(particleEmitter);
		}
	}
	timer = 0.0f;
}
void EnemyStateDeath::Leave()
{
	for (auto& p : particleEmitterList) {
		DeleteGO(p);
	}
	particleEmitterList.clear();
}
