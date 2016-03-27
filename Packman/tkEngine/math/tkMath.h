/*!
 * @brief	���w�֌W�F�X�B
 */

#ifndef _TK_MATH_H_
#define _TK_MATH_H_

namespace tkEngine{
	class CMath{
	public:
		static const f32 PI;
		/*!
		 * @brief	degree����radian�ɕϊ��B
		 */
		static f32 DegToRad( f32 deg )
		{
			return deg * (PI/180.0f);
		}
		/*!
		 * @brief	radian����degree�ɕϊ��B
		 */
		static f32 RadToDeg( f32 rad )
		{
			return rad / (PI/180.0f);
		}
	};
}

#endif //_TK_MATH_H_