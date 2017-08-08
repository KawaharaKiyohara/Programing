/*!
 *@brief	�`��G���W��
 */

#pragma once


#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"

namespace tkEngine{
	/*!
	 *@brief	�`��G���W���B
	 */
	class CGraphicsEngine : Noncopyable{
	public:
		CGraphicsEngine();
		~CGraphicsEngine();
		/*!
		* @brief	�������B
		*/
		bool Init(HWND hwnd, const SInitParam& initParam);
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		* @brief	ZPrepass�̎擾�B
		*/
		CZPrepass& GetZPrepass()
		{
			return m_preRender.GetZPrepass();
		}
		/*!
		*@brief	���C���J�������擾�B
		*/
		CCamera& GetMainCamera()
		{
			return m_mainCamera;
		}
		/*!
		*@brief	Direct3DDevice�̎擾�B
		*/
		ID3D11Device* GetD3DDevice() const
		{
			return m_pd3dDevice;
		}
		/*!
		*@brief	ID3D11DeviceContext�̎擾�B
		*/
		ID3D11DeviceContext* GetD3DDeviceContext() const
		{
			return m_pImmediateContext;
		}
		/*!
		*@brief		�t���[���o�b�t�@�̕����擾�B
		*/
		int GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/*!
		*@brief		�t���[���o�b�t�@�̍������擾�B
		*/
		int GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/*!
		* @brief	���C�������_�����O�^�[�Q�b�g��؂�ւ��B
		*/
		void ToggleMainRenderTarget()
		{
			m_currentMainRenderTarget ^= 1;
		}
		/*!
		* @brief	���C�������_�����O�^�[�Q�b�g�̎擾�B
		*/
		CRenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget[m_currentMainRenderTarget];
		}
		/*!
		* @brief	�`��J�n�B
		*/
		void BeginRender();
		/*!
		* @brief	�`��I���B
		*/
		void EndRender();
		CPreRender& GetPreRender()
		{
			return m_preRender;
		}
		CRenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/*!
		*@brief	���C�g�̊Ǘ��҂��擾�B
		*/
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}
	private:
		ID3D11Device*			m_pd3dDevice = nullptr;						//!<D3D11�f�o�C�X�B
		CRenderContext			m_renderContext;							//!<�����_�����O�R���e�L�X�g�B
		ID3D11DeviceContext*	m_pImmediateContext = nullptr;				//!<D3D11�����f�o�C�X�R���e�L�X�g�B
		IDXGISwapChain*			m_pSwapChain = nullptr;						//!<SwapChain�B
		int						m_currentMainRenderTarget = 0;				//!<���݂̃��C�������_�����O�^�[�Q�b�g�B
		CRenderTarget			m_mainRenderTarget[2];						//!<���C�������_�����O�^�[�Q�b�g�B
		CPreRender				m_preRender;								//!<�v�������_�����O�B
		CCamera					m_mainCamera;								//!<���C���J�����B
		int						m_frameBufferWidth = 0;						//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		int						m_frameBufferHeight = 0;					//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<�h���C�o�̎�ނ̃I�v�V�����B
		D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;	//!<Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
		CLightManager			m_lightManager;								//!<���C�g�̊Ǘ��ҁB
	};
}