// WIN32API_16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
int main(int argc, char* argv[])
{
	if (!argv[1])
	{
		printf("δ���յ��κβ���\n");
		system("pause");
		return -1;
	}
	printf("���յ���ֵ:%s\n", argv[1]);
	TCHAR szDATA[0x4] = {0};
	memcpy(szDATA, argv[1], 0x4);
	DWORD dwNumber = 0;
	sscanf(szDATA, "%x", &dwNumber);
	HANDLE hEvent = (HANDLE)dwNumber;
	printf("����%s��ʼ�ȴ�...\n", argv[0]);
	
	DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);
	if (dwRet == WAIT_FAILED)
	{
		printf("�������մ���,������:0x%08x...\n", GetLastError());
		system("pause");
		return -1;
	}
	printf("����%s��ʼִ��!...\n", argv[0]);
	WaitForSingleObject(hEvent, INFINITE);
	printf("����%s����!...\n", argv[0]);
	system("pause");
	return 0;
}
*/

unsigned char func[] = 
{
	0x55,
	0x8B, 0xEC,
	0x81, 0xEC, 0xC0, 0x00, 0x00, 0x00,
	0x53,
	0x56,
	0x57,
	0x8D, 0xBD, 0x40, 0xFF, 0xFF, 0xFF,
	0xB9, 0x30, 0x00, 0x00, 0x00,
	0xB8, 0xCC, 0xCC, 0xCC, 0xCC,
	0xF3, 0xAB,
	0x8B, 0x45, 0x08,
	0x03, 0x45, 0x0C,
	0x5F,
	0x5E,
	0x5B,
	0x8B, 0xE5,
	0x5D,
	0xC3,
};

int main(int argc, char* argv[])
{
	// �˳���LordPE��VC++6.0��ֲ��vs2010
	// ���޸�ԭ����ĸ�������
	::MessageBox(0, TEXT("������"), 0, 0);
	int(WINAPIV *p)(int, int) = (int(WINAPIV *)(int, int))&func;
	int dwRet = p(2, 3);
	printf("%d\n", dwRet);
	return 0;
}