#pragma once

class Sky : public IGameObject {
	enum InitStep {
		InitStep_Load,
		InitStep_Wait,
	};
	CSkinModelDataHandle	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel				skinModel;			//�X�L�����f���B
	CAnimation				animation;			//�A�j���[�V�����B
	CLight					light;				//���C�g�B
	CTexture				normalMap;
	Player*					player;				//�v���C���B
	InitStep				initStep = InitStep_Load;
public:
	Sky();
	
	~Sky()
	{

	}
	bool Start() override;
	void SetPlayer(Player* player)
	{
		this->player = player;
	}
	void Update() override;
	
	void Render(CRenderContext& renderContext) override;
	
};
