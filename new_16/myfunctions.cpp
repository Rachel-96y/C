#include "stdafx.h"
#include "myfunctions.h"
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>

Data FileData;  // ����һ���洢�ļ������ݵı��� (�ļ���С, Դ�ļ�ָ��, Ŀ���ļ�ָ��)

Data* GetFileSize(char* PATH)
{
	/* ���ļ��� ��ȡ�ļ���С ������ ����: unsigned int */

	_iobuf* pFileOpen = fopen(PATH, "rb"); // ��ֻ��������ģʽ���ļ���  

	if (pFileOpen == NULL)  
	{
		// ����ֵΪNULL����fopenִ�г��ִ���
		exit(0);
	}

	int result = fseek(pFileOpen, 0, SEEK_END);

	if (result)
	{
		// ����ֵ��Ϊ0��fseekִ��ʧ��
		exit(0);
	}

	int FileSize = (int)ftell(pFileOpen);

	if (FileSize == -1L)
	{
		// ����ֵΪ-1L��ftellִ��ʧ��
		exit(0);
	}

	FileData.SizeOfFile = FileSize;   // ��FileData�еĳ�ԱSizeOfFileд��FileSize

	FileData.FileStream = pFileOpen;  // ��FileData�еĳ�ԱFileStreamд��pFileOpen

	Data* pFileData = (Data*)&FileData;   // ��ȡFileData(ȫ�ֱ���)�ĵ�ַ������

	return pFileData;
}

int CloseFileStream(_iobuf* pFileOpen)
{
	/* �˺������ڹر��ļ��� */
	int ReturnValue = fclose(pFileOpen);  

	if (ReturnValue == EOF)
	{
		// �ļ���δ�ɹ��ر�
		exit(0);
	}

	return 0;
}

char* RequestMemory(int fileSize)
{
	/* 
	���������С��������ռ�
	����ֵ��char*����
	ע��: �˺���û���ֶ��ͷ���������ڴ�
	*/

	char* pMemory = (char*)malloc(sizeof(char) * fileSize);

	if (pMemory == NULL)
	{
		// �ڴ�����ʧ��
		pMemory = NULL;

		return pMemory;
	}

	memset(pMemory, 0xCCCCCCCC, sizeof(char) * fileSize);  // ������ڴ��ʼ��
	
	return pMemory;
}

void FreeMemory(char* pMemory)
{
	/* �ͷ�������Ķ����ڴ�ռ� */

	free(pMemory);  // �ͷ��ڴ�

	pMemory = NULL;  // ��ʼ��ָ��
}

char* ReadFileToMemory(char* pMemory, unsigned int SizeOfFile,  \
					   unsigned int ReadSizeMax, _iobuf* pFileStream)
{
	/* ��ȡ�ļ�����ָ���Ķ����ڴ�ռ䲢�����ڴ��� */

	fseek(pFileStream, 0, SEEK_SET);  // ���ļ�ָ�����õ���ͷ

	unsigned int result = fread(pMemory, SizeOfFile, ReadSizeMax, pFileStream);
	
	if (result - ReadSizeMax)
	{
		pMemory = NULL;
	}

	return pMemory;
}

int WriteMemoryToNewFile(char* pMemory, unsigned int SizeOfFile, \
						 unsigned int ReadSizeMax, char* PATH)
{
	/* �����ж�ȡ����д�뵽Ӳ��ָ��λ�� */

	_iobuf* pNewFileOpen = fopen(PATH, "wb");

	if (pNewFileOpen == NULL)  
	{
		// ����ֵΪNULL����fopenִ�г��ִ���
		exit(0);
	}

	unsigned int result = fwrite(pMemory, SizeOfFile, ReadSizeMax, pNewFileOpen);

	if (result - ReadSizeMax)
	{
		return 1;
	}

	FileData.WriteFileStream = pNewFileOpen;

	return 0;
}

void PrintFormatOfPe(unsigned int number, char* pMemoryAddress)
{
	/* 

	�˺������ڴ�ӡPE�ļ������� 
	��ʮ�����Ƶĸ�ʽ��ʾ
	�˺��������ڶѿռ估 FileData �ṹ�������ݵ�����²ſ���ʹ��
	��Ҫ���� FileData �е� SizeOfFile ��Ա

	*/

	for (unsigned int i = 0; i < number; i++)
	{

		if (i != 0 && i % 0x10 == 0)
		{
			printf("\n");
		}

		switch(*(pMemoryAddress + i))
		{
			case 0x00:
				printf("00    ");
				break;
			case 0x01:
				printf("01    ");
				break;
			case 0x02:
				printf("02    ");
				break;
			case 0x03:
				printf("03    ");
				break;
			case 0x04:
				printf("04    ");
				break;
			case 0x05:
				printf("05    ");
				break;
			case 0x06:
				printf("06    ");
				break;
			case 0x07:
				printf("07    ");
				break;
			case 0x08:
				printf("08    ");
				break;
			case 0x09:
				printf("09    ");
				break;
			case 0x0A:
				printf("0a    ");
				break;
			case 0x0B:
				printf("0b    ");
				break;
			case 0x0C:
				printf("0c    ");
				break;
			case 0x0D:
				printf("0d    ");
				break;
			case 0x0E:
				printf("0e    ");
				break;
			case 0x0F:
				printf("0f    ");
				break;
			default:
				printf("%x    ", (unsigned char)*(pMemoryAddress + i));
		}
	}
}