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
	SAtmosphericScatteringParam	atomosphereParam;	//��C�����p�����[�^�B
	CVector3				sunPosition = CVector3::Zero;			//���z�̈ʒu�B
	float					sunAngle = 0.0f;
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
	//��C�����p�����[�^�[���擾�B
	const SAtmosphericScatteringParam& GetAtomosphereParam() const
	{
		return atomosphereParam;
	}
	void Render(CRenderContext& renderContext) override;
	
};
