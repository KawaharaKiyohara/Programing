/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#define TILE_WIDTH	16		//�^�C���̕��B

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
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
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
	float4x4 skinning = 0;
	float4 pos = 0.0f;
	
	[unroll]
    for (int i = 0; i < 4; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
    }
	pos.xyz = mul(skinning, In.Position);
	psInput.Normal = mul(skinning, In.Normal);
	pos.w = 1.0f;
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	if(isZPrepass){
		//ZPrepass?
		return In.posInProj.z / In.posInProj.w;
	}
#if 0 //PBR
	float4 diffuseColor = float4(Texture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
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
	float3 toEye = normalize(eyePos - In.Pos);
	biNormal = normalize(cross(In.Normal, tangentNormal));
	float3 color = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		float3 diffuseLightColor = 0.0f;
		float3 lightDir = directionLight[i].direction;
		diffuseLightColor += BRDF(-lightDir, toEye, In.Normal, tangentNormal, biNormal, diffuseColor.xyz);
		diffuseLightColor *= dot( In.Normal, -lightDir );
		color += diffuseLightColor;
	}
	color += diffuseColor * float3(0.1f, 0.1f, 0.1f);
    return float4( color, 1.0f ); 
#else	//not pbr
		//�X�N���[���̍����(0,0)�A�E����(1,1)�Ƃ�����W�n�ɕϊ�����B
	float2 screenPos = (In.posInProj.xy / In.posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
	//�r���[�|�[�g���W�n�ɕϊ�����B
	float2 viewportPos = screenParam.zw * screenPos;
	//�X�N���[�����^�C���ŕ��������Ƃ��̃Z����X���W�����߂�B
	uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
	//�^�C���C���f�b�N�X���v�Z����B
	uint tileIndex = floor( viewportPos.x / TILE_WIDTH ) + floor( viewportPos.y / TILE_WIDTH ) * numCellX;
	
	//���̃s�N�Z�����܂܂��^�C���̃��C�g�C���f�b�N�X���X�g�̊J�n�ʒu���v�Z����B
	uint lightStart = tileIndex * numPointLight;
	//���̃s�N�Z�����܂܂��^�C���̃��C�g�C���f�b�N�X���X�g�̏I���ʒu���v�Z����B
	uint lightEnd = lightStart + numPointLight;
	
	float3 lig = 0.0f;
	for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++){
		uint lightIndex = pointLightListInTile[lightListIndex];
		if(lightIndex == 0xffffffff){
			//���̃^�C���Ɋ܂܂��|�C���g���C�g�͂����Ȃ��B
			break;
		}
		SPointLight light = pointLightList[lightIndex];
		float3 lightDir = In.Pos - light.position;
		float len = length(lightDir);
		lightDir = normalize(lightDir);	//���K���B
		float3 pointLightColor = saturate(-dot(In.Normal, lightDir)) * light.color.xyz;
		//�������v�Z����B
		float	litRate = len / light.attn.x;
		float	attn = max(1.0 - litRate * litRate, 0.0);
		pointLightColor *= attn;
		lig += pointLightColor;
	}
	lig += 0.2f;
	float4 color = float4(Texture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	color.xyz *= lig;
    return color; 
#endif
}

