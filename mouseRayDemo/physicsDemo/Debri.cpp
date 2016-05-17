#include "stdafx.h"
#include "Debri.h"
#include "bulletPhysics.h"

void CDebri::Start()
{
	m_light.SetDiffuseLightColor(0, CVector4(1.5f, 1.5f, 1.5f, 1.0f));
	m_light.SetDiffuseLightDirection(0, CVector3(0.0f, -1.0f, 0.0f));
	//m_light.SetAmbinetLight(CVector3(1.0f, 1.0f, 1.0f));
	m_life = 0.0f;
}
void CDebri::Update()
{
	//�����G���W���Ōv�Z���ꂽ���̂̈ʒu�Ɖ�]�𔽉f������B
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	CVector3 pos(rPos.x(), rPos.y(), rPos.z());
	CQuaternion rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
	m_box.SetPosition(pos);
	m_box.SetRotation(rot);
	m_box.UpdateWorldMatrix();
	m_shadowModel.SetWorldMatrix(m_box.GetWorldMatrix());
	ShadowMap().Entry(&m_shadowModel);
	m_life += 1.0f / 60.0f;
	if (m_life > 240.0f) {
		//240�b�ŏ�����B
		CGameObjectManager::Instance().DeleteGameObject(this);
	}
}
void CDebri::Render(CRenderContext& renderContext)
{
	m_box.RenderLight(
		renderContext,
		m_camera->GetViewProjectionMatrix(),
		m_light,
		true,
		false
		);
}
void CDebri::OnDestroy()
{
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	delete m_myMotionState;
	delete m_collisionShape;
	delete m_rigidBody;
}
/*!
*@brief	�\�z�����B
*@param[in]	size	���̃T�C�Y�B
*@param[in]	pos		���̍��W�B
*/
void CDebri::Build(const CVector3& size, const CVector3& pos)
{
	m_box.Create(size, 0xffffffff, true);
	m_box.SetPosition(pos);
	m_box.UpdateWorldMatrix();
	m_shadowModel.Create(m_box.GetPrimitive());

	//���̈����ɓn���̂̓{�b�N�Xhalfsize�Ȃ̂ŁA0.5�{����B
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(1);
	//���[���h�ɒǉ��B
	g_bulletPhysics.AddRigidBody(m_rigidBody);

}
