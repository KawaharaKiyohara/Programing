#include "stdafx.h"
#include "player.h"
#include "GameCamera.h"

const float PLAYER_HALF_SIZE_X = 0.1f;	//�v���C���[��X�����̔����̃T�C�Y�B
const float PLAYER_HALF_SIZE_Z = 1.0f;	//�v���C���[��Z�����̔����̃T�C�Y�B


Player::Player()
{
	position = CVector3(-4.3f, 0.5f, 0.0f);
}
Player::~Player()
{
}
void Player::Init()
{
	//���f���f�[�^�̃��[�h�B
	modelData.LoadModelData("Assets/modelData/player.x", NULL);
	//���f���Ƀ��f���f�[�^���Z�b�g�B
	model.Init(&modelData);
}
void Player::Update()
{
	CVector3 nextPos = position;
	bool isPossibleMove = true;
	//�ړ������B
	if (KeyInput().IsUpPress()) {
		nextPos.z += 0.1f;
	}
	if (KeyInput().IsDownPress()) {
		nextPos.z -= 0.1f;
	}
	if (KeyInput().IsLeftPress()) {
		nextPos.x -= 0.1f;
	}
	 if (KeyInput().IsRightPress()) {
		nextPos.x += 0.1f;
	}
	if (nextPos.x >= 0.0f) {
		//�R�[�g�̉E�����Ɉړ����悤�Ƃ��Ă���B
		isPossibleMove = false;
	}
	if (isPossibleMove) {
		position = nextPos;
	}
	//���[���h�s����X�V�B
	model.UpdateWorldMatrix(position, CQuaternion::Identity, CVector3::One);
}
bool Player::IsHit(CVector3 pos)
{
	if (pos.x > position.x - PLAYER_HALF_SIZE_X
		&& pos.x < position.x + PLAYER_HALF_SIZE_X
		&&pos.z > position.z - PLAYER_HALF_SIZE_Z
		&& pos.z < position.z + PLAYER_HALF_SIZE_Z
		) {
		//�������Ă���B
		return true;
	}
	return false;
}
void Player::Render( CRenderContext& renderContext )
{
	//�`��B
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}