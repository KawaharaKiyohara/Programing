/*!
 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�X�L�����f���̃}�e���A���m�[�h�̊��N���X�B
	 */
	class ISkinModelMaterialNode{
	public:
		ISkinModelMaterialNode()
		{
		}
		virtual ~ISkinModelMaterialNode()
		{
		}
		/*!
		 *@brief	�}�e���A���p�����[�^��GPU�ɓ]���B
		 */
		virtual void SendMaterialParamToGPU() = 0;
	};
}
