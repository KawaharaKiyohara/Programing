/*!
 *@brief	�f�B���N�V�������C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	�f�B���N�V�������C�g�B
		 */
		class CDirectionLight : public CLightBase {
		public:
			CDirectionLight();
			~CDirectionLight();
			bool StartSub() override final;
			void Update() override final;
			/*!
			*@brief ���C�g�̕�����ݒ�B
			*@param[in]	direction	���C�g�̕����B
			*/
			void SetDirection(const CVector3& direction);
			/*!
			*@brief ���C�g�̃J���[��ݒ�B
			*@param[in]	color	���C�g�̃J���[�B
			*/
			void SetColor(const CVector3& color);
			/*!
			*@brief ���f�[�^�̎擾�B
			*/
			SDirectionLight& GetRawData()
			{
				return light;
			}
		private:
			SDirectionLight		light;		//!<���C�g�B
		};
	}
}