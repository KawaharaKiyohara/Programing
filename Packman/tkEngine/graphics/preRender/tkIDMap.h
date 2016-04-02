/*!
 * @brief	ID�}�b�v
 */

#ifndef _TKIDMAP_H_
#define _TKIDMAP_H_

#include "tkEngine/graphics/tkRenderTarget.h"

namespace tkEngine{
	class CIDMap{
	public:
		/*!
		 * @brief	�R���X�g���N�^
		 */
		CIDMap();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CIDMap();
		/*!
		 * @brief	ID�}�b�v�̍쐬�B
		 */
		void Create(u32 w, u32 h);
		/*!
		 * @brief	�J���B
		 */
		void Release();
		/*!
		 * @brief	ID�}�b�v�ɏ�������
		 *@param[in]	renderContext	�����_�����O�R���e�L�X�g�B
		 */
		void RenderToIDMap( CRendeContext& renderContext );
	private:
		CRenderTarget				m_idMapRT;	//!<ID�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
		std::vector<IGameObject>	
		
	};
}
#endif // _TKIDMAP_H_
