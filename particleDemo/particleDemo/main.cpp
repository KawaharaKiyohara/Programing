#include "stdafx.h"
#include "tkEngine/graphics/tkCamera.h"
#include <time.h>
#include "tkEngine/random/tkRandom.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"

CRandom random;	//�����B

SParicleEmitParameter particleParameterTbl[] =
{
	//�R���オ�鉊
	{
		"Assets/Effect/PRT_Fire.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		CVector3(0.0f, 1.0f, 0.0f),		//CVector3	initVelocity;						//!<�����x�B
		1.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.01f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.5f,							//float		h;									//!<�p�[�e�B�N���̍����B
		CVector3(0.2f, 0.0f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		CVector3(0.3f, 0.0f, 0.3f),		//CVector3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		CVector3(0.005f, 0.0f, 0.005f),	//CVector3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{											//!<CVector4	uvTable[4];			UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		1.0f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
	//�}�O�}�̕��o���ۂ���
	{
		"Assets/Effect/PRT_Fire.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		CVector3(0.0f, 5.0f, 0.0f),		//CVector3	initVelocity;						//!<�����x�B
		1.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.01f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.5f,							//float		h;									//!<�p�[�e�B�N���̍����B
		CVector3(0.2f, 0.0f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		CVector3(0.3f, 0.0f, 0.3f),		//CVector3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{											//!<CVector4	uvTable[4];			UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		CVector3(0.0f, -9.8f, 0.0f ),	//CVector3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.1f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
	//�͂�����Ԑ��G�t�F�N�g
	{
		"Assets/Effect/star.png",		//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		CVector3(0.0f, 5.0f, 0.0f),		//CVector3	initVelocity;						//!<�����x�B
		0.5f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.02f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.5f,							//float		h;									//!<�p�[�e�B�N���̍���z�B
		CVector3(0.2f, 0.2f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		CVector3(3.0f, 0.0f, 3.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{											//!<CVector4	uvTable[4];			UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			CVector4(0.0f,  0.0f, 1.0f, 1.0f),
			CVector4(0.0f, 0.0f,  0.0f, 0.0f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		1,								//int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		CVector3(0.0f, -9.8f, 0.0f),		//CVector3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.3f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		0.1f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
	//��
	{
		"Assets/Effect/leaf.png",		//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		CVector3(4.0f, 0.0f, 0.0f),		//CVector3	initVelocity;						//!<�����x�B
		3.0f,							//float		life;								//!<�����B�P�ʂ͕b�B
		0.2f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.4f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.4f,							//float		h;									//!<�p�[�e�B�N���̍����B
		CVector3(0.2f, 0.4f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		CVector3(0.0f, 2.0f, 2.0f),		//CVector3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{											//!<CVector4	uvTable[4];			UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			CVector4(0.0f,  0.0f, 1.0f, 1.0f),
			CVector4(0.0833333f, 0.0f,  0.1666666f, 0.0f),
			CVector4(0.1666666f,  0.0f, 0.2499999f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		1,								//int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		CVector3(0.0f, -0.0f, 0.0f),		//CVector3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.3f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		0.1f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		0,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	},
};
class ParticleDemo : public IGameObject{
private:
	CCamera				camera;			//�J�����B
	CParticleEmitter*	emitter;
	CVector3			cameraPos;
	int					currentEmitterNo;
public:
	ParticleDemo()
	{
		cameraPos = CVector3(0.0f, 1.0f, -5.0f);
		camera.SetPosition(cameraPos);
		camera.SetTarget(CVector3::Zero);
		currentEmitterNo = 0;	
	}
	~ParticleDemo()
	{
	}
	void Start() override
	{
		random.Init((unsigned long)time);
		emitter = GameObjectManager().NewGameObject<CParticleEmitter>(0);
	
		emitter->Init(random, camera, particleParameterTbl[currentEmitterNo], CVector3::Zero);
		camera.Update();
	}
	void Update() override
	{

		//�r���{�[�h�̃e�X�g�̂��߂ɃJ�����𓮂����B
		CMatrix mRot = CMatrix::Identity;
		if (KeyInput().IsRightPress()) {
			mRot.MakeRotationY(0.03f);
		}
		else if (KeyInput().IsLeftPress()) {
			mRot.MakeRotationY(-0.03f);
		}
		if (KeyInput().IsUpPress()) {
			mRot.MakeRotationX(0.03f);
		}
		else if (KeyInput().IsDownPress()) {
			mRot.MakeRotationX(-0.03f);
		}
		if (KeyInput().IsPress(CKeyInput::enKeyA)) {
			//�p�[�e�B�N���ɗ͂�������B
			emitter->ApplyForce(CVector3(1.0f, 0.0f, 0.0f));
		}
		else if(KeyInput().IsPress(CKeyInput::enKeyB)) {
			emitter->ApplyForce(CVector3(-5.0f, 0.0f, 1.0f));
		}
		if(KeyInput().IsTrgger(CKeyInput::enKeyA)){
			GameObjectManager().DeleteGameObject(emitter);
			emitter = GameObjectManager().NewGameObject<CParticleEmitter>(0);
			currentEmitterNo = (currentEmitterNo + 1) % ARRAYSIZE(particleParameterTbl);
			emitter->Init(random, camera, particleParameterTbl[currentEmitterNo], CVector3::Zero);
		}
		mRot.Mul(cameraPos);
		camera.SetPosition(cameraPos);
		camera.Update();
	}
	void Render(CRenderContext& renderContext) override
	{
	//	skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
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
	ParticleDemo particleDemo;
	GameObjectManager().AddGameObject(0, &particleDemo);
	Engine().RunGameLoop();		//�Q�[�����[�v�����s�B
	
	return 0;
}