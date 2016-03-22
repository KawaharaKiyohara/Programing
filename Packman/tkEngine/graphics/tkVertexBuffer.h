/*!
 * @brief	���_�o�b�t�@
 */

#ifndef _TKRENDERBUFFER_H_
#define _TKRENDERBUFFER_H_

namespace tkEngine{
	/*!
	 * @brief	���_�o�b�t�@
	 */
	class CVertexBuffer{
	public:
		CVertexBuffer();
		~CVertexBuffer();
		/*!
		 *@brief	���_�o�b�t�@�̍쐬�B
		 *@param[in]	size			���_�o�b�t�@�̃T�C�Y�B
		 *@param[in]	fvf				���_�o�b�t�@�̃t�H�[�}�b�g�BD3DFVF�̑g�ݍ��킹�B
		 *@param[in]	srcVertexBuffer	�\�[�X���_�o�b�t�@�B�쐬���ꂽ���_�o�b�t�@�ɃR�s�[����܂��BNULL���w��\�B
		 */
		void Create( u32 size, u32 format, const void* pSrcVertexBuffer );
		/*!
		 * @brief	���_�o�b�t�@�̊J���B
		 */
		void Release();
	private:
		LPDIRECT3DVERTEXBUFFER9	m_pVB;	//!<���_�o�b�t�@�B
	};
}
#endif // #define _TKRENDERBUFFER_H_