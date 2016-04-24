#pragma once

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"


class CWall : public IGameObject {
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	virtual void OnDestroy();
	void SetCamera(CCamera* cam)
	{
		m_camera = cam;
	}
	/*!
	 *@brief	�\�z�����B
	 *@param[in]	size	���̃T�C�Y�B
	 *@param[in]	pos		���̍��W�B
	 */
	void Build(const CVector3& size, const CVector3& pos);
private:
	CCamera*		m_camera;
	CLight			m_light;
	CBoxShape		m_box;
	CShadowModel	m_shadowModel;	//�e���f���B
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody;	//���́B
	btDefaultMotionState* m_myMotionState;
};