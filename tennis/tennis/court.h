#pragma once

//�e�j�X�R�[�g
class Court {
public:
	//�R���X�g���N�^�B
	Court();
	//�f�X�g���N�^�B
	~Court();
	//�������B
	void Init();
	//�`��B
	void Render(CRenderContext& renderContext);
private:
	CSkinModelData	modelData;		//���f���f�[�^�B
	CSkinModel		model;			//���f���B
};

const float COURT_MAX_X = 5.0f;		//�R�[�g��X���W�̍ő�l�B
const float COURT_MIN_X = -5.0f;	//�R�[�g��X���W�̍ŏ��l�B
const float COURT_MAX_Z = 3.0f;		//�R�[�g��Z���W�̍ő�l�B
const float COURT_MIN_Z = -3.0f;	//�R�[�g��Z���W�̍ŏ��l�B