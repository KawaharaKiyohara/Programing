/*!
 * @brief	�o�o�����̃v���C���[
 */

#pragma once

#include "CardSelectPerfomance.h"

class Card;
class ICardSelect;

class Player : public IGameObject{
public:
	//�X�e�[�^�X�B
	enum EnState {
		enStateIdle,		//�ҋ@�B
		enStateSelectCard,	//�J�[�h�I�𒆁B
		enStateSelectPerformance,	//�J�[�h�I�����o�B
	};
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	/*!
	* @brief	��Ԃ��擾�B
	*/
	EnState GetState() const
	{
		return state;
	}
	/*!
	 * @brief	�J�[�h��ǉ��B
	 */
	void AddCard(Card* card)
	{
		cardList.push_back(card);
	}
	/*!
	* @brief	�v���C���[�ԍ���ݒ�B
	*/
	void SetPlayerNo(int no)
	{
		playerNo = no;
	}
	/*!
	* @brief	�X�e�[�^�X�؂�ւ��B
	*/
	void ChangeState(EnState state);
	
	/*!
	* @brief	�J�[�h����������ɂȂ�v���C���[��ݒ�B
	*/
	void SetTargetPlayer(Player* targetPlayer)
	{
		this->targetPlayer = targetPlayer;
	}
	/*!
	* @brief	�J�[�h�̃��X�g���擾�B
	*/
	std::vector<Card*>& GetCardList()
	{
		return cardList;
	}
	/*!
	* @brief	�J�[�h�̍��W���X�V�B
	*/
	void UpdateCardPosition();
private:
	/*!
	* @brief	�d���J�[�h�����X�g���珜���B
	*/
	void EraseMultipyCardFromList();
	
private:
	
	std::vector<Card*>		cardList;				//!<�z��ꂽ�J�[�h�̃��X�g�B
	int						playerNo = 0;			//!<�v���C���[�ԍ��B
	EnState					state = enStateIdle;	//!<�X�e�[�g�B
	Player*					targetPlayer;			//!<�J�[�h�������v���C���[�B
	ICardSelect*			selectCard = NULL;
	CardSelectPerfomance	cardSelectPerfomance;	//!<�J�[�h�I���p�t�H�[�}���X�B
};