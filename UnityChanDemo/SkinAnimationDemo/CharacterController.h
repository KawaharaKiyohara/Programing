/*!
 * @brief	キャラクタコントローラー。。
 */

#pragma once

#include "Physics/SphereCollider.h"
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"

/*!
 * @brief
 */
class CharacterController{
public:
	CharacterController();
	~CharacterController();
	/*!
	 * @brief	初期化。
	 */
	void Init(float radius, float height, const CVector3& position);
	/*!
	 * @brief	実行。
	 */
	void Execute();
	/*!
	 * @brief	座標を取得。
	 */
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	 * @brief	座標を設定。
	 */
	void SetPosition(const CVector3& pos)
	{
		position = pos;
	}
	/*!
	 * @brief	移動速度を設定。
	 */
	void SetMoveSpeed(const CVector3& speed )
	{
		moveSpeed = speed;
	}
	/*!
	 * @brief	移動速度を取得。
	 */
	const CVector3& GetMoveSpeed() const
	{
		return moveSpeed;
	}
	/*!
	 * @brief	ジャンプさせる。
	 */
	void Jump( )
	{
		isJump = true;
	}
	/*!
	 * @brief	ジャンプ中か判定
	 */
	bool IsJump() const
	{
		return isJump;
	}
	/*!
	* @brief	コライダーを取得。
	*/
	CapsuleCollider* GetCollider()
	{
		return &collider;
	}
	/*!
	* @brief	死亡したことを通知。
	*/
	void NotifyDead();
private:
	CVector3 			position;		//座標。
	CVector3 			moveSpeed;		//移動速度。 
	bool 				isJump;			//ジャンプ中？
	//SphereCollider		collider;		//コライダ。
	CapsuleCollider		collider;		//コライダー。
	float				radius;
	float				height;		
	RigidBody			rigidBody;			//剛体。
};