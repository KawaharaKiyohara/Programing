/*!
 *@brief	�����G���W���̃f���v���O�����B
 */

#include "stdafx.h"
#include "Player.h"
#include "Ground.h"
#include "Camera.h"
#include "bulletPhysics.h"
#include "Wall.h"
#include "DebriCreator.h"

#define USE_DEBRI		//�f�u���B

CGameCamera g_gameCamera;
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
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1280;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 720;
	CEngine::Instance().Init(initParam);	//�������B
	tkEngine::CEngine::Instance().ShadowMap().SetNear(2.0f);
	tkEngine::CEngine::Instance().ShadowMap().SetFar(10.0f);
	tkEngine::CEngine::Instance().ShadowMap().SetLightPosition(CVector3(0.0f, 3.5f, 0.0f));
	tkEngine::CEngine::Instance().ShadowMap().SetLightDirection(CVector3(0.0f, -1.0f, -0.0f));
}
/*!
* @brief	�ǂ��\�z�B
*/
void BuildWalls(CCamera* camera)
{
	const float GRID_SIZE = 0.2f;
	const int NUM_GRID = 15;
	//1�͕ǁB
	static int sMap[NUM_GRID][NUM_GRID] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },


	};
	for (int i = 0; i < NUM_GRID; i++) {
		for (int k = 0; k < NUM_GRID; k++) {
			int x = k - NUM_GRID / 2;
			int z = i - NUM_GRID / 2;
			if (sMap[i][k] == 1) {
				//�ǂ��쐬�B
				CWall* wall = CGameObjectManager::Instance().NewGameObject<CWall>(0);
				wall->Build(CVector3(GRID_SIZE, GRID_SIZE, GRID_SIZE), CVector3(GRID_SIZE*x, GRID_SIZE*0.5f, GRID_SIZE*-z));
				wall->SetCamera(camera);
			}
		}
	}
}

/*!
 * @brief	���C���֐��B
 */
int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	) 
{
	//tkEngine�̏������B
	InitTkEngine( hInst );
	//bulletPhysics���������B
	g_bulletPhysics.InitPysics();
	
	//��������Q�[���̂��낢��B
	CGameObjectManager::Instance().AddGameObject(0, &g_gameCamera);
	CPlayer player;
	CGameObjectManager::Instance().AddGameObject(0, &player);	//�v���C����o�^�B
	CGround ground;
	CGameObjectManager::Instance().AddGameObject(0, &ground);	//�n�ʂ�o�^�B
#ifdef USE_DEBRI
	CDebriCreator debriCreator;
	CGameObjectManager::Instance().AddGameObject(0, &debriCreator);	//�S�~�����@��o�^�B
	debriCreator.SetCamera(g_gameCamera.GetCamera());
#endif
	//�Ǎ\�z
	BuildWalls(g_gameCamera.GetCamera());
	CGameObjectManager::Instance().AddGameObject(0, &g_bulletPhysics);
	g_gameCamera.SetPlayer(&player);
	player.SetCamera(g_gameCamera.GetCamera());
	ground.SetCamera(g_gameCamera.GetCamera());
	CEngine::Instance().RunGameLoop();		//�Q�[�����[�v�����s�B
}