/*!
 * @brief	�G�B
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

/*!
 * @brief	�G�B
 */
class Enemy : public IGameObject{
public:
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_Num,
	};
	CAnimationClip	m_animationClip[enAnimationClip_Num];	//!<�A�j���[�V�����N���b�v
	CAnimation		m_animation;				//!<�A�j���[�V�����B
	CSkinModelData	m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel		m_skinModel;			//!<�X�L�����f���B
	CVector3		m_position;				//!<���W�B
	CQuaternion		m_rotation = CQuaternion::Identity;		//!<��]�B
	CCharacterController m_characterController;
};