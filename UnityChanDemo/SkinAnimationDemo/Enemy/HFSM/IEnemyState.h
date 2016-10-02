/*!
 * @brief	�G�̏�Ԃ̊��N���X�B
 */

#pragma once

#include "Enemy/Enemy.h"


/*!
 * @brief	�G�̏�Ԃ̊��N���X�B
 */
class IEnemyState{
public:
	IEnemyState( Enemy* enemy ) :
		enemy(enemy),
		m_localState(-1)
	{
	}
	virtual ~IEnemyState()
	{
	}

	virtual void Update() = 0;
	virtual void Enter() 
	{
		m_localState = -1;
	}
	virtual void Leave()
	{

	}
	void ChangeLocalState( int nextState )
	{
		if(m_localState != -1){
			m_localStates[m_localState]->Leave();
		}
		m_localState = nextState;
		m_localStates[m_localState]->Enter();
	}
protected:
	std::vector<IEnemyState*>	m_localStates;		//���[�J���B
	int							m_localState;		//���[�J���X�e�[�g�B
	Enemy*						enemy;

};