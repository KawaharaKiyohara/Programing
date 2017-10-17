#pragma once
class Game : public IGameObject
{
public:
	/////////////////////////////////////////////
	//�����o�֐��B
	/////////////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	/*!
	*@brief	Render�֐������s���ꂽ��ŌĂ΂��`�揈��
	*@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*/
	void PostRender(CRenderContext& rc);
	/////////////////////////////////////////////
	//�����o�ϐ��Ƃ��B
	/////////////////////////////////////////////
	CSkinModel m_skinModel;			//�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
	CSprite m_sprite;				//�X�v���C�g�B
	CShaderResourceView m_texture;	//�e�N�X�`���B
};

