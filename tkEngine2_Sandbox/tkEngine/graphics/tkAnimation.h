/*!
 * @brief	�A�j���[�V����
 */

#pragma once

#include "tkEngine/graphics/tkAnimationClip.h"

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
		 *@param[in]	clipName	�A�j���[�V�����N���b�v�̖��O�B
		 */
		void Play(const wchar_t* clipName)
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
			
			PlayCommon(*it);
		}
		/*!
		*@brief	�A�j���[�V�����̍Đ��B
		*@param[in]	clipNo	�A�j���[�V�����N���b�v�̔ԍ��BInit�֐��ɓn����animClipList�̕��тƂȂ�B
		*/
		void Play(int clipNo)
		{
			PlayCommon(m_animationClips[clipNo]);
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
		void PlayCommon(CAnimationClip* nextClip)
		{
			m_currentAnimationClip = nextClip;
			m_globalTime = 0.0f;
			m_currentKeyframeNo = 0;
		}
	private:
		std::vector<CAnimationClip*>	m_animationClips;	//!<�A�j���[�V�����N���b�v�̔z��B
		CSkeleton* m_skeleton = nullptr;	//!<�A�j���[�V������K�p����X�P���g���B
		CAnimationClip* m_currentAnimationClip = nullptr;	//!<���ݍĐ����̃A�j���[�V�����N���b�v�B
		float m_globalTime = 0.0f;
		int m_currentKeyframeNo = 0;		//!<���ݍĐ����̃A�j���[�V�����L�[�t���[���ԍ��B
		
	};
}