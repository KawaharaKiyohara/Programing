/*!
 *@brief	�X�L�����f���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	CSkinModel::CSkinModel()
	{
	}
	CSkinModel::~CSkinModel()
	{
	}
	void CSkinModel::Init(CSkinModelData& modelData, int numInstance)
	{
		m_numInstance = numInstance;
		m_skinModelData = &modelData;
		m_cb.Create(NULL, sizeof(SVSConstantBuffer));
		m_shadowCaster.Create(this);

		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		m_samplerState.Create(desc);

		if (numInstance > 1) {
			//�C���X�^���V���O�p�̃f�[�^���쐬�B
			m_instancingData.reset(new CMatrix[numInstance]);
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
			desc.ByteWidth = sizeof(CMatrix) * numInstance;
			desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			desc.StructureByteStride = sizeof(CMatrix);
			m_instancingDataSB.Create(m_instancingData.get(), desc);
		}
	}
	
	void CSkinModel::UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
	{
		//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
		CMatrix mBias;
		mBias.MakeRotationX(CMath::PI * -0.5f);
		CMatrix mScale, mTrans, mRot;
		mScale.MakeScaling(scale);
		mRot.MakeRotationFromQuaternion(rot);
		mRot.Mul(mBias, mRot);
		mTrans.MakeTranslation(trans);
		m_worldMatrix.Mul(mScale, mRot);
		m_worldMatrix.Mul(m_worldMatrix, mTrans);
	}
	void CSkinModel::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
	{		
		UpdateWorldMatrix(trans, rot, scale);
		GraphicsEngine().GetZPrepass().AddSkinModel(this);
		if (m_isShadowCaster) {
			GraphicsEngine().GetShadowMap().Entry(&m_shadowCaster);
		}

	}
	
	void CSkinModel::UpdateInstancingData(
		const CVector3& trans,
		const CQuaternion& rot,
		const CVector3& scale )
	{		
		UpdateWorldMatrix(trans, rot, scale);
		if (m_updateInstance < m_numInstance) {
			//�C���X�^���V���O�f�[�^���X�V����B
			m_instancingData[m_updateInstance] = m_worldMatrix;
			m_updateInstance++;
		}
		else {
			TK_WARNING("invalid UpdateInstancingData.");
		}
	}
	
	void CSkinModel::PostUpdateInstancingData()
	{
		GraphicsEngine().GetZPrepass().AddSkinModel(this);
		if (m_isShadowCaster) {
			GraphicsEngine().GetShadowMap().Entry(&m_shadowCaster);
		}
	}
	void CSkinModel::Draw(
		CRenderContext& renderContext, 
		const CMatrix& viewMatrix, 
		const CMatrix& projMatrix
	)
	{
		
		(void)renderContext;
		if (m_skinModelData == nullptr) {
			return;
		}
		if (m_numInstance > 1) {
			//�C���X�^���V���O�p�̃f�[�^���X�V�B
			renderContext.UpdateSubresource(m_instancingDataSB, m_instancingData.get());
			renderContext.VSSetShaderResource(enSkinModelSRVReg_InstanceMatrix, m_instancingDataSB.GetSRV());
		}
		//�X�P���g���X�V�B
		m_skinModelData->GetSkeleton().Update(m_worldMatrix);

		static DirectX::CommonStates state(GraphicsEngine().GetD3DDevice());
		//�萔�o�b�t�@���X�V�B
		SVSConstantBuffer vsCb;
		vsCb.mWorld = m_worldMatrix;
		vsCb.mProj = projMatrix;
		vsCb.mView = viewMatrix;
		vsCb.screenParam.x = 0.0f;
		vsCb.screenParam.y = 0.0f;
		vsCb.screenParam.z = static_cast<float>(GraphicsEngine().GetFrameBufferWidth());
		vsCb.screenParam.w = static_cast<float>(GraphicsEngine().GetFrameBufferHeight());
		vsCb.isShadowReceiver = m_isShadowReceiver ? 1 : 0;
		
		renderContext.UpdateSubresource(m_cb, &vsCb);
		renderContext.VSSetConstantBuffer(enSkinModelCBReg_VSPS, m_cb);
		renderContext.PSSetConstantBuffer(enSkinModelCBReg_VSPS, m_cb);
		renderContext.PSSetSampler(0, m_samplerState);
		m_skinModelData->GetSkeleton().Render(renderContext);

		
		m_skinModelData->FindMesh([&](auto& mesh) {
			CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
			//�����_�����O�R���e�L�X�g���G�t�F�N�g�ɐݒ肷��B
			effect->SetRenderContext(renderContext);
			//�C���X�^���X�̐���ݒ�B
			if (m_updateInstance > 1) {
				effect->SetNumInstance(m_updateInstance);
			}
			else {
				effect->SetNumInstance(1);
			}
			
		});
		m_skinModelData->GetBody().Draw(
			GraphicsEngine().GetD3DDeviceContext(),
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix,
			false,
			nullptr,
			m_updateInstance > 1 ? m_updateInstance : 1
		);
	}
}
