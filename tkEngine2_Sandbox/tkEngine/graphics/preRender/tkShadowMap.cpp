/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{
	
	CShadowMap::CShadowMap()
	{
	}
	
	CShadowMap::~CShadowMap()
	{
	}
	
	bool CShadowMap::Init(const SShadowRenderConfig& config)
	{
		Release();
		m_isEnable = config.isEnable;
		if (m_isEnable == false) {
			return true;
		}
		if(config.numShadowMap > MAX_SHADOW_MAP){
			TK_WARNING("numShadowMap is invalid");
			m_numShadowMap = MAX_SHADOW_MAP;
		}
		else {
			m_numShadowMap = config.numShadowMap;
		}
		
		int wh[MAX_SHADOW_MAP][2] = {
			{ config.shadowMapWidth, config.shadowMapHeight},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
		};
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		for(int i = 0; i < m_numShadowMap; i++ ){
			m_shadowMapRT[i].Create(
				wh[i][0], 
				wh[i][1], 
				1, 
				DXGI_FORMAT_R16G16_FLOAT,
				DXGI_FORMAT_D24_UNORM_S8_UINT, 
				multiSampleDesc
			);
		}
		return true;
	}
	
	void CShadowMap::Release()
	{
		for (auto& rt : m_shadowMapRT) {
			rt.Release();
		}
	}
	
	void CShadowMap::Entry(IShadowCaster* caster)
	{
		if (!m_isEnable) {
			return;
		}
		m_shadowCaster.push_back(caster);
	}
	
	void CShadowMap::Update()
	{
		if (!m_isEnable) {
			return;
		}
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		CVector3 cameraDir;
		cameraDir.Subtract(MainCamera().GetTarget(), MainCamera().GetPosition());
		if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
			//�قڐ^����ނ��Ă���B
			return;
		}
		cameraDir.y = 0.0f;
		cameraDir.Normalize();
		CVector3 lightViewForward;
		lightViewForward.Subtract(m_lightTarget, m_lightPosition);
		lightViewForward.Normalize();

		CVector3 lightViewUp;
		lightViewUp.Cross(lightViewForward, cameraDir);
		lightViewUp.Normalize();
		CVector3 lgihtViewRight;
		lgihtViewRight.Cross(lightViewUp, lightViewForward);
		lgihtViewRight.Normalize();
		//���C�g�r���[�̓J�����̉���������A�J�����̉�������O�A�J�����̑O���������Ƃ���Ƃ��������ɂȂ��B
		CMatrix lightViewRot;
		//���C�g�r���[�̉���ݒ肷��B
		lightViewRot.m[0][0] = lgihtViewRight.x;
		lightViewRot.m[0][1] = lgihtViewRight.y;
		lightViewRot.m[0][2] = lgihtViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��B
		lightViewRot.m[1][0] = lightViewUp.x;
		lightViewRot.m[1][1] = lightViewUp.y;
		lightViewRot.m[1][2] = lightViewUp.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��B
		lightViewRot.m[2][0] = lightViewForward.x;
		lightViewRot.m[2][1] = lightViewForward.y;
		lightViewRot.m[2][2] = lightViewForward.z;
		lightViewRot.m[2][3] = 0.0f;

		static float shadowAreaTbl[MAX_SHADOW_MAP] = {
			200.0f,
			400.0f,
			800.0f
		};
		//���C�g�̈ʒu�����߂āA�J�����s����m�肳���Ă����B

		const CVector3& cameraPos = MainCamera().GetPosition();
		CVector3 lightPos = cameraPos;
		CVector3 lightOffset = cameraDir;
		lightOffset.Scale(shadowAreaTbl[0] * 0.2f);
		lightPos.Add(lightOffset);
		for (int i = 0; i < m_numShadowMap; i++) {

			CMatrix mLightView;
			CVector3 vTmp;
			vTmp = lightViewForward;
			vTmp.Scale(-100.0f);

			mLightView = lightViewRot;
			mLightView.m[3][0] = lightPos.x + vTmp.x;
			mLightView.m[3][1] = lightPos.y + vTmp.y;
			mLightView.m[3][2] = lightPos.z + vTmp.z;
			mLightView.m[3][3] = 1.0f;
			mLightView.Inverse(mLightView);	//�J�����r���[�����B
											//�����ăv���W�F�N�V�����s��B
			float viewAngle = MainCamera().GetViewAngle();
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				shadowAreaTbl[i] * m_accpect,
				tan(viewAngle * 0.5f) * (shadowAreaTbl[i] * (i + 1))* 2.0f,
				m_near,
				m_far
			);
			m_LVPMatrix[i].Mul(mLightView, proj);
			//@todo GPU�ɓ]������p�����[�^�͖������B�@m_shadowRecieverParam.mLVP[i] = m_LVPMatrix[i];
			lightOffset = cameraDir;
			lightOffset.Scale(shadowAreaTbl[i] * 0.9f);
			lightPos.Add(lightOffset);
		}

		//@todo GPU�ɓ]������p�����[�^�͖������B�@m_shadowRecieverParam.vsmFlag_numShadowMap[0] = m_isDisableVSM ? 0 : 1;
		//@todo GPU�ɓ]������p�����[�^�͖������B�@m_shadowRecieverParam.vsmFlag_numShadowMap[1] = m_numShadowMap;
	}
	/*!
	*@brief	�V���h�E�}�b�v�֏������݁B
	*/
	void CShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		for (int i = 0; i < m_numShadowMap; i++) {
			CRenderTarget* renderTargets[] = {
				&m_shadowMapRT[i]
			};

			rc.OMSetRenderTargets(1, renderTargets);
			float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor);

			for (auto& caster : m_shadowCaster) {
				caster->Render(rc, m_LVPMatrix[i]);
			}

		}
		m_shadowCaster.clear();
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);

	}
}