/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"


/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = mul(mWorld, In.Normal);
	
    return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = mul(mWorld, In.Normal);
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 color = float4(Texture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//�]�x�N�g���Ɛڃx�N�g�������߂�B<-�����̏ꍇ�Ŏ��O�v�Z�ς݂̃f�[�^�Ƃ��āA���_�f�[�^�ɖ��ߍ��܂�Ă��邩��v�Z���Ȃ��Ă悢�B
//	float3 lig = max(0.0f, -dot( In.Normal, diffuseLightDir )) * diffuseLightColor;
	float3 biNormal;
	float3 tangentNormal;
	if(In.Normal.x < 0.001f && In.Normal.z < 0.001f){
		//�@�����قڐ^��
		tangentNormal = normalize(cross(In.Normal, float3( 1.0f, 0.0f, 0.0f)));
	}else{
		tangentNormal = normalize(cross(In.Normal, float3( 0.0f, 1.0f, 0.0f)));
	}
	float3 toEye = normalize(eyeVec - In.Pos);
	biNormal = normalize(cross(In.Normal, tangentNormal));
	color.xyz = BRDF(-diffuseLightDir, toEye, In.Normal, tangentNormal, biNormal, color.xyz);
	color.xyz *= dot( In.Normal, -diffuseLightDir );
    return color; 
}

