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
		const VSD3DStarter::Keyframe* keyFrames,
		int baseBoneNo,
		std::vector<int> localBoneIDtoGlobalBoneIDTbl
	)
	{
		m_name = clipName;
		m_startTime = clip->StartTime;
		m_endTime = clip->EndTime;
		//m_keyframes.resize(m_numKeys);
		for (int i = 0; i < clip->keys; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			int localBoneIndex = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->boneIndex = localBoneIDtoGlobalBoneIDTbl[localBoneIndex];
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
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
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	�A�j���[�V�����N���b�v�����[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*/
	void CAnimationClip::Load(const wchar_t* filePath)
	{
		FILE* fp = _wfopen(filePath, L"rb");
		if (fp == nullptr) {
			TK_WARNING("�t�@�C���̃I�[�v���Ɏ��s���܂����B: CAnimationClip::Load");
			return;
		}
		//�L�[�̐����擾����B
		int numKey;
		fread(&numKey, sizeof(numKey), 1, fp);
		//���g���������ƃ��[�h�B
		std::unique_ptr<KeyframeRow[]> keyframes;
		keyframes = std::make_unique<KeyframeRow[]>(numKey);
		fread(keyframes.get(), sizeof(KeyframeRow), numKey, fp);
		fclose(fp);
	}
	
	/*!
	*@brief	�L�[�t���[����ǉ��B
	*/
	void CAnimationClip::AddKeyFrame(
		int numKey, 
		const VSD3DStarter::Keyframe* keyFrames, 
		int baseBoneNo,
		const std::vector<int>& localBoneIDtoGlobalBoneIDTbl
	)
	{
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			int localBoneID = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->boneIndex = localBoneIDtoGlobalBoneIDTbl[localBoneID];
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			m_numKeys = m_keyFramePtrListArray[keyframe->boneIndex].size();
			m_keyframes.push_back(std::move(keyframe));
			
		}
	}
}

