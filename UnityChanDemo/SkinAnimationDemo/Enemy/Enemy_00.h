/*!
 * @brief	�^�C�v0�̓G�B
 */

#pragma once

#include "CharacterController.h"

/*!
 * @brief	�^�C�v0�̓G�B
 */
class Enemy_00 : public IGameObject{
	enum EnAnimation {
		enAnimStand,
		enAnimWalk,
		enAnimAttack,
	};
	//���
	enum EnState {
		enState_Search,	//�p�j���B
		enState_Find,	//������ԁB
	};
public:
	Enemy_00();
	~Enemy_00();
	void Init( const char* modelPath, CVector3 pos, CQuaternion	rotation);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	void PlayAnimation(EnAnimation animNo);
private:
	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//�X�L�����f���B
	CAnimation						animation;			//�A�j���[�V�����B
	CLight							light;				//���C�g�B
	CVector3						position;			//�ʒu
	CQuaternion						rotation;			//��]�B
	CVector3						initPosition;		//�����ʒu�B
	EnState							state;				//�X�e�[�g�B
	CVector3						moveDirection;		//�i�s�����B
	float							timer;				//�^�C�}
	CharacterController				characterController;	//�L�����N�^�R���g���[���B
	int								currentAnimNo;			//���݂̃A�j���[�V�����ԍ��B
	float							moveSpeed;
};