/*!
 * @brief	��ʊE�[�x
 */

#pragma once

#include "tkEngine/graphics/tkGaussianBlur.h"

namespace tkEngine{
	class CPostEffect;
	/*!
	 * @brief	��ʊE�[�x
	 */
	class CDof : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CDof();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CDof();
		/*!
		 * @brief	�`��B
		 */
		void Render( CRenderContext& renderContext, CPostEffect* postEffect );
		/*!
		* @brief	�쐬�B
		*@param[in]	config		�O���t�B�b�N�R���t�B�O�B
		*/
		void Create(const SGraphicsConfig& config);
		/*!
		* @brief	�[�x���������ރ����_�����O�^�[�Q�b�g�̎擾�B
		*/
		CRenderTarget* GetDepthRenderTarget()
		{
			return &m_depthRT;
		}
		/*!
		* @brief	�J���B
		*/
		void Release();
	private:
		CRenderTarget		m_depthRT;		//!<�[�x���������ރ����_�����O�^�[�Q�b�g�B
		bool				m_isEnable;		//!<DOF�L���H
		CGaussianBlur		m_blurForward;	//!<�O�{�P�p�̃u���[�B
		CGaussianBlur		m_blurBack;		//!<���{�P�p�̃u���[�B
		CEffect*			m_effect;		//!<�G�t�F�N�g�B
	};
}
