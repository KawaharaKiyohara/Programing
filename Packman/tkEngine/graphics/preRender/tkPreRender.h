/*!
 * @brief	�v�������_�[
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"
#include "tkEngine/graphics/preRender/tkIDMap.h"
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
		 * @brief	�쐬�B
		 *@param[in]	config	�R���t�B�O�B
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		 * @brief	�`��B
		 */
		void Render( CRenderContext& context )
		{
			m_idMap.RenderToIDMap(context);
		}
		/*!
		* @brief	IDMap�̎擾�B
		*/
		CIDMap& GetIDMap()
		{
			return m_idMap;
		}
	private:
		SGraphicsConfig	m_config;	//!<�R���t�B�O�B
		CIDMap			m_idMap;	//!<ID�}�b�v
	};
}
#endif //_TKPRERENDER_H_