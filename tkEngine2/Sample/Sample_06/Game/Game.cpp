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
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	//�e�N�X�`�������[�h�B
	m_texture.CreateFromDDSTextureFromFile(L"sprite/mikyan.dds");
	m_sprite.Init(m_texture, 400, 300);
	return true;
}
void Game::Update()
{
	//���[���h�s��̍X�V�B
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	m_sprite.Update({-200.0f, 200.0f, 1.0f}, CQuaternion::Identity, CVector3::One);
}
void Game::PostRender(CRenderContext& rc)
{
	//�X�v���C�g��`��B
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
void Game::Render(CRenderContext& rc)
{
	//���f����`��B
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}