#pragma once

class Player;
class Background;
class GameCamera;
class Enemy;
class Game : public IGameObject
{
public:
	//�����o�֐��B
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	void OnDestroy()override;
private:
	void InitSceneLight();
private:
	Player*	m_player = nullptr;			//!<�v���C���[
	std::vector<Enemy*> m_enemyList;	//!<�G�l�~�[�̃��X�g�B
	Background* m_background = nullptr;
	GameCamera* m_gameCamera = nullptr;
	std::vector<prefab::CPointLight*> m_pointLight;
};

