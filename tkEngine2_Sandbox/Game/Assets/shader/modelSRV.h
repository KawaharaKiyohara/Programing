/*!
 * @brief	���f����SRV�B
 */

/*!
 * @brief	�f�B���N�V�������C�g�B
 */
struct SDirectionLight{
	float3	direction;		//!<���C�g�̕����B
	float3	color;			//!<���C�g�̃J���[�B
};
StructuredBuffer<SDirectionLight> directionLight : register(t100);

Texture2D<float4> Texture : register(t0);

sampler Sampler : register(s0);

