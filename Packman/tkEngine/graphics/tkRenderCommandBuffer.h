/*!
 *@brief	�����_�����O�R�}���h�o�b�t�@�N���X�B
 */

#ifndef _TKRENDERCOMMANDBUFFER_H_
#define _TKRENDERCOMMANDBUFFER_H_

namespace tkEngine{
	/*!
	 *@brief	�`��R�}���h�o�b�t�@
	 */
	class CRenderCommandBuffer{
	public:
		/*!
		 *@brief	�R���X�g���N�^
		 */
		CRenderCommandBuffer();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CRenderCommandBuffer();
		/*!
		 *@brief	�������B
		 *@param[in]	size	�R�}���h�o�b�t�@�̃T�C�Y�B
		 */
		void Init(u32 size);
		/*!
		 *@brief	128�o�C�g�̃R�}���h���������݁B
		 *@details	�R�}���h�͕K��128b
		 *@param[in]	command		�R�}���h�B
		 */
		template<class T>
		void WriteCommand128(T& command)
		{
			static_assert( sizeof(T) == 128, "command size error");
			TK_ASSERT( m_writePos + 128 <= m_size, "command buffer size over!!!");
			struct Write128Byte{
				u32 data[4]
			};
			Write128Byte* dst = reinterpret_cast<Write128Byte*>(&m_buffer[m_writePos]);
			Write128Byte* src = reinterpret_cast<Write128Byte*>(p);
			*dst = command;
			m_command.push_back(dst);
			m_writePos += 128;
		}
		/*!
		 *@brief	�R�}���h�o�b�t�@���T�u�~�b�g�B
		 */
		void Submit(LPDIRECT3DDEVICE9 pD3DDevice);
	private:
		std::unique_ptr<u8[]>	m_buffer;	//!<�R�}���h�o�b�t�@
		std::vector<void*>		m_command;	//!<�R�}���h�B
		u32						m_writePos;	//!<�������݈ʒu
		u32						m_size;		//!<�R�}���h�o�b�t�@�̃T�C�Y�B
	};
}
#endif // _TKRENDERCOMMANDBUFFER_H_