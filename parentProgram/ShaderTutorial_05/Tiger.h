#pragma once

#include "Model.h"

//�ՃN���X�B
class Tiger {
public:
	//�R���X�g���N�^
	Tiger();
	//�f�X�g���N�^
	~Tiger();
	//�������B
	void Init( LPDIRECT3DDEVICE9 pd3dDevice );
	//�X�V�B
	void Update();
	//�`��B
	void Tiger::Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
	);
	//�J���B
	void Release();
	//�e��ݒ�B
	void SetParent(Tiger* parent);
	
	D3DXMATRIX GetWorldMatrix()
	{
		return mWorld;
	}
	D3DXMATRIX GetRotationMatrix()
	{
		return mRotation;
	}
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}
	D3DXQUATERNION GetRotation()
	{
		return rotation;
	}

	D3DXQUATERNION GetLocalRotation()
	{
		return localRotation;
	}
	void SetLocalRotation(D3DXQUATERNION rot)
	{
		localRotation = rot;
	}
	D3DXVECTOR3 GetLocalPosition()
	{
		return localPosition;
	}
	void SetLocalPosition(D3DXVECTOR3 pos)
	{
		localPosition = pos;
	}
private:
	Model					model;			//���f���B
	D3DXVECTOR3				position;		//���[���h���W�B
	D3DXVECTOR3				localPosition;	//���[�J�����W�B
	D3DXQUATERNION			rotation;		//��]�N�H�[�^�j�I���B
	D3DXQUATERNION			localRotation;	//���[�J����]�N�H�[�^�j�I���B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Tiger*					parent;			//�e�B
};