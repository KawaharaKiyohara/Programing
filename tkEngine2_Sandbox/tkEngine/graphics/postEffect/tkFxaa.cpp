/*!
 *@brief	FXAA
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkFxaa.h"

namespace tkEngine{
	CFxaa::CFxaa()
	{
	}
	CFxaa::~CFxaa()
	{
		Release();
	}
	void CFxaa::Release()
	{
		m_samplerState.Release();
	}
	void CFxaa::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.aaConfig.isEnable;
		m_vsShader.Load("Assets/shader/fxaa.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("Assets/shader/fxaa.fx", "PSMain", CShader::EnType::PS);
		//サンプラを作成。
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);
	}
	void CFxaa::Render(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_AntiAlias");
		//@todo レンダリングステートをFXAA用に設定するようにする。
		
		//現在のレンダリングターゲットを取得。
		CRenderTarget& rt = Engine().GetGraphicsEngine().GetMainRenderTarget();
		//レンダリングターゲットを切り替える。
		Engine().GetGraphicsEngine().ToggleMainRenderTarget();
		CRenderTarget* renderTargets[] = {
			&Engine().GetGraphicsEngine().GetMainRenderTarget()
		};
		rc.PSSetSampler(0, m_samplerState);
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		//入力レイアウトを設定。
		rc.IASetInputLayout(m_vsShader.GetInputLayout());

		GraphicsEngine().GetPostEffect().DrawFullScreenQuad(rc);
		
		EndGPUEvent();
	}
}
