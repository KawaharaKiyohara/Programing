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
void EnemyStateDeath::Enter() 
{
}
void EnemyStateDeath::Leave()
{
}
