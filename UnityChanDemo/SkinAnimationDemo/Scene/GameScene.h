/*!
 *@brief	�Q�[���V�[���B
 */

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"

class Map;
class Ground;
class PlayerHPBar;
class PlayerMPBar;
class Sky;
class UnityChanInstance;
class GameOver2D;

class GameScene : public IGameObject{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	GameScene();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~GameScene();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	//����擾�B
	Sky* GetSky() const
	{
		return sky;
	}
	//�f�t�H���g���C�g�̎擾�B
	CLight& GetDefaultLight()
	{
		return defaultLight;
	}
private:
	enum InitStep {
		InitStep_Load,
		InitStep_WaitLoad,
	};
	enum State {
		State_Play,	//�Q�[���v���C���B
		State_Over,	//�Q�[���I�[�o�[�B
	};
	Map*				map = NULL;
	Ground*				ground = NULL;
	PlayerHPBar*		playerHPBar = NULL;
	PlayerMPBar*		playerMPBar = NULL;
	Sky* 				sky = NULL;
	UnityChanInstance*	unityChanInstance = NULL;
	CSoundSource		bgmSoundSource;
	InitStep			initStep = InitStep_Load;
	State				state = State_Play;
	float				gameOverTimer = 0.0f;
	GameOver2D*			gameOver2D = NULL;
	CLight				defaultLight;		//�f�t�H���g���C�g�B
};

extern GameScene* gameScene;