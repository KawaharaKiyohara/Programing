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
		m_keyframes.resize(m_numKeys);
		unsigned int boneIDMax = 0;
		for (int i = 0; i < m_numKeys; i++) {
			Keyframe& keyframe = m_keyframes.at(i);
			keyframe.boneIndex = keyFrames[i].BoneIndex;
			keyframe.time = keyFrames[i].Time;
			keyframe.transform = keyFrames[i].Transform;
			boneIDMax = max(boneIDMax, keyframe.boneIndex);
		}
		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����B
		m_keyFramePtrListArray.resize(boneIDMax+1);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe.boneIndex].push_back(&keyframe);
		}

	}
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
}

