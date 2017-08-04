/*!
 *@brief	�f�B���N�V�������C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	/*!
	 *@brief	�f�B���N�V�������C�g�B
	 */
	class CDirectionLight : public IGameObject{
	public:
		CDirectionLight();
		~CDirectionLight();
		bool Start() override;
		void Update() override;
	private:
		SDirectionLight		light;		//!<���C�g�B
	};
}