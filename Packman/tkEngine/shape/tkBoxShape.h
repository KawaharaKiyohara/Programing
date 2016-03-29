/*!
 * @brief	�{�b�N�X
 */

#ifndef _CBOXSHAPE_H_
#define _CBOXSHAPE_H_

#include "tkEngine/graphics/tkMaterial.h"
#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/shape/tkShapeBase.h"

namespace tkEngine{
	/*!
	 * @brief	�{�b�N�X
	 */
	class CBoxShape : public CShapeBase{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CBoxShape();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CBoxShape();
		/*!
		 *@brief	�J���[�{�b�N�X���쐬�B
		 *@param[in]	size	�T�C�Y�B
		 *@param[in]	color	�J���[�B
		 */
		void Create( CVector3 size, u32 color );
	};
}

#endif // _CBOXSHAPE_H_