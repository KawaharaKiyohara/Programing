/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"


/*!
 *@brief	�e���v�Z�B
 */
int CalcShadow( float3 worldPos )
{
	int shadow = 0;
	//������ƓK���B
	if(isShadowReceiver){
		//�e�𗎂Ƃ��B
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv���W�ɕϊ��B
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float2 shadow_val = 1.0f;
			if(shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f){
				if(i == 0){
					shadow_val = shadowMap_0.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 1){
					shadow_val = shadowMap_1.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 2){
					shadow_val = shadowMap_2.Sample(Sampler, shadowMapUV ).r;
				}
				if( depth > shadow_val.r + 0.006f ){
					shadow = 1;
				}
				break;
			}
		}
	}
	return shadow;
}
/*!
 *@brief	�@�����v�Z�B
 */
float3 CalcNormal( float3 normal, float3 biNormal, float3 tangent, float2 uv )
{
	if(hasNormalMap){
		//�@���}�b�v������B
		float3 binSpaceNormal = normalMap.Sample(Sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z; 
	}
	return normal;
}
/*!
 *@brief	�X�L���s����v�Z�B
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�̃R�A�v���O�����B
-------------------------------------------------------------------------------------- */
PSInput VSMainCore( VSInputNmTxVcTangent In, float4x4 worldMat )
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(worldMat, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(worldMat, In.Normal));
	psInput.Tangent = normalize(mul(worldMat, In.Tangent));
    return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	return VSMainCore(In, mWorld);
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[(�C���X�^���V���O�`��p)�B
-------------------------------------------------------------------------------------- */
PSInput VSMainInstancing( VSInputNmTxVcTangent In, uint instanceID : SV_InstanceID )
{
	return VSMainCore(In, instanceMatrix[instanceID]);
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	//�X�L���s����v�Z�B
	float4x4 skinning = CalcSkinMatrix(In);
	//���[���h���W�A�@���A�ڃx�N�g�����v�Z�B
	float4 pos = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}


/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L���Ȃ����f���p
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
PSInput_RenderToDepth VSMain_RenderDepth(VSInputNmTxVcTangent In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L���Ȃ��C���X�^���V���O���f���p
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */

PSInput_RenderToDepth VSMainInstancing_RenderDepth(
	VSInputNmTxVcTangent In, 
	uint instanceID : SV_InstanceID
)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(instanceMatrix[instanceID], In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L�����胂�f���p�B
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
PSInput_RenderToDepth VSMainSkin_RenderDepth(VSInputNmTxWeights In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	//�X�L���s����v�Z�B
	float4x4 skinning = CalcSkinMatrix(In);
	//���[���h���W�A�@���A�ڃx�N�g�����v�Z�B
	float4 pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
	
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
#if 0
	//�A���x�h�B
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	float4 color = albedo * float4(ambientLight, 1.0f);
	int shadow = CalcShadow(In.Pos);
	if(shadow != 0){
		color.xyz *= 0.5f;
	}
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - In.Pos);
	//�]�x�N�g�����v�Z����B
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//�@�����v�Z�B
	float3 normal = normalize(In.Normal);
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if(toEyeLen > 0.001f){
		toEyeDir = toEye / toEyeLen;
	}
	
	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//�|�C���g���C�g���v�Z�B
	color.xyz += CalcPointLight(
		albedo,
		In.Pos, 
		In.posInProj, 
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		1.0f,
		0.0f
	);
	
	return color;
#else
	float3 lig = 0.0f;
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - In.Pos);
	//�]�x�N�g�����v�Z����B
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//�A���x�h�B
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//�@�����v�Z�B
	float3 normal = CalcNormal( In.Normal, biNormal, In.Tangent, In.TexCoord);
		
	float specPow = 0.0f;
	float roughness = 1.0f;
	if(hasSpecularMap){
		float4 t = specularMap.Sample(Sampler, In.TexCoord);
		specPow = t.x;
		roughness = 1.0f - t.w;
		roughness *= 0.8f;	//@todo �}�e���A���p�����[�^�ɂ��ׂ����ȁB
	}
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if(toEyeLen > 0.001f){
		toEyeDir = toEye / toEyeLen;
	}

	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//�e���v�Z�B
	int shadow = CalcShadow(In.Pos);	
	//�f�B���N�V�������C�g
	float3 finalColor = 0.0f;
	if(shadow == 0){
		//�e�������Ă���ꍇ�̓f�B���N�V�������C�g�̓J�b�g����B
		finalColor = CalcDirectionLight(
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
	}
	
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
	finalColor += CalcAmbientLight(
		albedo,
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		roughness,
		specPow
	);
	
	// brightness
	float brightness = 1.0f;
    finalColor *= brightness;
/*
    // exposure
    float exposure = 1.0f;
    finalColor *= pow( 2.0, exposure );
  */  
    float gamma = 2.2f;
    finalColor = max( 0.0f, pow( finalColor, 1.0 / gamma ) );
    if(isnan(finalColor.x) || isnan(finalColor.y) || isnan(finalColor.z)){
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
    return float4(finalColor, 1.0f); 
#endif
}


/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p�����s�N�Z���V�F�[�_�[�B
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
float4 PSMain_RenderDepth( PSInput_RenderToDepth In ) : SV_Target0
{
	return In.posInProj.z / In.posInProj.w;
}
