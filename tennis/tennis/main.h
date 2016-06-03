#pragma once
#include "court.h"
#include "Player.h"
#include "ball.h"

/*!
* @brief	�Q�[���N���X
*/
class Game : public IGameObject {
public:
	//�R���X�g���N�^�B
	Game();
	//�f�X�g���N�^�B
	~Game();
	//Update���Ă΂��O�Ɉ�x�����Ă΂�鏈���B
	void Start();
	//�`��B
	void Render( CRenderContext& renderContext );
	//�X�V�B
	void Update();
	//�R�[�g���擾�B
	Court* GetCourt()
	{
		return &court;
	}
	//�v���C���[���擾�B
	Player* GetPlayer()
	{
		return &player;
	}
private:
	Court court;
	Player player;
	Ball ball;
};
extern Game* game;