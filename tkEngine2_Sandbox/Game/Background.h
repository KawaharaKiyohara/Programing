#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Background : public IGameObject
{
public:
	Background();
	~Background();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
private:
	CSkinModelData		m_skinModelData;	//!<�X�L�����f���f�[�^�B
	CSkinModel			m_skinModel;		//!<�X�L�����f���B
	CShaderResourceView	m_normalMapSRV;		//!<�@���}�b�v��SRV�B
	CMeshCollider		m_meshCollider;		//!<���b�V���R���C�_�[�B
	CRigidBody			m_rigidBody;		//!<���́B
};

