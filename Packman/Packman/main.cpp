#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

using namespace tkEngine;
int WINAPI wWinMain(
	HINSTANCE hInst, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow 
){
	//�������B
	SInitParam initParam;
	initParam.hInstance = hInst;
	CEngine::GetInstance().Init( initParam );	//�������B
	CEngine::GetInstance().RunGameLoop();		//�Q�[�����[�v�����s�B
	
	return 0;
}