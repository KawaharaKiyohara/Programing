/*!
 * @brief	�o�l�J�����B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/camera/tkSpringCamera.h"

namespace tkEngine{
	namespace {
		float dampingK = 35.0f;
		float dampingRate = 1.0f;
		/*!
		* @brief	�o�l�������g�p���āA���݂̈ʒu�A�ڕW�ƂȂ�ʒu�A���x�A�����x����V�����ʒu���v�Z����B
		*/
		CVector3 CalcSpring( 
			const CVector3& positionNow, 
			const CVector3& positionTarget, 
			CVector3& moveSpeed ,
			float maxMoveSpeed
		)
		{
			//���݂̈ʒu�ƖڕW�̈ʒu�Ƃ̍��������߂�B
			CVector3 distance;
			distance.Subtract( positionTarget, positionNow );
			
			CVector3 springAccel;
			springAccel = distance;
			
			float t = dampingK / (2.0f * dampingRate);
			float springK = t * t;
			springAccel.Scale(springK);
			//�����x������B
			CVector3 vt = moveSpeed;
			vt.Scale(dampingK);
			springAccel.Subtract(vt);
			
			springAccel.Scale(GameTime().GetFrameDeltaTime());
			moveSpeed.Add(springAccel);
			if (moveSpeed.LengthSq() > maxMoveSpeed*maxMoveSpeed) {
				//�ō����x��葬���Ȃ��Ă��܂����B
				moveSpeed.Normalize();
				moveSpeed.Scale(maxMoveSpeed);
			}
			CVector3 newPos = positionNow;
			CVector3 addPos = moveSpeed;
			addPos.Scale(GameTime().GetFrameDeltaTime());
			if (moveSpeed.LengthSq() > maxMoveSpeed*maxMoveSpeed) {
				//�ō����x��葬���Ȃ��Ă��܂����B
				moveSpeed.Normalize();
				moveSpeed.Scale(maxMoveSpeed);
			}
			newPos.Add(addPos);
			return newPos;
		}
	}
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CSpringCamera::CSpringCamera()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^
	 */
	CSpringCamera::~CSpringCamera()
	{
	}
	/*!
	* @brief	�������B
	*/
	void CSpringCamera::Init(const CVector3& target, const CVector3& position, float maxMoveSpeed)
	{
		m_camera.SetTarget(target);
		m_camera.SetPosition(position);
		m_target = target;
		m_position = position;
		m_targetMoveSpeed = CVector3::Zero;
		m_positionMoveSpeed = CVector3::Zero;
		m_maxMoveSpeed = maxMoveSpeed;
	}
	/*!
	 * @brief	�X�V�B
	 */
	void CSpringCamera::Update()
	{
		CVector3 target = CalcSpring(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed);
		CVector3 position = CalcSpring(m_camera.GetPosition(), m_position,  m_positionMoveSpeed, m_maxMoveSpeed);
		m_camera.SetTarget(target);
		m_camera.SetPosition(position);
		m_camera.Update();
	}
}