/*!
 * @brief	�u���[��
 */
#pragma once

namespace tkEngine{
	/*!
	 * @brief	�u���[��
	 */
	class CBloom : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CBloom();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CBloom();
		/*!
		 * @brief	�J��
		 */
		void Release();
		/*!
		 * @brief	�������B
		 */
		void Init( const SGraphicsConfig& config );
		/*!
		 * @brief	�`��
		 */
		void Render(CRenderContext& rc);
	private:
		bool m_isEnable = false;		//!<�L���B
	};
}