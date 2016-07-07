
#include "stdafx.h"
#include "ConstRefTest.h"
#include "tkEngine/timer/tkStopwatch.h"
#include "tkEngine/random/tkRandom.h"

//�����o�ϐ���int�^��1024���̔z���ێ����邾���̃N���X�B
class CDummy {
public:
	int a[1024];
};
int hoge = 0;

extern tkEngine::CRandom random;
//�l�n���̊֐��B
void FunctionParamCopy(CDummy dummy)
{
}
//const�Q�Ƃ̊֐��B
void FunctionConstRef(const CDummy& dummy)
{
}


/*!
*@brief	�X�V
*/
void ConstRefCallTest::Update()
{
	{
		CStopwatch sw;
		sw.Start();
		CDummy dummy;
		//�Q�Ɠn��
		for (int i = 0; i < 10000000; i++) {
			FunctionConstRef(dummy);
		}

		sw.Stop();

		char resultTxt[256];
		sprintf(resultTxt, "const �Q�Ƃ̏������� = %lf(�~��)\n", sw.GetElapsedMillisecond());
		MessageBox(NULL, resultTxt, "����", MB_OK);
	}

	{
		CStopwatch sw;
		sw.Start();
		CDummy dummy;
		//�R�s�[�B
		for (int i = 0; i < 10000000; i++) {
			FunctionParamCopy(dummy);
		}
		sw.Stop();

		char resultTxt[256];
		sprintf(resultTxt, "�l�n���̏������� = %lf(�~��)\n", sw.GetElapsedMillisecond());
		MessageBox(NULL, resultTxt, "����", MB_OK);
	}
	//���S
	DeleteGO(this);
}

