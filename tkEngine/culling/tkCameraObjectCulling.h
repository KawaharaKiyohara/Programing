/*!
 *@brief	�J�������g�p�����I�u�W�F�N�g�J�����O�����B
 */

#pragma once

#include "tkEngine/culling/tkObjectCulling.h"

namespace tkEngine{
	/*!
	 *@brief	�J�������g�p�����I�u�W�F�N�g�J�����O�����B
	 *@details
	 * �I�u�W�F�N�g������AABB���\������8���_���J�����ɉf��Ȃ��ꍇ�ɃJ�����O����܂��B
	 */
	class CCameraObjectCulling : public IObjectCulling{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CCameraObjectCulling();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CCameraObjectCulling();
		/*!
		 *@brief	�������B
		 */
		void Init( const CCamera& camera )
		{
			m_camera = &camera;
		}
		/*!
		 *@brief	�J�����O�A���S���Y���̎��s�B
		 */
		void Execute() override;
	private:
		const CCamera*	m_camera = nullptr;
	};
}