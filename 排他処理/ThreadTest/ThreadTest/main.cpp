#include <future>
#include <windows.h>
int count = 0;
void Thread1()
{
	//count��10����C���N�������g
	for (int i = 0; i < 100000; i++) {
		count++;
	}
}
void Thread2()
{
	//count��10����C���N�������g
	for (int i = 0; i < 100000; i++) {
		count++;
	}
}
int main()
{
	std::thread th1 = std::thread([] {Thread1(); });	//Thread1���N���B
	std::thread th2 = std::thread([] {Thread2(); });	//Thread2���N���B
	th1.join();											//Thread1���I������܂őҋ@�B
	th2.join();											//Thread2���I������܂őҋ@�B

	//���ʂ�\���B
	char message[256];
	sprintf_s(message, "count = %d\n", count);
	MessageBox(NULL, message, "Thread1�̌���", MB_OK);			//20���ɂȂ�H
	return 0;
}