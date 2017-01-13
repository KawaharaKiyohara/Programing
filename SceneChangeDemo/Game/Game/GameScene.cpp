#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "tkEngine/sound/tkSoundSource.h"

GameScene::GameScene()
{
	bgmSource = NULL;
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/bgm.wav");
	bgmSource->Play(true);
}
GameScene::~GameScene()
{
	//�����ƍ폜���Ȃ��Ɖ��������Ȃ���B
	DeleteGO(bgmSource);
}
bool GameScene::Start() 
{
	return true;
}
void GameScene::Update()
{
	if (Pad(0).IsPress(enButtonA)) {
		//A�{�^���������ꂽ��^�C�g���V�[���ɑJ�ڂ���B
		NewGO<TitleScene>(0);
		DeleteGO(this);
	}
}
