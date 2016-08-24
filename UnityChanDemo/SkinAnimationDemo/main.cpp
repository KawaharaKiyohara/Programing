#include "stdafx.h"

#include "UnityChan.h"
#include "UnityChanInstance.h"
#include "Car.h"


class Map : public IGameObject {
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CLight			light;				//���C�g�B
	CTexture		normalMap;
public:
	Map()
	{
		skinModelData.LoadModelData("Assets/modelData/Court.X", NULL);
		skinModel.Init(&skinModelData);
		skinModel.SetLight(&light);
		normalMap.Load("Assets/modelData/Grass_Normals.tga");
		skinModel.SetNormalMap(&normalMap);
		light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
		light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

		light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));
		skinModel.SetShadowReceiverFlag(true);
	}
	~Map()
	{

	}
	void Map::Start() override
	{

	}
	void Map::Update() override
	{
		skinModel.Update(CVector3(0.0f, -0.05f, 0.0f), CQuaternion::Identity, CVector3(10.0f, 1.0f, 10.0f));
	}
	void Map::Render(CRenderContext& renderContext) override
	{
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
};
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