/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

#include "tkEngine/graphics/tkRenderContext.h"
#include "tkEngine/graphics/tkEffectManager.h"
#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/graphics/tkPrimitive.h"
namespace tkEngine{
	/*!
	* @brief	�`��D�悲�ƂɑΉ����郌���_�����O�R���e�L�X�g�̔ԍ��̃}�b�v���`���邽�߂̍\���́B
	*/
	struct SRenderContextMap {
		u8	startPrio;			//!<�J�n�v���C�I���e�B
		u32 renderContextNo;	//!<�����_�����O�R���e�L�X�gNo
	};
	/*!
	 * @brief	�������p�̃p�����[�^�B
	 */
	struct SInitParam{
		SInitParam()
		{
			memset(this, 0, sizeof(SInitParam));
		}
		HINSTANCE 			hInstance;
		u8 					gameObjectPrioMax;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l(255�܂�)
		u32 				numRenderContext;		//!<�����_�����O�R���e�L�X�g�̐��B���̐���2�ȏ�̏ꍇ�ArenderContextMap�̎w�肪�K���K�v�ɂȂ�܂��B
		u32*				commandBufferSizeTbl;	//!<�R�}���h�o�b�t�@�̃T�C�Y�̃e�[�u���B�����_�����O�R���e�L�X�g�̃T�C�Y���K�v�B
		SRenderContextMap*	renderContextMap;		//!<�`��D�悲�ƂɑΉ����郌���_�����O�R���e�L�X�g�̔ԍ��̃}�b�v�BnumRenderContext��1�̏ꍇ�͖��������B
		u32					screenWidth;			//!<�X�N���[���̕��B
		u32					screenHeight;			//!<�X�N���[���̍����B
		u32					frameBufferWidth;		//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		u32					frameBufferHeight;		//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
	};
	
	/*!
	 * @brief	�G���W���B
	 */
	class CEngine : Noncopyable {
		CEngine() : 
			m_hWnd(nullptr),
			m_pD3D(nullptr),
			m_pD3DDevice(nullptr),
			m_frameBufferHeight(0),
			m_frameBufferWidth(0),
			m_screenHeight(0),
			m_screenWidth(0),
			m_numRenderContext(0),
			m_pTransformedPrimEffect(nullptr)
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
		static CEngine& Instance()
		{
			static CEngine instance;
			return instance;
		}
		/*!
		* @brief	�G�t�F�N�g�}�l�[�W���̎擾�B
		*/
		static CEffectManager& EffectManager()
		{
			return Instance().m_effectManager;
		}
		/*!
		 *@brief	Direct3DDevice�̎擾�B
		 */
		LPDIRECT3DDEVICE9 GetD3DDevice() const
		{
			return m_pD3DDevice;
		}
		/*!
		*@brief		�X�N���[���̕����擾
		*/
		u32 GetScreenWidth() const
		{
			return m_screenWidth;
		}
		/*!
		*@brief		�X�N���[���̍������擾
		*/
		u32 GetScreenHeight() const
		{
			return m_screenHeight;
		}
		/*!
		*@brief		�t���[���o�b�t�@�̕����擾�B
		*/
		u32 GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/*!
		*@brief		�t���[���o�b�t�@�̍������擾�B
		*/
		u32 GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
	private:
		/*!
		* @brief	���C�������_�����O�^�[�Q�b�g�̓��e���o�b�N�o�b�t�@�ɃR�s�[�B
		*/
		void CopyMainRenderTargetToBackBuffer(CRenderContext& renderContext);
		/*!
		* @brief	�E�B���h�E�������B
		* @retval	true	�������ɐ����B
		* @retval	false	�������Ɏ��s�B
		*/
		bool InitWindow(const SInitParam& initParam);
		/*!
		* @brief	DirectX�̏������B
		* @retval	true	�������ɐ����B
		* @retval	false	�������Ɏ��s�B
		*/
		bool InitDirectX(const SInitParam& initParam);
		/*!
		* @brief	���C�������_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɃR�s�[����Ƃ��Ɏg���v���~�e�B�u���������B
		*/
		void InitCopyBackBufferPrimitive();
		/*!
		* @brief	�E�B���h�E�v���V�[�W���B
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND									m_hWnd;						//!<�E�B���h�E�n���h���B
		LPDIRECT3D9								m_pD3D;						//!<D3DDevice
		LPDIRECT3DDEVICE9						m_pD3DDevice;				//!<Rendering device
		std::unique_ptr<CRenderContext[]>		m_renderContextArray;		//!<�����_�����O�R���e�L�X�g
		u32										m_numRenderContext;			//!<�����_�����O�R���e�L�X�g�̐��B
		std::unique_ptr<SRenderContextMap[]>	m_renderContextMap;			//!<�����_�����O�R���e�L�X�g�̃}�b�v�B
		CEffectManager							m_effectManager;			//!<�G�t�F�N�g�}�l�[�W���B
		u32										m_screenWidth;				//!<�X�N���[���̕��B
		u32										m_screenHeight;				//!<�X�N���[���̍����B
		u32										m_frameBufferWidth;			//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		u32										m_frameBufferHeight;		//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		CRenderTarget							m_mainRenderTarget;			//!<���C�������_�����O�^�[�Q�b�g
		CEffect*								m_pTransformedPrimEffect;	//!<�g�����X�t�H�[���ς݃v���~�e�B�u��`�悷�邽�߂̃G�t�F�N�g�B
		CPrimitive								m_copyBackBufferPrim;		//!<���C�������_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɃR�s�[����Ƃ��Ɏg���v���~�e�B�u�B
		CRenderTarget							m_backBufferRT;				//!<�o�b�N�o�b�t�@�̃����_�����O�^�[�Q�b�g�B
	};
	
}

#endif // _TKENGINE_TKENGINE_H_
