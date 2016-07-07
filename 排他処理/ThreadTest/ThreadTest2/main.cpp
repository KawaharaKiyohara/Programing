#include <future>
#include "Semaphore.h"

Semaphore sem;		//count�ւ̃A�N�Z�X��r�����������邽�߂̃Z�}�t�H�B
int count = 0;
void Thread1()
{
	//count��10����C���N�������g
	for (int i = 0; i < 100000; i++) {
		sem.GetSemaphore();		//�Z�}�t�H�������擾(1���Z)�B�Z�}�t�H���l���ł��Ȃ�������҂��s��ɒǉ��B
		count++;
		sem.ReleaseSemaphore();	//�Z�}�t�H������ԋp(1���Z)�B
	}
}
void Thread2()
{
	//count��10����C���N�������g
	for (int i = 0; i < 100000; i++) {
		sem.GetSemaphore();		//�Z�}�t�H�������擾(1���Z)�B�Z�}�t�H���l���ł��Ȃ������疰��B
		count++;
		sem.ReleaseSemaphore();	//�҂��s������Ă���X���b�h��������N�����B���Ȃ���΃Z�}�t�H������ԋp(1���Z)�B
	}
}
int main()
{
	sem.Init( 1, 1 );									//�Z�}�t�H���������B
	std::thread th1 = std::thread([] {Thread1(); });	//Thread1���N���B
	std::thread th2 = std::thread([] {Thread2(); });	//Thread2���N���B
	th1.join();											//Thread1���I������܂őҋ@�B
	th2.join();											//Thread2���I������܂őҋ@�B

	//���ʂ�\���B
	char message[256];
	sprintf_s( message, "count = %d\n", count);
	MessageBox(NULL, message, "Thread2�̌���", MB_OK);
	return 0;
}