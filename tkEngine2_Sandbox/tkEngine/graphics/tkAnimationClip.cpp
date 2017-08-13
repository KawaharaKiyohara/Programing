/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine {
	/*!
	* @brief	�R���X�g���N�^
	*@param[in]	clipName	�N���b�v���B
	*@param[in]	clip		�A�j���[�V�����N���b�v�B
	*@param[in]	keyFrames	�L�[�t���[���B
	*@param[in]	baseBoneNo	��{�{�[���ԍ��B
	*/
	CAnimationClip::CAnimationClip(
		const wchar_t* clipName,
		const VSD3DStarter::Clip* clip,
		const VSD3DStarter::Keyframe* keyFrames
	)
	{
		m_name = clipName;
		m_startTime = clip->StartTime;
		m_endTime = clip->EndTime;
		m_numKeys = clip->keys;
		//m_keyframes.resize(m_numKeys);
		for (int i = 0; i < m_numKeys; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyFrames[i].BoneIndex;
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyframes.push_back(std::move(keyframe));
		}
		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����B
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
		}
	}
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	�L�[�t���[����ǉ��B
	*/
	void CAnimationClip::AddKeyFrame(int numKey, const VSD3DStarter::Keyframe* keyFrames, int baseBoneNo)
	{
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			m_keyframes.push_back(std::move(keyframe));
			
		}
	}
}

