#pragma once

class Sky : public IGameObject {
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CLight			light;				//���C�g�B
	CTexture		normalMap;
public:
	Sky();
	
	~Sky()
	{

	}
	void Start() override
	{

	}
	void Update() override;
	
	void Render(CRenderContext& renderContext) override;
	
};
