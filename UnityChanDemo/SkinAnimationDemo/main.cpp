#include "stdafx.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "HUD/NowLoading.h"

//#define MEMORY_LEAK_TEST		//��`�Ń��������[�N�e�X�g���L���ɂȂ�B
//#define PLAY_WAVE_FILE_TEST		//��`�Ŕg�`�f�[�^�̍Đ��e�X�g���L���ɂȂ�B
//#define DRAW_SPRITE_TEST		//��`�ŃX�v���C�g�`��e�X�g�B
//#define CHNAGE_SCENE_TEST		//�L���ŃV�[���؂�ւ��e�X�g�B

GameScene* gameScene = NULL;
NowLoading* g_nowLoading = NULL;

#ifdef DRAW_SPRITE_TEST
class DrawSpriteTest : public IGameObject {
	CSprite	sprite;
	CTexture texture;
public:
	DrawSpriteTest()
	{
	}
	~DrawSpriteTest()
	{
	}
	bool Start() override
	{
		texture.Load("Assets/sprite/test.png");
		sprite.Init(&texture);
		sprite.SetPosition({ -640, 360 });
		sprite.SetPivot({ 0.0f, 1.0f });
		return true;
	}
	void Update() override
	{
	}
	void PostRender( CRenderContext& renderContext ) override
	{
		sprite.Draw(renderContext);
	}
};
#endif
#ifdef PLAY_WAVE_FILE_TEST
class PlayWaveFileTest : public IGameObject {
	/*CWaveFile waveFile;
	char* buffer;*/
	CSoundSource soundSource;
public:
	PlayWaveFileTest() 
	{
	}
	~PlayWaveFileTest()
	{
	}
	bool Start() override
	{
		//�T�E���h�\�[�X���������B
		soundSource.InitStreaming("Assets/sound/wind.wav");
		//soundSource.Init("Assets/sound/MusicMono.wav");
		soundSource.Play(true);
		soundSource.SetVolume(0.5f);
		AddGO(0, &soundSource);
		return true;
	}
	void Update() override
	{
		/*if (Pad(0).IsPress(enButtonDown)) {
			CSoundSource* s = NewGO<CSoundSource>(0);
			s->Init("Assets/sound/EnemyAttack.wav", true);
			s->Play(false);
			s->SetPosition(g_player->GetPosition());
			s = NewGO<CSoundSource>(0);
			s->Init("Assets/sound/Damage_00.wav");
			s->Play(false);
		}*/
	}
	void Render(CRenderContext& renderContext) override
	{
	}
};
#endif
#ifdef MEMORY_LEAK_TEST
//���������[�N�e�X�g�B
class MemoryLeakTest : public IGameObject {
	
public:
	MemoryLeakTest()
	{

	}
	bool Start() override
	{
		return true;
	}
	void Update() override
	{
		//�X�L���Ȃ����f���B
		CSkinModelDataHandle nonSkinModelData;		//�X�L�����f���f�[�^�B
		SkinModelDataResources().Load(nonSkinModelData, "Assets/modelData/ground.X", NULL);
		
		//�X�L���Ȃ��C���X�^���V���O���f���B
		CSkinModelDataHandle nonSkinModelInstancing;
		SkinModelDataResources().Load(nonSkinModelInstancing, "Assets/modelData/ground.X", NULL, true, 10);
		
		//�X�L�����胂�f���B
		CSkinModelDataHandle skinModelData;
		SkinModelDataResources().Load(skinModelData, "Assets/modelData/Unity.X", NULL);
		//�X�L������C���X�^���V���O���f���B
		CSkinModelDataHandle skinModelInstancing;
		SkinModelDataResources().Load(skinModelInstancing, "Assets/modelData/Unity.X", NULL, true, 10);

		CSoundSource soundSource;
		soundSource.InitStreaming("Assets/sound/SoundTest.wav");
		//soundSource.Init("Assets/sound/MusicMono.wav");
		soundSource.Play(true);

	}
	void Render(CRenderContext& renderContext) override
	{

	}
};
#endif

#ifdef CHNAGE_SCENE_TEST
class ChangeSceneTest : public IGameObject {
public:
	void Update() override
	{
		if (Pad(0).IsTrigger(enButtonStart)) {
			if (gameScene == NULL) {
				gameScene = NewGO<GameScene>(0);
			}
			else {
				DeleteGO(gameScene);
				gameScene = NULL;
			}
		}
	}
};
#endif

/*!
 * @brief	tkEngine�̏������B
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//�R�}���h�o�b�t�@�̃T�C�Y�̃e�[�u���B
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//�����_�����O�R���e�L�X�g�͈�{
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 3;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	//DOF
	initParam.graphicsConfig.dofConfig.isEnable = true;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = true;
	//MotionBlur
	initParam.graphicsConfig.motionBlurConfig.isEnable = true;

	Engine().Init(initParam);	//�������B
	
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(40.0f);
	
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//tkEngine�̏������B
	InitTkEngine( hInst );
	g_nowLoading = NewGO<NowLoading>(1);
	
	g_random.Init((unsigned long)time(NULL));
#ifdef DRAW_SPRITE_TEST
	NewGO<DrawSpriteTest>(1);
#endif
#ifdef PLAY_WAVE_FILE_TEST
	NewGO<PlayWaveFileTest>(0);
#endif
#ifdef MEMORY_LEAK_TEST
	NewGO<MemoryLeakTest>(0);
#else
	//gameScene = NewGO<GameScene>(0);
	NewGO<TitleScene>(0);
#endif
#ifdef CHNAGE_SCENE_TEST
	NewGO<ChangeSceneTest>(0);
#endif
	Engine().RunGameLoop();		//�Q�[�����[�v�����s�B

	return 0;
}