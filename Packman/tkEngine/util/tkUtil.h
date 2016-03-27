/*!
 * @brief	���[�e�B���e�B�֐��B
 */
#ifndef _TKUTIL_H_
#define _TKUTIL_H_

namespace tkEngine{
	class CUtil{
	public:
		/*!
		 * @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
		 */
		static u32 MakeHash( const c8* string )
		{
			u32 hash = 0;
			s32 l = strlen(string);
			for( s32 i = 0; i < l; i++ ){
				hash = hash * 37 + string[i];
			}
			return hash;
		}
	};
}

#endif // _TKUTIL_H_