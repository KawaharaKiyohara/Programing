#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_walk,
		enAnimationClip_Num,
	};
	CSkinModelData	m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel		m_skinModel;			//!<�X�L�����f���B
	CAnimationClip	m_animationClip[enAnimationClip_Num];	//!<�A�j���[�V�����N���b�v
	CAnimation		m_animation;				//!<�A�j���[�V�����B
	CVector3		m_position = CVector3::Zero;
	CVector3		m_moveSpeed = CVector3::Zero;
	CQuaternion		m_rotation = CQuaternion::Identity;
	CShaderResourceView	m_normalMapSRV;			//!<�@���}�b�v��SRV�B
	CShaderResourceView m_specularMapSRV;		//!<�X�y�L�����}�b�v��SRV�B
	CShaderResourceView	m_wnormalMapSRV;		//!<����̖@���}�b�v��SRV�B
	CShaderResourceView m_wspecularMapSRV;		//!<����̃X�y�L�����}�b�v��SRV�B
	CCharacterController m_characterCtr;		//!<�L�����N�^�[�R���g���[���[�B
	prefab::CPointLight* m_pointLight;			//!<�|�C���g���C�g�B
};

