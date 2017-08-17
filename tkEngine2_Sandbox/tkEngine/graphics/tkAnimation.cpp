/*!
 * @brief	�A�j���[�^�[�N���X�B
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimation.h"

namespace tkEngine{
	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
	}
	void CAnimation::Init(CSkinModelData& skinModelData)
	{
		std::vector<CAnimationClipPtr>& animClips = skinModelData.GetAnimationClips();
		for(auto& clip : animClips){
			m_animationClips.push_back(clip.get());
		}
		m_skeleton = &skinModelData.GetSkeleton();
	}
	/*!
	* @brief	�A�j���[�V������i�߂�B
	*@param[in]	deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)�B
	*/
	void CAnimation::Update(float deltaTime)
	{
		if (m_currentAnimationClip == nullptr 
			|| m_skeleton == nullptr 
		) {
			return;
		}
		//�Ƃ肠�����K���ɐi�߂Ă����B
		int numBones = m_skeleton->GetNumBones();
		const auto& topBoneKeyFrameList = m_currentAnimationClip->GetTopBoneKeyFrameList();
		m_globalTime += deltaTime;
		while (true) {
			if (m_currentKeyframeNo >= topBoneKeyFrameList.size()) {
				//�I�[�܂ōs�����B
				if (m_currentAnimationClip->IsLoop()) {
					//���[�v�B
					m_currentKeyframeNo = 0;
					m_globalTime = 0.0f;
				}
				else {
					//�����V���b�g�Đ��B
					m_currentKeyframeNo--;
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyframeNo)->time >= m_globalTime) {
				//�I���B
				break;
			}
			//���ցB
			m_currentKeyframeNo++;
		}
		//�X�P���g���ɔ��f�����Ă����B
		//�Ƃ肠�����e�X�g�f�[�^�̓t���L�[�Ȃ̂ŉ����l���Ȃ��Ă悳���B
		const auto& keyFramePtrListArray = m_currentAnimationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray) {
			if (keyFrameList.size() == 0) {
				continue;
			}
			//���ݍĐ����̃L�[�t���[��������Ă���B
			Keyframe* keyframe = keyFrameList.at(m_currentKeyframeNo);
			m_skeleton->SetBoneLocalMatrix(
				keyframe->boneIndex, 
				keyframe->transform
			);
		}
	}
}