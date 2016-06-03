#pragma once

#include <iostream>

class Player{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Render( CRenderContext& renderContext );
	bool Player::IsHit(CVector3 pos);
	void Draw() {}
private:
	CSkinModelData	modelData;		//���f���f�[�^�B
	CSkinModel		model;			//���f���B
	CVector3		position;		//���W�B
};