/*!
 * @brief	DX9�����̃G���W��������
 */

#ifndef _TKENGINEINITIALIZERDX9_H_
#define _TKENGINEINITIALIZERDX9_H_

#include "tkEngine\tkEngine.h"

namespace tkEngine{
	/*!
	 * @brief	DX9�����̃G���W���̏���������
	 */
	class EngineInitializerDX9 : public IEngineInitializer{
	public:
		EngineInitializerDX9()
		{
		}
		~EngineInitializerDX9()
		{
		}
		/*!
		 * @brief	�����������̎��s
		 */
		void Execute( const InitParam& initParam ) final;
	};
}

#endif // _TKENGINEINITIALIZERDX9_H_

