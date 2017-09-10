/*!
 * @brief	�A�j���[�V����
 */

#pragma once

#include "tkEngine/graphics/animation/tkAnimationClip.h"
#include "tkEngine/graphics/animation/tkAnimationPlayController.h"

namespace tkEngine{
	
	class CSkeleton;
	/*!
	 * @brief	�A�j���[�V�����N���X�B
	 */
	class CAnimation {
	public:
		CAnimation();
		~CAnimation();
		/*!
		 *@brief	�������B
		 *@param[in]	skinModelData	�X�L�����f���f�[�^�A
		 *@param[in]	animeClipList	�A�j���[�V�����N���b�v�̃��X�g�B
		 *@param[in]	numAnimClip		�A�j���[�V�����N���b�v�̐��B
		 */
		void Init(CSkinModelData& skinModelData, CAnimationClip* animClipList[], int numAnimClip);
		/*!
		* @brief	�A�j���[�V������i�߂�B
		*@param[in]	deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)�B
		*/
		void Update(float deltaTime);
		/*!
		 *@brief	�A�j���[�V�����̍Đ��B
		 *@param[in]	clipName			�A�j���[�V�����N���b�v�̖��O�B
		 *@param[in]	interpolateTime		�⊮����(�P�ʁF�b)
		 */
		void Play(const wchar_t* clipName, float interpolateTime = 0.0f)
		{
			if (clipName == nullptr) {
				TK_WARNING("clipName is NULL");
				return;
			}
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(), 
				[clipName](auto& clip) {
					return wcscmp(clip->GetName(), clipName ) == 0;
				}
			);
			if (it == m_animationClips.end()) {
				TK_WARNING("not found clip");
				return;
			}
			
			PlayCommon(*it, interpolateTime);
		}
		/*!
		*@brief	�A�j���[�V�����̍Đ��B
		*@param[in]	clipNo	�A�j���[�V�����N���b�v�̔ԍ��BInit�֐��ɓn����animClipList�̕��тƂȂ�B
		*@param[in]	interpolateTime		�⊮����(�P�ʁF�b)
		*/
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			PlayCommon(m_animationClips[clipNo], interpolateTime);
		}
		/*!
		*@brief	�A�j���[�V�����N���b�v�̃��[�v�t���O��ݒ肵�܂��B
		*@param[in]	clipName	�A�j���[�V�����N���b�v�̖��O�B
		*@param[in]	flag		�t���O�B
		*/
		void SetAnimationClipLoopFlag(const wchar_t* clipName, bool flag)
		{
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto& clip) {return clip->GetName() == clipName; }
			);
			if (it == m_animationClips.end()) {
				//������Ȃ������B
				return ;
			}
			(*it)->SetLoopFlag(flag);
		}
	private:
		void PlayCommon(CAnimationClip* nextClip, float interpolateTime)
		{
			if (interpolateTime == 0.0f) {
				//�⊮�Ȃ��B
				m_numAnimationPlayController = 1;
			}
			else {
				//�⊮����B
				m_numAnimationPlayController++;
			}
			int index = GetLastAnimationControllerIndex();
			m_animationPlayController[index].ChangeAnimationClip(nextClip);
			m_animationPlayController[index].SetInterpolateTime(interpolateTime);
			m_interpolateTime = 0.0f;
			m_interpolateTimeEnd = interpolateTime;
		}
		/*!
		 * @brief	���[�J���|�[�Y�̍X�V�B
		 */
		void UpdateLocalPose(float deltaTime);
		/*!
		 * @brief	�O���[�o���|�[�Y�̍X�V�B
		 */
		void UpdateGlobalPose();
	private:
		/*!
		 *@brief	�ŏI�|�[�Y�ɂȂ�A�j���[�V�����̃����O�o�b�t�@��ł̃C���f�b�N�X���擾�B
		 */
		int GetLastAnimationControllerIndex() const
		{
			return GetAnimationControllerIndex(m_startAnimationPlayController, m_numAnimationPlayController - 1);
		}
		/*!
		*@brief	�A�j���[�V�����R���g���[���̃����O�o�b�t�@��ł̃C���f�b�N�X���擾�B
		*@param[in]	startIndex		�J�n�C���f�b�N�X�B
		*@param[in]	localIndex		���[�J���C���f�b�N�X�B
		*/
		int GetAnimationControllerIndex(int startIndex, int localIndex) const
		{
			return (startIndex + localIndex) % ANIMATION_PLAY_CONTROLLER_NUM;
		}
	private:
		static const int ANIMATION_PLAY_CONTROLLER_NUM = 32;	//!<�A�j���[�V�����R���g���[���̐��B
		std::vector<CAnimationClip*>	m_animationClips;	//!<�A�j���[�V�����N���b�v�̔z��B
		CSkeleton* m_skeleton = nullptr;	//!<�A�j���[�V������K�p����X�P���g���B
		CAnimationPlayController	m_animationPlayController[ANIMATION_PLAY_CONTROLLER_NUM];	//!<�A�j���[�V�����R���g���[���B�����O�o�b�t�@�B
		int m_numAnimationPlayController = 0;		//!<���ݎg�p���̃A�j���[�V�����Đ��R���g���[���̐��B
		int m_startAnimationPlayController = 0;		//!<�A�j���[�V�����R���g���[���̊J�n�C���f�b�N�X�B
		float m_interpolateTime = 0.0f;
		float m_interpolateTimeEnd = 0.0f;
		bool m_isInterpolate = false;				//!<��Ԓ��H
	};
}