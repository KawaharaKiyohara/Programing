/*!
 * @brief	�G�̊��N���X�B
 */
 
#pragma once


class Enemy : public IGameObject{
public:
	enum EnAnimation {
		enAnimStand,
		enAnimWalk,
		enAnimAttack,
		enAnimInvalid = 0xffffffff
	};
	Enemy() :
		currentAnimNo(enAnimInvalid),
		moveSpeed(0.0f),
		moveDirection(CVector3::AxisZ)
	{
	}
	virtual ~Enemy()
	{
	}
	void PlayAnimation(EnAnimation animNo)
	{
		if(currentAnimNo != animNo)
		{
			animation.PlayAnimation(animNo, 0.3f);
			currentAnimNo = animNo;
		}
	}
	void SetMoveSpeed(float moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}
	const CVector3& GetMoveDirection() const
	{
		return moveDirection;
	}
	void SetMoveDirection( const CVector3& dir )
	{
		moveDirection = dir;
	}
	void SetDirection(const CVector3& dir)
	{
		direction = dir;
	}
	const CVector3& GetPosition() const
	{
		return position;
	}
	bool IsPlayAnimation() const
	{
		return animation.IsPlay();
	}
protected:
	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//�X�L�����f���B
	CAnimation						animation;			//�A�j���[�V�����B
	CLight							light;				//���C�g�B
	CVector3						position;			//�ʒu
	CQuaternion						rotation;			//��]�B
	EnAnimation						currentAnimNo;		//���݂̃A�j���[�V�����ԍ��B
	float							moveSpeed;			//�ړ����x�B
	CVector3						moveDirection;		//�i�s�����B
	CVector3						direction;			//�����B
};