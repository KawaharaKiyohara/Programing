#pragma once

#include "Camera/GameCamera.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"


class Game : public IGameObject
{
public:
	Game();
	~Game();
	void OnDestroy() override;
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	CPlayer m_player;			//!<�v���C���[
	CBackGround m_bg;			//!<�w�i�B
	CGameCamera m_gameCamera;	//!<�Q�[���J�����B
	prefab::CDirectionLight* m_directionLig = nullptr;	//!<�f�B���N�V�������C�g�B
};

