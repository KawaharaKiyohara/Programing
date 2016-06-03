#include "stdafx.h"
#include "GameCamera.h"
#include "court.h"


Court::Court()
{

}
Court::~Court()
{

}
void Court::Init()
{
	//���f���f�[�^�̃��[�h�B
	modelData.LoadModelData("Assets/modelData/court.x", NULL);
	//���f���Ƀ��f���f�[�^���Z�b�g�B
	model.Init(&modelData);
}

void Court::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}