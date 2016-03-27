/*!
 * @brief	�x�N�g��
 */

#ifndef _TKVECTOR_H_
#define _TKVECTOR_H_


namespace tkEngine{
	/*!
	 * @brief	�x�N�g���B
	 */
	class CVector3{
	public:
		union{
			struct { float x, y, z; };
			float v[3];
		};
		static const CVector3 Zero;
		static const CVector3 Right;
		static const CVector3 Left;
		static const CVector3 Up;
		static const CVector3 Down;
		static const CVector3 Front;
		static const CVector3 Back;
		static const CVector3 AxisX;
		static const CVector3 AxisY;
		static const CVector3 AxisZ;
	public:
		operator D3DXVECTOR3(void) { return s_cast<D3DXVECTOR3>(*this); }
		/*!
		* @brief	�x�N�g���̊e�v�f��ݒ�B
		*/
		void Set(f32 x, f32 y, f32 z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		/*!
		 * @brief	�x�N�g�������Z�B
		 */
		void Add(const CVector3& v) 
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}
		void Add( const CVector3& v0, const CVector3& v1 )
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
		}
		/*!
		 * @brief	�x�N�g�������Z�B
		 */
		void Subtract( const CVector3& v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		void Subtract( const CVector3& v0, const CVector3& v1 )
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
		}
		/*!
		 * @brief	���ρB
		 */
		float Dot( const CVector3& v )
		{
			return x * v.x + y * v.y + z * v.z;
		}
		/*!
		 * @brief	�O�ρB
		 */
		void Cross(const CVector3& v)
		{
			f32 _x = ( x * v.z ) - ( v.y * z );
			f32 _y = ( z * v.x ) - ( v.z * x );
			f32 _z = ( x * v.y ) - ( v.x * y );
			x = _x;
			y = _y;
			z = _z;
		}
		void Cross(const CVector3& v0, const CVector3& v1)
		{
			f32 _x = ( v0.y * v1.z ) - ( v1.y * v0.z );
			f32 _y = ( v0.z * v1.x ) - ( v1.z * v0.x );
			f32 _z = ( v0.x * v1.y ) - ( v1.x * v0.y );
			x = _x;
			y = _y;
			z = _z;
		}
		/*!
		 * @brief	�������擾
		 */
		float Length()
		{
			return sqrt(LengthSq());
		}
		/*!
		 * @brief	�����̓����擾
		 */
		float LengthSq()
		{
			return x * x + y * y + z * z;
		}
	};
}
#endif // _TKVECTOR_H_