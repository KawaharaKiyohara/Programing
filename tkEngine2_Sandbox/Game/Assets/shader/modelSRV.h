/*!
 * @brief	���f����SRV�B
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�B
StructuredBuffer<uint> pointLightListInTile : register(t102);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t103);



Texture2D<float4> albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B
Texture2D<float4> normalMap : register(t1);		//�@���}�b�v�B
Texture2D<float4> specularMap : register(t2);	//�X�y�L�����}�b�v�B
sampler Sampler : register(s0);

