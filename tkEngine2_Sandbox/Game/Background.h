#pragma once
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
};

