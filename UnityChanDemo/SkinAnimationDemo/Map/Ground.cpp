#include "stdafx.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "Map/Ground.h"
#include "Player/Player.h"
#include "tkEngine/Physics/tkCollisionAttr.h"
#include "Scene/GameScene.h"
#include "tkEngine/nature/tkSky.h"
#include "GameCamera.h"

Ground* g_ground = NULL;
LPD3DXMESH testMesh;

Ground::Ground()
{

}
Ground::~Ground()
{
}
void Ground::OnDestroy()
{
	DeleteGO(&terrain);
}
bool Ground::Start()
{
	switch (initStep) {
	case InitStep_Load: {
		g_ground = this;
		AddGO(GetPriority(), &terrain);
		const char* textures[] = {
			NULL
		};
		terrain.Init("Assets/modelData/ground.X", NULL, textures, g_camera->GetCamera(), gameScene->GetDefaultLight());
		initStep = InitStep_Wait;
	}break;
	case InitStep_Wait: {
		if (terrain.IsStart()) {
			//�n�ʂ�Start�֐������������B
			return true;
		}
	}break;
	}
	
	return false;
}

void Ground::Update() 
{
	//skinModel.Update(CVector3(0.0f, 0.0f, 0.0f), CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
}
void Ground::Render(CRenderContext& renderContext) 
{
	//skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
