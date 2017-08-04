/*!
 * @brief	�v�������_�[
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"
#include "tkEngine/graphics/preRender/tkZPrepass.h"

namespace tkEngine{
	/*!
	 * @brief	�v�������_�����O�B
	 */
	class CPreRender : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPreRender();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPreRender();
		/*!
		* @brief	�J��
		*/
		void Release();
		/*!
		 * @brief	�쐬�B
		 *@param[in]	config	�R���t�B�O�B
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		* @brief	�`��B
		*/
		void Render(CRenderContext& rc);
		/*!
		* @brief	�X�V�B
		*/
		void Update() {}
		/*!
		* @brief	ZPrepass�̎擾�B
		*/
		CZPrepass& GetZPrepass()
		{
			return m_zprepass;
		}
	private:
		SGraphicsConfig	m_config;			//!<�R���t�B�O�B
		CZPrepass		m_zprepass;			//!<ZPrepass�B
	};
}
#endif //_TKPRERENDER_H_