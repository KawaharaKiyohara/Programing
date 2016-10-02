/*!
 * @brief	������ԁB
 */

#pragma once

#include "IEnemyState.h"

/*!
 * @brief	������ԁB
 */
class EnemyStateWalk : public IEnemyState{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	EnemyStateWalk();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~EnemyStateWalk();
	void Update() override;
	void Enter() override;
	void Leave() override;
};