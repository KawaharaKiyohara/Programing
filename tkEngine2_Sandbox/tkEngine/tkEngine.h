/*!
 *@brief	�G���W���B
 */
#pragma once

#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/timer/tkStopwatch.h"
#include "tkEngine/Sound/tkSoundEngine.h"
#include "tkEngine/graphics/tkGraphicsEngine.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"

namespace tkEngine{
	/*!
	 *@brief	�G���W���B
	 */
	class CEngine : Noncopyable {
	private:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CEngine();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CEngine();
	public:
		/*!
		 *@brief	�������B
		 *@param[in]	initParam		�������p�����[�^�B
		 */
		bool Init( const SInitParam& initParam );
		/*!
		 *@brief	�I�������B
		 */
		void Final();
		/*!
		 *@brief	�Q�[�����[�v�����s�B
		 */
		void RunGameLoop();
		/*!
		 *@brief	�C���X�^���X���擾�B
		 */
		static CEngine& GetInstance()
		{
			static CEngine* instance = nullptr;
			if(instance == nullptr){
				instance = new CEngine;
			}
			return *instance;
		}
		
		/*!
		* @brief	�Q�[���p�b�h�̎擾�B
		*@param[in]	padNo	�p�b�h�ԍ�
		*/
		CPad& GetPad(int padNo)
		{
			TK_ASSERT(padNo < CPad::CONNECT_PAD_MAX && padNo >= 0, "padNo is invalid");
			return m_pad[padNo];
		}
		/*!
		* @brief	�T�E���h�G���W���̎擾�B
		*/
		CSoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		/*!
		* @brief	�O���t�B�b�N�X�G���W���̎擾�B
		*/
		CGraphicsEngine& GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/*!
		* @brief	ZPrepass�̎擾�B
		*/
		CZPrepass& GetZPrepass()
		{
			return m_graphicsEngine.GetZPrepass();
		}
		
		/*!
		*@brief	���C���J�������擾�B
		*/
		CCamera& GetMainCamera()
		{
			return m_graphicsEngine.GetMainCamera();
		}
		/*!
		*@brief	���C�g�̊Ǘ��҂��擾�B
		*/
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}
	private:
		/*!
		 *@brief	�E�B���h�E�������B
		 */
		bool InitWindow( const SInitParam& initParam );

		/*!
		* @brief	�E�B���h�E�v���V�[�W���B
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		/*!
		* @brief	�X�V�B
		*/
		void Update();
	private:
		HINSTANCE				m_hInst = nullptr;	//!<�A�v���P�[�V�����̃C���X�^���X�B
		HWND					m_hWnd = nullptr;	//!<�E�B���h�E�n���h���B
		CGraphicsEngine			m_graphicsEngine;							//!<�O���t�B�b�N�G���W���B
		CSoundEngine			m_soundEngine;								//!<�T�E���h�G���W���B
		CLightManager			m_lightManager;								//!<���C�g�̊Ǘ��ҁB
		int						m_screenWidth = 0;							//!<�X�N���[���̕��B
		int						m_screenHeight = 0;							//!<�X�N���[���̍����B
		CPad					m_pad[CPad::CONNECT_PAD_MAX];				//!<�Q�[���p�b�h�B
	public:
		CStopwatch				m_sw;
	};

	/*!
	* @brief	Engine�̃C���X�^���X���擾�B
	*/
	static inline CEngine& Engine()
	{
		return CEngine::GetInstance();
	}
	/*!
	* @brief	CPad�̃C���X�^���X���擾�B
	*/
	static inline CPad& Pad(int padNo)
	{
		return Engine().GetPad(padNo);
	}
	/*!
	* @brief	CSoundEngine�̃C���X�^���X���擾�B
	*/
	static inline CSoundEngine& SoundEngine()
	{
		return Engine().GetSoundEngine();
	}
	/*!
	* @brief	CGraphicsEngine�̃C���X�^���X���擾�B
	*/
	static inline CGraphicsEngine& GraphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
	/*!
	* @brief	���C���J�����̃C���X�^���X���擾�B
	*/
	static inline CCamera& MainCamera()
	{
		return GraphicsEngine().GetMainCamera();
	}
	/*!
	* @brief	CLightManager�̃C���X�^���X���擾�B
	*/
	static inline CLightManager& LightManager()
	{
		return Engine().GetLightManager();
	}
	
}