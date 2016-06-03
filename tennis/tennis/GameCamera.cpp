#include "stdafx.h"
#include "GameCamera.h"

GameCamera* gameCamera;

GameCamera::GameCamera()
{
	camera.SetPosition(CVector3(0.0f, 6.0f, -5.0f));
	camera.SetTarget(CVector3(0.0f, 0.0f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
}
GameCamera::~GameCamera()
{
}
CMatrix GameCamera::GetViewMatrix()
{
	return camera.GetViewMatrix();
}
//�v���W�F�N�V�����s��̎擾�B
CMatrix GameCamera::GetProjectionMatrix()
{
	return camera.GetProjectionMatrix();
}
void GameCamera::Update()
{
	camera.Update();
}