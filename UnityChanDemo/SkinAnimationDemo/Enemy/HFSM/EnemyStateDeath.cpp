/*!
 * @brief	��������ԁB
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDeath.h"


/*!
 * @brief	�R���X�g���N�^�B
 */
EnemyStateDeath::EnemyStateDeath( Enemy* enemy ) :
	IEnemyState(enemy)
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
}
void EnemyStateDeath::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
}
void EnemyStateDeath::Leave()
{
}
