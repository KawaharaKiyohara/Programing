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
	void Enter(const SEnterArg& enterArg) override;
	void Leave() override;
	//�_���[�W���󂯂邱�Ƃ��o���邩����B
	bool IsPossibleApplyDamage(const DamageCollisionWorld::Collision* colli) const override
	{
		return false;
	}
};