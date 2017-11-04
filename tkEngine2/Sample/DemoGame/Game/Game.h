#pragma once

class Player;
class Background;
class GameCamera;
class Enemy;
class GameOverControl;
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
	void NotifyGameOver();
	void NotifyRestart();
	bool IsGameOver() const
	{
		return m_isGameOver;
	}
	/*!
	 *@brief	�G�������B
	 */
	Enemy* FindEnemy(std::function<bool(Enemy*)> findEnemyFunc)
	{
		Enemy* findEnemy = nullptr;
		auto findIt = std::find_if(m_enemyList.begin(), m_enemyList.end(), findEnemyFunc);
		if (findIt != m_enemyList.end()) {
			findEnemy = *findIt;
		}		
		return findEnemy;
	}

private:
	void InitSceneLight();
private:
	Player*	m_player = nullptr;			//!<�v���C���[
	std::vector<Enemy*> m_enemyList;	//!<�G�l�~�[�̃��X�g�B
	Background* m_background = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameOverControl* m_gameOverControl = nullptr;	//!<�Q�[���I�[�o�[�R���g���[���B
	std::vector<prefab::CPointLight*> m_pointLight;
	bool m_isGameOver = false;

};

