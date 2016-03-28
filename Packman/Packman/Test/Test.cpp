/*!
 * @brief	�e�X�g�N���X�B
 */
#include "stdafx.h"
#include "test.h"
#include "TestPrimitiveRender.h"
#include "TestBoxRender.h"
#include "tkEngine/tkEngine.h"

using namespace tkEngine;

void CTest::Start()
{
	//CGameObjectManager::GetInstance().NewGameObject<CTestPrimitiveRender>(0);
	CGameObjectManager::GetInstance().NewGameObject<CTestBoxRender>(0);
}
void CTest::Update()
{

}
void CTest::Render(tkEngine::CRenderContext& renderContext)
{
	renderContext.SetRenderCommand(CRenderCommand_Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0
		));
	D3DVIEWPORT9 vp = {
		0,
		0,
		s_cast<DWORD>(tkEngine::CEngine::Instance().GetScreenWidth()),
		s_cast<DWORD>(tkEngine::CEngine::Instance().GetScreenHeight()),
		0.0f,
		1.0f
	};
	renderContext.SetRenderCommand(CRenderCommand_SetViewport(vp));
}