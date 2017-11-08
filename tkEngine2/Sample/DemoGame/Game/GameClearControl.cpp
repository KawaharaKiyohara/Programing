#include "stdafx.h"
#include "GameClearControl.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameClearCamera.h"
GameClearControl::GameClearControl()
{
}


GameClearControl::~GameClearControl()
{
}
void GameClearControl::Awake()
{
	//�v���C���[�ɃN���A��ʒm�B
	FindGO<Player>("Player")->NotifyGameClear();
	FindGO<GameCamera>("GameCamera")->NotifyGameClear();
}
bool GameClearControl::Start()
{
	//�Q�[���N���A�J�������쐬�B
	m_gameClearCamera = NewGO<GameClearCamera>(0, "GameClearCamera");
	return true;
}
void GameClearControl::Update()
{
}
void GameClearControl::OnDestroy()
{
	DeleteGO(m_gameClearCamera);
}