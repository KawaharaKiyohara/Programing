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
		m_startTime = clip->StartTime;
		m_endTime = clip->EndTime;
		m_numKeys = clip->keys;
		m_keyframes.resize(m_numKeys);
		for (int i = 0; i < m_numKeys; i++) {
			Keyframe& keyframe = m_keyframes.at(i);
			keyframe.boneIndex = keyFrames[i].BoneIndex;
			keyframe.time = keyFrames[i].Time;
			keyframe.transform = keyFrames[i].Transform;
		}
	}
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
}

