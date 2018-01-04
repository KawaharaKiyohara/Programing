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
		float time;					//!<���ԁB
		CVector3 transform[4];		//!<�g�����X�t�H�[���B
	};
	/*!
	 *@brief	�A�j���[�V�����N���b�v�B
	 */
	class CAnimationClip : Noncopyable {
	public:
		/*!
		 *@brief	�{�[���̃t���[�Y���B
		 */
		struct SFreezeBoneInfo {
			int boneNo;		//!<�t���[�Y������{�[���ԍ��B
			bool freezeX;	//!<X�����̈ړ����t���[�Y������H
			bool freezeY;	//!<Y�����̈ړ����t���[�Y������H
			bool freezeZ;	//!<Z�����̈ړ����t���[�Y������H
		};
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		* @brief	�R���X�g���N�^
		*/
		CAnimationClip() 
		{
			m_freezeBoneInfo.boneNo = -1;
			m_freezeBoneInfo.freezeX = false;
			m_freezeBoneInfo.freezeY = false;
			m_freezeBoneInfo.freezeZ = false;
		}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CAnimationClip();
		/*!
		 *@brief	�A�j���[�V�����N���b�v�����[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 *@param[in]	clipName	�N���b�v���B
		 */
		void Load(const wchar_t* filePath, const wchar_t* cliipName = nullptr);
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
		/*!
		 *@brief	�N���b�v�����擾�B
		 */
		const wchar_t* GetName() const
		{
			return m_clipName.c_str();
		}
		/*!
		*@brief	�A�j���[�V�������t���[�Y����{�[���̏���ݒ�B
		*@details
		* �t���[�Y���ꂽ�{�[����Y�����̈ړ��ʂ͂��ׂẴ{�[������ł�������܂��B
		*  ���ȂɂŎg����H
		*		���A�j���[�V�����Ɉړ��ʂ������Ă���W�����v���[�V�����Ƃ��Ŏg����B
		*/
		void SetFreezeBoneInfo(int boneNo, bool freezeX, bool freezeY, bool freezeZ)
		{
			m_freezeBoneInfo.boneNo = boneNo;
			m_freezeBoneInfo.freezeX = freezeX;
			m_freezeBoneInfo.freezeY = freezeY;
			m_freezeBoneInfo.freezeZ = freezeZ;
		}
		/*!
		*@brief	X�����̃A�j���[�V�������t���[�Y���Ă���{�[���̔ԍ����擾�B
		*/
		const SFreezeBoneInfo& GetFreezeBoneInfo() const
		{
			return m_freezeBoneInfo;
		}
	private:
		std::wstring m_clipName;	//!<�A�j���[�V�����N���b�v�̖��O�B
		bool m_isLoop = false;	//!<���[�v�t���O�B
		typedef std::unique_ptr<Keyframe> KeyframePtr;
		std::vector<KeyframePtr>	m_keyframes;	//�L�[�t���[���B
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
		keyFramePtrList*				m_topBoneKeyFramList = nullptr;
		SFreezeBoneInfo m_freezeBoneInfo;	//!<�t���[�Y������{�[�����B
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
}