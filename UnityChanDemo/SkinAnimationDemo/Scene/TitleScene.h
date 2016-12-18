/*!
 *@brief	�^�C�g���V�[���B
 */

#pragma once


#include "tkEngine/Sound/tkSoundSource.h"

class TitleScene : public IGameObject{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	TitleScene();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~TitleScene();
	void OnDestroy() override;
	void Update() override;
	bool Start() override;
private:
	CSoundSource bgmSoundSource;
};