// DoublePointer.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"


struct SBullet {
public:
	float velocity;		//�����x�B
};
//�_�u���|�C���^���g�p����o�[�W����
void CreateBullet( SBullet** bullet )
{
	*bullet = new SBullet();
	(*bullet)->velocity = 10;
}
//���ʂ̃|�C���^���g�p����o�[�W����
void CreateBullet2(SBullet* bullet)
{
	bullet = new SBullet();
	//bullet->velocity = 10;
}
int main()
{
	SBullet* bullet = NULL;
	//�e�ۂ𐶐�
	CreateBullet( &bullet );	//���Ғʂ�bullet->velocity��10�������Ă���B
	SBullet* bullet2 = NULL;
	CreateBullet2(bullet2);		//bullet2��NULL�̂܂܁I

	//bullet��bullet2�ɓ����Ă���A�h���X��\���B
	printf("bullet  addr = %x\n", (unsigned int)bullet );
	printf("bullet2 addr = %x\n", (unsigned int)bullet2 );
    return 0;
}

