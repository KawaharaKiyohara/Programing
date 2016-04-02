/*!
 * @brief	�v�������_�[
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/preRender/tkPreRender.h"

namespace tkEngine{
	/*!
	 * @brief	�v�������_�����O�B
	 */
	class CPreRender{
	public:
		CPreRender();
		~CPreRender();
		void Create( u32 effectFlags );
	private:
		CIDMap		m_idMap;		//!<ID�}�b�v
	};
}
#endif //_TKPRERENDER_H_