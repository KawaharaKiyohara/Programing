#include <stdio.h>
#include "UniquePtr.h"
#include <memory>

class HogeHoge {
public:
	HogeHoge()
	{
		printf("Call HogeHoge::Ctor\n");
	}
	~HogeHoge()
	{
		printf("Call HogeHoge::~Ctor\n");
	}

};
class Hoge {
	UniquePtr<HogeHoge>	hogehoge;			//���O��UniquePtr���g�p�����ꍇ�B
	std::unique_ptr<HogeHoge> hogehoge2;	//C++11�Œǉ����ꂽ�W����unique_ptr���g�p�����ꍇ�B���������g�����ˁB
public:
	Hoge()
	{
		hogehoge.reset(new HogeHoge);
		hogehoge2.reset(new HogeHoge);
		printf("Call Hoge::Ctor\n");
	}
	~Hoge()
	{
		printf("Call Hoge::~Ctor\n");
		//HogeHoge�̊J�����Ă�ł��Ȃ��������ƌĂ΂��B
	}
	void Print()
	{
		printf("Hoge::Print\n");
	}
};
void Func()
{
	UniquePtr<Hoge>	hoge;	//Hoge�N���X��UniquePtr;
	hoge.reset(new Hoge);	//Hoge�̃C���X�^���X�𐶐��B
	hoge->Print();			//���ʂ̃|�C���^�̂悤�Ƀ����o�֐����ĂԂ��Ƃ��������\�B
	//�J�������Ă��Ȃ����ǁAUniquePtr�̃f�X�g���N�^�̒���delete���s���Ă���̂ŁAnew�����C���X�^���X�͎����ō폜�����B
	//�X�R�[�v�𔲂���ƍ폜����邽�߁AScoped_ptr�ƌĂ΂�Ă����B
}
int main()
{
	Func();
	return 0;
}