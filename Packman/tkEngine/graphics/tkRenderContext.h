#ifndef _TK_CRENDERCONTEXT_H_
#define _TK_CRENDERCONTEXT_H_

#include "tkEngine/graphics/tkRenderCommandBuffer.h"

namespace tkEngine{
	class CVertexBuffer;
	class CIndexBuffer;
	class CPrimitive;
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
		 * @brief	���_��`��ݒ�BIDirect3DDevice9::SetVertexDeclaration�Ɠ����B
		 *@param[in]	vertexDecl		���_��`�B
		 */
		__inline void SetVertexDeclaration(SVertexDecralation* vertexDecl);
		/*!
		 * @brief	���_�X�g���[����ݒ�BIDirect3DDevice9::SetStreamSource�Ɠ����B
		 *@param[in]	streamNo		�X�g���[���ԍ��B
		 *@param[in]	pVB				���_�o�b�t�@�B
		 */
		__inline void SetStreamSource(u32 streamNo, CVertexBuffer* pVB);
		/*!
		 * @brief	�C���f�b�N�X�o�b�t�@��ݒ�BIDirect3DDevice9::SetIndices�Ɠ����B
		 *@param[in]	pIB		�C���f�b�N�X�o�b�t�@�B
		 */
		__inline void SetIndices(CIndexBuffer* pIB);
		/*!
		 * @brief	�C���f�b�N�X�o�b�t�@���Q�Ƃ��ăv���~�e�B�u��`��BIDirect3DDevice9::DrawIndexPrimitive�Ɠ����B
		 */
		__inline void DrawIndexedPrimitive(CPrimitive* prim);
		/*!
		* @brief	�����_�����O�^�[�Q�b�g�Ɛ[�x�X�e���V���o�b�t�@�̃N���A�BIDirect3DDevice9::Clear�Ɠ����B
		*@param[in]	Count		�N���A����̈�̃J�E���g�BpRects��NULL�ɐݒ肷��ꍇ�͂��̃p�����[�^���O�ɂ���B
		*@param[in] pRects		�����_�����O�^�[�Q�b�g���N���A����̈��������`�B</br>
		*						���̈�����NULL���w�肵���ꍇ�̓����_�����O�^�[�Q�b�g�S�̂��N���A�����B
		*@param[in]	Flags		�N���A����T�[�t�F�C�X�������t���O�B
		*@param[in]	Color		�����_�����O�^�[�Q�b�g�̃N���A�J���[�B32bit ARGB�B
		*@param[in]	Z			Z�o�b�t�@�̃N���A�l�B
		*@param[in]	Stencil		�X�e���V���o�b�t�@�̃N���A�l�B
		*/
		__inline void Clear(
			u32 Count,
			const D3DRECT  *pRects,
			u32 Flags,
			u32 Color,
			f32 Z,
			u32 Stencil);
		/*!
		* @brief	�r���[�|�[�g��ݒ�B�BIDirect3DDevice9::SetViewport�Ɠ����B
		*/
		__inline void SetViewport(const tkEngine::SViewport& viewport);
		/*!
		* @brief	�����_�[�X�e�[�g��ݒ�B
		*@param[in]	renderStateType		�ݒ肷�郌���_�����O�X�e�[�g�̎�ށB
		*@param[in]	value				�ݒ肷��l�B
		*/
		__inline void SetRenderState(ERenderStateType renderStateType, u32 value);
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

#include "tkEngine/graphics/tkRenderCommand.h"
namespace tkEngine {
	__inline void CRenderContext::SetVertexDeclaration(SVertexDecralation* vertexDecl)
	{
		SetRenderCommand(CRenderCommand_SetVertexDeclaration(vertexDecl));
	}
	__inline void CRenderContext::SetStreamSource(u32 streamNo, CVertexBuffer* pVB)
	{
		SetRenderCommand(CRenderCommand_SetStreamSource(
			0,
			pVB
			));
	}
	__inline void CRenderContext::SetIndices(CIndexBuffer* pIB)
	{
		SetRenderCommand(CRenderCommand_SetIndices(
			pIB
			));
	}
	__inline void CRenderContext::DrawIndexedPrimitive(CPrimitive* prim)
	{
		SetRenderCommand(CRenderCommand_DrawIndexedPrimitive(
			prim
			));
	}
	__inline void CRenderContext::Clear(
		u32 Count,
		const D3DRECT *pRects,
		u32 Flags,
		u32 Color,
		f32 Z,
		u32 Stencil
		)
	{
		SetRenderCommand(CRenderCommand_Clear(
			Count, 
			pRects, 
			Flags,
			Color, 
			Z, 
			Stencil
		));
	}
	__inline void CRenderContext::SetViewport(const tkEngine::SViewport& viewport)
	{
		SetRenderCommand(CRenderCommand_SetViewport(viewport));
	}
	__inline void CRenderContext::SetRenderState(ERenderStateType renderStateType, u32 value)
	{
		SetRenderCommand(CRenderCommand_SetRenderState(renderStateType, value));
	}
}


#endif // _TK_CRENDERCONTEXT_H_