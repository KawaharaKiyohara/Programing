#include "stdafx.h"
#include "Tiger.h"

//�R���X�g���N�^
Tiger::Tiger()
{
	//�������B
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRotation);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	parent = NULL;
	localPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	localRotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}
//�f�X�g���N�^
Tiger::~Tiger()
{
	Release();
}

//�������B
void Tiger::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice);
}
//�e��ݒ�B
void Tiger::SetParent(Tiger* parent)
{
	//�e���ݒ肳�ꂽ�̂ŁA���[���h���W�����߂邽�߂ɁB��UUpdate���Ăяo���B
	Update();

	this->parent = parent;
	//�e���ݒ肳�ꂽ�̂ŁA���[�J�����W��e�̃��[�J�����W�ɕϊ�����B
	D3DXMATRIX mParentWorldInv = parent->GetWorldMatrix();
	D3DXMatrixInverse(&mParentWorldInv, NULL, &mParentWorldInv);
	D3DXVECTOR4 pos;
	D3DXVec3Transform(&pos, &position, &mParentWorldInv);
	localPosition.x = pos.x;
	localPosition.y = pos.y;
	localPosition.z = pos.z;

	//��]�N�H�[�^�j�I�������[�J����]�N�H�[�^�j�I���ɕϊ�����B
	D3DXQUATERNION qParentRotInv = parent->GetRotation();
	D3DXQuaternionInverse(&qParentRotInv, &qParentRotInv);
	localRotation = rotation * qParentRotInv;
}
//�X�V�B
void Tiger::Update()
{
	if (parent) {
		//�e������B
		D3DXMATRIX mParentWorld = parent->GetWorldMatrix();
		D3DXQUATERNION qParentRot = parent->GetRotation();
		//�e�̃��[���h�s�����Z���āA���[�J�����W�����[���h���W�ɕϊ�����B
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		
		rotation = localRotation * qParentRot;
	}
	else {
		position = localPosition;
		rotation = localRotation;
	}

	//���[���h�s������߂�B
	D3DXVECTOR4 pos;
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&mRotation, &rotation);
	mWorld = mRotation * mWorld;
}
//�`��B
void Tiger::Render( 
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix, 
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
)
{
	model.Render(pd3dDevice, mWorld, mRotation, viewMatrix, projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight);

}
//�J���B
void Tiger::Release()
{}