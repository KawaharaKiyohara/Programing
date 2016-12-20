/*!
 *@brief	�J�����̃R���W�����\���o�[
 */

#pragma once

#include "tkEngine/Physics/tkSphereCollider.h"

namespace tkEngine{
	/*!
	 *@brief	�J�����̃R���W�����\���o�[�B
	 *@details
	 * ��ʓI�ȃQ�[���̃J�����̃R���W�����\���o�[��񋟂��܂��B
	 */
	class CCameraCollisionSolver{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CCameraCollisionSolver();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CCameraCollisionSolver();
		/*!
		 *@brief	�������B
		 *@param[in]	radius		�J�����̃o�E���f�B���O�X�t�B�A�̔��a�B
		 */
		void Init(float radius);
		/*!
		 *@brief	�R���W�����\���o�[�̎��s�B
		 *@param[in]	camera		�J�����B
		 */
		void Execute( CCamera& camera );
	private:
		CSphereCollider		m_collider;		 //�R���C�_�[�B
		float				m_radius = 0.0f; //���a�B
	};
}