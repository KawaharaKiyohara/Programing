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
	private:
		bool m_isCreatePrimitive;		//!<�����Ńv���~�e�B�u���쐬�������ǂ����̃t���O�B
		CPrimitive* m_pPrimitive;		//!<�v���~�e�B�u�B
		CVector3	m_position;			//!<���W�B
		CQuaternion m_rotation;			//!<��]�B
		CMatrix		m_worldMatrix;		//!<���[���h�s��B
	};
}
#endif // _TKSPHERESHAPE_H_
