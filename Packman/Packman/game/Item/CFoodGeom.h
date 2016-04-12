/*!
 *@brief	�H�ו��̌`��N���X�B
 */

#ifndef _CFOODGEOM_H_
#define _CFOODGEOM_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFoodGeom{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CFoodGeom();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~CFoodGeom();
	/*!
	 *@brief	�\�z�B
	 *@param[in]	radius		���a
	 */
	void Build( f32 radius );
private:
	tkEngine::CSphereShape	m_sphere;
};

#endif //_CFOODGEOM_H_