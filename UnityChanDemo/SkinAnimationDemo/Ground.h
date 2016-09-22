#pragma once

#include "Physics/MeshCollider.h"
#include "Physics/RigidBody.h"

class Ground : public IGameObject {
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CLight			light;				//���C�g�B
	CTexture		normalMap;
	CMatrix*		m_worldMatrix;		//���[���h�s��
	MeshCollider	meshCollider;		//���b�V���R���C�_�[�B
	RigidBody		rigidBody;			//���́B
public:
	Ground()
	{
		
	}
	~Ground()
	{

	}
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
	//�n�ʂƂ̓����蔻��B
	//pos	���C�̎n�_�B
	//ray	���C����
	//bHit	���C�ƒn�ʂ��Փ˂�����1���ݒ肳���B
	//len	���C�̎n�_�����_�܂ł̋����B
	void IsIntersect(const CVector3& pos, const CVector3& ray, int& bHit, float& len);
private:
};
extern Ground* g_ground;