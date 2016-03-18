/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

namespace tkEngine{
	/*!
	 * @brief	�������p�̃p�����[�^�B
	 */
	struct InitParam{
#if defined(TK_PLATFORM_DX9)
		HINSTANCE hInstance;
#else //#if defined(TK_PLATFORM_DX9)
 #error "�T�|�[�g����Ă��Ȃ��v���b�g�t�H�[���ł��B"
#endif //
	};
	/*!
	 * @brief	�G���W���������̃C���^�[�t�F�[�X�B
	 */
	class IEngineInitializer : Noncopyable{
	public:
		IEngineInitializer(){}
		virtual ~IEngineInitializer(){}
		/*!
		 * @brief	�����������̎��s�B
		 */
		virtual void Execute( const InitParam& initParam ) = 0;
	};
	
	/*!
	 * @brief	�G���W���̏I�������̃C���^�[�t�F�[�X�B
	 */
	class IEngineFinalizer : Noncopyable{
	public:
		IEngineFinalizer() {}
		virtual ~IEngineFinalizer() {}
		/*!
		 * @brief	�I�������̎��s�B
		 */
		virtual void Execute() = 0;
	};
	/*!
	 * @brief	�G���W���B
	 */
	class Engine : Noncopyable {
		Engine() {}
		~Engine() {}
	public:
		/*!
		 * @brief	�������B
		 *@param[in]	�������p�����[�^
		 */
		void Init( const InitParam& initParam );
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
		static Engine* GetInstance()
		{
			static Engine instance;
			return &instance;
		}
	private:
		std::unique_ptr<IEngineInitializer>	m_initializer;	//!<�����������B
		std::unique_ptr<IEngineFinalizer>	m_finalizer;	//!<�I�������B
	};
	
}

#if defined(TK_PLATFORM_DX9)
	#include "tkEngine/Platform/DX9/tkEngineInitializerDX9.h"
	#include "tkEngine/Platform/DX9/tkEngineFinalizerDX9.h"
#else // #if defined(TK_PLATFORM_DX9)

#error "�Ή�����Ă��Ȃ��v���b�g�t�H�[���ł��B"
#endif //#if defined(TK_PLATFORM_DX9)
#endif // _TKENGINE_TKENGINE_H_
