/*!
 * @brief	�U����ԁB
 */

#pragma once

#include "IEnemyState.h"

class EnemyStateAttack : public IEnemyState{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	EnemyStateAttack( Enemy* enemy );
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~EnemyStateAttack();
	void Update() override;
	void Enter() override;
	void Leave() override;
};