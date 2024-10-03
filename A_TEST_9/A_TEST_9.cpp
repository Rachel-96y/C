// A_TEST_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	/*
		��ϰ��
		����ʵ�ֵ����ע��
	*/

	// ��̬ DLL ע�� (�����ע��) | EXE_PATH (��Ҫ����ע���Ŀ�� EXE ) | NEW_EXE_PATH (���ɵ��ļ�·��)

	printf("������Ŀ�� EXE �ľ���·�� (���Խ� EXE ��ק����)\n");
	CHAR EXE_PATH[100] = {0};
	scanf("%s", EXE_PATH);

	printf("������Ҫע��� DLL �ľ���·�� (���Խ� DLL ��ק����)\n");
	CHAR INJECT_DLL_PATH[100] = {0};
	scanf("%s", INJECT_DLL_PATH);

	// ƴ��һ�� .bak �ַ�����Ϊ��·��
	CHAR BAK_PATH[100] = {0};
	strcpy(BAK_PATH, EXE_PATH);
	LPSTR result = &BAK_PATH[0];

	while(TRUE)
	{
		if (!(*result))
		{
			*(result - 3) = 'b';
			*(result - 2) = 'a';
			*(result - 1) = 'k';
			break;
		}
		result++;
	}

	// �ȱ��� EXE �ļ�
	LPVOID pFileBuffer_bak = CreateFileBuffer(EXE_PATH);
	if (!pFileBuffer_bak)
	{
		printf("·�������� ��������ո�˫����\n");
		system("pause");
		return NULL;
	}

	// ��ȡ EXE �ļ��� FileBuffer_bak ��
	DWORD dwSizeOfFileBuffer_bak = ReadPeFileToFileBuffer(EXE_PATH, pFileBuffer_bak);

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pFileBuffer_bak;

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
		printf("�ⲻ��һ����Ч��PE�ṹ: �����MZͷ��־\n");
		system("pause");
		return NULL;
	}

	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ṹ: �����PE��־\n");
		system("pause");
		return NULL;
	}

	// ���� ��·��Ϊ BAK_PATH (xxx.bak)
	WriteMemeryToFile(pFileBuffer_bak, dwSizeOfFileBuffer_bak, BAK_PATH);

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(EXE_PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD dwReadPeFileToFileBuffer = ReadPeFileToFileBuffer(EXE_PATH, pFileBuffer);

	// ����������� PE �ļ������������������ FileBuffer ָ�� (��������һ���µĿռ��ͷžɵĿռ�)
	LPVOID pFileBufferEx = CleanPeData(pFileBuffer, dwReadPeFileToFileBuffer);

	// ��ȡ PE �ļ��� FileBuffer �еĴ�С
	DWORD dwSizeOfFileBufferEx = SizeOfFileBuffer(pFileBufferEx);

	// ������Ҫע��� DLL �еĺ��������� (����ֻ��Ҫһ��DLL �е�һ����������)
	DWORD dwFunctionNameLength = SizeOfDllFunctionLength(INJECT_DLL_PATH);

	// �õ� DLL ��ĵ�һ������������ ����洢�� strDllFunctionNameAddr ��
	LPSTR strDllFunctionNameAddr = DllFunctionName(INJECT_DLL_PATH);

	// ������Ҫ�ƶ��ı���Ҫ�����ı��ܹ�ռ�����ֽ�
	DWORD dwSizeOfCodeToInjectDll = SizeOfCodeToInjectDll(pFileBufferEx, INJECT_DLL_PATH, dwFunctionNameLength);

	// ��ȡģ������ 
	LPSTR FileNameAddr = GetFileName(INJECT_DLL_PATH);
	
	// ������Ҫд������ݴ�С ��������Ĵ�С
	DWORD dwAlignment = MyAlignment(pFileBufferEx, 0, dwSizeOfCodeToInjectDll);

	// ����� (IsSuccess Ϊ NULL ��˺�����������ִ��)
	LPVOID pNewFileBuffer = ExpandSection(0xFFFFFFFF, pFileBufferEx, dwAlignment);

	// �����ע��
	ImportDescriptorInjectDll(pNewFileBuffer, (LPVOID)0xFFFFFFFF, strDllFunctionNameAddr, FileNameAddr, dwSizeOfFileBufferEx);

	// ���� NewFileBuffer �ļ�Ŀǰ�Ĵ�С
	DWORD dwSizeOfFileBuffer = SizeOfFileBuffer(pNewFileBuffer);

	// ����(·��: NEW_EXE_PATH)
	WriteMemeryToFile(pNewFileBuffer, dwSizeOfFileBuffer, EXE_PATH);

	// ���!
	printf("DLL ע��ɹ�! \n�뽫 DLL �� EXE ����ͬһĿ¼�»� DLL ����ϵͳ����������!\nע��: ͬĿ¼���Ѿ�������һ�� .bak �ļ� (��EXE�ı����ļ�)\nһ�� EXE ֻ��ע��һ�� DLL\n");

	system("pause");

	return 0;
}