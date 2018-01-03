/*!
 * @brief	�v���C���[�̃A�j���[�^�[
 */

#pragma once

class CPlayer;

/*!
 * @brief	�v���C���[�̃A�j���[�^�[�B
 */
class CPlayerAnimator : public IGameObject{
public:
	CPlayerAnimator(CPlayer* player)
	{
		m_player = player;
	}
	~CPlayerAnimator()
	{
	}
	bool Start() override;
	void Update() override;
private:
	enum EnAnimationClip{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enANimationClip_Num,
	};
	CAnimationClip m_animClips[enANimationClip_Num];	//!<�A�j���[�V�����N���b�v�G�B
	CAnimation m_animation;								//!<�A�j���[�V�����B
	CPlayer* m_player = nullptr;						//!<�v���C���[�����_���[�B
};