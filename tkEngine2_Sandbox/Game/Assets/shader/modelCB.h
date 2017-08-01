/*!
 * @brief	���f���p�̒萔�o�b�t�@�B
 */
/*!
 * @brief	���_�V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4 screenParam;	// �X�N���[���p�����[�^(near, far, screenWidth, screenHeight)
	int isZPrepass;		//Z�v���p�X�H
};

/*!
 * @brief	���C�g�p�̒萔�o�b�t�@�B
 */
cbuffer lightCb : register(b1)
{
	float4 diffuseLightDir;
	float4 diffuseLightColor;
	float4 ambientLight;
	float3 eyeVec;
};

cbuffer MaterialParamCb : register(b2){
	float roughness;	//�e���B
	float metallic ;	//���^���b�N�B
	float anisotropic;	//�ٕ�������
};