#include "stdafx.h"
#include "lib/system.h"
#include "main.h"
#include "GameCamera.h"

Game* game = NULL;

//�R���X�g���N�^�B
Game::Game()
{

}
//�f�X�g���N�^�B
Game::~Game()
{
	delete gameCamera;
}
//Update���Ă΂��O�Ɉ�x�����Ă΂�鏈���B
void Game::Start()
{
	gameCamera = new GameCamera;
	court.Init();
	player.Init();
	ball.Init();
}
//�`��B
void Game::Render(CRenderContext& renderContext)
{
	court.Render(renderContext);
	player.Render(renderContext);
	ball.Render(renderContext);
}
//�X�V�B
void Game::Update()
{
	//�Q�[���J�����̍X�V�B
	gameCamera->Update();
	player.Update();
	ball.Update();
}
