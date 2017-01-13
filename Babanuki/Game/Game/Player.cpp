/*!
 * @brief	�v���C���[�B
 */

#include "stdafx.h"
#include "Player.h"
#include "Common/Card.h"
#include "ICardSelect.h"
#include "tkEngine/Sound/tkSoundSource.h"

Player::Player()
{
}
Player::~Player()
{
}
bool Player::Start()
{
	//�d�����Ă���J�[�h�������B
	EraseMultipyCardFromList();
	//�z��ꂽ�J�[�h�����ׂăA�N�e�B�u�ɂ���B
	for (auto card : cardList)
	{
		card->SetActiveFlag(true);
	}
	UpdateCardPosition();
	return true;
}
void Player::UpdateCardPosition()
{
	const CVector2& cardSize = Card::GetSize();
	//�J�[�h��S���܂񂾕��B
	float cardAllHalfWidth = ((cardSize.x * 0.5f) * cardList.size())*0.5f;
	CVector3 pos = CVector3::Zero;
	pos.x = -cardAllHalfWidth;
	if (playerNo == 0) {
		pos.y = -300.0f;
	}
	else {
		pos.y = 300.0f;
	}
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY, CMath::PI);
	for (int i = 0; i < cardList.size(); i++) {
		pos.x = -cardAllHalfWidth + (cardSize.x * 0.5f) * i;
		pos.z = -0.1f * i;
		cardList[i]->SetPosition(pos);
		
		if (playerNo == 1) {
			cardList[i]->SetRotation(rot);
		}
		else {
			cardList[i]->SetRotation(CQuaternion::Identity);
		}
	}
}
/*!
* @brief	�X�e�[�^�X�؂�ւ��B
*/
void Player::ChangeState(Player:: EnState state)
{
	this->state = state;
	if (state == enStateSelectCard) {
		if (playerNo == 0) {
			selectCard = NewGO<CardSelectPlayer>(0);
		}
		else {
			selectCard = NewGO<CardSelectCom>(0);
		}
		selectCard->Init(targetPlayer);
	}
}
/*!
* @brief	�d���J�[�h�����X�g���珜���B
*/
void Player::EraseMultipyCardFromList()
{
	//�ԍ����d�����Ă���J�[�h�����O���Ă����B
	std::unique_ptr<bool[]> removeFlags;
	removeFlags.reset(new bool[cardList.size()]);
	memset(removeFlags.get(), 0, sizeof(bool) * cardList.size());
	std::vector<Card*> newCardList;
	newCardList.reserve(cardList.size());
	for (int i = 0; i < cardList.size(); i++) {
		if (removeFlags[i]) {
			//�폜�̃t���O�����łɗ����Ă���̂Œ��ׂ�K�v�Ȃ��B
			continue;
		}
		for (int j = i + 1; j < cardList.size(); j++) {
			if (removeFlags[j]) {
				//�폜�t���O�����ɗ����Ă���̂Œ��ׂ�K�v�Ȃ��B
				continue;
			}
			if (cardList[i]->GetNo() == cardList[j]->GetNo()) {
				//�폜�B
				removeFlags[i] = true;
				removeFlags[j] = true;
				//��A�N�e�B�u�ɁB
				cardList[i]->SetActiveFlag(false);
				cardList[j]->SetActiveFlag(false);
				break;
			}
		}
		if (!removeFlags[i]) {
			//�����c��B
			newCardList.push_back(cardList[i]);
		}
	}
	//�d���Ȃ��̃J�[�h���X�g���R�s�[�B
	cardList = std::move(newCardList);
}
void Player::Update()
{
	
	switch (state) {
	case enStateIdle:
		break;
	case enStateSelectCard:
		if (selectCard->IsDecide()) {
			//HandsOn-4 �J�[�h���艹�̍Đ�
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init("Assets/sound/enter.wav");
			se->Play(false);
			//����B
			AddGO(0, &cardSelectPerfomance);
			int selectCardNo = selectCard->GetSelectCardNo();
			std::vector<Card*>& targetCardList = targetPlayer->GetCardList();
			Card* multiplyCard = NULL;
			for (Card* card : cardList) {
				if (card->GetNo() == targetCardList[selectCardNo]->GetNo()) {
					//�d���J�[�h�����������B
					multiplyCard = card;
					break;
				}
			}
			cardSelectPerfomance.Init(playerNo, targetCardList[selectCardNo], multiplyCard);
			state = enStateSelectPerformance;
		}
		break;
	case enStateSelectPerformance:
		if (cardSelectPerfomance.IsEnd()) {
			int selectCardNo = selectCard->GetSelectCardNo();
			//�܂��I�������J�[�h���v���C���[�̎�D�ɑ}������B
			std::vector<Card*>& targetCardList = targetPlayer->GetCardList();
			Card* card = targetCardList[selectCardNo];
			cardList.push_back(card);
			//����̃J�[�h���X�g����͏����B
			targetCardList.erase(std::find(targetCardList.begin(), targetCardList.end(), card));
			//�d���J�[�h�������B
			EraseMultipyCardFromList();
			UpdateCardPosition();
			state = enStateIdle;
		}
		break;
	}
}