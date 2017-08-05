/*!
 *@brief	�f�B���N�V�������C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	/*!
	 *@brief	�f�B���N�V�������C�g�B
	 */
	class CDirectionLight : public CLightBase{
	public:
		CDirectionLight();
		~CDirectionLight();
		bool StartSub() override;
		void Update() override;
	private:
		SDirectionLight		light;		//!<���C�g�B
	};
}