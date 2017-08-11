/*!
 * @brief	�A�j���[�^�[�N���X�B
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimator.h"

namespace tkEngine{
	CAnimator::CAnimator()
	{
	}
	CAnimator::~CAnimator()
	{
	}
	void CAnimator::Init(CSkinModelData& skinModelData)
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
	void CAnimator::Progress(float deltaTime)
	{
		if (m_currentAnimationClip == nullptr 
			|| m_skeleton == nullptr 
		) {
			return;
		}
		//�Ƃ肠�����K���ɐi�߂Ă����B
		int numBones = m_skeleton->GetNumBones();
		const auto& keyFramePtrListArray = m_currentAnimationClip->GetKeyFramePtrListArray();
		const auto& topBoneKeyFrameList = keyFramePtrListArray.at(0);
		m_globalTime += deltaTime;
		while (true) {
			if (m_currentKeyframeNo >= topBoneKeyFrameList.size()) {
				//�I�[�܂ōs�����B
				//@todo ���[�v����A�j���[�V�����N���b�v�Ȃ烋�[�v����悤�ɂ��邩�H
				m_currentKeyframeNo--;
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
		for (const auto& keyFrameList : keyFramePtrListArray) {
			//���ݍĐ����̃L�[�t���[��������Ă���B
			Keyframe* keyframe = keyFrameList.at(m_currentKeyframeNo);
			m_skeleton->SetBoneLocalMatrix(
				keyframe->boneIndex, 
				keyframe->transform
			);
		}
	}
}