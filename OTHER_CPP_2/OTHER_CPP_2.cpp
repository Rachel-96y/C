// OTHER_CPP_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>

/* ��Ҫ���� 2 ��·�� + һ�� MessageBox ��ַ������������ */

// ************ ���� ************
// LPSTR lpszFile = (LPSTR)("D:\\\\BaiduNetdiskDownload\\\\�ؼ���.exe"); 
#define lpszFile "C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\notepad.exe"

// ************ ���� ************
// WORD Maddress = 0x761328B0; 
DWORD Maddress = 0x76691610;

// ************ ���� ************
/*		
BYTE ShellCode[] = {	
	0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00 ,
	0xE8, 0x00, 0x00, 0x00, 0x00,
	0xE9, 0x00, 0x00, 0x00,0x00,0x00	
};	
*/

BYTE ShellCode[] = {
	0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00 ,
	0xE8, 0x00, 0x00, 0x00, 0x00,
	0xE9, 0x00, 0x00, 0x00, 0x00
};



int main(int argc, char* argv[])
{
	DWORD Codesize = sizeof(ShellCode);
	printf("%d", Codesize);
	// printf("%s\n", lpszFile);
	PVOID pFileBuffer = 0;
	PVOID pImageBuffer = 0;
	PVOID pNewBuffer = 0;
	DWORD FileBuffersize = CreateFileBuffer(lpszFile,&pFileBuffer);
	// ��ӡPEͷ�ļ�
	ToLoaderPE(pFileBuffer);
	
	// DWORD ImageBuffersize = CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
	// printf("Buffer����:%x\nBufferָ��:%x\n", FileBuffersize, pFileBuffer);
	// printf("ImageBuffer����:%x\nImageBufferָ��:%x\n", ImageBuffersize, pImageBuffer);

	// DWORD pNewBuffersize = ImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
	// printf("pNewBuffersize����:%x\npNewBufferָ��:%x\n", pNewBuffersize, pNewBuffer);
	
	// RVA  FOA  VAת��
	// convertFoaToRva(IN lpszFile);
	
	// ���ڿհ�����Ӵ���
	ChangeImageBufferCode1(IN lpszFile, IN ShellCode, IN  Codesize, IN Maddress);

	// �ļ�����  
	// WriteMemeryToFile(pNewBuffer, pNewBuffersize);
	
	// std::cout << "Hello World!\n";

	// ************ ��� ************
	system("pause");	
	
	return 0;
}
