/*!
 *@brief	�X�L�����f���}�e���A���B
 */

#pragma once

#include "tkEngine/graphics/material/node/tkSkinModelMaterialNode.h"

namespace tkEngine{
	class ISkinModelMaterialNode;
	/*!
	 *@brief	�X�L�����f���}�e���A���B
	 */
	class CSkinModelMaterialEx
	{
	public:
		enum EnShaderHandle {
			enShaderHandleLastFrameViewProj,	//1�t���[���O�̃r���[�v���W�F�N�V�����B	
			enShaderHandleViewProj,				//�r���[�v���W�F�N�V�����B	
			enShaderHandleLight,				//���C�g�B
			enShaderHandleLVP,					//���C�g�r���[�v���W�F�N�V�����s��B
			enShaderHandleCameraPos,			//�J�����̈ʒu�B
			enShaderHandleAtmosParam,			//��C�����p�����[�^�B
			enShaderHandleFlags,				//g_flags
			enShaderHandleFlags2,				//g_flags2
			enShaderHandleFarNear,				//FarNear
			enShaderHandleFogParam,				//Fog�p�����[�^�B
			enShaderHandleWorldMatrixArray,		//�{�[���s��
			enShaderHandleNumBone,				//�{�[���̐��B
			enShaderHandleCurNumBones,			//�X�L���O���s�Ȃ��{�[���̐��B
			enShaderHandleViewMatrixRotInv,		//�r���[�s��̉�]�����̋t�s��B
			enShaderHandleWorldMatrix,			//���[���h�s��
			enShaderHandleRotationMatrix,		//��]�s��B
			enShaderHandleShadowMap_0,			//�V���h�E�}�b�v
			enShaderHandleShadowMap_1,			//�V���h�E�}�b�v
			enShaderHandleShadowMap_2,		//�V���h�E�}�b�v
			enShaderHandleNormalTexture,	//�@���}�b�v�B
			enShaderHandleSpeculerMap,		//�X�y�L�����}�b�v�B
			enShaderHandleDiffuseTexture,	//�f�B�t���[�Y�e�N�X�`���B
			enShaderHandleCameraDir,		//�J�����̕����B
			enShaderHandleShadowRecieverParam,	//�V���h�E���V�[�o�[�p�̃p�����[�^�B
			enShaderHandleTec_SkinModelInstancingRenderToShadowMap,		//SkinModelInstancingRenderToShadowMap�e�N�j�b�N
			enShaderHandleTec_SkinModelInstancing,						//SkinModelInstancing�e�N�j�b�N�B
			enShaderHandleTec_NoSkinModelInstancingRenderToShadowMap,	//NoSkinModelInstancingRenderToShadowMap�e�N�j�b�N�B
			enShaderHandleTec_NoSkinModelInstancing,					//NoSkinModelInstancing�e�N�j�b�N�B
			enShaderHandleTec_SkinModelRenderShadowMap,					//SkinModelRenderShadowMap�e�N�j�b�N�B
			enShaderHandleTec_SkinModel,								//SkinModel�e�N�j�b�N�B
			enShaderHandleTec_NoSkinModelRenderShadowMap,				//NoSkinModelRenderShadowMap�e�N�j�b�N�B
			enShaderHandleTec_NoSkinModel,								//NoSkinModel�e�N�j�b�N�B
			enShaderHandleTec_Sky,										//Sky�e�N�j�b�N�B
			enShaderHandleNum,				//�V�F�[�_�[�n���h���̐��B
		};
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSkinModelMaterialEx()
		{
		}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CSkinModelMaterialEx()
		{
		}
		/*!
		*@brief	�������B
		*/
		void Init();
		/*!
		 *@brief	�`��J�n�B
		 */
		void BeginDraw();
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		void SendMaterialParamToGPU();
		/*!
		 *@brief	�`��I���B
		 */
		void EndDraw();
	private:
		/*!
		*@brief	�V�F�[�_�[�n���h���̏������B
		*/
		void InitShaderHandles();
	private:
		std::vector<ISkinModelMaterialNode*>	m_materialNodes;		//!<�}�e���A���̃m�[�h�B
		CEffect* m_pEffect = nullptr;					//!<�G�t�F�N�g�B
		std::string m_tecName;							//!<�e�N�j�b�N���B
		D3DXHANDLE m_hShaderHandle[enShaderHandleNum];	//!<�V�F�[�_�[�n���h���B
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		bool m_isBeginDraw = false;						//!<BeginDraw���Ă΂�Ă���H
#endif
	};
}