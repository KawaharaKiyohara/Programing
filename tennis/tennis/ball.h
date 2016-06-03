#pragma once

class Ball {
public:
	Ball();
	~Ball();
	void Init();
	void Update();
	void Render(CRenderContext& renderContext);
public:
	CSkinModelData	modelData;		//���f���f�[�^�B
	CSkinModel		model;			//���f���B
	CVector3		position;		//���W�B
	CVector3		moveSpeed;		//�ړ����x�B
};