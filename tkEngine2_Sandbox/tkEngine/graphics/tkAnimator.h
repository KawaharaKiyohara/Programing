/*!
 * @brief	�A�j���[�^�[�N���X�B
 */

#pragma once

#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine{
	
	class CSkeleton;
	/*!
	 * @brief	�A�j���[�^�[�N���X�B
	 */
	class CAnimator{
	public:
		CAnimator();
		~CAnimator();
		/*!
		 * @brief	�������B
		 *@param[in]	skinModelData	�X�L�����f���f�[�^�B
		 */
		void Init(CSkinModelData& skinModelData);
		/*!
		* @brief	�A�j���[�V������i�߂�B
		*@param[in]	deltaTime		�A�j���[�V������i�߂鎞��(�P�ʁF�b)�B
		*/
		void Progress(float deltaTime);
		/*!
		 *@brief	�A�j���[�V�����̍Đ��B
		 *@param[in]	no		�Đ�����A�j���[�V�����̔ԍ��B
		 */
		void Play(int no)
		{
			if (no >= (int)m_animationClips.size()) {
				TK_LOG("warning : no is over m_animationClips.size()");
				return;
			}
			m_currentAnimationClip = m_animationClips.at(no);
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