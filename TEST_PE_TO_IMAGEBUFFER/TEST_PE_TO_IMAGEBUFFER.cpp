// TEST_PE_TO_IMAGEBUFFER.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	/* ���� PE �ļ������� */

	// ��ȡһ���ļ� ���ݴ�С����ռ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ��ȡӲ���ϵ��ļ���ָ���ڴ�ռ� ���ض�ȡ�Ĵ�С
	DWORD SizeOfReadFileToFileBuffer = ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���� FileBuffer �е� SizeOfImage ��Ա��С����һ�� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);

	// �� PE �ļ� �� FileBuffer ���첢����  ImageBuffer
	DWORD SizeOfCopyFileBufferToImageBuffer = CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);
	
	// �� NewBuffer �е����ݴ洢��ָ����·��
	DWORD SizeOfWriteDate = WriteMemeryToFile(pImageBuffer, SizeOfCopyFileBufferToImageBuffer, NEW_PATH);

	getchar();

	return 0;
}