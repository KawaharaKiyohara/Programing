#pragma once
class Enemy : public IGameObject
{
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
		enAnimationClip_run,
		enAnimationClip_num,
	};
	CSkinModelData m_skinModelData;		//!<�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;				//!<�X�L�����f���B
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	CVector3 m_position = CVector3::Zero;
};

