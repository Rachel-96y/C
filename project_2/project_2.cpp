#include "stdafx.h"

/*

��ϰ��

1���ֶ�����һ���ڱ�ͽڣ���֤�޸ĺ�ĳ�������ȷִ��.

2�����ʵ�֣�����һ���ڣ�����Ӵ���.

*/



int main(int argc, char* argv[])
{
	/*
		����һ���ڱ�ͽڣ���֤�޸ĺ�ĳ�������ȷִ��
		���ʵ�֣�����һ���ڣ�����Ӵ���.
	*/

	// ���� ShellCode ����
	UCHAR CodeArray[18] = 
	{	
		0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,  
		0xE8, 0x00, 0x00, 0x00, 0x00, 
		0xE9, 0x00, 0x00, 0x00, 0x00,
	}; 

	// �����ļ���С����ռ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ���ļ�����ָ���ڴ�
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���� FileBuffer ���� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);

	// �� FileBuffer ������ ImageBuffer
	CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);

	// ������Ҫ��ӵĴ����С ����һ�� NewImageBuffer �ռ�
	// (��Ҫ���ж��Ƿ��пռ����1���ڱ�)
	// (�ܹ�������ڴ�ռ�Ϊ ����һ�������ݺ��ڴ����Ĵ�С)
	LPVOID pNewImageBuffer = CreateNewImageBuffer(pImageBuffer, 18);

	//�����ݴ� ImageBuffer ������ NewImageBuffer ������һ���ڱ��һ���� У׼ȫ������ 
	CopyImageBufferToNewImageBuffer(pImageBuffer, pNewImageBuffer, 18, 0);

	// �������Ľڵ�������Ӵ���
	DWORD result = AddCodeToImageBuffer(&CodeArray[0], 4, 18, pNewImageBuffer);
	if (!result)
	{
		return NULL;
	}

	// ���� NewImageBuffer ����ó� NewBuffer�Ĵ�С �����Ӧ�ռ�

	LPVOID pNewBuffer = CreateNewBuffer(pNewImageBuffer);

	// �� NewImageBuffer ��ԭ�� NewBuffer (ʹ�� CopyImageBufferToNewBuffer �������ԴﵽҪ��)
	DWORD SizeOfCopyByte = CopyImageBufferToNewBuffer(pNewImageBuffer, pNewBuffer);

	// ����
	WriteMemeryToFile(pNewBuffer, SizeOfCopyByte, NEW_PATH);
	
 	return 0;
}