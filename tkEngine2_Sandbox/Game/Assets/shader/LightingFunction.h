/*!
 * @brief	���C�g�v�Z�֌W�B
 */


#define TILE_WIDTH	16		//�^�C���̕��B

float3 CalcSpecular(float3 lightDir, float4 lightColor, float3 toEyeReflection, float specPow)
{
	return lightColor.xyz * pow(max(0.0f, dot(-lightDir,toEyeReflection)), 2 ) * lightColor.w * specPow;
}
/*!
 * @brief	�f�B���N�V�������C�g�̉e�����v�Z�B
 *@param[in]	posInWorld		���[���h��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 *@param[in]	specPow			�X�y�L�������x�B
 */
float3 CalcDirectionLight(float3 posInWorld, float3 normal, float3 toEyeReflection, float specPow)
{
	float3 spec = 0.0f;
	//�g�U���ˌ����v�Z����B
	float3 lig = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		float3 lightDir = directionLight[i].direction;
		lig += max( 0.0f, dot( normal, -lightDir ) ) * directionLight[i].color;
//		lig += directionLight[i].color * pow(max(0.0f, dot(-lightDir,toEyeReflection)), 2 ) * directionLight[i].color.w * specPow;	//�X�y�L�������x�B
		lig += CalcSpecular(lightDir, directionLight[i].color, toEyeReflection, specPow);
	}
	
	return lig;
}
/*!
 * @brief	�|�C���g���C�g���v�Z�B
 *@param[in]	posInWorld		���[���h���W�n�ł̍��W�B
 *@param[in]	posInProj		�ˉe��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	tangent			�ڃx�N�g���B
 *@param[in]	biNormal		�]�x�N�g���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 */
float3 CalcPointLight(
	float3 posInWorld, 
	float4 posInProj, 
	float3 normal,
	float3 tangent,
	float3 biNormal,
	float3 toEye,
	float3 toEyeReflection, 
	float specPow
)
{
	
	//�X�N���[���̍����(0,0)�A�E����(1,1)�Ƃ�����W�n�ɕϊ�����B
	float2 screenPos = (posInProj.xy / posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
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
		float3 lightDir = posInWorld - light.position;
		float len = length(lightDir);
		lightDir = normalize(lightDir);	//���K���B
//		float3 pointLightColor = BRDF(-lightDir, toEye, normal, tangent, biNormal, light.color.xyz);
		float3 pointLightColor = saturate(-dot(normal, lightDir)) * light.color.xyz;
		pointLightColor += CalcSpecular(lightDir, light.color, toEyeReflection, specPow);
		//�������v�Z����B
		float	litRate = len / light.attn.x;
		float	attn = max(1.0 - litRate * litRate, 0.0);
		pointLightColor *= attn;

		lig += pointLightColor;
	}
	
	return lig;
}