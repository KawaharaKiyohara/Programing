/*!
 * @brief	�ҋ@��ԁB
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateIdle.h"


/*!
 * @brief	�R���X�g���N�^�B
 */
EnemyStateIdle::EnemyStateIdle(Enemy* enemy) :
	IEnemyState(enemy)
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
EnemyStateIdle::~EnemyStateIdle()
{
}
void EnemyStateIdle::Update()
{
}
void EnemyStateIdle::Enter() 
{
	IEnemyState::Enter();
	enemy->SetMoveSpeed(0.0f);
	enemy->PlayAnimation(Enemy::enAnimStand);
}
void EnemyStateIdle::Leave() 
{
}
