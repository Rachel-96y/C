// project_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL AddCodeToFreeArea()
{
	/* ��������Ӵ��� && �������ڿհ�����Ӵ��� */

	// ���� ShellCode ����
	UCHAR CodeArray[CODE_LENGTH] = 
	{	
		0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,  
		0xE8, 0x00, 0x00, 0x00, 0x00, 
		0xE9, 0x00, 0x00, 0x00, 0x00,
	};  

	// ��ȡһ���ļ� ���ݴ�С����ռ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ��ȡӲ���ϵ��ļ���ָ���ڴ�ռ� ���ض�ȡ�Ĵ�С
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���� FileBuffer �е� SizeOfImage ��Ա��С����һ�� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);


	// �� PE �ļ� �� FileBuffer ���첢����  ImageBuffer
	DWORD SizeOfCopyFileBufferToImageBuffer = CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);

	// �����ھ�̬ע�����  
	AddCodeToImageBuffer(&CodeArray[0], 1, CODE_LENGTH, pImageBuffer);

	// ���� ImageBuffer �е�ֵ ����һ�� NewBuffer �ռ�
	LPVOID pNewBuffer = CreateNewBuffer(pImageBuffer);

	// ���� pImageBuffer �� pNewBuffer �� ImageBuffer �е����ݿ����� NewBuffer ��
	DWORD SizeOfCopyImageBufferToNewBuffer = CopyImageBufferToNewBuffer(pImageBuffer, pNewBuffer);
	
	// ����
	WriteMemeryToFile(pNewBuffer, SizeOfCopyImageBufferToNewBuffer, NEW_PATH);

	printf("���̳ɹ�!\n");
	getchar();

	return TRUE;
}

BOOL AddSection()
{
	/* ����һ���ڣ�����Ӵ��� */

	// ���� ShellCode ����
	UCHAR CodeArray[CODE_LENGTH] = 
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
	LPVOID pNewImageBuffer = CreateNewImageBuffer(pImageBuffer, CODE_LENGTH);

	//�����ݴ� ImageBuffer ������ NewImageBuffer ������һ���ڱ��һ���� У׼ȫ������ 
	CopyImageBufferToNewImageBuffer(pImageBuffer, pNewImageBuffer, CODE_LENGTH, 0);

	// �������Ľ�����̬ע�����
	DWORD result = AddCodeToImageBuffer(&CodeArray[0], 4, CODE_LENGTH, pNewImageBuffer);
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

	printf("���̳ɹ�!\n");
	getchar();

	return TRUE;
}

BOOL ExpandSection()
{
	/* ����� �������һ���ڣ�����Ӵ��� */

	// ���� ShellCode ����
	UCHAR CodeArray[CODE_LENGTH] = 
	{	
		0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,  
		0xE8, 0x00, 0x00, 0x00, 0x00, 
		0xE9, 0x00, 0x00, 0x00, 0x00,
	}; 

	// �����ļ���С ����һ���ڴ�ռ� FileBuffer
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ���ļ����� FileBuffer
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���� FileBuffer ����һ���ڴ�ռ� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);

	// �� FileBuffer �����ݶ��� ImageBuffer
	CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);

	// ����� ��ȡ��������Ӧ�Ķ����Ĵ�С
	DWORD AlignNumber = MyAlignment(pImageBuffer, 0, CODE_LENGTH);

	// Ϊ����������㹻�Ŀռ�
	LPVOID pNewImageBuffer = CreateNewImageBufferEx(pImageBuffer, AlignNumber);

	// �� ImageBuffer �����ݸ��Ƶ� NewImageBuffer
	CopyImageBufferToNewImageBufferEx(pImageBuffer, pNewImageBuffer, AlignNumber, 1, CODE_LENGTH);

	// ��̬ע�����
	BOOL result = AddCodeToImageBuffer(&CodeArray[0], 3, CODE_LENGTH, pNewImageBuffer);
	if (!result)
	{
		// �޷�ע�����
		return NULL;
	}

	// ���� NewImageBuffer ����һ�� NewBuffer �Ŀռ� ���ڴ洢ѹ���������
	LPVOID pNewBuffer = CreateNewBuffer(pNewImageBuffer);

	// �� NewImageBuffer ѹ������Ӳ���ϵĸ�ʽ
	DWORD SizeOfCopyByte = CopyImageBufferToNewBuffer(pNewImageBuffer, pNewBuffer);

	// ����
	WriteMemeryToFile(pNewBuffer, SizeOfCopyByte, NEW_PATH);

	printf("���̳ɹ�!\n");
	getchar();

	return TRUE;
}

BOOL MergeSection()
{
	/* �����нںϲ�������Ӵ��� */

	// ���� ShellCode ����
	UCHAR CodeArray[CODE_LENGTH] = 
	{	
		0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00,  
		0xE8, 0x00, 0x00, 0x00, 0x00, 
		0xE9, 0x00, 0x00, 0x00, 0x00,
	}; 
	
	// �����ļ���С ����һ���ڴ�ռ� FileBuffer
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ���ļ����� FileBuffer
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���� FileBuffer ����һ���ڴ�ռ� ImageBuffer
	LPVOID pImageBuffer = CreateImageBuffer(pFileBuffer);

	// �� FileBuffer �����ݶ��� ImageBuffer
	CopyFileBufferToImageBuffer(pFileBuffer, pImageBuffer);

	// �޸� imageBuffer �ڵ�ֵ �ϲ���
	ChangeImageBufferData(pImageBuffer, 1, CODE_LENGTH);

	// ��̬ע�����
	BOOL result = AddCodeToImageBuffer(&CodeArray[0], 1, CODE_LENGTH, pImageBuffer);
	if (!result)
	{
		// �޷�ע�����
		return NULL;
	}

	// ���� NewImageBuffer ����һ�� NewBuffer �Ŀռ� ���ڴ洢ѹ���������
	LPVOID pNewBuffer = CreateNewBuffer(pImageBuffer);

	// �� NewImageBuffer ѹ������Ӳ���ϵĸ�ʽ
	DWORD SizeOfCopyByte = CopyImageBufferToNewBuffer(pImageBuffer, pNewBuffer);

	// ����
	WriteMemeryToFile(pNewBuffer, SizeOfCopyByte, NEW_PATH);

	printf("���̳ɹ�!\n");
	getchar();

	return TRUE;
}

BOOL PrintOfDirectoryEntry()
{
	/* ���ȫ��Ŀ¼�� */

	// ������
	// �����
	// ��Դ��
	// �쳣��
	// ��ȫ֤���
	// �ض�λ��
	// ������Ϣ��
	// ��Ȩ���б�
	// ȫ��ָ���
	// TLS��
	// �������ñ�
	// �󶨵����
	// IAT��
	// �ӳٵ����
	// COM��
	// ������
	
	// �����ļ���С ����һ���ڴ�ռ� FileBuffer
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// ���ļ����� FileBuffer
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// �ж�DOS_MZͷ�Ƿ���Ч
	if (pPIMAGE_DOS_HEADER -> e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ļ�: �����MZͷ��־");
		return NULL;
	}
	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ļ�: �����PE��־");
		return NULL;
	}
	
	// �ҵ�����Ŀ¼��λ�ò���������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)\
		((DWORD)pPIMAGE_SECTION_HEADER - IMAGE_NUMBEROF_DIRECTORY_ENTRIES * sizeof(IMAGE_DATA_DIRECTORY));
	
	char* arr[16] = 
	{
		"������", "�����", "��Դ��", "�쳣��Ϣ��", 
		"��ȫ֤���", "�ض�λ��", "������Ϣ��", "��Ȩ���б�", 
		"ȫ��ָ���", "TLS��", "�������ñ�", "�󶨵����",
		"IAT��", "�ӳٵ����", "COM��Ϣ��", "������δʹ�õı�",
	};

	for (int i = 0; i < 16; i++)
	{
		printf("%s:\nRVA:%x  Size:%x\n\n", arr[i], \
			(pPIMAGE_DATA_DIRECTORY + i) -> VirtualAddress, (pPIMAGE_DATA_DIRECTORY + i) -> Size);
	}

	getchar();

	return TRUE;
}



int main(int argc, char* argv[])
{
	/*
		��ϰ��

		1���������һ���ڣ���֤������������.

		2�����ʵ�֣��������һ���ڣ�����Ӵ���.

		3�������нںϲ�����֤������������.

		4������һ���������ܹ����ض����Ĵ�С Alignment(int x,int y)

		5��������ȫ��Ŀ¼��.

	*/
	
	// AddCodeToFreeArea();		// ��������Ӵ��� && �������ڿհ�����Ӵ���

	// AddSection();		// �����ڲ���Ӵ���

	// ExpandSection();			// ����ڲ���Ӵ���

	// MergeSection();		// �ϲ��ڲ���Ӵ���
	
	// PrintOfDirectoryEntry();  // ���ȫ��Ŀ¼��
	

	return 0;
}