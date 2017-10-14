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
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		CVector3 cameraDirXZ = MainCamera().GetForward();
		if (fabs(cameraDirXZ.x) < FLT_EPSILON && fabsf(cameraDirXZ.z) < FLT_EPSILON) {
			//�قڐ^����ނ��Ă���B
			return;
		}
		cameraDirXZ.y = 0.0f;
		cameraDirXZ.Normalize();
		CVector3 lightViewForward = m_lightDirection;
		CVector3 lightViewUp;
		if (lightViewForward.y > 0.999f) {
			//�قڐ^��B
			lightViewUp.Cross(lightViewForward, CVector3::Right);
		}
		else {
			lightViewUp.Cross(lightViewForward, CVector3::Up);
		}
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

		float shadowAreaTbl[NUM_SHADOW_MAP] = {
			400,
			800,
			1600
		};

		//���C�g�r���[�̃^�[�Q�b�g���v�Z�B
		float toFarplane = m_far - m_near;
		CVector3 lightTarget;
		lightTarget = MainCamera().GetPosition();
		lightTarget.y = MainCamera().GetTarget().y;
		lightTarget += cameraDirXZ * shadowAreaTbl[0] * 0.5f;
		CVector3 lightPos = lightTarget + m_lightDirection * toFarplane * -0.5f;
		CVector3 lightOffset;
		SShadowCb shadowCB;
		float nearPlaneZ = 0.0f;
		float farPlaneZ ;
		//������𕪊�����悤�Ƀ��C�g�r���[�v���W�F�N�V�����s����v�Z����B
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			CMatrix mLightView;
			mLightView = lightViewRot;
			mLightView.m[3][0] = lightPos.x;
			mLightView.m[3][1] = lightPos.y;
			mLightView.m[3][2] = lightPos.z;
			mLightView.m[3][3] = 1.0f;
			mLightView.Inverse(mLightView);	//���C�g�r���[�����B
											//�����ăv���W�F�N�V�����s��B
			float halfViewAngle = MainCamera().GetViewAngle() * 0.5f;
			//�������4���_�����C�g��Ԃɕϊ�����AABB�����߂߂āA���ˉe�̕��ƍ��������߂�B
			float w, h;
			CVector3 v[4];
			{
				float t = tan(halfViewAngle);
				//�ߕ��ʂ̒������W���v�Z�B
				CVector3 vWk = MainCamera().GetPosition() + cameraDirXZ * nearPlaneZ;
				v[0] = vWk + MainCamera().GetRight() * t * nearPlaneZ;
				v[1] = vWk + MainCamera().GetRight() * -t * nearPlaneZ;
				//�����ʂ̒������W���v�Z�B
				vWk = MainCamera().GetPosition() + cameraDirXZ * farPlaneZ;
				v[2] = vWk + MainCamera().GetRight() * t * farPlaneZ;
				v[3] = vWk + MainCamera().GetRight() * -t * farPlaneZ;

				//��������\������4���_���v�Z�ł����̂ŁA���C�g��Ԃɍ��W�ϊ����āAAABB�����߂�B
				float fMax[2] = { -FLT_MAX, -FLT_MAX };
				float fMin[2] = { FLT_MAX, FLT_MAX };
				for (auto& vInLight : v) {
					mLightView.Mul(vInLight);
					fMax[0] = max(fMax[0], vInLight.x);
					fMax[1] = max(fMax[1], vInLight.y);
					fMin[0] = min(fMin[0], vInLight.x);
					fMin[1] = min(fMin[1], vInLight.y);
				}
#if 1
				w = fMax[0] - fMin[0];
				h = fMax[1] - fMin[1];
#else
				w = fMax[1] - fMin[1];
				h = fMax[0] - fMin[0];
#endif
			}
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				w * 1.5f,	//���傢���点��B
				h * 1.5f,
				m_near,
				m_far
			);
			m_LVPMatrix[i].Mul(mLightView, proj);
			m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
			
			lightOffset = cameraDirXZ;
			lightOffset.Scale(shadowAreaTbl[i]);
			lightPos.Add(lightOffset);
			nearPlaneZ = farPlaneZ;
		}
	}
	/*!
	*@brief	�V���h�E�}�b�v�֏������݁B
	*/
	void CShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		rc.SetRenderStep(enRenderStep_RenderToShadowMap);
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_RenderToShadowMap");
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
		EndGPUEvent();
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