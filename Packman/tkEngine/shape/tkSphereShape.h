/*!
 *@brief	��
 */

#ifndef _TKSPHERESHAPE_H_
#define _TKSPHERESHAPE_H_

#include "tkEngine/shape/tkShapeVertex.h"

namespace tkEngine{
	/*!
	 *@brief	���B
	 */
	class CSphereShape{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSphereShape();
		/*!
		 *@brief	�f�X�g���N�^
		 */
		~CSphereShape();
		/*!
		 *@brief	�J���[�X�t�B�A���쐬�B
		 *@param[in]	radius	���a�B
		 *@param[in]	grid	�O���b�h�B
		 *@param[in]	color	�J���[�B
		 */
		void Create(f32 radius, f32 grid, u32 color);
		/*!
		 *@brief	�����[�X�B
		 */
		void Release();
	};
}
#endif // _TKSPHERESHAPE_H_
