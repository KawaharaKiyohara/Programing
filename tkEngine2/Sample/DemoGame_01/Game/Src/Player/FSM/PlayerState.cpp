/*!
 * @brief	�v���C���[�̃X�e�[�g
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/FSM/PlayerState.h"


namespace {
	const float WALK_THREDHOLD = 0.01f;							//!<������ԂɑJ�ڂ��鑬�x��臒l�B
	const float RUN_THREDHOLD = CPlayerConst::RUN_SPEED * 0.8f;	//!<�����ԂɑJ�ڂ��鑬�x��臒l�B
}
void CPlayerStateIdle::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD ;
	float moveSpeedScaler = moveSpeed.Length();
	if (moveSpeedScaler > runThreadhold) {
		//�����ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler > WALK_THREDHOLD) {
		//������ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
}

void CPlayerStateWalk::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();
	
	if (moveSpeedScaler > runThreadhold) {
		//�����ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//�ҋ@��ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}

void CPlayerStateRun::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();

	if (moveSpeedScaler < runThreadhold) {
		//������ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//�ҋ@��ԂɑJ�ځB
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}