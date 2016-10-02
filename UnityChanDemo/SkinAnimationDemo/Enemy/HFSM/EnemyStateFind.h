/*!
 * @brief	������ԁB
 */

#pragma once

#include "UnityChan.h"
#include "IEnemyState.h"

/*!
 * @brief	���G��ԁB
 */
class EnemyStateFind : public IEnemyState{
private:

	enum EnLocalState{
		enLocalState_Run,
		enLocalState_Attack,
		enLocalState_Idle,
	};
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	EnemyStateFind(Enemy* enemy);
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~EnemyStateFind();
	void Update() override;
	void Enter() override;
	void Leave() override;
private:
	float timer;
	UnityChan::SBattleSeat*		battleSeat;
};