#pragma once
class Game : public IGameObject
{
public:
	//�����o�֐��B
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//�����o�ϐ��B
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_num,
	};
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	prefab::CDirectionLight* m_directionLight = nullptr;
};

