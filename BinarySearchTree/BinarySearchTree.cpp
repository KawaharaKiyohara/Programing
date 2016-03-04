// BinarySearchTree.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

#define NAME_MAX_LEN	256

#define USE_SEARCH_RECURSIVE_CALL		//������`����ƍċA�Ăяo��search�֐����g�p�����

//�m�[�h
struct NODE {
	char	*text;		//�e�L�X�g�B
	NODE*	left;		//���̃m�[�h�B
	NODE*	right;		//�E�̃m�[�h�B
};
//�g�b�v
NODE* top = NULL;
/*
*�T�v�@�w�肵���P���񕪖؂��猟���B(�������͍ċA�Ăяo���I�I�I)
*����	tango		�����Ώۂ̒P��B
*����  result		���ʂ̊i�[��B
*/
int searchRecursiveCall(NODE* node, const char* tango, NODE** result)
{
	int ret = 0;
	int cmp;
	if (node == NULL) {
		//�P�꒠�ɓo�^����Ă���P�ꂪ�O�B
		*result = NULL;
		return 0;
	}
	cmp = strcmp(tango, node->text);	//�������r
	if (cmp == 0) {
		//���������B
		*result = node;
		ret = 1;
	}
	else if (cmp < 0) {
		if (node->left != NULL) {
			//���̃m�[�h������B
			ret = searchRecursiveCall(node->left, tango, result);		//�ċA�Ăяo���I�I�I
		}
		else {
			//�I�[�܂Œ��ׂ����ǌ�����Ȃ������B
			*result = node;	//�I�[�̃m�[�h���L�^����B
			ret = -1;		//���𒲂ׂČ�����Ȃ������������B
		}
	}
	else {
		if (node->right != NULL) {
			ret = searchRecursiveCall(node->right, tango, result);		//�ċA�Ăяo���I�I�I
		}
		else {
			//�I�[�܂Œ��ׂ����ǌ�����Ȃ�����
			*result = node;
			ret = -2;

		}
	}
	return ret;
}

/*
 *�T�v�@�w�肵���P���񕪖؂��猟���B
 *����	tango		�����Ώۂ̒P��B
 *����  result		���ʂ̊i�[��B
 */
int search(const char* tango, NODE** result)
{
	NODE* node = top;
	int ret = 0;
	int cmp;
	if (top == NULL) {
		//�P�꒠�ɓo�^����Ă���P�ꂪ�O�B
		*result = NULL;
		return 0;
	}
	do {
		cmp = strcmp( tango, node->text);	//�������r
		if (cmp == 0) {
			//���������B
			*result = node;		
			ret = 1;
		}
		else if ( cmp < 0 ) {
			if ( node->left != NULL ) {
				//���̃m�[�h������B
				node = node->left;
			}
			else {
				//�I�[�܂Œ��ׂ����ǌ�����Ȃ������B
				*result = node;	//�I�[�̃m�[�h���L�^����B
				ret = -1;		//���𒲂ׂČ�����Ȃ������������B
			}
		}
		else {
			if (node->right != NULL) {
				node = node->right;
			}
			else {
				//�I�[�܂Œ��ׂ����ǌ�����Ȃ�����
				*result = node;
				ret = -2;

			}
		}
	} while (ret == 0);
	return ret;
}
/*
 * �T�v�@	�P���񕪖؂ɒǉ��B
 * �����@	tango		�ǉ�����P��B
 * �߂�l�@	�ǉ������m�[�h
*/
NODE* add(char* tango)
{
	NODE* node;
	NODE* item;
	char* word;
#ifdef USE_SEARCH_RECURSIVE_CALL
	//�ċA�Ăяo�����g�p����search�֐����g�p����B
	int result = searchRecursiveCall(top, tango, &node);
#else
	//�ċA�Ăяo�����g�p���Ȃ�search�֐����g�p����B
	int result = search(tango, &node);
#endif
	if (result == 1) {
		//���̒P��͓o�^�ς݁B
		printf("���̒P��͓o�^�ς݂ł�\n");
		return NULL;
	}
	item = (NODE*)malloc( sizeof( NODE ) );
	word = (char*)malloc( strlen( tango ) + 1 );	//�k�������̂��߂�+1����B
	item->text = word;
	//�E�ƍ��̃m�[�h��NULL�ŏ���������B
	item->left = NULL;
	item->right = NULL;
	strcpy_s( item->text, strlen(tango) + 1, tango );
	switch (result) {
	case 0:
		//���߂ĒP�ꂪ�ǉ����ꂽ�B
		printf("���߂ĒP�ꂪ�ǉ�����܂����B\n");
		top = item;
		break;
	case -1:
		//�e�̃m�[�h�̍��ɒǉ�����B
		printf("�e�̃m�[�h�̍��ɒǉ����܂��B\n");
		node->left = item;
		break;
	case -2:
		//�e�̃m�[�h�̉E�ɒǉ�����B
		printf("�e�̃m�[�h�̉E�ɒǉ����܂��B\n");
		node->right = item;
		break;
	}
	return item;
}
int main()
{
	char text[NAME_MAX_LEN];
	int ret = 0;
	
	do {
		printf("�ǉ����������������͂��Ă��������B\n");
		ret = scanf_s("%s", text, NAME_MAX_LEN);
		add( text );
	} while ( ret == 1 );
	
    return 0;
}

