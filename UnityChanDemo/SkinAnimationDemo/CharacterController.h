/*!
 * @brief	�L�����N�^�R���g���[���[�B�B
 */

#pragma once

#include "Physics/SphereCollider.h"

/*!
 * @brief
 */
class CharacterController{
public:
	CharacterController();
	~CharacterController();
	/*!
	 * @brief	�������B
	 */
	void Init(float radius, const CVector3& position);
	/*!
	 * @brief	���s�B
	 */
	void Execute();
	/*!
	 * @brief	���W���擾�B
	 */
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	 * @brief	���W��ݒ�B
	 */
	void SetPosition(const CVector3& pos)
	{
		position = pos;
	}
	/*!
	 * @brief	�ړ����x��ݒ�B
	 */
	void SetMoveSpeed(const CVector3& speed )
	{
		moveSpeed = speed;
	}
	/*!
	 * @brief	�ړ����x���擾�B
	 */
	const CVector3& GetMoveSpeed() const
	{
		return moveSpeed;
	}
	/*!
	 * @brief	�W�����v������B
	 */
	void Jump( )
	{
		isJump = true;
	}
	/*!
	 * @brief	�W�����v��������
	 */
	bool IsJump() const
	{
		return isJump;
	}
private:
	CVector3 			position;		//���W�B
	CVector3 			moveSpeed;		//�ړ����x�B 
	bool 				isJump;			//�W�����v���H
	SphereCollider		collider;		//�R���C�_�B
	float				radius;
};