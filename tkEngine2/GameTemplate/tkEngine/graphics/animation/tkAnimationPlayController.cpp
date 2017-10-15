/*!
 * @brief	�A�j���[�V�����Đ��R���g���[���B
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationPlayController.h"


namespace tkEngine{
	
	/*!
	*@brief	�������B
	*/
	void CAnimationPlayController::Init(CSkeleton* skeleton)
	{
		int numBones = skeleton->GetNumBones();
		//�{�[���s����o�V�b�Ɗm�ہB
		m_boneMatrix.resize(numBones);
	}
	/*!
	 * @brief	�A�j���[�V������i�߂�B
	 *@param[in]	deltaTime		�A�j���[�V������i�߂鎞�ԁB
	 */
	void CAnimationPlayController::Update(float deltaTime)
	{
		if(m_animationClip == nullptr){
			TK_WARNING("m_animationClip is nullptr\n");
			return ;
		}
		const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();
		m_time += deltaTime;
		//�⊮���Ԃ��i�߂Ă����B
		m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
		while (true) {
			if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size()) {
				//�I�[�܂ōs�����B
				if (m_animationClip->IsLoop()) {
					//���[�v�B
					m_currentKeyFrameNo = 0;
					m_time = 0.0f;
				}
				else {
					//�����V���b�g�Đ��B
					m_currentKeyFrameNo--;
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time) {
				//�I���B
				break;
			}
			//���ցB
			m_currentKeyFrameNo++;
		}
		//�{�[���s����v�Z���Ă����B
		const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray) {
			if (keyFrameList.size() == 0) {
				continue;
			}
			//���ݍĐ����̃L�[�t���[��������Ă���B
			Keyframe* keyframe = keyFrameList.at(m_currentKeyFrameNo);
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
		
	}
}