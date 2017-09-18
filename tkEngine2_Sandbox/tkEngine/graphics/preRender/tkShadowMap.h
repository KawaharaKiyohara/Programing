/*!
 * @brief	�V���h�E�}�b�v
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�V���h�E�}�b�v�B
	 */
	class CShadowMap : Noncopyable{
	public:
		static const int MAX_SHADOW_MAP = 3;
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CShadowMap();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CShadowMap();
		/*!
		 * @brief	�V���h�E�}�b�v�̍쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 *@return	true���Ԃ��Ă�����V���h�E�}�b�v�̍쐬�����B
		 */
		bool Init( const SShadowRenderConfig& config );
		
	private:
		bool m_isEnable = false;							//!<�e�̏������L���H
		CRenderTarget	m_shadowMapRT[MAX_SHADOW_MAP];		//!<�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
		int m_numShadowMap = 0;								//!<�V���h�E�}�b�v�̖����B
	};
}