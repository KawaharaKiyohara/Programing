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
	*@brief	�L�[�t���[���B
	*/
	struct KeyframeRow {
		unsigned int boneIndex;		//!<�{�[���C���f�b�N�X�B
		CVector3 transform[4];		//!<�g�����X�t�H�[���B
	};
	/*!
	 *@brief	�A�j���[�V�����N���b�v�B
	 */
	class CAnimationClip : Noncopyable {
	public:
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		 * @brief	�R���X�g���N�^
		 *@details
		 * �폜�\��B
		 *@param[in]	clipName	�N���b�v���B
		 *@param[in]	clip		�A�j���[�V�����N���b�v�B
		 *@param[in]	keyFrames	�L�[�t���[���B
		 *@param[in]	baseBoneNo	��{�{�[���ԍ��B
		 */
		CAnimationClip(
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip,
			const VSD3DStarter::Keyframe* keyFrames,
			int baseBoneNo,
			std::vector<int> localBoneIDtoGlobalBoneIDTbl
		);
		/*!
		* @brief	�R���X�g���N�^
		*/
		CAnimationClip() {}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CAnimationClip();
		/*!
		 *@brief	�A�j���[�V�����N���b�v�����[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 */
		void Load(const wchar_t* filePath);
		/*!
		*@brief	�L�[�t���[����ǉ��B
		*/
		void AddKeyFrame(
			int numKeyframes,
			const VSD3DStarter::Keyframe* keyFrames,
			int baseBoneNo,
			const std::vector<int>& localBoneIDtoGlobalBoneIDTbl
		);
		
		/*!
		*@brief	���O���擾�B
		*/
		const std::wstring& GetName() const
		{
			return m_name;
		}
		/*!
		*@brief	���[�v����H
		*/
		bool IsLoop() const
		{
			return m_isLoop;
		}
		/*!
		*@brief	���[�v�t���O��ݒ肷��B
		*/
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
		/*!
		*@brief
		*/
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
		{
			return m_keyFramePtrListArray;
		}
		const keyFramePtrList& GetTopBoneKeyFrameList() const
		{
			return *m_topBoneKeyFramList;
		}
	private:
		
		std::wstring m_name;	//!<�N���b�v�̖��O�B
		float m_startTime;		//!<�J�n���ԁB
		float m_endTime;		//!<�I�����ԁB
		unsigned int m_numKeys;	//!<�L�[�t���[���̐��B
		bool m_isLoop = false;	//!<���[�v�t���O�B
		typedef std::unique_ptr<Keyframe> KeyframePtr;
		std::vector<KeyframePtr>	m_keyframes;	//�L�[�t���[���B
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
		keyFramePtrList*				m_topBoneKeyFramList = nullptr;
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
}