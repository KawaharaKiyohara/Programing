/*!
 * @brief	�J�[�h�I�������̊��N���X�B
 */

#pragma once

class Player;
/*!
 * @brief	�J�[�h�I�������B
 */
class ICardSelect : public IGameObject{
public:
	/*!
	 * @brief	�������B
	 *@param[in]	targetPlayer	�J�[�h����������ɂȂ�v���C���[�B
	 */
	void Init( Player* targetPlayer );
	bool Start() override;
	void Update() override;
	/*!
	 * @brief	�J�[�h�����肵��������B
	 */
	bool IsDecide() const
	{
		return state == enState_Decide;
	}
	/*!
	 * @brief	�I�������J�[�h�̔ԍ����擾�B
	 */
	int GetSelectCardNo() const
	{
		return selectCardNo;
	}
private:
	virtual void UpdateSelectCard() = 0;
protected:
	enum EnState{
		enState_SelectCard,
		enState_Decide,
	};
	Player*		targetPlayer = NULL;
	int			selectCardNo = 0;				//�I�������J�[�h�̔ԍ��B
	CLight		selectLight;					//�I���������̃��C�g�B
	EnState		state = enState_SelectCard;		//�J�[�h�I�𒆁B
};

/*!
 * @brief	�v���C���[�̃J�[�h�I�������B
 */
class CardSelectPlayer : public ICardSelect
{
private:
	void UpdateSelectCard() override;
};
/*!
 * @brief	Com�̃J�[�h�I�������B
 */
class CardSelectCom : public ICardSelect
{
private:
	float timer = 0.0f;
private:
	bool Start() override;
	void UpdateSelectCard() override;
};