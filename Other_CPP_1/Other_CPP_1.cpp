// Other_CPP_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Ŀ�� EXE ����·��
LPSTR lpszFile = (LPSTR)("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\notepad.exe");

// OUT
#define PATH "C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\NEW_notepad.exe"

// MessageBoxA�ĵ�ַ
DWORD Maddress = 0x76691610;

// ��Ҫע��Ĵ���
UCHAR ShellCode[] = {
	0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00 ,
	0xE8, 0x00, 0x00, 0x00, 0x00,
	0xE9, 0x00, 0x00, 0x00, 0x00
};


int main()
{
	// ��ȡҪע��Ĵ����С
	DWORD Codesize = sizeof(ShellCode);

	// ���ڿհ�����Ӵ���
	ChangeImageBufferCode1(lpszFile, ShellCode, Codesize, Maddress);

	getchar();

	return 0;
}



	/*
	// 3�� Buffer ��ָ��
	// LPVOID pFileBuffer = NULL;

	// LPVOID pImageBuffer = NULL;

	// LPVOID pNewBuffer = NULL;

	// �õ� FileBuffer �Ĵ�С 
	// DWORD FileBuffersize = CreateFileBuffer(lpszFile, &pFileBuffer);

	// ���� ImageBuffer ���� pImageBuffer ָ�� �õ� ImageBuffersize ��С
	// DWORD ImageBuffersize = CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);

	// DWORD SizeOfNewBuffer = ImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);

	
	// �ļ�����  
	// WriteMemeryToFile(pNewBuffer, SizeOfNewBuffer);
	*/