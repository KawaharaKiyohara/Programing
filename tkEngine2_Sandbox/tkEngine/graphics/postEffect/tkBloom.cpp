/*!
 * @brief	�u���[��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CBloom::CBloom()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CBloom::~CBloom()
	{
		Release();
	}
	/*!
	 * @brief	�J��
	 */
	void CBloom::Release()
	{
		if (m_alphaBlendAdd) {
			m_alphaBlendAdd->Release();
		}
	}
	/*!
	 * @brief	�������B
	 */
	void CBloom::Init( const SGraphicsConfig& config )
	{
		Release();
		
		if(!config.bloomConfig.isEnable){
			return ;
		}
		m_vsShader.Load("Assets/shader/bloom.fx", "VSMain", CShader::EnType::VS);
		m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", CShader::EnType::PS);
		m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", CShader::EnType::VS);
		m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", CShader::EnType::VS);
		m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", CShader::EnType::PS);
		m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", CShader::EnType::PS);
		m_copyVS.Load("Assets/shader/copy.fx", "VSMain", CShader::EnType::VS);
		m_copyPS.Load("Assets/shader/copy.fx", "PSMain", CShader::EnType::PS);
		int w = Engine().GetGraphicsEngine().GetFrameBufferWidth();
		int h = Engine().GetGraphicsEngine().GetFrameBufferHeight();

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
		DXGI_SAMPLE_DESC multiSampleDesc;
		ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		if (!m_luminanceRT.Create(
			w,
			h,
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		)) {
			TK_WARNING("Failed CBloom::Init");
			return;
		}

		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬����B
		for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++) {
			int shift = i + 1;
			int baseIndex = i * 2;
			//���u���[�p�B
			if (!m_downSamplingRT[baseIndex].Create(
				w >> shift,
				h >> (shift - 1),
				1,
				1,
				DXGI_FORMAT_R16G16B16A16_FLOAT,
				DXGI_FORMAT_UNKNOWN,
				multiSampleDesc
			)) {
				TK_WARNING("Failed CBloom::Init");
				return ;
			}
			//�c�u���[�p�B
			if (!m_downSamplingRT[baseIndex + 1].Create(
				w >> shift,
				h >> shift,
				1,
				1,
				DXGI_FORMAT_R16G16B16A16_FLOAT,
				DXGI_FORMAT_UNKNOWN,
				multiSampleDesc
			)) {
				TK_WARNING("Failed CBloom::Init");
				return;
			}
		}
		//�ڂ��������p�B
		if (!m_combineRT.Create(
			w >> 2,
			h >> 2,
			1, 1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		)) {
			TK_WARNING("Failed CBloom::Init");
			return;
		}
		m_cbBlur.Create(&m_blurParam, sizeof(m_blurParam));
		m_isEnable = config.bloomConfig.isEnable;

		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		m_samplerState.Create(desc);
		//@todo ��ł܂Ƃ߂�B
		{
			ID3D11Device* pd3d = Engine().GetGraphicsEngine().GetD3DDevice();
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			pd3d->CreateBlendState(&blendDesc, &m_alphaBlendAdd);

			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			pd3d->CreateBlendState(&blendDesc, &m_alphaBlendTrans);
		}
	}
	void CBloom::UpdateWeight(float dispersion)
	{
		float total = 0;
		for (int i = 0; i<NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
			total += 2.0f*m_blurParam.weights[i];

		}
		// �K�i��
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] /= total;
		}
	}
	void CBloom::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		UpdateWeight(25.0f);
		rc.SetRenderStep(enRenderStep_Bloom);
		CGraphicsEngine& ge = Engine().GetGraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Bloom");
		rc.PSSetSampler(0, m_samplerState);
		float clearColor[] = {
			0.0f, 0.0f, 0.0f, 0.0f
		};
		//�P�x���o�B
		{
			ge.BeginGPUEvent(L"enRenderStep_Bloom::Luminance");
			CRenderTarget* rts[] = {
				&m_luminanceRT
			};
			
			rc.OMSetRenderTargets(1, rts);
			rc.ClearRenderTargetView(0, clearColor);
			rc.PSSetShaderResource(0, ge.GetMainRenderTarget().GetRenderTargetSRV());
			rc.VSSetShader(m_vsShader);
			//���̓��C�A�E�g��ݒ�B
			rc.IASetInputLayout(m_vsShader.GetInputLayout());
			rc.PSSetShader(m_psLuminance);
			postEffect->DrawFullScreenQuad(rc);
			ge.EndGPUEvent();
		}
		//�P�x���ڂ����B
		{
			ge.BeginGPUEvent(L"enRenderStep_Bloom::Blur");
			CRenderTarget* prevRt = &m_luminanceRT;

			int rtIndex = 0;
			for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++) {
				//XBlur
				{
					CRenderTarget* rts[] = {
						&m_downSamplingRT[rtIndex]
					};
					m_blurParam.offset.x = 16.0f / prevRt->GetWidth();
					m_blurParam.offset.y = 0.0f;
					rc.UpdateSubresource(m_cbBlur, &m_blurParam);
					rc.OMSetRenderTargets(1, rts);
					rc.ClearRenderTargetView(0, clearColor);
					rc.VSSetShaderResource(0, prevRt->GetRenderTargetSRV());
					rc.PSSetShaderResource(0, prevRt->GetRenderTargetSRV());
					rc.PSSetConstantBuffer(0, m_cbBlur);
					rc.RSSetViewport(0.0f, 0.0f, m_downSamplingRT[rtIndex].GetWidth(), m_downSamplingRT[rtIndex].GetHeight());
					rc.VSSetShader(m_vsXBlur);
					rc.PSSetShader(m_psBlur);
					postEffect->DrawFullScreenQuad(rc);
				}

				prevRt = &m_downSamplingRT[rtIndex];
				rtIndex++;
				//YBlur
				{
					CRenderTarget* rts[] = {
						&m_downSamplingRT[rtIndex]
					};
					m_blurParam.offset.x = 0.0f;
					m_blurParam.offset.y = 16.0f / prevRt->GetWidth();
					rc.UpdateSubresource(m_cbBlur, &m_blurParam);
					rc.PSSetConstantBuffer(0, m_cbBlur);
					rc.OMSetRenderTargets(1, rts);
					rc.ClearRenderTargetView(0, clearColor);
					rc.VSSetShaderResource(0, prevRt->GetRenderTargetSRV());
					rc.PSSetShaderResource(0, prevRt->GetRenderTargetSRV());
					rc.RSSetViewport(0.0f, 0.0f, m_downSamplingRT[rtIndex].GetWidth(), m_downSamplingRT[rtIndex].GetHeight());
					rc.VSSetShader(m_vsYBlur);
					rc.PSSetShader(m_psBlur);
					postEffect->DrawFullScreenQuad(rc);
				}
				prevRt = &m_downSamplingRT[rtIndex];
				rtIndex++;
			}
			ge.EndGPUEvent();
		}
		//�{�P�摜�̍쐬�B
		{
			//@todo ���u�����f�B���O�𖳌��ɂ���B
			CRenderTarget* rts[] = {
				&m_combineRT
			};
			rc.RSSetViewport(0.0f, 0.0f, m_combineRT.GetWidth(), m_combineRT.GetHeight());
			rc.OMSetRenderTargets(1, rts);
			rc.ClearRenderTargetView(0, clearColor);

			rc.PSSetShaderResource(0, m_downSamplingRT[3].GetRenderTargetSRV());
			rc.PSSetShaderResource(1, m_downSamplingRT[5].GetRenderTargetSRV());
			rc.PSSetShaderResource(2, m_downSamplingRT[7].GetRenderTargetSRV());
			rc.PSSetShaderResource(3, m_downSamplingRT[9].GetRenderTargetSRV());
			rc.VSSetShader(m_vsShader);
			rc.PSSetShader(m_psCombine);
			postEffect->DrawFullScreenQuad(rc);
		}
		//�ŏI�����B
		{
			CRenderTarget* rts[] = {
				&ge.GetMainRenderTarget()
			};
			rc.RSSetViewport(0.0f, 0.0f, ge.GetFrameBufferWidth(), ge.GetFrameBufferHeight());
			rc.OMSetRenderTargets(1, rts);
			//@todo �A���t�@�u�����f�B���O�����Z�����ɂ���B
			{
				//�K���B
				ge.GetD3DDeviceContext()->OMSetBlendState(m_alphaBlendAdd, 0, 0xFFFFFFFF);
			}
			//@todo �萔�o�b�t�@��ݒ肷��B
			rc.VSSetShader(m_copyVS);
			rc.PSSetShader(m_copyPS);
			rc.PSSetShaderResource(0, m_combineRT.GetRenderTargetSRV());
			postEffect->DrawFullScreenQuad(rc);
			//@todo �A���t�@�u�����f�B���O�����Ƃɖ߂��B
			{
				//�K���B
				ge.GetD3DDeviceContext()->OMSetBlendState(m_alphaBlendTrans, 0, 0xFFFFFFFF);
			}
		}

		Engine().GetGraphicsEngine().EndGPUEvent();
	}
}