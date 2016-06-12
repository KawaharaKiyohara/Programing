#include "stdafx.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"

/*!
 * @brief	�X�L�����f���\���e�X�g
 */
class CSkinModelDrawTest : public IGameObject {
	enum AnimationNo {
		AnimationStand,		//�����B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationJump,		//�W�����v�B
	};
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CCamera			camera;				//�J�����B
	CLight			light;				//���C�g�B
	int				currentAnimSetNo;		
	CTexture		normalMap;			//�@���}�b�v�B
public:
	void Start() override 
	{
		skinModelData.LoadModelData("Assets/modelData/unity.X", &animation);
		normalMap.Load("Assets/modelData/utc_nomal.tga");

		//skinModelData.LoadModelData("Assets/modelData/unity.X", NULL);
		skinModel.Init(&skinModelData);
		skinModel.SetLight(&light);
		skinModel.SetNormalMap(&normalMap);

		camera.SetPosition(CVector3(0.0f, 0.5f, 1.0f));
		camera.SetTarget(CVector3(0.0f, 0.5f, 0.0f));
	
		camera.SetFar(1000.0f);
		camera.Update();

		light.SetDiffuseLightDirection(0,  CVector3(0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
		light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

		light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(2, CVector4(0.3f, 0.3f, 0.3f, 1.0f));
		light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetAmbinetLight(CVector3(0.3f, 0.3f, 0.3f));
		animation.SetAnimationEndTime(AnimationRun, 0.8);
		currentAnimSetNo = AnimationStand;
		animation.PlayAnimation(AnimationStand);
	}
	void Update() override 
	{
		animation.Update(1.0f / 60.0f);
		static float angle = 0.0f;
		if (KeyInput().IsRightPress()) {
			angle += 0.01f;
		}
		else if (KeyInput().IsLeftPress()) {
			angle -= 0.01;
		}
		camera.Update();
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisY, CMath::DegToRad(-90.0f) * angle);
		
		skinModel.UpdateWorldMatrix(CVector3(0.0f, 0.0f, 0.0f), qRot, CVector3::One);
		if (KeyInput().IsTrgger(CKeyInput::enKeyA)) {
			currentAnimSetNo++;
			currentAnimSetNo %= animation.GetNumAnimationSet();
			animation.PlayAnimation(currentAnimSetNo);
		}
		if (KeyInput().IsTrgger(CKeyInput::enKeyB)) {
			currentAnimSetNo++;
			currentAnimSetNo %= animation.GetNumAnimationSet();
			animation.PlayAnimation(currentAnimSetNo, 0.1f);
		}
	}
	void Render( CRenderContext& renderContext ) override
	{
		skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
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
	initParam.frameBufferHeight = 1080;
	initParam.frameBufferWidth = 1920;
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	//initParam.graphicsConfig.edgeRenderConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1280;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 720;
	Engine().Init(initParam);	//�������B
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(10.0f);
	ShadowMap().SetLightPosition(CVector3(0.0f, 3.5f, 0.0f));
	ShadowMap().SetLightDirection(CVector3(0.0f, -1.0f, -0.0f));
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
	GameObjectManager().NewGameObject<CSkinModelDrawTest>(0);
	Engine().RunGameLoop();		//�Q�[�����[�v�����s�B
	
	return 0;
}