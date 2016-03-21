#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

using namespace tkEngine;
class CTestGameObject : public IGameObject {
	/*!
	*@brief	�X�V
	*/
	virtual void Update() override
	{

	}
	/*!
	*@brief	�`��
	*/
	virtual void Render(const CRenderContext& renderContext) override
	{

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