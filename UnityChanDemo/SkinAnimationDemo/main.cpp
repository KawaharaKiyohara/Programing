#include "stdafx.h"

#include "UnityChan.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map.h"


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
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 2048;
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = true;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	Engine().Init(initParam);	//�������B

	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(20.0f);
	
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
	
	NewGO<Map>(0);
	NewGO<UnityChanInstance>(0);
	g_car = NewGO<Car>(0);
	UnityChan* unityChan = NewGO<UnityChan>(0);
	g_camera = NewGO<GameCamera>(0);
	unityChan->SetPosition(CVector3(0.0f, 0.0f, 0.0f));
	g_camera->SetUnityChan(unityChan);

	Engine().RunGameLoop();		//�Q�[�����[�v�����s�B
	
	return 0;
}