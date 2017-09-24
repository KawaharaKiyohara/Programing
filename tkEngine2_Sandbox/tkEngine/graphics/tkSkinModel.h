/*!
 *@brief	�X�L�����f���B
 */

#pragma once

#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{
	class CSkinModelData;
	/*!
	 *@brief	�X�L�����f���B
	 */
	class CSkinModel : Noncopyable{
	public:
		/*!
		*@brief QueryEffects�����s�����Ƃ��̃R�[���o�b�N�ɓn���������\���́B
		*/
		struct SQuerryEffectsCbArg {
			DirectX::ModelMeshPart*	meshPart;		//���݂̃G�t�F�N�g�B
		};
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	������
		*/
		void Init(CSkinModelData& modelData);
		/*!
		*@brief	�X�V�B
		*@details
		*@param[in]		trans	���s�ړ��B
		*@param[in]		rot		��]�B
		*@param[in]		scale	�g��B
		*/
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale);
		
		/*!
		*@brief	�`��
		*@param[in]	viewMatrix		�r���[�s��B
		*@param[in]	projMatrix		�v���W�F�N�V�����s��B
		*@param[in]	isZPrepass		ZPrepass?
		*@param[in]	isDrawShadowMap	�V���h�E�}�b�v�ɕ`�撆�H
		*/
		void Draw(
			CRenderContext& renderContext, 
			const CMatrix& viewMatrix, 
			const CMatrix& projMatrix,
			bool isZPrepass = false,
			bool isDrawShadowMap = false
		);
		/*!
		*@brief	���b�V���̌����B
		*@param[in]	findMesh		���b�V�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMesh(CSkinModelData::OnFindMesh findMesh) const
		{
			if (m_skinModelData != nullptr) {
				m_skinModelData->FindMesh(findMesh);
			}
		}
		/*!
		* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}
		/*!
		* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}
	private:
		struct SVSConstantBuffer {
			CMatrix mWorld;
			CMatrix mView;
			CMatrix mProj;
			CVector4 screenParam;
			int isZPrepass;
			int isDrawShadowMap;
			int isShadowReceiver;
		};
		CSkinModelData*	m_skinModelData = nullptr;
		CMatrix m_worldMatrix = CMatrix::Identity;
		CConstantBuffer m_cb;			//�萔�o�b�t�@�B
		CShadowCaster_SkinModel m_shadowCaster;	//!<�V���h�E�L���X�^�[�B
		bool m_isShadowCaster = false;		//!<�V���h�E�L���X�^�[�H
		bool m_isShadowReceiver = false;	//!<�V���h�E���V�[�o�[�H
	};
}