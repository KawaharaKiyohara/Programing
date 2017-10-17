#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(CRenderContext& rc);
	bool Start();
private:
	////////////////////////////////////
	// �����o�ϐ��B
	////////////////////////////////////
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSkinModel m_skinModel;			//�X�L�����f���B
	CVector3 m_position = CVector3::Zero;	//���W�B
};

