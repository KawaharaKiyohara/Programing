/*!
 *@brief	�|�C���g���C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	�|�C���g���C�g�B
		 */
		class CPointLight : public CLightBase {
		public:
			CPointLight();
			~CPointLight();
			bool StartSub() override final;
			void Update() override final;
			/*!
			*@brief ���f�[�^�̎擾�B
			*/
			SPointLight& GetRawData()
			{
				return light;
			}
		private:
			SPointLight	light;
		};
	}
}