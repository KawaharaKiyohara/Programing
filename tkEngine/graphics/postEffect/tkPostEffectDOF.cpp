/*!
 * @brief	��ʊE�[�x�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffectDOF.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CDof::CDof() :
		m_isEnable(false)
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CDof::~CDof()
	{
	}
	
	void CDof::Release()
	{
		m_depthRT.Release();
	}
	
	void CDof::Create(const SGraphicsConfig& config)
	{
		if (config.dofConfig.isEnable) {
			//DOF���L���B
			m_isEnable = config.dofConfig.isEnable;
			//DOF�̓��C�������_�����O�^�[�Q�b�g�ɏ������ނƂ���MRT���g�p���ď������ނ̂ŁA
			//���C���Ɠ������ƍ����B
			int w = Engine().GetFrameBufferWidth();
			int h = Engine().GetFrameBufferHeight();
			//32bit�Ń��b�`�ɂ���Ă݂�B
			m_depthRT.Create(w, h, 1, FMT_R32F, FMT_INVALID, MULTISAMPLE_NONE, 0);
			m_blurForward.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.SetBlurPower(1.0f);
			m_blurForward.SetBlurPower(10.0f);
			m_effect = EffectManager().LoadEffect("Assets/presetShader/dof.fx");
		}
	}
	
	void CDof::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		CPIXPerfTag tag(renderContext, L"CDof::Render");
		if (m_isEnable) {
			//�{�P�p�̃p�����[�^��������Ōv�Z����B
			//��ʑ̂Ƃ̋�������A������Ōv�Z����B
			//�Ƃ肠�����K���B
			static float pint = 3000.0f;		//��ʑ̂܂ł̋���(�P�ʂ�mm)
			static float focalLength = 28.0f;	//�œ_����(�P�ʂ�mm)
			static float f = 5.6f;				//�i��l
			static float CoC = 0.033f;			//���e�����~(�P�ʂ�mm)
			float forwardDof = (CoC * f * pint * pint) / (focalLength * focalLength + CoC * f * pint);
			float backDof = (CoC * f * pint * pint) / (focalLength * focalLength - CoC * f * pint);
			//��O�{�P�A���{�P�A�s���g��m�P�ʂɕύX����GPU�ɑ���
			
			
			float dofParam[] = {
				forwardDof / 1000.0f,
				backDof / 1000.0f,
				pint / 1000.0f
			};

			static float depth = 5.0f;
			float t = depth - dofParam[2];
			float forwardRate = max(0.0f, -dofParam[0] - t);
			float backRate = max(0.0f, t - dofParam[1]);
			t = max(forwardRate, backRate);
			t = min(t / (dofParam[2] - dofParam[0]), 1.0f);

			//�{�P�摜���쐬����B
			//���{�P
			m_blurBack.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.Draw(renderContext);
			//��O�{�P
			m_blurForward.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
			m_blurForward.Draw(renderContext);
			
			//�����B
			m_effect->SetTechnique(renderContext, "Dof");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetValue(renderContext, "g_dofParam", dofParam, sizeof(dofParam));
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->SetTexture(renderContext, "g_depthTexture", m_depthRT.GetTexture());
			m_effect->SetTexture(renderContext, "g_blurBack", m_blurBack.GetTexture());
			m_effect->SetTexture(renderContext, "g_blurForward", m_blurForward.GetTexture());

			float texSize[] = {
				s_cast<float>(m_depthRT.GetWidth()),
				s_cast<float>(m_depthRT.GetHeight()),
			};
			m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
			m_effect->CommitChanges(renderContext);
			postEffect->RenderFullScreen(renderContext);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);

			
		}
	}
}
