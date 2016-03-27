#ifndef _TK_CRENDERCONTEXT_H_
#define _TK_CRENDERCONTEXT_H_

#include "tkEngine/graphics/tkRenderCommandBuffer.h"

namespace tkEngine{
	/*!
	* @brief	�����_�����O�R���e�L�X�g�B
	*/
	class CRenderContext : Noncopyable{
	public:
		CRenderContext() {}
		~CRenderContext() {}
		/*!
		 *@brief	�C���X�^���X�̎擾�B
		 */
		static CRenderContext* GetInstance()
		{
			static CRenderContext instance;
			return &instance;
		}
		/*!
		 *@brief	�������B
		 *@param[in]	pD3DDevice			Direct3D�f�o�C�X
		 *@param[in]	commandBufferSize	�R�}���h�o�b�t�@�̃T�C�Y�B
		 */
		void Init(LPDIRECT3DDEVICE9 pD3DDevice, u32 commandBufferSize);
		/*!
		 *@brief	�����_�����O�R�}���h��ǉ�
		 */
		template<class T>
		void SetRenderCommand( T& command )
		{
			static_assert( sizeof(T) <= 32, "command size is over 32byte" );
			m_commandBuffer.WriteCommand32( command );
		}
		/*!
		 *@brief	�R�}���h�o�b�t�@���T�u�~�b�g
		 */
		void SubmitCommandBuffer()
		{
			m_commandBuffer.Submit(m_pD3DDevice);
		}
		/*!
		*@brief	�R�}���h�o�b�t�@����A���P�[�g
		*/
		void* AllocFromCommandBuffer(u32 sizeInByte)
		{
			return m_commandBuffer.Alloc(sizeInByte);
		}
	private:
		LPDIRECT3DDEVICE9		m_pD3DDevice;
		CRenderCommandBuffer 	m_commandBuffer;
	};
}

#endif // _TK_CRENDERCONTEXT_H_