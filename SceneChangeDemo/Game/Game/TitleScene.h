/*!
 *@brief	�^�C�g���V�[���B
 */
#pragma once

class TitleScene : public IGameObject{
public:
	TitleScene();
	~TitleScene();
	bool Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
private:
	CSprite sprite;		//�X�v���C�g�B
	CTexture texture;	//�e�N�X�`���B
};