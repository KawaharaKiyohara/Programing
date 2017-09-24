/*!
 * @brief	�V���h�E�}�b�v
 */

#pragma once

namespace tkEngine{
	class IShadowCaster;
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
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/*!
		 *@brief	�V���h�E�}�b�v�֏������݁B
		 */
		void RenderToShadowMap(CRenderContext& rc);
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		* @brief	�V���h�E�L���X�^�[���G���g���[�B
		*/
		void Entry(IShadowCaster* caster);
		/*!
		* @brief	���C�g�r���[�̒����_��ݒ�B
		*/
		void SetLightTarget(const CVector3& lightTarget)
		{
			m_lightTarget = lightTarget;
		}
		/*!
		* @brief	���C�g�̈ʒu��ݒ�B
		*/
		void SetLightPosition(const CVector3& lightPosition)
		{
			m_lightPosition = lightPosition;
		}
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetFar(float Far)
		{
			m_far = Far;
		}
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetNear(float Near)
		{
			m_near = Near;
		}
	private:
		bool m_isEnable = false;							//!<�e�̏������L���H
		CVector3 m_lightPosition = CVector3::Zero;			//!<���C�g�̈ʒu�B
		CVector3 m_lightTarget = CVector3::Zero;			//!<�����_
		float m_near = 0.1f;								//!<�ߕ��ʁB
		float m_far = 100.0f;								//!<�����ʁB
		float m_accpect = 1.0f;								//!<�A�X�y�N�g�B�s�v�H
		float m_shadowAreaW[MAX_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̕��B
		float m_shadowAreaH[MAX_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̍����B
		CRenderTarget	m_shadowMapRT[MAX_SHADOW_MAP];		//!<�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
		std::vector<IShadowCaster*> m_shadowCaster;			//!<�V���h�E�L���X�^�[�B
		CMatrix	m_LVPMatrix[MAX_SHADOW_MAP] = { CMatrix::Identity };				//!<���C�g�r���[�v���W�F�N�V�����s��B
		int m_numShadowMap = 0;								//!<�V���h�E�}�b�v�̖����B
	};
}