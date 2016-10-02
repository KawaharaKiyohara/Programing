/*!
 * @brief	������ԁB
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateAttack.h"

/*!
* @brief	�R���X�g���N�^�B
*/
EnemyStateAttack::EnemyStateAttack( Enemy* enemy ) :
	IEnemyState(enemy)
{

}
/*!
	* @brief	�f�X�g���N�^�B
	*/
EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	enemy->PlayAnimation(Enemy::enAnimAttack);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateAttack::Enter()
{
	IEnemyState::Enter();
}
void EnemyStateAttack::Leave()
{
}
