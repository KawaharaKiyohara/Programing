/*!
 *@brief	�`��G���W��
 */

#pragma once


#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"

namespace tkEngine{
	
	 
	/*!
	*@brief	�`��G���W���B
	*@details
	* 2017/08/03 release notes
	* 	tkEngine�̕`��G���W����forward+�Ŏ�������Ă���B
	* 	�V�[���̕`��菇�͉��L�ƂȂ�B
	*  	.1 �v�������_�����O
	*     		1-1 ZPrepass
	*	   		1-2 LightCulling
	*  	.2 ���f���`��
	*  	.3 �|�X�g�G�t�F�N�g
	* forward+�̗̍p�ɂ��A��ʂ̓��I�����������Ɉ������Ƃ��ł���B
	* ���I�����͍ő��1024�ݒu���邱�Ƃ��ł���B�G���W�����J�X�^�}�C�Y���邱�ƂŊg�����\�B
	* �Ǝ��̃��f���V�F�[�_�[���L�q����ꍇ�͉��L�̒��ӂ��K�v�ł��B
	*    t���W�X�^��100�Ԉȍ~��b���W�X�^��1�Ԃ̓G���W�����g�p���Ă��邽�߁A�g���Ă͂Ȃ�Ȃ��B
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
		* @brief	�V���h�E�}�b�v���擾�B
		*/
		CShadowMap& GetShadowMap()
		{
			return m_preRender.GetShadowMap();
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
		/*!
		* @brief	�v�������_�����O�擾�B�B
		*/
		CPreRender& GetPreRender()
		{
			return m_preRender;
		}
		/*!
		* @brief	�|�X�g�G�t�F�N�g���擾�B
		*/
		CPostEffect& GetPostEffect()
		{
			return m_postEffect;
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
		/*!
		*@brief	GPU�C�x���g�J�n�B
		*@param[in]		eventName		�C�x���g�̖��O�B
		*/
		void BeginGPUEvent(const wchar_t* eventName)
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			if (m_userAnnoation) {
				m_userAnnoation->BeginEvent(eventName);
			}
#endif
		}
		/*!
		*@brief	GPU�C�x���g�I���B
		*/
		void EndGPUEvent()
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			if (m_userAnnoation) {
				m_userAnnoation->EndEvent();
			}
#endif
		}
	private:
		ID3D11Device*			m_pd3dDevice = nullptr;						//!<D3D11�f�o�C�X�B
		CRenderContext			m_renderContext;							//!<�����_�����O�R���e�L�X�g�B
		ID3D11DeviceContext*	m_pImmediateContext = nullptr;				//!<D3D11�����f�o�C�X�R���e�L�X�g�B
		IDXGISwapChain*			m_pSwapChain = nullptr;						//!<SwapChain�B
		int						m_currentMainRenderTarget = 0;				//!<���݂̃��C�������_�����O�^�[�Q�b�g�B
		CRenderTarget			m_mainRenderTarget[2];						//!<���C�������_�����O�^�[�Q�b�g�B
		CPreRender				m_preRender;								//!<�v�������_�����O�B
		CPostEffect				m_postEffect;								//!<�|�X�g�G�t�F�N�g�B
		CCamera					m_mainCamera;								//!<���C���J�����B
		int						m_frameBufferWidth = 0;						//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		int						m_frameBufferHeight = 0;					//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<�h���C�o�̎�ނ̃I�v�V�����B
		D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;	//!<Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
		CLightManager			m_lightManager;								//!<���C�g�̊Ǘ��ҁB

		ID3DUserDefinedAnnotation* m_userAnnoation = nullptr;
	};
}