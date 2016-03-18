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
	InitParam initParam;
	initParam.hInstance = hInst;
	Engine::GetInstance()->Init( initParam );	//�������B
	Engine::GetInstance()->RunGameLoop();		//�Q�[�����[�v�����s�B
	Engine::GetInstance()->Final();				//�I�������B
	return 0;
}