/*!
 *@brief	�|�C���g���C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	/*!
	 *@brief	�|�C���g���C�g�B
	 */
	class CPointLight : public IGameObject{
	public:
		CPointLight();
		~CPointLight();
		bool Start() override;
		void Update() override;
	private:
		SPointLight	light;		
	};
}