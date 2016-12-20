/*!
 *@brief	�J�����̃R���W�����\���o�[�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

namespace tkEngine{
	CCameraCollisionSolver::CCameraCollisionSolver()
	{
	}
	CCameraCollisionSolver::~CCameraCollisionSolver()
	{
	}
	void CCameraCollisionSolver::Init(float radius)
	{
		m_radius = radius;
		m_collider.Create(radius);
	}
	void CCameraCollisionSolver::Execute( CCamera& camera )
	{
		CVector3 target = camera.GetTarget();
		CVector3 position = camera.GetPosition();
		CVector3 vWk;
		vWk.Subtract(target, position);
		if (vWk.LengthSq() < FLT_EPSILON) {
			//���_�ƒ����_���قړ������W�ɂ���B
			return;
		}
		//���C���쐬����B
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();
		btStart.setOrigin(btVector3(target.x, target.y, target.z));
		btEnd.setOrigin(btVector3(position.x, position.y, position.z));
		btCollisionWorld::ClosestConvexResultCallback callback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
		if (callback.hasHit()) {
			CVector3 vOffset = vWk;
			vOffset.Normalize();
			vOffset.Scale(m_radius);
			//���_���Փ˓_�ɂ��Ă݂�e�X�g�B
			position.Set(callback.m_hitPointWorld);
			position.Add(vOffset);
			camera.SetPosition(position);
		}
	}
}
