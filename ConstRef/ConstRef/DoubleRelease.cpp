#include "stdafx.h"
#include "DoubleRelease.h"


class CHoge {
	int* a;
public:
	CHoge()
	{
		a = new int;
	}
	~CHoge()
	{
		delete a;
	}
};

//�_�~�[�֐�
void FunctionDummy(CHoge hoge)
{

}

//�X�V�֐��B
void DoubleRelease::Update()
{
	CHoge hoge;
	FunctionDummy(hoge);
	//Update�֐��𔲂���ƂQ�d�J���ŃN���b�V������B
}
