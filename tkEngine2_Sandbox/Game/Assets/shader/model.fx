/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"


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
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
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
	
/*	[unroll]
    for (int i = 0; i < 4; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
    }*/
    skinning += boneMatrix[In.Indices[0]] * In.Weights[0];
    skinning += boneMatrix[In.Indices[1]] * In.Weights[1];
    skinning += boneMatrix[In.Indices[2]] * In.Weights[2];
    skinning += boneMatrix[In.Indices[3]] * In.Weights[3];
    
	pos.xyz = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
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
	
	
	float3 lig = 0.0f;
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - In.Pos);
	//�]�x�N�g�����v�Z����B
	float3 biNormal = normalize(cross(In.Normal, In.Tangent));
	//�A���x�h�B
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	float3 normal = In.Normal;
	
	if(hasNormalMap){
		//�@���}�b�v������B
		float3 binSpaceNormal = normalMap.Sample(Sampler, In.TexCoord).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = In.Tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + In.Normal * binSpaceNormal.z; 
	}
	
	float specPow = 0.0f;
	float roughness = 1.0f;
	if(hasSpecularMap){
		float4 t = specularMap.Sample(Sampler, In.TexCoord);
		specPow = t.x;
		roughness = 1.0f - t.w;
	}
	
	float3 toEyeDir = normalize( toEye - In.Pos );
	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//�f�B���N�V�������C�g
	float3 finalColor = CalcDirectionLight(
		albedo,
		In.Pos, 
		normal, 
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		roughness,
		specPow
	);
	
	//�|�C���g���C�g���v�Z�B
	finalColor += CalcPointLight(
		albedo,
		In.Pos, 
		In.posInProj, 
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		roughness,
		specPow
	);
	
	//�A���r�G���g���C�g�B
	finalColor += albedo * ambientLight;
    return float4(finalColor, 1.0f); 
#endif
}

