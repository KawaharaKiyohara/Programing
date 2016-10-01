/*!
 * @brief	�L�����N�^�̃R���W�����R���g���[���B
 */

#pragma once

/*!
 * @brief
 */
class CharacterCollisionController{
public:
	CharacterCollisionController();
	~CharacterCollisionController();
	
	/*!
	 * @brief	���s�B
	 */
	void Execute( CVector3 nextPosition );
private:
	CVector3 			position;		//���W�B
	CVector3 			moveSpeed;		//�ړ����x�B 
	bool 				isJump;			//�W�����v���H
	SphereCollider		collider;		//�R���C�_�B
};