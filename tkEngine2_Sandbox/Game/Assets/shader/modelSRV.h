/*!
 * @brief	���f����SRV�B
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�B
StructuredBuffer<uint> pointLightListInTile : register(t102);


Texture2D<float4> Texture : register(t0);

sampler Sampler : register(s0);

