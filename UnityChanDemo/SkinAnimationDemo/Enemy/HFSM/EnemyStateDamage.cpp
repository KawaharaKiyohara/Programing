/*!
 * @brief	��������ԁB
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDamage.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "GameCamera.h"

namespace {
	SParicleEmitParameter emitterParam =
	{
		"Assets/effect/Eff_water_2.png",	//const char* texturePath;						//!<�e�N�X�`���̃t�@�C���p�X�B
		CVector3(1.5f, 0.0f, 0.0f),		//CVector3	initVelocity;						//!<�����x�B
		2.0f,						//float		life;								//!<�����B�P�ʂ͕b�B
		0.01f,							//float		intervalTime;						//!<�������ԁB�P�ʂ͕b�B
		0.5f,							//float		w;									//!<�p�[�e�B�N���̕��B
		0.5f,							//float		h;									//!<�p�[�e�B�N���̍����B
		CVector3(0.0f, 0.1f, 0.0f),		//CVector3	initPositionRandomMargin;			//!<�����ʒu�̃����_�����B
		CVector3(0.0f, 0.2f, 0.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<�����x�̃����_�����B
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{											//!<CVector4	uvTable[4];			UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
		CVector4(0.5f,  0.0f, 0.75f, 0.5f),
		CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UV�e�[�u���̃T�C�Y�B
		CVector3(0.0f, 0.0f, 0.0f),	//CVector3	gravity;							//!<�d�́B
		true,							//bool		isFade;								//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.5f,							//float		fadeTime;							//!<�t�F�[�h���鎞�ԁB
		1.0f,							//float		initAlpha;							//!<�����A���t�@�l�B
		true,							//bool		isBillboard;						//!<�r���{�[�h�H
		2.0f,							//float		brightness;							//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,								//int		alphaBlendMode;						//!<0�����������A1���Z�����B
	};
}
/*!
 * @brief	�R���X�g���N�^�B
 */
EnemyStateDamage::EnemyStateDamage(Enemy* enemy) :
	IEnemyState(enemy),
	dmgCollisionGroupID(0),
	particleEmitter(NULL)
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
EnemyStateDamage::~EnemyStateDamage()
{
}
void EnemyStateDamage::Update() 
{
	//enemy->PlayAnimation(Enemy::enAnimDamage);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateDamage::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
	dmgCollisionGroupID = enterArg.arg[0];
	enemy->PlayAnimationForce(Enemy::enAnimDamage);
	//�p�[�e�B�N���G�~�b�^�[��o�^�B
	particleEmitter = NewGO<CParticleEmitter>(0);
	particleEmitter->Init(g_random, g_camera->GetCamera(), emitterParam, enemy->GetPosition());
}
void EnemyStateDamage::Leave()
{
}
