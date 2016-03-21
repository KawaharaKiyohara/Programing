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
		 *@brief	32�o�C�g�̃R�}���h���������݁B
		 *@details	�R�}���h�͕K��32byte
		 *@param[in]	command		�R�}���h�B
		 */
		template<class T>
		void WriteCommand32(T& command)
		{
			static_assert( sizeof(T) <= 32, "command size error\n");
			TK_ASSERT( m_writePos + 32 <= m_size, "command buffer size over!!!");
			struct Write32Byte{
				u32 data[8];
			};
			Write32Byte* dst = reinterpret_cast<Write32Byte*>(&m_buffer[m_writePos]);
			Write32Byte* src = reinterpret_cast<Write32Byte*>(&command);
			*dst = *src;
			m_command.push_back(dst);
			m_writePos += 32;
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