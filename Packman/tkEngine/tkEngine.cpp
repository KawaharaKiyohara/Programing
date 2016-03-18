/*!
 * @brief	tkEngine
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	/*!
	 * @brief	�������B
	 */
	void Engine::Init(const InitParam& initParam)
	{
		m_initializer.reset( new EngineInitializerDX9 );
		m_finalizer.reset( new EngineFinalizerDX9 );
		m_initializer->Execute( initParam );
	}
	/*!
	* @brief	�Q�[�����[�v�����s�B
	*/
	void Engine::RunGameLoop()
	{

	}
	/*!
	 * @brief	�I�������B
	 */
	void Engine::Final()
	{
		m_finalizer->Execute();
		m_finalizer.reset();
		m_initializer.reset();
	}
}// namespace tkEngine
