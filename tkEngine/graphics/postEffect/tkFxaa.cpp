/*!
 *@brief	FXAA���g�p�����A���`�G�C���A�X
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CFxaa::CFxaa() :
		m_effect(nullptr),
		m_isEnable(false)
	{
	}
	CFxaa::~CFxaa()
	{
	}
	void CFxaa::Init(const SGraphicsConfig& config)
	{
		/*if(config.isEnable){
			m_isEnable = config.isEnable;
			m_effect = EffectManager().LoadEffect("Assets/presetShader/fxaa.fx");
		}*/
	}
	void CFxaa::Render(CRenderContext& renderContext, CPostEffect* postEffect)
	{
		/*if(m_isEnable){
			//�A���`�L���B
			m_effect->SetTechnique(renderContext, "FXAA");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->CommitChanges(renderContext);
			//�����_�����O�^�[�Q�b�g��؂�ւ��B
			Engine().ToggleMainRenderTarget();
			renderContext.SetRenderTarget(0, Engine().GetMainRenderTarget());
			postEffect->RenderFullScreen(renderContext);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
			
		}*/
	}
}