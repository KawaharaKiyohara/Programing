/*!
 *@brief	�|�C���g���C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	/*!
	 *@brief	�|�C���g���C�g�B
	 */
	class CPointLight : public CLightBase{
	public:
		CPointLight();
		~CPointLight();
		bool StartSub() override;
		void Update() override;
	private:
		SPointLight	light;		
	};
}