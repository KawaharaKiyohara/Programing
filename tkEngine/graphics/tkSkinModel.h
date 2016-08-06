/*!
*@brief	�X�L�����f��
*/
#ifndef _TKSKINMODEL_H_
#define _TKSKINMODEL_H_

#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkSkinModelData.h"

namespace tkEngine {
	class CEffect;
	class CSkinModelData;
	class CRenderContext;
	class CLight;
	/*!
	*@brief	�X�L�����f��
	*/
	class CSkinModel {
	public:
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	������
		*/
		void Init(CSkinModelData* modelData);
		/*!
		*@brief	�`��
		*/
		void Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	�C�~�f�B�G�C�g�`��B
		*@details
		* ���̊֐������s����Ƒ��`��R�}���h��GPU�ɑ����܂��B
		*/
		void ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
		/*!
		*@brief	�C���X�^���V���O�`��B
		*@details
		* CSkinModelData::CreateInstancingDrawData�����s���āA�C���X�^���V���O�`��̏��������������Ă���K�v������܂��B
		*/
		void InstancingDraw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	�C�~�f�B�G�C�g�C���X�^���V���O�`��B
		*@details
		* ���̊֐������s����Ƒ��`��R�}���h��GPU�ɑ����܂��B
		*/
		void ImmidiateInstancingDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
		/*!
		*@brief	���[���h�s����X�V�B
		*@details
		* ���CMotion�N���X�Ɉړ������܂��B
		*@param[in]		trans	���s�ړ��B
		*@param[in]		rot		��]�B
		*@param[in]		scale	�g��B
		*/
		void UpdateWorldMatrix( const CVector3& trans, const CQuaternion& rot, const CVector3& scale );
		/*!
		* @brief	�C���X�^���V���O�`��p�̃f�[�^���X�V�B
		*@details
		* ���_�X�g���[���P�ɗ������ޒ��_�o�b�t�@�ɐݒ肷��f�[�^�ɂȂ�܂��B
		*@param[in]		data		���_�o�b�t�@�ɃR�s�[����f�[�^�B
		*/
		void UpdateInstancingDrawData(const void* data)
		{
			m_skinModelData->UpdateInstancingDrawData(data);
		}
		/*!
		*@brief	���C�g��ݒ�B
		*/
		void SetLight(CLight* light)
		{
			m_light = light;
		}
		/*!
		*@brief	�@���}�b�v��ݒ�B
		*@param[in] normalMap
		*/
		void SetNormalMap(CTexture* normalMap)
		{
			m_normalMap = normalMap;
		}
	private:
		void DrawMeshContainer(
			IDirect3DDevice9* pd3dDevice,
			LPD3DXMESHCONTAINER pMeshContainerBase,
			LPD3DXFRAME pFrameBase,
			ID3DXEffect* pEffect,
			D3DXMATRIX* worldMatrix,
			D3DXMATRIX* rotationMatrix,
			D3DXMATRIX* viewMatrix,
			D3DXMATRIX* projMatrix,
			CLight* light,
			CTexture* normalMap,
			bool isInstancingDraw
		);
		void DrawFrame(
			IDirect3DDevice9* pd3dDevice,
			LPD3DXFRAME pFrame,
			ID3DXEffect* pEffect,
			D3DXMATRIX* worldMatrix,
			D3DXMATRIX* rotationMatrix,
			D3DXMATRIX* viewMatrix,
			D3DXMATRIX* projMatrix,
			bool isInstancingDraw
		);
		//DrawMeshContainer����Ă΂��C���X�^���V���O�`��̋��ʏ����B
		void DrawMeshContainer_InstancingDrawCommon(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID);		
	private:
		CMatrix				m_worldMatrix;		//!<���[���h�s��B
		CMatrix				m_rotationMatrix;	//!<��]�s��B
		CSkinModelData*		m_skinModelData;	//!<�X�L�����f���f�[�^�B
		CEffect*			m_pEffect;			//!<�G�t�F�N�g�B
		CAnimation			m_animation;		//!<�A�j���[�V�����B
		CLight*				m_light;			//!<���C�g�B
		CTexture*           m_normalMap;		//!<�@���}�b�v�B
		static const int MAX_MATRIX_PALLET = 128;	//!<�}�g���N�X�p���b�g�̍ő吔�B
		D3DXMATRIX			m_boneMatrixPallet[MAX_MATRIX_PALLET];	//!<�}�g���N�X�p���b�g�B
	};
}

#endif // #ifndef _TKSKINMODEL_H_