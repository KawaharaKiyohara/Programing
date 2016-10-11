/*!
 * @brief	��������ԁB
 */

#pragma once 

#include "IEnemyState.h"

class EnemyStateDamage : public IEnemyState{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	EnemyStateDamage( Enemy* enemy );
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~EnemyStateDamage();
	void Update() override;
	void Enter() override;
	void Leave() override;
};