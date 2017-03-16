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
		/*!
		*@brief	�e�N�X�`���̃V�F�[�_�[�n���h���B
		*/
		enum EnTextureShaderHandle {
			enTextureShaderHandle_DiffuseMap,	//!<�f�B�t���[�Y�}�b�v�B
			enTextureShaderHandle_ShadowMap_0,	//!<�V���h�E�}�b�v0
			enTextureShaderHandle_ShadowMap_1,	//!<�V���h�E�}�b�v1
			enTextureShaderHandle_ShadowMap_2,	//!<�V���h�E�}�b�v2
			enTextureShaderHandle_NormalMap,	//!<�@���}�b�v�B
			enTextureShaderHandle_SpecularMap,	//!<�X�y�L�����}�b�v�B
			enTextureShaderHandle_Num,
		};
		/*!
		*@brief	�s��̃V�F�[�_�[�n���h���B
		*/
		enum EnMatrixShaderHandle {
			enMatrixShaderHandle_LastFrameViewProj,		//!<1�t���[���O�̃r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_ViewProj,				//!<�r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_LVP,					//!<���C�g�r���[�v���W�F�N�V�����s��B
			enMatrixShaderHandle_ViewMatrixRotInv,		//!<�r���[�s��̉�]�t�s��B
			enMatrixShaderHandle_WorldMatrix,			//!<���[���h�s��
			enMatrixShaderHandle_RotationMatrix,		//!<��]�s��i�s�v�j
			enMatrixShaderHandle_Num,
		};
		/*!
		*@brief	���������_�x�N�g���̃V�F�[�_�[�n���h���B
		*/
		enum EnFVectorShaderHandle {
			enFVectorShaderHandle_CameraPos,	//!<�J�����̈ʒu�B
			enFVectorShaderHandle_FarNear,		//!<�����ʂƋߕ��ʁB
			enFVectorShaderHandle_FogParam,		//!<Fog�p�����[�^�B
			enFVectorShaderHandle_CameraDir,	//!<�J�����̕����B
			enFVectorShaderHandle_Num,
		};
		/*!
		*@brief	�����x�N�g���̃V�F�[�_�[�n���h���B
		*/
		enum EnIVectorShaderHandle {
			enIVectorShaderHandle_Flags,		//!<�e��t���O�Bx�ɖ@���}�b�v�Ay�̓V���h�E���V�[�o�[�Az�̓������C�g�Aw�̓X�y�L�����}�b�v�B
			enIVectorShaderHandle_Flags2,		//!<�e��t���O�Bx�ɑ��x�}�b�v�ւ̏������݁Ay�͑�C�����V�~�����[�V������ށB
			enIVectorShaderHandle_Num,
		};
		/*!
		*@brief	�����̃V�F�[�_�[�n���h���B
		*/
		enum EnIntShaderHandle {
			enIntShaderHandle_NumBone,			//!<�{�[���̐��B
			enIntshaderHandle_CurNumBone,		//!<�X�L�j���O���s���{�[���̐��B
			enIntShaderHandle_Num,
		};
		enum EnShaderHandle {
			enShaderHandleLight,				//���C�g�B
			enShaderHandleWorldMatrixArray,		//�{�[���s��
			enShaderHandleShadowRecieverParam,	//�V���h�E���V�[�o�[�p�̃p�����[�^�B
			enShaderHandleNum,					//�V�F�[�_�[�n���h���̐��B
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
		 *@brief	�e�N�X�`����ݒ�B
		 */
		void SetTexture(EnTextureShaderHandle eTexHandle, CTexture& tex)
		{
			TK_ASSERT(eTexHandle < enTextureShaderHandle_Num, "eTexHandle is invalid");
			m_textures[eTexHandle] = &tex;
		}
		/*!
		*@brief	�s���ݒ�B
		*/
		void SetMatrix(EnMatrixShaderHandle eMatrixHandle, const CMatrix& mat)
		{
			TK_ASSERT(eMatrixHandle < enMatrixShaderHandle_Num, "eMatrixHandle is invalid");
			m_matrices[eMatrixHandle] = mat;
		}
		/*!
		*@brief ���������x�N�g����ݒ�B
		*/
		template<class TVector>
		void SetFVector(EnFVectorShaderHandle eFVecHandle, const TVector& v)
		{
			TK_ASSERT(eFVecHandle < enFVectorShaderHandle_Num, "eFVecHandle is invalid");
			m_fVector[eFVecHandle].Set(v);
		}
		/*!
		*@brief �����x�N�g����ݒ�B
		*/
		void SetIVector(EnIVectorShaderHandle eIVecHandle, const CVector4i& v)
		{
			TK_ASSERT(eIVecHandle < enIVectorShaderHandle_Num, "eIVecHandle is invalid");
			m_iVector[eIVecHandle] = v;
		}
		/*!
		*@brief �����f�[�^��ݒ�B
		*/
		void SetInt(EnIntShaderHandle eIntHandle, int data)
		{
			TK_ASSERT(eIntHandle < enIntShaderHandle_Num, "eIntHandle is invalid");
			m_int[eIntHandle] = data;
		}
		/*!
		*@brief ��C�����p�����[�^��ݒ�B
		*/
		void SetAtmosphericScatteringParam(const SAtmosphericScatteringParam& param)
		{
			m_atmosParam = param;
		}
		/*!
		*@brief ���C�g��ݒ�B
		*/
		void SetLight(const CLight& light)
		{
			m_light = light;
		}
		/*!
		*@brief	�V���h�E���V�[�o�[�p�����[�^��ݒ�B
		*/
		void SetShadowRecieverParam(const CShadowMap::ShadowRecieverParam& shadowRecParam)
		{
			m_shadowRecParam = shadowRecParam;
		}
		/*!
		*@brief	�������B
		*@param[in]		effect		�G�t�F�N�g
		*@param[in]		tecName		�e�N�j�b�N���B
		*/
		void Init(CEffect* effect, const char* tecName);
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
		void InitShaderHandles(const char* tecName);
	protected:
		CTexture*	m_textures[enTextureShaderHandle_Num];	//!<�e�N�X�`���B
		CMatrix 	m_matrices[enMatrixShaderHandle_Num];	//!<�s��B
		CVector4 	m_fVector[enFVectorShaderHandle_Num];	//!<4�v�f�̕��������x�N�g���B
		CVector4i	m_iVector[enIVectorShaderHandle_Num];	//!<4�v�f�̐����x�N�g���B
		int			m_int[enIntShaderHandle_Num];			//!<�����B
		SAtmosphericScatteringParam m_atmosParam;			//!<��C�����p�����[�^�B
		CLight m_light;										//!<���C�g�B
		CShadowMap::ShadowRecieverParam m_shadowRecParam;	//!<�V���h�E���V�[�o�[�p�����[�^�B
	private:
		std::vector<ISkinModelMaterialNode*>	m_materialNodes;		//!<�}�e���A���̃m�[�h�B
		CEffect* m_pEffect = nullptr;									//!<�G�t�F�N�g�B
		D3DXHANDLE m_hTec;												//!<�e�N�j�b�N�n���h���B
		D3DXHANDLE m_hTexShaderHandle[enTextureShaderHandle_Num];		//!<�e�N�X�`���V�F�[�_�[�n���h���B
		D3DXHANDLE m_hMatrixShaderHandle[enMatrixShaderHandle_Num];		//!<�s��̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hFVectorShaderHandle[enFVectorShaderHandle_Num];	//!<���������x�N�g���̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hIVectorShaderHandle[enIVectorShaderHandle_Num];	//!<�����x�N�g���̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hIntShaderHandle[enIntShaderHandle_Num];			//!<�����̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hAtmosShaderHandle;								//!<��C�����̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hLightShaderHandle;								//!<���C�g�p�̃V�F�[�_�[�n���h���B
		D3DXHANDLE m_hShadowRecieverParamShaderHandle;					//!<�V���h�E���V�[�o�[�p�����[�^�̃V�F�[�_�[�n���h���B						
		D3DXHANDLE m_hShaderHandle[enShaderHandleNum];				//!<�V�F�[�_�[�n���h���B
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		bool m_isBeginDraw = false;						//!<BeginDraw���Ă΂�Ă���H
#endif
	};
}