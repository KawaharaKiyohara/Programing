/*!
 *@brief	�^�C�g���V�[���B
 */
#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}
bool TitleScene::Start()
{
	texture.Load("Assets/sprite/titleBG.png");	
	sprite.Init(&texture);
	return true;
}
void TitleScene::Update()
{
	if (Pad(0).IsPress(enButtonStart)) {
		//�X�^�[�g�{�^���������ꂽ��Q�[���V�[���ɑJ�ڂ���B
		//GameScene�̃C���X�^���X�𐶐��B
		NewGO<GameScene>(0);
		//TitleScene�̃C���X�^���X���폜�B
		DeleteGO(this);
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}