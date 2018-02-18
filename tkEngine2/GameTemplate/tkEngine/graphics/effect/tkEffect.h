/*!
 * @brief	�G�t�F�N�g
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	�G�t�F�N�g�B
		 */
		class CEffect : public IGameObject{
		public:
			CEffect();
			~CEffect();
			/*!
			 *@brief	����B
			 */
			void Release();
			/*!
			 *@brief	�G�t�F�N�g�����[�h�B
			 */
			void Init(const wchar_t* filePath);
			/*!
			 *@brief	�G�t�F�N�g���Đ��B
			 */
			void Play();
			/*!
			 *@brief	���W��ݒ�B
			 */
			void SetPosition(const CVector3& pos)
			{
				m_position = pos;
			}
			/*!
			 *@brief	��]�̐ݒ�B
			 */
			void SetRotation(const CQuaternion& rot)
			{
				m_rotation = rot;
			}
			bool IsPlay() const
			{
				return GraphicsEngine().GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
			}
			/*!
			 *@brief	�X�V�B
			 */
			void Update() override;
		private:
			Effekseer::Effect*	m_effect = nullptr;
			Effekseer::Handle	m_handle = -1;
			CVector3 m_position = CVector3::Zero;			//!<���W�B
			CQuaternion m_rotation = CQuaternion::Identity;	//!<��]�B
		};
	}
}