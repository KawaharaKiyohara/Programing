#pragma once

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"

class CGround : public IGameObject {
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	virtual void OnDestroy();
	void SetCamera(CCamera* cam)
	{
		m_camera = cam;
	}
	void OnPlayerOverlapDebriCreator(const btCollisionObject* collisionObject);
private:
	CCamera*		m_camera;
	CLight			m_light;
	CBoxShape		m_box;
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape;			//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody;			//���́B
	btDefaultMotionState* m_myMotionState;
	btGhostObject*		m_debriCreateSwitch;		//�f�u���쐬�X�C�b�`�B
};