#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	
}
Player::~Player()
{
}

/*!
*@brief	初期化。
*/
bool Player::Start()
{
	m_skinModelData.Load(L"Assets/modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);

	//アニメーションクリップのロード。
	m_animationClip[enAnimationClip_idle].Load(L"Assets/animData/player/idle.tka", L"Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].Load(L"Assets/animData/player/run.tka", L"Run");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].Load(L"Assets/animData/player/walk.tka", L"Walk");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	CAnimationClip* animClip[] = {
		&m_animationClip[enAnimationClip_idle],
		&m_animationClip[enAnimationClip_run],
		&m_animationClip[enAnimationClip_walk],
	};
	m_animation.Init(m_skinModelData, animClip, 3);
	m_animation.Play(L"Idle");

	return true;
}
void Player::Update() 
{
	CVector3 inputPad;
	inputPad.x = Pad(0).GetRStickXF();
	inputPad.y = Pad(0).GetRStickYF();
	inputPad.z = 0.0f;
	if (inputPad.Length() > 0.8f) {
		m_animation.Play(L"Run", 0.2);
	}else if (inputPad.Length() > 0.0f) {
		m_animation.Play(L"Walk", 0.2);
	}else{
		m_animation.Play(L"Idle", 0.2f);
	}
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_skinModel.Update({ 0.0f, 0.0f, 0.0f }, qRot, CVector3::One);
	m_animation.Update(GameTime().GetFrameDeltaTime());
}
void Player::Render(CRenderContext& rc) 
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}