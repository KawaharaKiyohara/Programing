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
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestorySub() {}

		};
	}
}