/*!
 * @brief	�^�C�v0�̓G�B
 */

#pragma once

#include "CharacterController.h"
#include "Enemy/Enemy.h"

class IEnemyState;
/*!
 * @brief	�^�C�v0�̓G�B
 */
class Enemy_00 : public Enemy{
	//���
	enum EnLocalState {
		enLocalState_Search,	//�p�j���B
		enLocalState_Find,	//������ԁB
	};
public:
	Enemy_00();
	~Enemy_00();
	void Init( const char* modelPath, CVector3 pos, CQuaternion	rotation);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	
	void InitHFSM();
private:
	std::vector<IEnemyState*>		states;				//�X�e�[�g�̃��X�g�B
	CVector3						initPosition;		//�����ʒu�B
	EnLocalState					state;				//�X�e�[�g�B
	CTexture						specMap;			//�X�y�L�����}�b�v�B
	CTexture						normalMap;			//�@���}�b�v�B
	CharacterController				characterController;	//�L�����N�^�R���g���[���B
};