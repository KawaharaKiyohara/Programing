/*!
 *@brief	AABB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/math/tkAabb.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CAabb::CAabb()
	{
	}
	/*!
	 *@brief	�������B
	 */
	void CAabb::Init(const CVector3& centerPosition, const CVector3& halfSize)
	{
		Update(centerPosition, halfSize);
	}
	/*!
	 *@brief	�X�V�B
	 *@param[in]	centerPosition		���S���W�B
	 */
	void CAabb::Update( const CVector3& centerPosition, const CVector3& halfSize)
	{
	}
}