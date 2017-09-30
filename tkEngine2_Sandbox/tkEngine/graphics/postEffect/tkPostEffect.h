/*!
 *@brief	�|�X�g�G�t�F�N�g�B
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"
#include "tkEngine/graphics/tkPrimitive.h"


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
		/*!
		*@brief	�t���X�N���[���`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void DrawFullScreenQuad(CRenderContext& rc);
	private:
		/*!
		*@brief	�t���X�N���[���`��p�̋�`�v���~�e�B�u�̏������B�B
		*/
		void InitFullScreenQuadPrimitive();
	private:
		CFxaa		m_fxaa;				//!<FXAA�B
		CBloom		m_bloom;			//!<BLOOM�B
		CPrimitive	m_fullscreenQuad;	//!<�t���X�N���[���`��p�̋�`�v���~�e�B�u�B
	};
}