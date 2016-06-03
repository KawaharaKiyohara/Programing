/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Tiger.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------

const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
D3DXVECTOR4				g_ambientLight;						//����

const int NUM_TIGER = 2;	//�g���̐��B
Camera camera;				//�J�����B
Tiger tiger[NUM_TIGER];		//�ՁB



/*!-----------------------------------------------------------------------------
 *@brief	���C�g���X�V�B
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	g_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[3] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	
	//�f�B�t���[�Y���C�g�B
	g_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.4f, 0.6f, 1.0f);
	g_diffuseLightColor[3] = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);

	//�����B
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//���C�g���������B
	ZeroMemory( g_diffuseLightDirection, sizeof(g_diffuseLightDirection) );
	ZeroMemory( g_diffuseLightColor, sizeof(g_diffuseLightColor) );
	
	//�Ղ��������B
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Init(g_pd3dDevice);
		int y = i / 10;
		int x = i % 10;
		tiger[i].SetLocalPosition(D3DXVECTOR3(0.5f * x, 0.5f * y, 0.0f));
	}
	tiger[1].SetParent(&tiger[0]);
	//�J�����̏������B
	camera.Init();

}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	//�g����`��B
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			g_diffuseLightDirection,
			g_diffuseLightColor,
			g_ambientLight,
			LIGHT_NUM
			);
	}
	
	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�J�����̍X�V
	camera.Update();
	//�Ղ̍X�V�B
	tiger[0].Update();
	tiger[1].Update();
	if (GetAsyncKeyState(VK_SHIFT)) {
		if (GetAsyncKeyState(VK_LEFT)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.x -= 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.x += 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_UP)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.y += 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.y -= 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState('W')) {
			D3DXVECTOR3 pos = tiger[1].GetLocalPosition();
			pos.x -= 0.02f;
			tiger[1].SetLocalPosition(pos);
		}
	}
	else {
		if (GetAsyncKeyState(VK_LEFT)) {
			D3DXQUATERNION rot = tiger[0].GetRotation();
			D3DXQUATERNION addRot;
			D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.01f);
			rot = rot * addRot;
			tiger[0].SetLocalRotation(rot);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			D3DXQUATERNION rot = tiger[1].GetLocalRotation();
			D3DXQUATERNION addRot;
			D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.01f);
			rot = rot * addRot;
			tiger[1].SetLocalRotation(rot);
		}
	}
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Release();
	}
}
