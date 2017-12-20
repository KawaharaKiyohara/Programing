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
 *@return �e��������m�����Ԃ�܂��B0.0�Ȃ�e�������Ȃ��B1.0�Ȃ�e��������B
 */
float CalcShadow( float3 worldPos )
{
	float shadow = 0.0f;
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
				#if 0 
					//�ʏ�
					shadow_val = shadowMap_0.Sample(Sampler, shadowMapUV ).r;
				#else
					//VSM
					shadow_val = vsm.Sample(Sampler, shadowMapUV ).rg;
					float depth_sq = shadow_val.r * shadow_val.r;
			        float variance = max(shadow_val.g - depth_sq, 0.0006f);
					float md = depth - shadow_val.r;
			        float P = variance / ( variance + md * md );
					shadow =  1.0f - pow( P, 50.0f );
					break;
				#endif
				}else if(i == 1){
					shadow_val = shadowMap_1.Sample(Sampler, shadowMapUV ).r;
					if( depth > shadow_val.r + 0.006f ){
						//�e�������Ă���B
						shadow = 1.0f;
					}
				}else if(i == 2){
					shadow_val = shadowMap_2.Sample(Sampler, shadowMapUV ).r;
					if( depth > shadow_val.r + 0.006f ){
						//�e�������Ă���B
						shadow = 1.0f;
					}
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
	if(shadow == 1){
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
	float shadow = CalcShadow(In.Pos);	
	//�f�B���N�V�������C�g
	float3 finalColor = 0.0f;
	if(shadow < 0.99f){ 
		//�e��������\�����Ⴂ�ꍇ�̂݌v�Z����B
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
		) * (1.0f - shadow);
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
	float z = In.posInProj.z / In.posInProj.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z+0.25f*(dx*dx+dy*dy), 0.0f, 1.0f);
}

/*!
 *@brief	�V���G�b�g�`��B
 * GameDemo�̂��߂̃X�y�V�����V�F�[�_�[�B
 */
float4 PSMain_Silhouette( PSInput In ) : SV_Target0
{
	float2 screenPos = In.posInProj.xy / In.posInProj.w;
	screenPos = screenPos * float2( 0.5f, -0.5f ) + 0.5f;
	
#if 1 ////�f�B�U�����O�������B
	//�f�B�U�p�^�[��
	static const int pattern[] = {
	    0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
	    48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
	    12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
	    60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
	    3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
	    51, 19, 59, 27, 49, 17, 57, 25,
	    15, 47,  7, 39, 13, 45,  5, 37,
	    63, 31, 55, 23, 61, 29, 53, 21 
	};
	screenPos.x *= 1.7777f;
	float2 uv = fmod(screenPos * 200.0f, 8.0f);
	float t = 0.0f;
	int x = (int)uv.x;
	int y = (int)uv.y;
	int index = y * 8 + x;
	t = (float)pattern[index] / 64.0f;
	//�f�B�U
	clip(t - 0.5f);
	return float4(t, t, t, 1.0f);

#else
	screenPos.x *= 1.7777f;		//�A�X�y�N�g���������B
	return silhouetteTexture.Sample(Sampler, screenPos * 12.0f) * 4.0f;
#endif
}