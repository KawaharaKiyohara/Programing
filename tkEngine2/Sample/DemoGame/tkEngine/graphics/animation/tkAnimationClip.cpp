/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationClip.h"

namespace tkEngine {
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	�A�j���[�V�����N���b�v�����[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*@param[in]	clipName	�N���b�v���B
	*/
	void CAnimationClip::Load(const wchar_t* filePath, const wchar_t* clipName)
	{
		FILE* fp = _wfopen(filePath, L"rb");
		if (fp == nullptr) {
			TK_WARNING("�t�@�C���̃I�[�v���Ɏ��s���܂����B: CAnimationClip::Load");
			return;
		}
		if (clipName != nullptr) {
			m_clipName = clipName;
		}
		//�L�[�̐����擾����B
		int numKey;
		fread(&numKey, sizeof(numKey), 1, fp);
		//���g���������ƃ��[�h�B
		std::unique_ptr<KeyframeRow[]> keyframes;
		keyframes = std::make_unique<KeyframeRow[]>(numKey);
		fread(keyframes.get(), sizeof(KeyframeRow), numKey, fp);
		fclose(fp);
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyframes[i].boneIndex;
			keyframe->transform = CMatrix::Identity;
			keyframe->time = keyframes[i].time;
			for (int j = 0; j < 4; j++) {
				keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
				keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
				keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
			}
			m_keyframes.push_back(std::move(keyframe));
		}

		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����B
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			if (m_topBoneKeyFramList == nullptr) {
				m_topBoneKeyFramList = &m_keyFramePtrListArray[keyframe->boneIndex];
			}
		}
	}
}

