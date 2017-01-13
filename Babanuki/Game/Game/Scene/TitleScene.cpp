#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ScreenEffect/Fade.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}
bool TitleScene::Start()
{
	m_titleBGTexture.Load("Assets/sprite/titleBG.png");
	m_titleBGSprite.Init(&m_titleBGTexture);
	g_fade->StartFadeIn();
	return true;
}
void TitleScene::Update()
{
	switch (m_state) {
	case eStateWaitFadeIn:
		if (!g_fade->IsExecute()) {
			m_state = eStateRun;
		}
		break;
	case eStateRun:
		if (Pad(0).IsPress(enButtonStart)) {
			g_fade->StartFadeOut();
			m_state = eStateWaitFadeOut;
		}
		break;
	case eStateWaitFadeOut:
		if (!g_fade->IsExecute()) {
			//�t�F�[�h�I������B
			//�Q�[���V�[���ɑJ�ځB
			g_gameScene = NewGO<GameScene>(0);
			//�������폜�B
			DeleteGO(this);
			return;
		}
		break;
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	m_titleBGSprite.Draw(renderContext);
}