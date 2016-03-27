/*!
 * @brief	�J����
 */

#ifndef _TKCAMERA_H_
#define _TKCAMERA_H_

namespace tkEngine{
	class CCamera{
	public:
		CCamera();
		~CCamera();
		/*!
		 * @brief	�r���[�s��A�v���W�F�N�V�����s��A�r���[�v���W�F�N�V�����s����X�V�B
		 */
		void Update();
		/*!
		 * @brief	�J�����̍��W��ݒ�B
		 *@param[in]	pos		�J�����̍��W�B
		 */
		void SetPosition( const CVector3& pos ) 
		{
			m_position = pos;
		}
		/*!
		 * @brief	�J�����̍��W���擾
		 *@return	�J�����̍��W�B
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		 * @brief	�����_��ݒ�B
		 *@param[in]	target		�����_�B
		 */
		void SetTarget( const CVector3& target )
		{
			m_target = target;
		}
		/*!
		 * @brief	�����_���擾�B
		 *@return	�����_�B
		 */
		const CVector3& GetTarget() const
		{
			return m_target;
		}
		/*!
		 * @brief	�J�����̏������ݒ�B
		 */
		void SetUp( const CVector3& up )
		{
			m_up = up;
		}
		/*!
		 * @brief	�J�����̏�������擾
		 */
		const CVector3& GetUp() const
		{
			return m_up;
		}
		/*!
		 * @brief	�r���[�s����擾�B
		 */
		const CMatrix& GetViewMatrix() const
		{
			return m_viewMatrix;
		}
		/*!
		 * @brief	�v���W�F�N�V�����s����擾�B
		 */
		const CMatrix& GetProjectionMatrix() const
		{
			return m_projectionMatrix;
		}
		/*!
		 * @brief	�r���[�v���W�F�N�V�����s����擾�B
		 */
		const CMatrix& GetViewProjectionMatrix() const
		{
			return m_viewProjectionMatrix;
		}
		/*!
		 * @brief	�����ʂ�ݒ�B
		 */
		void SetFar( f32 fFar )
		{
			m_far = fFar;
		}
		/*!
		 * @brief	�ߕ��ʂ�ݒ�B
		 */
		void SetNear( f32 fNear )
		{
			m_near = fNear;
		}
		/*!
		 * @brief	�����ʂ��擾�B
		 */
		f32 GetFar() const
		{
			return m_far;
		}
		/*!
		 * @brief	�ߕ��ʂ��擾�B
		 */
		f32 GetNear() const
		{
			return m_near;
		}
	private:
		CVector3	m_position;							//!<�J�����ʒu�B
		CVector3	m_up;								//!<�J�����̏�����B
		CVector3	m_target;							//!<�J�����̒��~�_�B
		CMatrix		m_viewMatrix;						//!<�r���[�s��B
		CMatrix		m_projectionMatrix;					//!<�v���W�F�N�V�����s��B
		CMatrix		m_viewProjectionMatrix;				//!<�r���[�v���W�F�N�V�����s��B
		CMatrix		m_viewMatrixInv;					//!<�r���[�s��̋t�s��B
		f32			m_near;								//!<�ߕ��ʁB
		f32			m_far;								//!<�����ʁB
		f32			m_viewAngle;						//!<��p(Y����)�B
		f32			m_aspect;							//!<�A�X�y�N�g��B
		bool		m_isNeedUpdateProjectionMatrix;
	};
}
#endif //_TKCAMERA_H_