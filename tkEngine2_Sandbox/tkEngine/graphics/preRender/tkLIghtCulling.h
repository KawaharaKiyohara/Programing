/*!
 *@brief	���C�g�J�����O
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	���C�g�J�����O�B
	 *@details
	 * TBFR�̓��I�����̃^�C���x�[�X�̃J�����O�̏����B
	 */
	class CLightCulling{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CLightCulling();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CLightCulling();
		/*!
		 *@brief	���C�g�J�����O�̎��s�B
		 */
		void Render(CRenderContext& rc);
	private:
		
	};
}