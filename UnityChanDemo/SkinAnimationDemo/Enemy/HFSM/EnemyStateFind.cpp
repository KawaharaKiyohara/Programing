/*!
 * @brief	������ԁB
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateFind.h"
#include "Enemy/HFSM/EnemyStateRun.h"
#include "Enemy/HFSM/EnemyStateAttack.h"
#include "UnityChan.h"

/*!
 * @brief	�R���X�g���N�^�B
 */
EnemyStateFind::EnemyStateFind(Enemy* enemy) :
	IEnemyState(enemy)
{
	m_localStates.push_back( new EnemyStateRun(enemy) );
	m_localStates.push_back( new EnemyStateAttack(enemy) );
}
/*!
 * @brief	�f�X�g���N�^�B
 */
EnemyStateFind::~EnemyStateFind()
{
}
void EnemyStateFind::Update()
{
	m_localStates[m_localState]->Update();
	if( m_localState == enLocalState_Run){
		CVector3 moveDirTmp;
		moveDirTmp.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
		if (moveDirTmp.LengthSq() > 1.0f * 1.0f) {
			moveDirTmp.Normalize();
			enemy->SetMoveDirection(moveDirTmp);
		}
		else {
			//�U����ԂɑJ��
			ChangeLocalState(enLocalState_Attack);
		}
	}else if(m_localState == enLocalState_Attack){
		CVector3 dist;
		dist.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
		if (dist.LengthSq() > 1.0f * 1.0f) {
			ChangeLocalState(enLocalState_Run);
		}
	}
}
void EnemyStateFind::Enter() 
{
	IEnemyState::Enter();
	ChangeLocalState(enLocalState_Run);
}
void EnemyStateFind::Leave() 
{
	IEnemyState::Leave();
}
