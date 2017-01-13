#pragma once

#include "Common/CardDeck.h"
#include "Player.h"
#include "tkEngine/Sound/tkSoundSource.h"

/*!
 *@brief	�Q�[���V�[���B
 */
class GameScene :
	public IGameObject
{
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
	 *@brief	�J�n�֐��B
	 *@details
	 * �������Ȃǂ����̊֐��Ɏ������Ă��������B</br>
	 * ���̊֐���true��Ԃ��Ɩ{�ِ��͈ȍ~�̃t���[���ł͌Ă΂�Ȃ��Ȃ�܂��B</br>
	 * �����ăQ�[���I�u�W�F�N�g�̏�Ԃ������������ɂȂ�Update�֐����Ă΂��悤�ɂȂ�܂��B</br>
	 *@return	true���A���Ă����珉���������B
	 */
	bool Start() override;
	/*!
	 *@brief	�X�V�֐��B
	 */
	void Update() override;
	void Render(CRenderContext& rc);
	void OnDestroy() override;
	/*!
	*@brief	�J�������擾�B
	*/
	const CCamera& GetCamera() const
	{
		return camera;
	}
	/*!
	*@brief	���C�g���擾�B
	*/
	CLight& GetLight() 
	{
		return light;
	}
private:
	/*!
	*@brief	���s����B
	*/
	bool Judgement();
private:
	//�������X�e�[�^�X
	enum EnInitState{
		enInitState_Init00,			//!<�������X�e�b�v00�B
		enInitState_WaitInit,
		
	};
	enum EnGameStep {
		enGameStep_DealCards,		//!<�J�[�h��z��B
		enGameStep_WaitFadeIn,		//!<�t�F�[�h�C���҂��B
		enGameStep_SelectPlayer,	//!<�v���C���[���J�[�h��I�𒆁B
		enGameStep_SelectCom,		//!<COM���J�[�h��I�𒆁B
		enGameStep_Over,			//!<�I���B
		enGameStep_WaitFadeOut,		//!<�t�F�[�h�A�E�g�҂��B
	};
	static const int NUM_PLAYER = 2;
	EnInitState m_initState = enInitState_Init00;
	CardDeck cardDeck;				//!<�J�[�h�f�b�L�B
	CCamera camera;					//!<�J�����B
	CLight  light;					//!<���C�g�B
	Player  playerList[NUM_PLAYER];		//!<�v���C���[�̃��X�g
	CTexture*	textureBG;				//!<�w�i�̃e�N�X�`���B
	CSprite		spriteBG;				//!<�w�i�̃X�v���C�g�B
	EnGameStep gameStep = enGameStep_DealCards;
	// HansOn-1 BGM���Đ����邽�߂�CSoundSource�̃����o�ϐ���ǉ��B
	CSoundSource* bgmSource = NULL;
};

extern GameScene* g_gameScene;
