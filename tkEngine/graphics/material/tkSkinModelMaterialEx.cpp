/*!
 *@brief	�X�L�����f���}�e���A���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/material/tkSkinModelMaterialEx.h"
#include "tkEngine/graphics/tkEffect.h"


namespace tkEngine{
	void CSkinModelMaterialEx::Init(CEffect* effect, const char* tecName)
	{
		m_pEffect = effect;
		InitShaderHandles(tecName);
	}
	void CSkinModelMaterialEx::InitShaderHandles(const char* tecName)
	{
		if (m_pEffect) {
			ID3DXEffect* effectDx = m_pEffect->GetD3DXEffect();
			//�e�N�X�`���̃V�F�[�_�[�n���h���B
			m_hTexShaderHandle[enTextureShaderHandle_DiffuseMap] = effectDx->GetParameterByName(NULL, "g_diffuseTexture");
			m_hTexShaderHandle[enTextureShaderHandle_NormalMap] = effectDx->GetParameterByName(NULL, "g_normalTexture");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_0] = effectDx->GetParameterByName(NULL, "g_shadowMap_0");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_1] = effectDx->GetParameterByName(NULL, "g_shadowMap_1");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_2] = effectDx->GetParameterByName(NULL, "g_shadowMap_2");
			m_hTexShaderHandle[enTextureShaderHandle_SpecularMap] = effectDx->GetParameterByName(NULL, "g_speculerMap");
			//�s��̃V�F�[�_�[�n���h���B
			m_hMatrixShaderHandle[enMatrixShaderHandle_LastFrameViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProjLastFrame");
			m_hMatrixShaderHandle[enMatrixShaderHandle_ViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProj");
			m_hMatrixShaderHandle[enMatrixShaderHandle_LVP] = effectDx->GetParameterByName(NULL, "g_mLVP");
			m_hMatrixShaderHandle[enMatrixShaderHandle_ViewMatrixRotInv] = effectDx->GetParameterByName(NULL, "g_viewMatrixRotInv");
			m_hMatrixShaderHandle[enMatrixShaderHandle_WorldMatrix] = effectDx->GetParameterByName(NULL, "g_worldMatrix");
			m_hMatrixShaderHandle[enMatrixShaderHandle_RotationMatrix] = effectDx->GetParameterByName(NULL, "g_rotationMatrix");
			//���������x�N�g���̃V�F�[�_�[�n���h���B
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraPos] = effectDx->GetParameterByName(NULL, "g_cameraPos");
			m_hFVectorShaderHandle[enFVectorShaderHandle_FarNear] = effectDx->GetParameterByName(NULL, "g_farNear");
			m_hFVectorShaderHandle[enFVectorShaderHandle_FogParam] = effectDx->GetParameterByName(NULL, "g_fogParam");
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraDir] = effectDx->GetParameterByName(NULL, "g_cameraDir");
			//�����x�N�g���̃V�F�[�_�[�n���h���B
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags] = effectDx->GetParameterByName(NULL, "g_flags");
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags2] = effectDx->GetParameterByName(NULL, "g_flags2");
			//�����̃V�F�[�_�[�n���h���B
			m_hIntShaderHandle[enIntShaderHandle_NumBone] = effectDx->GetParameterByName(NULL, "g_numBone");
			m_hIntShaderHandle[enIntshaderHandle_CurNumBone] = effectDx->GetParameterByName(NULL, "CurNumBones");
			//��C�����̃V�F�[�_�[�n���h���B
			m_hAtmosShaderHandle = effectDx->GetParameterByName(NULL, "g_atmosParam");
			//���C�g�̃V�F�[�_�[�n���h���B
			m_hLightShaderHandle = effectDx->GetParameterByName(NULL, "g_light");
			//�V���h�E���V�[�o�[�p�����[�^�n���h���B
			m_hShadowRecieverParamShaderHandle = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");

			m_hShaderHandle[enShaderHandleWorldMatrixArray] = effectDx->GetParameterByName(NULL, "g_mWorldMatrixArray");
			m_hShaderHandle[enShaderHandleShadowRecieverParam] = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");
			m_hTec = effectDx->GetTechniqueByName(tecName);
		}
	}
	void CSkinModelMaterialEx::BeginDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(!m_isBeginDraw, "forgot call EndDraw!!!!");
		m_isBeginDraw = true;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->SetTechnique(m_hTec);
			effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			effect->BeginPass(0);
		}
	}
	void CSkinModelMaterialEx::SendMaterialParamToGPU()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			for (auto& node : m_materialNodes) {
				node->SendMaterialParamToGPU();
			}

			effect->CommitChanges();
		}
	}
	void CSkinModelMaterialEx::EndDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
		m_isBeginDraw = false;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->EndPass();
			effect->End();
		}
	}
}