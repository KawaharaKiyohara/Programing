/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CShadowModel::CShadowModel() :
		m_prim(nullptr),
		m_mWorld(CMatrix::Identity)
	{
	}
	CShadowModel::~CShadowModel()
	{
	}
	void CShadowModel::Create( CPrimitive* prim )
	{
		m_prim = prim;
	}
	void CShadowModel::Render( CRenderContext& renderContext, CEffect* pEffect, const CMatrix& mLVP )
	{
		CMatrix mWVP;
		mWVP.Mul(m_mWorld, mLVP);
		pEffect->BeginPass(renderContext, 0);
		pEffect->SetValue(renderContext, "g_mWVP", &mWVP, sizeof(mWVP));
		pEffect->CommitChanges(renderContext);
		renderContext.SetVertexDeclaration(m_prim->GetVertexDecl());
		renderContext.SetStreamSource(0, m_prim->GetVertexBuffer());
		renderContext.SetIndices(m_prim->GetIndexBuffer());
		renderContext.DrawIndexedPrimitive(m_prim);
		pEffect->EndPass(renderContext);
	}
	CShadowMap::CShadowMap() :
		m_isEnable(false),
		m_pShadowMapEffect(nullptr),
		m_lightPosition(CVector3::Zero),
		m_lightDirection(CVector3::AxisZ)
	{
	}
	CShadowMap::~CShadowMap()
	{
		Release();
	}
	void CShadowMap::Create( u32 w, u32 h )
	{
		Release();
		m_shadowMapRT.Create( w, h, 1, FMT_A8R8G8B8, FMT_D16, MULTISAMPLE_NONE, 0 );
		m_isEnable = true;
		m_pShadowMapEffect = CEngine::EffectManager().LoadEffect( "Assets/presetshader/shadowMap.fx" );
		m_projectionMatrix.MakeProjectionMatrix(
			CMath::DegToRad(45.0f),
			s_cast<f32>(w) / s_cast<f32>(h),
			1.0f,
			100.0f
		);
	}
	void CShadowMap::Release()
	{
		m_shadowMapRT.Release();
	}
	void CShadowMap::Entry( CShadowModel* model )
	{
		m_shadowModels.push_back(model);
	}
	/*!
	* @brief	�X�V�B
	*/
	void CShadowMap::Update()
	{
		if (m_isEnable) {
			//���C�g�r���[�v���W�F�N�V�����s����쐬�B
			CVector3 lightUp;
			f32 t = fabsf(m_lightDirection.Dot(CVector3::AxisX));
			if (fabsf((t - 1.0f)) < 0.00001f) {
				//���C�g�̕������ق�X���ƕ��s�B
				lightUp.Cross(m_lightDirection, CVector3::AxisZ);
			}
			else {
				lightUp.Cross(m_lightDirection, CVector3::AxisX);
			}
			//���C�g����݂��r���[�s����쐬�B
			CVector3 target;
			target.Add(m_lightPosition, m_lightDirection);
			CMatrix lightViewMatrix;
			lightViewMatrix.MakeLookAt(m_lightPosition, target, lightUp);
			m_LVPMatrix.Mul(lightViewMatrix, m_projectionMatrix);
		}

	}
	void CShadowMap::RenderToShadowMap( CRenderContext& renderContext )
	{
		if(m_isEnable){
			CRenderTarget* pRTBackup = renderContext.GetRenderTarget(0);
			renderContext.SetRenderTarget( 0, &m_shadowMapRT );
			renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0xffffffff, 1.0f, 0);
			m_pShadowMapEffect->SetTechnique( renderContext, "RenderShadowMap" );
			m_pShadowMapEffect->Begin(renderContext);
			//���C�g�r���[�v���W�F�N�V�����s������B
			
			for (auto model : m_shadowModels) {
				model->Render( renderContext, m_pShadowMapEffect, m_LVPMatrix);
			}
			m_pShadowMapEffect->End(renderContext);
			renderContext.SetRenderTarget( 0, pRTBackup );
			m_shadowModels.clear();
			
		}
	}
}