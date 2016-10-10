#include "stdafx.h"

#include "Player/Player.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map/Map.h"
#include "Map/Sky.h"
#include "Map/Ground.h"
#include "Physics/Physics.h"
#include "EnemyTest.h"
#include "Enemy/EnemyManager.h"
#include <time.h>
#include "DamageCollisionWorld.h"

PhysicsWorld* g_physicsWorld = NULL;
Player* g_player = NULL;
CRandom g_random;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
//#define MEMORY_LEAK_TEST		//��`�Ń��������[�N�e�X�g���L���ɂȂ�B

#ifdef MEMORY_LEAK_TEST
//���������[�N�e�X�g�B
class MemoryLeakTest : public IGameObject {
	
public:
	MemoryLeakTest()
	{

	}
	void Start() override
	{

	}
	void Update() override
	{
		//�X�L���Ȃ����f���B
		CSkinModelDataHandle nonSkinModelData;		//�X�L�����f���f�[�^�B
		SkinModelDataResources().Load(nonSkinModelData, "Assets/modelData/Court.X", NULL);
		
		//�X�L���Ȃ��C���X�^���V���O���f���B
		CSkinModelDataHandle nonSkinModelInstancing;
		SkinModelDataResources().Load(nonSkinModelInstancing, "Assets/modelData/Court.X", NULL, true, 10);
		
		//�X�L�����胂�f���B
		CSkinModelDataHandle skinModelData;
		SkinModelDataResources().Load(skinModelData, "Assets/modelData/Unity.X", NULL);
		//�X�L������C���X�^���V���O���f���B
		CSkinModelDataHandle skinModelInstancing;
		SkinModelDataResources().Load(skinModelInstancing, "Assets/modelData/Unity.X", NULL, true, 10);
	}
	void Render(CRenderContext& renderContext) override
	{

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
	g_random.Init((unsigned long)time(NULL));
#ifdef MEMORY_LEAK_TEST
	NewGO<MemoryLeakTest>(0);
#else

	g_physicsWorld = NewGO<PhysicsWorld>(0);
	g_player = NewGO<Player>(0);
	NewGO<UnityChanInstance>(0);
	NewGO<EnemyManager>(0);
	NewGO<Map>(0);
	NewGO<Ground>(0);
	g_damageCollisionWorld = NewGO<DamageCollisionWorld>(0);
#ifdef ENEMY_TEST
	EnemyTest* enemyTest = NewGO<EnemyTest>(0);
	enemyTest->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
#endif
	Sky* sky = NewGO<Sky>(0);
	sky->SetPlayer(g_player);
	g_car = NewGO<Car>(0);
	g_camera = NewGO<GameCamera>(0);
	g_player->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
	g_camera->SetPlayer(g_player);
#endif
	Engine().RunGameLoop();		//�Q�[�����[�v�����s�B

	return 0;
}