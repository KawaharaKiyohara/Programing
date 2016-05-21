/*!
*@brief	�X�L�����f��
*/
#ifndef _TKSKINMODEL_H_
#define _TKSKINMODEL_H_

#include "tkEngine/graphics/tkAnimation.h"

namespace tkEngine {
	class CEffect;
	class CSkinModelData;
	class CRenderContext;

	/*!
	*@brief	�X�L�����f��
	*/
	class CSkinModel {
	public:
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	�`��
		*/
		void Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	�X�L�����f���f�[�^���Z�b�g�B�B
		*/
		void SetSkinModelData(CSkinModelData* modelData)
		{
			m_skinModelData = modelData;
		}
		/*!
		*@brief	�C�~�f�B�G�C�g�`��B
		*@details
		* ���̊֐������s����Ƒ��`��R�}���h��GPU�ɑ����܂��B
		*/
		void ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
		
		/*!
		*@brief	���[���h�s����X�V�B
		*@details
		* ���CMotion�N���X�Ɉړ������܂��B
		*@param[in]		trans	���s�ړ��B
		*@param[in]		rot		��]�B
		*@param[in]		scale	�g��B
		*/
		void UpdateWorldMatrix( const CVector3& trans, const CQuaternion& rot, const CVector3& scale );
	private:
		CMatrix				m_worldMatrix;		//!<���[���h�s��B
		CMatrix				m_rotationMatrix;	//!<��]�s��B
		CSkinModelData*		m_skinModelData;	//!<�X�L�����f���f�[�^�B
		CEffect*			m_pEffect;			//!<�G�t�F�N�g�B
		CAnimation			m_animation;		//!<�A�j���[�V�����B
	};
}

#endif // #ifndef _TKSKINMODEL_H_