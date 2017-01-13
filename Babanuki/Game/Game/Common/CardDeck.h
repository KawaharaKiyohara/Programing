/*!
 * @brief	�J�[�h�f�b�L�N���X�B
 */

#pragma once

class Card;

class CardDeck : public IGameObject{
private:

public:
	CardDeck();
	~CardDeck();
	bool Start() override;
	void Update() override {

	}
	/*
	*@brief ���g�p�J�[�h�������_���Ɏ擾�B
	*@return	���g�p�J�[�h�����݂��Ȃ��Ȃ�����NULL��Ԃ��܂��B
	*/
	Card* GetUnuseCardRandom();
	/*
	*@brief ���������I�����������B
	*/
	bool IsInited() const;
private:
	static const int NUM_CARD = 53;		//!<�g�����v�̐��B
	int		numUnuseCard = NUM_CARD;	//!<���g�p�J�[�h�̐��B
	bool    useFlags[NUM_CARD];			//!<�J�[�h�g�p���t���O�B
	Card*	cardList[NUM_CARD];			//!<�J�[�h�̃��X�g�B
};