#pragma once

class Player {
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Render( CRenderContext& renderContext );
	bool Player::IsHit(CVector3 pos);
private:
	CSkinModelData	modelData;		//���f���f�[�^�B
	CSkinModel		model;			//���f���B
	CVector3		position;		//���W�B
};