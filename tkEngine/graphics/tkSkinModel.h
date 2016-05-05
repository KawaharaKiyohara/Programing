/*!
*@brief	�X�L�����f��
*/
#ifndef _TKSKINMODEL_H_
#define _TKSKINMODEL_H_

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
	private:
		CSkinModelData*		m_skinModelData;
		CEffect*			m_pEffect;
	};
}

#endif // #ifndef _TKSKINMODEL_H_