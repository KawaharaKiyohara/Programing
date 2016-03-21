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
	public:
		CRenderCommand_Clear() :
			CRenderCommandBase(eRendeCommand_Clear)
		{
		}
		void Execute( LPDIRECT3DDEVICE9 pD3DDevice )
		{
		}
	};
};
#endif // _TKRENDERCOMMAND_H_