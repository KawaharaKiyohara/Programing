#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel skinModel;							//�X�L�����f���B
	CSkinModelData skinModelData;					//�X�L�����f���f�[�^�B
	prefab::CDirectionLight* m_lig = nullptr;		//���C�g�B

};

