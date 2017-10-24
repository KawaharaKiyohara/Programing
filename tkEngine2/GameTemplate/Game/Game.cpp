#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"

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
	skinModelData.Load(L"modelData/unityChan.cmo");
	skinModel.Init(skinModelData);

	skinModel.FindMaterial([&] (auto material){
		material->SetMaterialID(1);
	});
	//�f�B���N�V�������C�g(���z���݂����Ȃ���)���V�[���ɒǉ��B
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection({ 0.707f, -0.707f, 0.0f });
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });

	m_lig->SetLightingMaterialIDGroup(1 << 1);
	return true;
}
void Game::Update()
{
	skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}