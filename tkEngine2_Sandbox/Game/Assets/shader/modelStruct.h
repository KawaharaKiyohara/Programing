/*!
 * @brief	���f���֌W�̍\���̃w�b�_�B
 */
 
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float4 Tangent  : TANGENT;
    float2 TexCoord : TEXCOORD0;
    float4 Color    : COLOR;
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord	: TEXCOORD0;
    uint4  Indices  : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position : SV_POSITION;
	float3 Normal	: NORMAL;
	float2 TexCoord : TEXCOORD0;
	float3 Pos		: TEXCOORD1;		//���[���h���W�n�ł̒��_���W�B
};
