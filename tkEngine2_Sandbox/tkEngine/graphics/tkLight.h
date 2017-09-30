/*!
 *@brief	�e�탉�C�g
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�f�B���N�V�������C�g�B
	 */
	struct SDirectionLight{
		CVector4	color;			//!<���C�g�̃J���[�B
		CVector3	direction;		//!<���C�g�̕����B
	};
	/*!
	 *@brief	�A���r�G���g���C�g�B
	 */
	struct SAmbientLight{
		CVector3	color;			//!<���C�g�̃J���[�B
	};
	/*!
	 *@brief	�|�C���g���C�g�B
	 *@details
	 * ���̃p�����[�^��ύX������ALightCulling.fx��modelStruct.h��ύX����悤�ɁB
	 */
	struct SPointLight{
		CVector3	position;		//!<�ʒu�B
		CVector3	positionInView;	//!<�r���[��Ԃł̍��W�B
		CVector4	color;			//!<���C�g�̃J���[�B
		CVector4	attn;			//!<�����萔�B
	};
}