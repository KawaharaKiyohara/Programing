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
	CSkinModelData		m_skinModelData2;
	CSkinModel			m_skinModel2;
	CShaderResourceView	m_normalMapSRV;		//!<�@���}�b�v��SRV�B
	CMeshCollider		m_meshCollider;		//!<���b�V���R���C�_�[�B
	CRigidBody			m_rigidBody;		//!<���́B
	CMeshCollider		m_meshCollider2;	//!<���b�V���R���C�_�[�Q�B
	CRigidBody			m_rigidBody2;		//!<���̂Q�B
};

