/*!
 * @brief	�G�t�F�N�g�G���W���B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�G�t�F�N�g�G���W���B
	 */
	class CEffectEngine : Noncopyable{
	public:
		CEffectEngine();
		~CEffectEngine();
		/*!
		 *@brief	����B
		 */
		void Release();
		/*!
		 *@brief	�������B
		 */
		void Init();
		/*!
		 *@brief	�X�V�B
		 */
		void Update();
		/*!
		 *@brief	�`��B
		 */
		void Render(CRenderContext& rc);
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g���쐬�B
		 */
		Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g���Đ��B
		 */
		Effekseer::Handle Play(Effekseer::Effect* effect);
		/*!
		 *@brief	Effekseer�}�l�[�W���̎擾�B
		 */
		Effekseer::Manager& GetEffekseerManager()
		{
			return *m_manager;
		}
		/*!
		 *@brief	Effekseer�̃G�t�F�N�g�̒�~�B
		 */
		void Stop(Effekseer::Handle handle);
	private:
		Effekseer::Manager*	m_manager= nullptr;
		EffekseerRenderer::Renderer*	m_renderer = nullptr;
	};
}