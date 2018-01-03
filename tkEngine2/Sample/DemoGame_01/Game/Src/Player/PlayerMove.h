/*!
 * @brief	�v���C���[�̈ړ������B
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

class CPlayer;
class CGameCamera;

class CPlayerMove : public IGameObject{
public:
	CPlayerMove( CPlayer* pl );
	~CPlayerMove();
	bool Start() override final;
	void Update() override final;
	/*!
	 *@brief	�ړ����x�̎擾�B
	 */
	CVector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
private:
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���B
	CPlayer* m_player = nullptr;
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CGameCamera* m_gameCamera = nullptr;
	float m_accelTime = 0.0f;
};