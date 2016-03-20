#ifndef TK_ENGINE_TYPEDEF_H
#define TK_ENGINE_TYPEDEF_H

/*!
 * @brief	��{�^�ʖ���`
 */

#include <climits>
#include <float.h>
typedef signed				char		s8;		//!< ��������8bit����
typedef unsigned			char		u8;		//!< �����Ȃ�8bit����
typedef signed				short		s16;	//!< ��������16bit����
typedef unsigned			short		u16;	//!< �����Ȃ�16bit����
typedef	signed		int					s32;	//!< ��������32bit����
typedef	unsigned	int					u32;	//!< ��������32bit����
typedef	signed		__int64				s64;	//!< ��������64bit����
typedef	unsigned	__int64				u64;	//!< ��������64bit����
typedef	const	signed		int			cs32;	//!< ��������32bit�����萔
typedef	const	unsigned	int			cu32;	//!< ��������32bit�����萔
typedef	const	signed		__int64		cs64;	//!< ��������64bit�����萔
typedef	const	unsigned	__int64		cu64;	//!< ��������64bit�����萔
typedef	volatile	signed		int		vs32;	//!< �s���� ��������32bit����
typedef	volatile	unsigned	int		vu32;	//!< �s���� ��������32bit����
typedef	volatile	signed		__int64	vs64;	//!< �s���� ��������64bit����
typedef	volatile	unsigned	__int64	vu64;	//!< �s���� ��������64bit����

// �ϐ��̌��E
static const s32 S32_MAX = INT_MAX; 				//!< ��������32bit�����̍ő�l
static const s32 S32_MIN = INT_MIN; 				//!< ��������32bit�����̍ŏ��l
static const u32 U32_MAX = UINT_MAX;				//!< ��������32bit�����̍ő�l
static const s64 S64_MAX = _I64_MAX;				//!< ��������64bit�����̍ő�l
static const s64 S64_MIN = _I64_MIN;				//!< ��������64bit�����̍ŏ��l
static const u64 U64_MAX = _UI64_MAX;				//!< ��������64bit�����̍ő�l

#endif // #ifndef TK_ENGINE_TYPEDEF_H
