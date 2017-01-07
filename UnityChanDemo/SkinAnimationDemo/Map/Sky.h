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
	CLight					sunLight;				//���C�g�B
	CSkinModelDataHandle	sunModelData;			//���z�̃��f���f�[�^�B
	CSkinModel				sunModel;				//���z�̃��f���B
	CVector3				sunDir;					//���z�̕����B
	float					deltaTimeMul = 1.0f;	//���^�C���ɏ�Z�����l�B
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
	/*!
	* @brief	���z�̕������擾�B
	* @details
	*  �f���̒��S���猩���ꍇ�̑��z�̕����ł��B
	*/
	const CVector3& GetSunDir() const
	{
		return sunDir;
	}
	/*!
	* @brief	���^�C���ɏ�Z�����l��ݒ�B
	*@param[in]	mul		�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�܂��B
	*/
	void SetFrameDeltaTimeMul(float mul)
	{
		deltaTimeMul = mul;
	}
	
};
