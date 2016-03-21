/*!
 *@brief	�����_�����O�R�}���h
 */

#ifndef _TKRENDERCOMMAND_H_
#define _TKRENDERCOMMAND_H_


namespace tkEngine{
	/*!
	 *@brief	�����_�����O�R�}���h�̃^�C�v
	 */
	enum ERenderCommand{
		eRendeCommand_Clear,	//!<�N���A
		eRenderCommand_Undef
	};
	/*!
	 *@brief	�����_�����O�R�}���h�̊��N���X�B
	 */
	class CRenderCommandBase{
	private:
		ERenderCommand m_commandType;
	public:
		/*!
		 *@brief	�R���X�g���N�^
		 */
		CRenderCommandBase(ERenderCommand commandType ) :
			m_commandType(commandType)
		{
			
		}
		/*!
		 *@brief	�^�����擾
		 */
		ERenderCommand GetType() const
		{
			return m_commandType;
		}
	};
	/*!
	 *@brief	�N���A�̃����_�����O�R�}���h�B
	 */
	class CRenderCommand_Clear : public CRenderCommandBase {
	private:
		DWORD m_Count;
		const D3DRECT *m_pRects;
		DWORD m_Flags;
		D3DCOLOR m_Color;
		float m_Z;
		DWORD m_Stencil;
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 *@details
		 * �����̈Ӗ���IDirect3DDevice9::Clear�Ɠ����B�ڍׂ�MSDN�w���v���Q�Ƃ��Ă��������B
		 */
		CRenderCommand_Clear( 
			DWORD Count,
			const D3DRECT *pRects,
			DWORD Flags,
			D3DCOLOR Color,
			float Z,
			DWORD Stencil

		) :
			CRenderCommandBase(eRendeCommand_Clear),
			m_Count(Count),
			m_pRects(pRects),
			m_Flags(Flags),
			m_Color(Color),
			m_Z(Z),
			m_Stencil(Stencil)
		{
		}
		void Execute( LPDIRECT3DDEVICE9 pD3DDevice )
		{
			pD3DDevice->Clear(m_Count, m_pRects, m_Flags, m_Color, m_Z, m_Stencil);
		}
	};
};
#endif // _TKRENDERCOMMAND_H_