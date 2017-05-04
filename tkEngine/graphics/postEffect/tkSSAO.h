/*!
 * @brief	SSAO
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	SSAO
	 */
	class CSSAO{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSSAO();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CSSAO();
		/*!
		 * @brief	�J���B
		 */
		void Release();
		/*!
		 * @brief	�������B
		 *@param[in]	config		�O���t�B�b�N�R���t�B�O�B
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		 * @brief	�`��B
		 */
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);
	private:
		bool		m_isEnable = false;		//!<SSAO���L�����ǂ����̃t���O�B
		CEffect* 	m_effect = nullptr;
	};
}