/*!
 *@brief	ShapeVertex�B
 */

#ifndef _TKSHAPE_H_
#define _TKSHAPE_H_

namespace tkEngine{
	/*!
	 *@brief	�J���[�B
	 */
	struct SShapeVertex_PC{
		f32		pos[4];
		u32		color;
	}; 
	/*!
	*@brief	�J���[�{�@���B
	*/
	struct SShapeVertex_PNC {
		f32		pos[4];
		f32		normal[3];
		u32		color;	
	};
}
#endif // _TKSHAPE_H_