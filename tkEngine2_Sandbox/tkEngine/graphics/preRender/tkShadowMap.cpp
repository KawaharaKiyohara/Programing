/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

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
		int wh[NUM_SHADOW_MAP][2] = {
			{ config.shadowMapWidth, config.shadowMapHeight},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
		};
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			m_shadowMapRT[i].Create(
				wh[i][0], 
				wh[i][1], 
				1, 
				1,
				DXGI_FORMAT_R32_FLOAT,
				DXGI_FORMAT_D24_UNORM_S8_UINT, 
				multiSampleDesc
			);
		}
		m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));
		return true;
	}
	
	void CShadowMap::Release()
	{
		m_shadowCb.Release();
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
		//���C�g�r���[�v���W�F�N�V�����s����쐬�B
		{
			CMatrix lightCamera;
			CVector3 lightTarget = MainCamera().GetTarget();
			CVector3 lightPos = lightTarget + m_lightDirection * -500.0f;	//@todo 500�͓K���B
			if (m_lightDirection.y > 0.998f) {
				//�قڐ^��������Ă���B
				lightCamera.MakeLookAt(lightPos, lightTarget, CVector3::Right);
			}
			else {
				lightCamera.MakeLookAt(lightPos, lightTarget, CVector3::Up);
			}
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				4000.0f,	//@todo �K���B
				4000.0f,	//@todo �K���B
				m_near,
				m_far
			);
			m_lvp.Mul(lightCamera, proj);
		}
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		CVector3 cameraForwardXZ = MainCamera().GetForward();
		cameraForwardXZ.y = 0.0f;
		cameraForwardXZ.Normalize();
		CVector3 cameraRightXZ = MainCamera().GetRight();
		cameraRightXZ.y = 0.0f;
		cameraRightXZ.Normalize();
		//���C�g�r���[�̓J�����̉���������A�J�����̉�������O�A�J�����̑O���������Ƃ���Ƃ��������ɂȂ��B
		CMatrix lightViewRot;
		//���C�g�r���[�̉���ݒ肷��B
		lightViewRot.m[0][0] = cameraRightXZ.x;
		lightViewRot.m[0][1] = cameraRightXZ.y;
		lightViewRot.m[0][2] = cameraRightXZ.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��B
		lightViewRot.m[1][0] = cameraForwardXZ.x;
		lightViewRot.m[1][1] = cameraForwardXZ.y;
		lightViewRot.m[1][2] = cameraForwardXZ.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��B
		lightViewRot.m[2][0] = 0.0f;
		lightViewRot.m[2][1] = -1.0f;
		lightViewRot.m[2][2] = 0.0f;
		lightViewRot.m[2][3] = 0.0f;

		float toFarPlane = m_far - m_near;
		float shadowAreaTbl[NUM_SHADOW_MAP] = {
			400,
			800,
			1600
		};

		
		CVector3 lightViewPos = MainCamera().GetPosition();
		CVector3 lightViewOffset = cameraForwardXZ;
		lightViewOffset.Scale(shadowAreaTbl[0] * 0.4f);
		lightViewPos.Add(lightViewOffset);
		
		SShadowCb shadowCB;
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {

			CMatrix mLightView;
			mLightView = lightViewRot;
			mLightView.m[3][0] = lightViewPos.x;
			mLightView.m[3][1] = lightViewPos.y;
			mLightView.m[3][2] = lightViewPos.z;
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
			m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
			
			lightViewOffset = cameraForwardXZ;
			lightViewOffset.Scale(shadowAreaTbl[i] * 0.9f);
			lightViewPos.Add(lightViewOffset);
		}
		m_shadowCbEntity.mLVP[NUM_SHADOW_MAP] = m_lvp;
	}
	/*!
	*@brief	�V���h�E�}�b�v�֏������݁B
	*/
	void CShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSUnsetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i);
		}

		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			CRenderTarget* renderTargets[] = {
				&m_shadowMapRT[i]
			};

			rc.OMSetRenderTargets(1, renderTargets);
			rc.RSSetViewport(
				0.0f, 0.0f, 
				(float)m_shadowMapRT[i].GetWidth(),
				(float)m_shadowMapRT[i].GetHeight()
			);
			float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor);

			for (auto& caster : m_shadowCaster) {
				caster->Render(rc, m_LVPMatrix[i]);
			}

		}
		m_shadowCaster.clear();
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//@todo �����_�����O�X�e�[�g�̓��X�g�A������@�ɕύX����B
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
	}
	/*!
	*@brief	�e�𗎂Ƃ����߂̃p�����[�^��GPU�ɓ]������B
	*/
	void CShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_shadowCb, &m_shadowCbEntity);
		rc.PSSetConstantBuffer(enSkinModelCBReg_Shadow, m_shadowCb);
		//�e�N�X�`����]���B
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSSetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i, m_shadowMapRT[i].GetRenderTargetSRV());
		}
	}
}