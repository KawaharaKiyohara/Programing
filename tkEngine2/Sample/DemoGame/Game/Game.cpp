#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 50.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 50.0f, 150.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(1000.0f);
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	m_animClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/damage.tka");
	
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animation.Init(m_skinModelData, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_idle);
	return true;
}
void Game::Update()
{
	//�㉺���E�̃L�[���͂ɂ��ړ������B
	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	if (Pad(0).IsTrigger(enButtonA)) {
		//Play�֐��̑������͕⊮���ԁB
		m_animation.Play(enAnimationClip_idle, 0.2f);
	}
	//B�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonB)) {
		m_animation.Play(enAnimationClip_run, 0.2f);
	}
	//Y�{�^���������ꂽ������A�j���[�V�������Đ�����B
	else if (Pad(0).IsTrigger(enButtonY)) {
		m_animation.Play(enAnimationClip_walk, 0.2f);
	}
	else if (Pad(0).IsTrigger(enButtonX)) {
		m_animation.Play(enAnimationClip_jump, 0.2f);
	}
	else if (Pad(0).IsTrigger(enButtonRB1)) {
		m_animation.Play(enAnimationClip_damage, 0.2f);
	}
	
	
	m_animation.Update(GameTime().GetFrameDeltaTime());
	CQuaternion qRot = CQuaternion::Identity;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//�Q�Ă�̂ŋN�����B
	//���[���h�s����X�V�B
	m_skinModel.Update(CVector3::Zero, qRot, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	//�`��B
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}