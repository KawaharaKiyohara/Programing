/*!
 *@brief	�`��̊�{�N���X�B
 */
#ifndef _TKSHAPEBASE_H_
#define _TKSHAPEBASE_H_

namespace tkEngine{
	/*!
	 *@brief	�`��̊�{�N���X�B
	 */
	class CShapeBase{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CShapeBase();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		virtual ~CShapeBase();
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
		*@brief	��]��ݒ�B
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	�v���~�e�B�u���擾�B
		*/
		CPrimitive* GetPrimitive()
		{
			return m_pPrimitive;
		}
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
	protected:
		bool m_isCreatePrimitive;	//!<�����Ńv���~�e�B�u���쐬�������ǂ����̃t���O�B
		CPrimitive*	m_pPrimitive;	//!<�v���~�e�B�u�B
		CVector3	m_position;		//!<���W�B
		CQuaternion	m_rotation;		//!<��]�B
		CMatrix		m_worldMatrix;	//!<���[���h�s��B
	};
}
#endif //_TKSHAPEBASE_H_