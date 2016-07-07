#pragma once
#include <windows.h>

//�Z�}�t�H�B
class Semaphore {
	HANDLE  m_hSemaphore;	//�Z�}�t�H�̃n���h��
public:
	Semaphore() : m_hSemaphore(NULL)
	{
		
	}
	~Semaphore()
	{
		Delete();
	}
	//������
	//initCount	�Z�}�t�H�̏����l
	//maxCount	�Z�}�t�H�̍ő�l
	void Init(int initCount, int maxCount)
	{
		//�Z�}�t�H���쐬�B
		m_hSemaphore = CreateSemaphore(
			NULL, 1, 1, TEXT("semaphore")
			);
	}
	//���
	void Delete()
	{
		if (m_hSemaphore != NULL) {
			CloseHandle(m_hSemaphore);
			m_hSemaphore = NULL;
		}
	}
	//�Z�}�t�H�̎������擾�B�擾�ł��Ȃ��ꍇ�͎擾�ł���悤�ɂȂ�܂Ŗ���B
	void GetSemaphore()
	{
		WaitForSingleObject(m_hSemaphore, INFINITE);
	}
	//�Z�}�t�H�̎�����ԋp�B
	void ReleaseSemaphore()
	{
		::ReleaseSemaphore(m_hSemaphore, 1, NULL);
	}
};