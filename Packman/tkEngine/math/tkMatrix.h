/*!
 * @brief	�s��B
 */

#ifndef _TKMATRIX_H_
#define _TKMATRIX_H_

#include "tkEngine/math/tkVector.h"

namespace tkEngine{
	/*!
	 * @brief	�s��B
	 */
	class CMatrix{
	public:
		union {
			struct {
				f32 _11, _12, _13, _14;
				f32 _21, _22, _23, _24;
				f32 _31, _32, _33, _34;
				f32 _41, _42, _43, _44;
			};
			f32 m[4][4];
		};
		static const CMatrix Identity;	//!<�P�ʍs��B
	public:
		/*!
		* @brief	�v���W�F�N�V�����s����쐬�B
		*@param[in]	viewAngle	��p�B
		*@param[in]	aspect		�A�X�y�N�g��B
		*@param[in]	fNear		�ߕ��ʁB
		*@param[in]	fFar		�����ʁB
		*/
		void MakeProjectionMatrix(
			f32 viewAngle,
			f32 aspect,
			f32 fNear,
			f32 fFar
			)
		{
			D3DXMatrixPerspectiveFovRH(
				r_cast<D3DXMATRIX*>(this),
				viewAngle,
				aspect,
				fNear,
				fFar
			);
		}
		/*!
		 * @brief	�����_�A������A�J�����ʒu����J�����s����쐬�B
		 *@param[in]	position	�J�����ʒu�B
		 *@param[in]	target		�����_�B
		 *@param[in]	up			�J�����̏�����B
		 */
		void MakeLookAt( const CVector3& position, const CVector3& target, const CVector3& up )
		{
			D3DXMatrixLookAtRH(
				r_cast<D3DXMATRIX*>(this),
				r_cast<const D3DXVECTOR3*>(&position),
				r_cast<const D3DXVECTOR3*>(&target),
				r_cast<const D3DXVECTOR3*>(&up)
			);
		}
		/*!
		 *@brief	�s��ƍs��̏�Z
		 *@details
		 * �s��̌v�Z�����͐��w�̋L�q�ɏ�������B
		 * *this = m0 * m1
		 */
		void Mul( const CMatrix& m0, const CMatrix& m1 )
		{
			D3DXMatrixMultiply(
				r_cast<D3DXMATRIX*>(this),
				r_cast<const D3DXMATRIX*>(&m0),
				r_cast<const D3DXMATRIX*>(&m1)
			);
		}
		/*!
		 *@brief	�t�s����v�Z�B
		 *@param[in]	m	���ɂȂ�s��B
		 */
		void Inverse( const CMatrix& m )
		{
			D3DXMatrixInverse(
				r_cast<D3DXMATRIX*>(this),
				NULL,
				r_cast<const D3DXMATRIX*>(&m)
			);
		}
		
	};
};
#endif // _TKMATRIX_H_