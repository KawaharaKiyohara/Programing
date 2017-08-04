/*!
 *@brief	ZPrepass
 */

#pragma once 

namespace tkEngine{
	class CCamera;
	/*!
	 *@brief	ZPrepass
	 */
	class CZPrepass{
	public:
		/*!
		 *@brief	�R���X�g���N�^
		 */
		CZPrepass();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CZPrepass();
		/*!
		*@brief	�������֐��B
		*/
		void Init();
		/*!
		 *@brief	�`��B
		 */
		void Render(CRenderContext& rc) ;
		
		/*!
		*@brief	�X�L�����f����ǉ��B
		*/
		void AddSkinModel(CSkinModel* skinModel)
		{
			m_skinModels.push_back(skinModel);
		}
	private:
		std::vector<CSkinModel*>	m_skinModels;			//!<�X�L�����f���̃��X�g�B
		CRenderTarget				m_depthBuffer;			//!<�[�x�o�b�t�@���������ނ��߂̃����_�����O�^�[�Q�b�g�B
	};
}