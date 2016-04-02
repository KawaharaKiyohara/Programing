/*!
 * @brief	�v�������_�[
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"

namespace tkEngine{
	/*!
	 * @brief	�v�������_�����O�B
	 */
	class CPreRender{
	public:
		CPreRender();
		~CPreRender();
		void Create( const SGraphicsConfig& config );
	private:
		CIDMap		m_idMap;		//!<ID�}�b�v
	};
}
#endif //_TKPRERENDER_H_