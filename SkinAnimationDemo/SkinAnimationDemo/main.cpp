#include "stdafx.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"

/*!
 * @brief	�X�L�����f���\���e�X�g
 */
class CSkinModelDrawTest : public IGameObject {
	CSkinModelData	skinModelData;		//�X�L�����f���f�[�^�B
	CSkinModel		skinModel;			//�X�L�����f���B
	CAnimation		animation;			//�A�j���[�V�����B
	CCamera			camera;
	int				currentAnimSetNo;		
public:
	void Start() override 
	{
		skinModelData.LoadModelData("Assets/modelData/PL_Girl_SSword.x", &animation);
		skinModel.SetSkinModelData(&skinModelData);
		camera.SetPosition(CVector3(0.0f, 1.5f, -4.0f));
		camera.SetTarget(CVector3(0.0f, 1.0f, 0.0f));
		camera.Update();
		camera.SetFar(1000.0f);
		currentAnimSetNo = 0;
	}
	void Update() override 
	{
		animation.Update(1.0f / 60.0f);
		skinModel.UpdateWorldMatrix(CVector3::Zero, CQuaternion::Identity, CVector3::One);
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
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.graphicsConfig.bloomConfig.isEnable = false;
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