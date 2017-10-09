/*!
 * @brief	�X�v���C�g�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�X�v���C�g�B
	 */
	class CSprite : Noncopyable {
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSprite();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CSprite();
		/*!
		 * @brief	�������B
		 *@param[in]	tex		�e�N�X�`���B
		 *@param[in]	w		���B
		 *@param[in]	h		�����B
		 */
		void Init(CShaderResourceView& tex, float w, float h);
		/*!
		 * @brief	�e�N�X�`����ݒ�B
		 *@param[in]	tex		�e�N�X�`���B
		 */
		void SetTexture(CShaderResourceView& tex)
		{
			m_textureSRV = &tex;
		}
		/*!
		*@brief	�`��
		*@param[in]	viewMatrix		�r���[�s��B
		*@param[in]	projMatrix		�v���W�F�N�V�����s��B
		*/
		void Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	���W��ݒ�B
		*/
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		
		/*!
		*@brief	���W���擾�B
		*/
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		*@brief	��]��ݒ�B
		*/
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/*!
		*@brief	��]���擾�B
		*/
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/*!
		*@brief	�g�嗦��ݒ�B
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/*!
		*@brief	�g�嗦���擾�B
		*/
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/*!
		*@brief	�s�{�b�g��ݒ�B
		*@details
		* 0.5, 0.5�ŉ摜�̒��S����_�B
		* 0.0, 0.0�ŉ摜�̍����B
		* 1.0, 1.0�ŉ摜�̉E��B
		* Unity��uGUI�ɏ����B
		*@param[in]	pivot		�T�C�Y�B
		*/
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
	private:
		struct SSpriteCB {
			CMatrix WVP;		//���[���h�r���[�v���W�F�N�V�����s��B
		};
		CVector3				m_position = CVector3::Zero;	//!<���W�B
		CQuaternion				m_rotation = CQuaternion::Identity;		//!<��]
		CVector3				m_scale = CVector3::One;
		CMatrix					m_world = CMatrix::Identity;	//!<���[���h�s��B
		CShader					m_ps;							//!<�s�N�Z���V�F�[�_�[�B
		CShader					m_vs;							//!<���_�V�F�[�_�[�B
		CPrimitive				m_primitive;					//!<�v���~�e�B�u�B
		CShaderResourceView*	m_textureSRV = nullptr;			//!<�e�N�X�`���B
		CConstantBuffer			m_cb;
		CVector2				m_pivot = {0.5f, 0.5f};		//!<�s�{�b�g�B
		CVector2				m_size = CVector2::Zero;		//!<�T�C�Y�B
	};
}