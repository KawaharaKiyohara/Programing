#pragma once
#include "tkEngine/shape/tkSphereShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"

class CPlayer : public IGameObject{
public:
	CPlayer()
	{
		m_camera = nullptr;
	}
	virtual void Start() ;
	virtual void PreUpdate();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	void SetCamera(CCamera* cam)
	{
		m_camera = cam;
	}
private:
	CVector3		m_position;
	CSphereShape	m_shape;
	CCamera*		m_camera;
	CLight			m_light;
	float			m_radius;
	CShadowModel	m_shadowModel;	//�e���f���B
	CVector3		m_moveSpeed;	//�ړ����x�B
	
	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
};
