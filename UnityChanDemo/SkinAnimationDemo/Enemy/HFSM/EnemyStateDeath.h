/*!
 * @brief	���S��ԁB
 */

#pragma once 

#include "IEnemyState.h"

class EnemyStateDeath : public IEnemyState{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	EnemyStateDeath( Enemy* enemy );
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~EnemyStateDeath();
	void Update() override;
	void Enter() override;
	void Leave() override;
};