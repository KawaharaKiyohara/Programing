/*!
 *@brief	�Q�[���V�[���B
 */
#pragma once

/*!
 *@brief	�Q�[���V�[���B
 */
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
	/*!
	 *@brief	�J�n�����B
	 */
	bool Start() ;
	/*!
	 *@brief	�X�V�����B
	 */
	void Update();
private:
	CSoundSource* bgmSource;
};