/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�L�[�t���[���B
	 */
	struct Keyframe {
		unsigned int boneIndex;		//!<�{�[���C���f�b�N�X�B
		float time;					//!<���ԁB
		CMatrix transform;			//!<�g�����X�t�H�[���B
	};
	/*!
	 *@brief	�A�j���[�V�����N���b�v�B
	 */
	class CAnimationClip : Noncopyable{
	public:
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		 * @brief	�R���X�g���N�^
		 *@param[in]	clipName	�N���b�v���B
		 *@param[in]	clip		�A�j���[�V�����N���b�v�B
		 *@param[in]	keyFrames	�L�[�t���[���B
		 */
		CAnimationClip(
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip,
			const VSD3DStarter::Keyframe* keyFrames
		);
		/*!
		 *@brief
		 */
		~CAnimationClip();
		/*!
		 *@brief
		 */
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
		{
			return m_keyFramePtrListArray;
		}
	private:
		
		std::wstring m_name;	//!<�N���b�v�̖��O�B
		float m_startTime;		//!<�J�n���ԁB
		float m_endTime;		//!<�I�����ԁB
		unsigned int m_numKeys;	//!<�L�[�t���[���̐��B
		std::vector<Keyframe>	m_keyframes;	//�L�[�t���[���B
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;

}
