/*!
 *@brief	�O���t�B�b�N�X�֌W�̌^��`
 */
 
#ifndef _TKGRAPHICSTYPE_H_
#define _TKGRAPHICSTYPE_H_

namespace tkEngine{
	/*!
	 *@brief	�r���[�|�[�g�B
	 */
	struct SViewport{
		u32		x;		//!<�r���[�|�[�g�̍����x���W(�X�N���[�����W�n)
		u32		y;		//!<�r���[�|�[�g�̍����y���W(�X�N���[�����W�n)
		u32		width;	//!<�r���[�|�[�g�̕��B
		u32		height;	//!<�r���[�|�[�g�̍����B
		f32		minZ;	//!<�ߕ��ʁB
		f32		maxZ;	//!<�����ʁB
	};
}

#endif //_TKGRAPHICSTYPE_H_