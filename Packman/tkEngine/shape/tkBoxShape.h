/*!
 * @brief	�{�b�N�X
 */

#ifndef _CBOXSHAPE_H_
#define _CBOXSHAPE_H_

#include "tkEngine/graphics/tkMaterial.h"

namespace tkEngine{
	/*!
	 * @brief	
	 */
	struct ShapeVertex_Color{
		f32		pos[4];
		u32		color;
	};
	/*!
	 * @brief	�{�b�N�X
	 */
	class CBoxShape{
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
		/*!
		 * @brief	�����[�X�B
		 */
		void Release();
		/*!
		*@brief	�X�V
		*/
		void UpdateWorldMatrix();
		/*!
		*@brief	�`��B
		*@param[in]	renderContext	�����_�����O�R���e�L�X�g�B
		*/
		void Render(CRenderContext& renderContext);
		/*!
		*@brief	���[���h�s��̎擾�B
		*/
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	���W��ݒ�B
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	�v���~�e�B�u���擾�B
		*/
		CPrimitive* GetPrimitive()
		{
			return m_pPrimitive;
		}
	private:
		bool m_isCreatePrimitive;	//!<�����Ńv���~�e�B�u���쐬�������ǂ����̃t���O�B
		CPrimitive*	m_pPrimitive;	//!<�v���~�e�B�u�B
		CVector3	m_position;		//!<���W�B
		CMatrix		m_worldMatrix;	//!<���[���h�s��B
	};
}

#endif // _CBOXSHAPE_H_