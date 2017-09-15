#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
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
};

