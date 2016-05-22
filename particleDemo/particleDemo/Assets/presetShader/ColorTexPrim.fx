/*!
 *@brief	�J���[�e�N�X�`���v���~�e�B�u�B
 */

float4x4	g_mWVP;		//���[���h�r���[�v���W�F�N�V�����s��B

struct VS_INPUT{
	float4	pos		: POSITION;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4 pos		: POSITION;
	float2	uv		: TEXCOORD0;
};

float g_alpha;			//!<�A���t�@
texture g_texture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_textureSampler = 
sampler_state
{
	Texture = <g_texture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_mWVP);
	Out.uv = In.uv;
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return tex * g_alpha;
}

/*!
 * @brief	���Z�p�e�N�j�b�N�B
 */
technique ColorTexPrimAdd
{
    pass P0
    {          
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMain();
    }
}