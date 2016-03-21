/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

#include "tkEngine/graphics/tkRenderContext.h"

namespace tkEngine{
	/*!
	 * @brief	�������p�̃p�����[�^�B
	 */
	struct SInitParam{
		HINSTANCE 	hInstance;
		u8 			gameObjectPrioMax;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l(255�܂�)
		u32 		numRenderContext;		//!<�����_�����O�R���e�L�X�g�̐�
		u32*		commandBufferSizeTbl;	//!<�R�}���h�o�b�t�@�̃T�C�Y�̃e�[�u���B�����_�����O�R���e�L�X�g�̃T�C�Y���K�v�B
	};
	
	/*!
	 * @brief	�G���W���B
	 */
	class CEngine : Noncopyable {
		CEngine() : 
			m_hWnd(NULL),
			m_pD3D(NULL),
			m_pD3DDevice(NULL)
		{}
		~CEngine() {}
	public:
		/*!
		 * @brief	�������B
		 *@param[in]	�������p�����[�^
		 *@retval	true	�������ɐ����B
		 *@retval	false	�������Ɏ��s�B
		 */
		bool Init( const SInitParam& initParam );
		/*!
		 * @brief	�I�������B
		 */
		void Final();
		/*!
		 * @brief	�Q�[�����[�v�����s�B
		 */
		void RunGameLoop();
		/*!
		 * @brief	�C���X�^���X�̎擾�B
		 */
		static CEngine& GetInstance()
		{
			static CEngine instance;
			return instance;
		}
	private:
		/*!
		* @brief	�E�B���h�E�������B
		* @retval	true	�������ɐ����B
		* @retval	false	�������Ɏ��s�B
		*/
		bool InitWindow();
		/*!
		* @brief	DirectX�̏������B
		* @retval	true	�������ɐ����B
		* @retval	false	�������Ɏ��s�B
		*/
		bool InitDirectX();
		/*!
		* @brief	�E�B���h�E�v���V�[�W���B
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND								m_hWnd;					//!<�E�B���h�E�n���h���B
		LPDIRECT3D9							m_pD3D;					//!<D3DDevice
		LPDIRECT3DDEVICE9					m_pD3DDevice;			//!<Rendering device
		std::unique_ptr<CRenderContext[]>	m_renderContextArray;	//!<�����_�����O�R���e�L�X�g
		u32									m_numRenderContext;		//!<�����_�����O�R���e�L�X�g�̐��B
	};
	
}

#endif // _TKENGINE_TKENGINE_H_
