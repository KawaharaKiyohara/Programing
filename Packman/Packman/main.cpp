#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkVertexBuffer.h"
using namespace tkEngine;
class CTestGameObject : public IGameObject {
	/*!
	*@brief	�X�V
	*/
	virtual void Update() override
	{
		//���_�o�b�t�@�̍쐬�e�X�g�B
		struct SVertex {
			float pos[4];
			float color[4];
		};
		SVertex vertices[] = {
			{
				(10.0f, 20.0f, 15.0f, 1.0f),
				(1.0f, 1.0f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
		};
		CVertexBuffer vb;
		vb.Create(sizeof(vertices), D3DFVF_XYZW | D3DFVF_DIFFUSE, vertices);
		vb.Release();

	}
	/*!
	*@brief	�`��
	*/
	virtual void Render(CRenderContext& renderContext) override
	{
		renderContext.SetRenderCommand(CRenderCommand_Clear(
			0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0
		));
	}
};
int WINAPI wWinMain(
	HINSTANCE hInst, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow 
){
	//�������B
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//�R�}���h�o�b�t�@�̃T�C�Y�̃e�[�u���B
	u32 commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//�����_�����O�R���e�L�X�g�͈�{
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	CEngine::GetInstance().Init( initParam );	//�������B
	CGameObjectManager::GetInstance().NewGameObject<CTestGameObject>(0);
	CEngine::GetInstance().RunGameLoop();		//�Q�[�����[�v�����s�B
	
	return 0;
}