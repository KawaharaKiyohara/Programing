#include "stdafx.h"
#include "ball.h"
#include "GameCamera.h"
#include "main.h"

Ball::Ball()
{
	position.x = 0.0f;
	position.y = 0.125f;
	position.z = 0.0f;
	moveSpeed.x = -0.06f;
	moveSpeed.y = 0.0f;
	moveSpeed.z = 0.06f;
}
Ball::~Ball()
{

}
void Ball::Init()
{
	//���f���f�[�^�̃��[�h�B
	modelData.LoadModelData("Assets/modelData/ball.x", NULL);
	//���f���Ƀ��f���f�[�^���Z�b�g�B
	model.Init(&modelData);
}
void Ball::Update()
{
	CVector3 pos = position;
	pos.Add(moveSpeed);
	if (pos.x < COURT_MIN_X || pos.x > COURT_MAX_X) {
		moveSpeed.x *= -1.0f;
	}else if (pos.z < COURT_MIN_Z || pos.z > COURT_MAX_Z) {
		moveSpeed.z *= -1.0f;
	}else if (game->GetPlayer()->IsHit(position) && moveSpeed.x < 0.0f) {
		//�v���C���[�Ƃ̏Փ˔���B
		moveSpeed.x *= -1.0f;
	}
	else {
		position = pos;
	}
	
	model.UpdateWorldMatrix(position, CQuaternion::Identity, CVector3::One);
}
void Ball::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}