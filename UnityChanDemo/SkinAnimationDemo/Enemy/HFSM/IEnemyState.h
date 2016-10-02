/*!
 * @brief	�G�̏�Ԃ̊��N���X�B
 */

#pragma once

/*!
 * @brief	�G�̏�Ԃ̊��N���X�B
 */
class IEnemyState{
public:
	IEnemyState()
	{
	}
	virtual ~IEnemyState()
	{
	}
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
protected:
	std::vector<IEnemyState*>	m_childState;		//�q���B

};