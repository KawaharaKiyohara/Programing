/*!
 * @brief	������ԁB
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateAttack.h"
#include "UnityChan.h"
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
	CVector3 dir;
	dir.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
	if (dir.LengthSq() > 0.01f) {
		dir.Normalize();
		enemy->SetMoveDirection(dir);
	}
}
void EnemyStateAttack::Enter()
{
	IEnemyState::Enter();
}
void EnemyStateAttack::Leave()
{
}
