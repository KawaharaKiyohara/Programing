/*!
 * @brief	�J�[�h�f�b�L�N���X�B
 */

#include "stdafx.h"
#include "Common/CardDeck.h"
#include "Common/Card.h"

CardDeck::CardDeck()
{
	memset(useFlags, 0, sizeof(useFlags));
}
CardDeck::~CardDeck()
{
	for(auto& card : cardList){
		DeleteGO(card);
	}
}
/*
*@brief ���������I�����������B
*/
bool CardDeck::IsInited() const
{
	for (auto& card : cardList) {
		if (!card || !card->IsStart()) {
			//�I����Ă��Ȃ��B
			return false;
		}
	}
	//�I���B
	return true;
}
/*
*@brief ���g�p�J�[�h�������_���Ɏ擾�B
*@return	���g�p�J�[�h�����݂��Ȃ��Ȃ�����NULL��Ԃ��܂��B
*/
Card* CardDeck::GetUnuseCardRandom()
{
	if (numUnuseCard == 0) {
		//�����Ȃ���B
		return NULL;
	}
	int pickUpCardNo = g_random.GetRandInt() % numUnuseCard;
	int currentUnuseCardNo = 0;
	//���g�p�J�[�h��T���B
	for (int i = 0; i < NUM_CARD; i++) {
		if (useFlags[i]) {
			//�g�p���B
			continue;
		}
		
		if (pickUpCardNo == currentUnuseCardNo) {
			//���g�p�J�[�h�𔭌��B
			//���g�p�J�[�h�����炷�B
			numUnuseCard--;
			//�g�p���ɂ���B
			useFlags[i] = true;
			return cardList[i];
		}
		currentUnuseCardNo++;
	}
	return NULL;
}
bool CardDeck::Start()
{
	static EnCardType cardType[] = {
		enCardType_Heart,
		enCardType_Dia,
		enCardType_Spade,
		enCardType_Clover,
	};
	int numCard = 0;
	for( auto type : cardType ){
		for(int i = 0; i < 13; i++ ){
			//�J�[�h�𐶐����Ă����B
			Card* card = NewGO<Card>(0);
			card->Init(type, i+1);
			cardList[numCard] = card;
			numCard++;
		}
	}
	//�Ō�ɃW���[�J�[�𐶐��B
	Card* card = NewGO<Card>(0);
	card->Init(enCardType_Joker, -1);
	cardList[numCard] = card;
	return true;
}