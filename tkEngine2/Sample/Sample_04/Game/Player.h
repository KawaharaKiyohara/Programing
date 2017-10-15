#pragma once
class Player : public IGameObject
{
public:
	////////////////////////////////////////////
	//�����o�֐��B
	////////////////////////////////////////////
	Player();
	~Player();
	/*!
	*@brief	Update�̒��O�ŌĂ΂��J�n�����B
	*@details
	* �{�֐���true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����</br>
	* Update�֐����Ă΂�o���܂��Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �Q�[���I�u�W�F�N�g�̏������ɕ����t���[��������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v�Ȃǂ��g����</br>
	* �K�؂ɏ��������s���Ă��������B
	*/
	bool Start();
	/*!
	*@brief	�X�V�B
	*/
	void Update();
	/*!
	*@brief	�`��B
	*/
	void Render(CRenderContext& rc);
	////////////////////////////////////////////
	//�����o�ϐ��B
	////////////////////////////////////////////
	CSkinModel m_skinModel;			//�L�����N�^�X�L�����f���B
	CSkinModelData m_skinModelData;	//�X�L�����f���f�[�^�B
};

