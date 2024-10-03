#include "stdafx.h"

/*

��ϰ��
1����������Ӵ���,���ʵ��
2���������ڿհ�����Ӵ���,���ʵ��

*/


int main(int argc, char* argv[])
{
	/* ��������Ӵ��� && �������ڿհ�����Ӵ��� */

	// �ȶ���������� ���ڶԴ������У�� �����鹲 18 ���ֽ�
	UCHAR CodeArray[18] = 
	{	
		0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,  
		0xE8, 0x00, 0x00, 0x00, 0x00, 
		0xE9, 0x00, 0x00, 0x00, 0x00,
	};  

	// ��ȡһ���ļ� ���ݴ�С����ռ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);
	if (!pFileBuffer)
	{
		printf("�ļ���ȡʧ��");
		free(pFileBuffer);
		pFileBuffer = NULL;
		getchar();
		return NULL;
	}

	// ��ȡӲ���ϵ��ļ���ָ���ڴ�ռ� ���ض�ȡ�Ĵ�С
	DWORD SizeOfReadFileToFileBuffer = ReadPeFileToFileBuffer(PATH, pFileBuffer);
	if (!SizeOfReadFileToFileBuffer)
	{
		printf("�ļ���ȡʧ��");
		free(pFileBuffer);
		pFileBuffer = NULL;
		getchar();
		return NULL;
	}

	// ���� FileBuffer �е� SizeOfImage ��Ա��С����һ�� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);
	if (!pImageBuffer)
	{
		printf(" ImageBuffer �ռ�����ʧ��");
		free(pFileBuffer);
		pFileBuffer = NULL;
		getchar();
		return NULL;
	}

	// �� PE �ļ� �� FileBuffer ���첢����  ImageBuffer
	DWORD SizeOfCopyFileBufferToImageBuffer = CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);
	if (!SizeOfCopyFileBufferToImageBuffer)
	{
		printf("�� FileBuffer �� ImageBuffer ����ʧ��");
		free(pFileBuffer);
		free(pImageBuffer);
		pFileBuffer = NULL;
		pImageBuffer = NULL;
		getchar();
		return NULL;
	}

	// ��������Ӵ���  
	BOOL IsTrue = AddCodeToImageBuffer(&CodeArray[0], 1, 18, pImageBuffer);
	if (IsTrue == NULL)
	{
		printf("��Ӵ���ʧ��!");
		free(pFileBuffer);
		free(pImageBuffer);
		pFileBuffer = NULL;
		pImageBuffer = NULL;
		getchar();
		return NULL;
		
	}

	// ���� ImageBuffer �е�ֵ ����һ�� NewBuffer �ռ�
	LPVOID pNewBuffer = CreateNewBuffer(pImageBuffer);
	if (!pNewBuffer)
	{
		printf("���� pImageBuffer ���� NewBuffer �ռ�ʧ��");
		free(pFileBuffer);
		free(pImageBuffer);
		pFileBuffer = NULL;
		pImageBuffer = NULL;
		getchar();
		return NULL;
	}

	// ���� pImageBuffer �� pNewBuffer �� ImageBuffer �е����ݿ����� NewBuffer ��
	DWORD SizeOfCopyImageBufferToNewBuffer = CopyImageBufferToNewBuffer(pImageBuffer, pNewBuffer);
	if (!SizeOfCopyImageBufferToNewBuffer)
	{
		printf("�� ImageBuffer �������ݵ� NewBuffer ʧ��");
		free(pFileBuffer);
		free(pImageBuffer);
		free(pNewBuffer);
		pNewBuffer = NULL;
		pFileBuffer = NULL;
		pImageBuffer = NULL;
		getchar();
		return NULL;
	}
	
	// �� NewBuffer �е����ݴ洢��ָ����·��
	DWORD SizeOfWriteDate = WriteMemeryToFile(pNewBuffer, SizeOfCopyImageBufferToNewBuffer, NEW_PATH);
	if (SizeOfWriteDate == NULL)
	{
		printf("����ʧ��!");
		free(pFileBuffer);
		free(pImageBuffer);
		free(pNewBuffer);
		pNewBuffer = NULL;
		pFileBuffer = NULL;
		pImageBuffer = NULL;
		getchar();
		return NULL;
	}

	// �ɹ�ִ�к���Ҫ�ͷſռ�
	printf("���̳ɹ�!\n");
	free(pFileBuffer);
	free(pImageBuffer);
	free(pNewBuffer);
	pNewBuffer = NULL;
	pFileBuffer = NULL;
	pImageBuffer = NULL;

	getchar();

	return 0;
}
