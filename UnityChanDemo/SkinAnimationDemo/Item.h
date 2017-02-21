#pragma once
#include "Light/InGameLight.h"
/*
�񕜃A�C�e���N���X
*/
class Item : public IGameObject
{
public:
	Item();
	~Item();
	
	void Init(CVector3);
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext&) override;


private:
	CSkinModel		skinModel;
	CSkinModelData	skinModelData;
	CVector3		position;
	CQuaternion		rotation;
};

