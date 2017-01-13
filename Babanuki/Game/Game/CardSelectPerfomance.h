/*!
 * @brief	�J�[�h�I�����o�B
 */
#pragma once

class Card;

class CardSelectPerfomance : public IGameObject{
public:
	CardSelectPerfomance();
	~CardSelectPerfomance();
	/*!
	* @brief	�������B
	*@param[in]	playerNo		�v���C���[�ԍ��B
	*@param[in]	selectCard		�I�������J�[�h�B
	*@param[in]	multiplyCard	�d���J�[�h�B�Ȃ��ꍇ��NULL�B
	*/
	void Init(int playerNo, Card* selectCard, Card* multiplyCard);
	bool Start() override;
	void Update() override;
	/*!
	 * @brief	�J�[�h�I�����o�̏I������B
	 */
	bool IsEnd() const
	{
		return execStep == enExecStep_End;
	}
private:
	//���s�X�e�b�v
	enum EnExecStep {
		enExecStep_PickupSelectCard,	//�I�������J�[�h�̃s�b�N�A�b�v���o�B
		enExecStep_RotateSelectCard,	//�I�������J�[�h�̔��]���o�B
		enExecStep_PickupMultiplyCard,	//�d���J�[�h�̃s�b�N�A�b�v���o�B
		enExecStep_RotateMultiplyCard,	//�d���J�[�h�̔��]���o�B
		enExecStep_Wait,				//�E�F�C�g�B
		enExecStep_End,
	};
	int playerNo = 0;
	Card* selectCard = NULL;
	Card* multiplyCard = NULL;
	float timer = 0.0f;
	EnExecStep execStep = enExecStep_PickupSelectCard;
};