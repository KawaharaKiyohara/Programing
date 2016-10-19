/*!
 * @brief	�L�����N�^�̃R���W�����R���g���[���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/character/tkCollisionAttr.h"
namespace tkEngine{

	namespace{
		//�n�ʂƂ̓����蔻��B
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;
			CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);
			CVector3 startPos = CVector3::Zero;
			CVector3 hitNormal = CVector3::Zero;
			btCollisionObject* me = nullptr;
			float dist = FLT_MAX;
			SweepResultGround()
			{
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
				if ((t < CMath::PI * 0.3f
					&& convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Character)
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground
					) {
					isHit = true;
					CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
					//��_�̍����𒲂ׂ�B�B
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					float distTmp = vDist.Length();
					if (dist > distTmp) {
						hitPos = hitPosTmp;
						hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
						dist = distTmp;
					}
				}
				return 0.0f;
			}
		};
		//��
		struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;
			CVector3 hitPos = CVector3::Zero;
			CVector3 startPos = CVector3::Zero;
			float dist = FLT_MAX;
			CVector3 hitNormal = CVector3::Zero;
			btCollisionObject* me = nullptr;
			SweepResultWall()
			{
			}
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me ) {
					//�����ɏՓ˂����Bor �n�ʂɏՓ˂����B
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

	CCharacterController::CCharacterController() :
		moveSpeed(CVector3::Zero),
		position(CVector3::Zero),
		isJump(false),
		radius(0.0f)
	{
	}
	CCharacterController::~CCharacterController()
	{
	}
	void CCharacterController::Init(float radius, float height, const CVector3& position)
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
		PhysicsWorld().AddRigidBody(&rigidBody);

	}
	void CCharacterController::Execute()
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
				callback.startPos = posTmp;
				CVector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (addPosXZ.Length() > 0.0001f) {
					newPos.Add(posTmp, addPosXZ);
					end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

					PhysicsWorld().ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
				}
				if (callback.isHit) {
					//���������B
					//�ǁB
					CVector3 vT0, vT1;
					//XZ���ʏ�ł̈ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
					vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
					vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
					//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
					CVector3 vMerikomi;
					vMerikomi.Subtract(vT0, vT1);
					//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B�B
					CVector3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();
					//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
					float fT0 = hitNormalXZ.Dot(vMerikomi);
					//�����߂��Ԃ��x�N�g�������߂�B
					//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
					CVector3 vOffset;
					vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + radius);
					nextPosition.Add(vOffset);
				}
				else {
					//�ǂ��Ƃ�������Ȃ��̂ŏI���B
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					//�ړ��ł��Ȃ��B
					break;
				}
			}
		}
		//XZ�̈ړ��͊m��B
		position.x = nextPosition.x;
		position.z = nextPosition.z;
		//�������𒲂ׂ�B
		{
			CVector3 addPos;
			addPos.Subtract(nextPosition, position);
			
			position = nextPosition;	//�ړ��̉��m��B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(position.x, position.y + height * 0.5f + radius, position.z));
			CVector3 newPos;
			SweepResultGround callback;
			callback.me = rigidBody.GetBody();
			callback.startPos = (*(CVector3*)&start.getOrigin());
			newPos = (*(CVector3*)&start.getOrigin());
			if (addPos.y > 0.0f) {
				//XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŏ�Ɉړ����Ă��Ă����𒲂ׂ�B
				newPos.y -= addPos.y * 0.1f;
			}
			else {
				//�������Ă���ꍇ�͂��̂܂܉��𒲂ׂ�B
				newPos.y += addPos.y;
			}
			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			PhysicsWorld().ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);

			if (callback.isHit) {
				//���������B
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
	void CCharacterController::RemoveRigidBoby()
	{
		PhysicsWorld().RemoveRigidBody(&rigidBody);
	}
}
