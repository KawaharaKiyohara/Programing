/*!
 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
 */

#pragma once

#include "tkEngine/graphics/material/tkSkinModelMaterial.h"

namespace tkEngine{
	class CSkinModelMaterial;
	/*!
	 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
	 */
	class ISkinModelMaterialNode{
	protected:
		CSkinModelMaterial*		m_material = nullptr;		//!<�X�L�����f���}�e���A���B
	public:
		ISkinModelMaterialNode(CSkinModelMaterial* mat) :
			m_material(mat)
		{
		}
		virtual ~ISkinModelMaterialNode()
		{
		}
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		virtual void SendMaterialParamToGPU() = 0;
	};
	/*!
	 *@brief	�e�N�X�`���]���m�[�h�̃e���v���[�g�N���X�B
	 */
	template<CSkinModelMaterial::EnTextureShaderHandle TTex>
	class TSkinModelMaterialNode_SendTexture : public ISkinModelMaterialNode{
	public:
		TSkinModelMaterialNode_SendTexture(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		void SendMaterialParamToGPU() final
		{
			//�X�v���b�g�}�b�v��]���B
			m_material->SendTextureTGPU(TTex);
		}
	};
	
	/*!
	*@brief	�s��]���m�[�h�̃e���v���[�g�N���X�B
	*/
	template<CSkinModelMaterial::EnMatrixShaderHandle TMatrix>
	class TSkinModelMaterialNode_SendMatrix : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendMatrix(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		*/
		void SendMaterialParamToGPU() final
		{
			//�X�v���b�g�}�b�v��]���B
			m_material->SendMatrixToGPU(TMatrix);
		}
	};

	//�f�B�t���[�Y�}�b�v�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DiffuseMap>
		CSkinModelMaterialNode_SendDiffuseMap;
	//�V���h�E�}�b�v0�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
		CSkinModelMaterialNode_SendShadowMap_0;
	//�V���h�E�}�b�v1�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_1>
		CSkinModelMaterialNode_SendShadowMap_1;
	//�V���h�E�}�b�v2�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_2>
		CSkinModelMaterialNode_SendShadowMap_2;
	//�@���}�b�v�]���m�[�h�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_NormalMap>
		CSkinModelMaterialNode_SendNormalMap;
	//�X�y�L�����}�b�v�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SpecularMap>
		CSkinModelMaterialNode_SendSpecularMap;
	//�X�J�C�L���[�u�B
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SkyCubeMap>
		CSkinModelMaterialNode_SendSkyCubeMap;
	//�X�v���b�g�}�b�v�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SplatMap>
		CSkinModelMaterialNode_SendSplatMap;
	//�n�`�e�N�X�`��0�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex0>
		CSkinModelMaterialNode_SendTerrainTex0;
	//�n�`�e�N�X�`��1�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex1>
		CSkinModelMaterialNode_SendTerrainTex1;
	//�n�`�e�N�X�`��2�]���m�[�h
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex2>
		CSkinModelMaterialNode_SendTerrainTex2;

	
	//1�t���[���O�̃r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LastFrameViewProj>
		CSkinModelMaterialNode_SendLastFrameViewProj;
	//�r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_ViewProj>
		CSkinModelMaterialNode_SendViewProj;
	//���C�g�r���[�v���W�F�N�V�����s��]���m�[�h�B
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LVP>
		CSkinModelMaterialNode_SendLVP;
	//���[���h�s��
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_WorldMatrix>
		CSkinModelMaterialNode_SendWorldMatrix;
}
