/*!
 * @brief	���C�g�̊��N���X�B
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	���C�g�̊��N���X�B
		 */
		class CLightBase : public IGameObject {
		public:
			bool Start() override final;
			void OnDestroy() override final;
			/*!
			*@brief ���C�g�̉e����^����I�u�W�F�N�g�����ʂ��邽�߂̃}�X�N��ݒ�B
			*@details
			* 0xFFFFFFFF���w�肷��ƁA���ׂẴI�u�W�F�N�g�Ƀ��C�g�𓖂Ă܂��B
			*/
			void SetMask(unsigned int mask)
			{
				m_mask = mask;
			}
			/*!
			*@brief ���C�g�̉e����^����I�u�W�F�N�g�����ʂ��邽�߂̃}�X�N���擾�B
			*/
			unsigned int GetMask() const
			{
				return m_mask;
			}
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestorySub() {}
		private:
			unsigned int m_mask;	//!<���C�g�̉e����^���鑊������ʂ��邽�߂̃}�X�N�B0xFFFFFFFF�ł��ׂẴI�u�W�F�N�g�Ƀ��C�g�𓖂Ă�B
		};
	}
}