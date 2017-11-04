#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	m_springCamera.Init(MainCamera(), 1200.0f, false, 20.0f);
	return true;
}
void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 50.0f;
	//���_���v�Z����B
	CVector3 toPos = { 0.0f, 350.0f, 550.0f };
	CVector3 pos = target + toPos;	//�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���B
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}
void GameCamera::NotifyGameOver()
{
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void GameCamera::NotifyRestart()
{
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = true;
}