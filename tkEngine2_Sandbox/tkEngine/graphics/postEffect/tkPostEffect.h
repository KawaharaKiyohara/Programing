/*!
 *@brief	�|�X�g�G�t�F�N�g�B
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkFxaa.h"

namespace tkEngine{
	/*!
	 *@brief	�|�X�g�G�t�F�N�g�B
	 */
	class CPostEffect : Noncopyable{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CPostEffect();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CPostEffect();
		/*!
		 *@brief	�J���B
		 */
		void Release();
		/*!
		 *@brief	�쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		*@brief	�`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void Render(CRenderContext& rc);
	private:
		CFxaa	m_fxaa;		//!<FXAA�B
	};
}