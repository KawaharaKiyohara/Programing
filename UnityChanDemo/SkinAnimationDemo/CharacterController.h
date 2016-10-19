/*!
 * @brief	�L�����N�^�R���g���[���[�B�B
 */

#pragma once

#include "tkEngine/Physics/tkSphereCollider.h"
#include "tkEngine/Physics/tkCapsuleCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

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
	void Init(float radius, float height, const CVector3& position);
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
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CCapsuleCollider* GetCollider()
	{
		return &collider;
	}
	/*!
	* @brief	���S�������Ƃ�ʒm�B
	*/
	void NotifyDead();
private:
	CVector3 			position;		//���W�B
	CVector3 			moveSpeed;		//�ړ����x�B 
	bool 				isJump;			//�W�����v���H
	CCapsuleCollider	collider;		//�R���C�_�[�B
	float				radius;
	float				height;		
	CRigidBody			rigidBody;		//���́B
};