/*!
 * @brief	�L�����N�^�̃R���W�����R���g���[���B
 */

#include "stdafx.h"
#include "CharacterController.h"
#include "CollisionAttr.h"

namespace{
	//�n�ʂƂ̓����蔻��B
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		CVector3 hitNormal;
		btCollisionObject* me;
		SweepResultGround()
		{
			isHit = false;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
			hitPos.y = -FLT_MAX;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me) {
				//�����ɏՓ˂����B
				return 0.0f;
			}
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = hitNormalTmp.Dot(CVector3::Up);
			t = fabsf(acosf(t));
			if (t < CMath::PI * 0.3f
				&& convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Character
				) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�̍����𒲂ׂ�B�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (hitPos.y < hitPosTmp.y) {
					hitPos = hitPosTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
				}
			}
			return 0.0f;
		}
	};
	//��
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		float dist;
		CVector3 hitNormal;
		btCollisionObject* me;
		SweepResultWall()
		{
			isHit = false;
			dist = FLT_MAX;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me) {
				//�����ɏՓ˂����B
				return 0.0f;
			}
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
			if (t >= CMath::PI * 0.3f 
				|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
			) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�Ƃ̋����𒲂ׂ�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (distTmp < dist) {
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
				}
			}
			return 0.0f;
		}
	};
}

CharacterController::CharacterController() :
	moveSpeed(CVector3::Zero),
	position(CVector3::Zero),
	isJump(false),
	radius(0.0f)
{
}
CharacterController::~CharacterController()
{
}
void CharacterController::Init(float radius, float height, const CVector3& position)
{
	this->position = position;
	//�R���W�����쐬�B
	this->radius = radius;
	this->height = height;
	collider.Create(radius, height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &collider;
	rbInfo.mass = 0.0f;
	rigidBody.Create(rbInfo);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physicsWorld->AddRigidBody(&rigidBody);

}
void CharacterController::Execute()
{
	//Y�����ɂ͏d�͗�����������B
	const float GRAVITY = -18.8f;
	moveSpeed.y += GRAVITY * GameTime().GetFrameDeltaTime();
	CVector3 nextPosition = position;
	CVector3 addPos = moveSpeed;
	addPos.Scale(GameTime().GetFrameDeltaTime());
	nextPosition.Add(addPos);
		
	//XZ���ʂ𒲂ׂ�B
	{
		int loopCount = 0;
		while (true) {
			CVector3 addPos;
			addPos.Subtract(nextPosition, position);
			CVector3 posTmp = position;
			posTmp.y += height * 0.5f + radius + 0.2f;
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			CVector3 newPos;
			SweepResultWall callback;
			callback.me = rigidBody.GetBody();
			callback.startPos = position;
			CVector3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() > 0.0001f) {
				newPos.Add(posTmp, addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

				g_physicsWorld->ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
			}
			if (callback.isHit) {
				//���������B
				//�ǁB
				nextPosition.x = callback.hitPos.x;
				nextPosition.z = callback.hitPos.z;
				//���a�������߂��B
				CVector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				CVector3 t = hitNormalXZ;
				t.Scale(radius);
				nextPosition.Add(t);
				//�����ĕǂɉ����Ċ��点��B
				t.Cross(hitNormalXZ, CVector3::Up);
				t.Normalize();
				//�����߂��œ��������͌��Z����B
				CVector3 t2;
				t2.Subtract(nextPosition, position);
				t2.y = 0.0f;
				addPosXZ.Subtract(t2);
				t.Scale(t.Dot(addPosXZ));
				nextPosition.Add(t);
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//�������𒲂ׂ�B
	{
		CVector3 addPos;
		addPos.Subtract(nextPosition, position);
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(position.x, position.y + height * 0.5f + radius, position.z));
		CVector3 newPos;
		SweepResultGround callback;
		callback.me = rigidBody.GetBody();
		callback.startPos = position;
		if (addPos.y < 0.0f) {
			newPos = (*(CVector3*)&start.getOrigin());
			newPos.y += addPos.y;

			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_physicsWorld->ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
		}
		if (callback.isHit) {
			//���������B
			float t = fabsf(acosf(callback.hitNormal.Dot(CVector3::Up)));
			//�n�ʁB
			CVector3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//�����߂��ʁB
			Circle = CVector3::Zero;

			Circle = position;
			Circle.y = callback.hitPos.y;//�~�̒��S
			CVector3 v;
			v.Subtract(Circle, callback.hitPos);
			x = v.Length();//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B

			offset = sqrt(max(0.0f, radius*radius - x*x));//y�̕����������߂�B

			moveSpeed.y = 0.0f;
			isJump = false;
			nextPosition.y = callback.hitPos.y + offset - radius;
		}
	}
	position = nextPosition;

	btRigidBody* btBody = rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
}
/*!
* @brief	���S�������Ƃ�ʒm�B
*/
void CharacterController::NotifyDead()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
}