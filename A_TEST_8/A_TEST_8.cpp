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

	printf("������Ŀ�� EXE �ľ���·��\n");
	CHAR EXE_PATH[100] = {0};
	scanf("%s", EXE_PATH);

	printf("������Ҫע��� DLL �ľ���·��\n");
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
	
	// ����ڵĿհ�����С �ܷ��㹻д������
	LPVOID pCodeBegin = IsEnoughSpace(pFileBufferEx, dwSizeOfCodeToInjectDll);

	// ��ȡģ������ 
	LPSTR FileNameAddr = GetFileName(INJECT_DLL_PATH);

	// �����ע�� (pCodeBegin Ϊ NULL ��ע��ʧ�� ���ʧ����ô����ֵΪ 0xFFFFFFFF)
	DWORD IsSuccess = ImportDescriptorInjectDll(pFileBufferEx, pCodeBegin, strDllFunctionNameAddr, FileNameAddr, dwSizeOfFileBufferEx);

	// ������Ҫд������ݴ�С ��������Ĵ�С
	DWORD dwAlignment = MyAlignment(pFileBufferEx, 0, dwSizeOfCodeToInjectDll);

	// ����� (IsSuccess Ϊ NULL ��˺�����������ִ��)
	LPVOID pNewFileBuffer = ExpandSection(IsSuccess, pFileBufferEx, dwAlignment);

	// �ٴ�ִ�е����ע��
	ImportDescriptorInjectDll(pNewFileBuffer, (LPVOID)IsSuccess, strDllFunctionNameAddr, FileNameAddr, dwSizeOfFileBufferEx);

	// ���� NewFileBuffer �ļ�Ŀǰ�Ĵ�С
	DWORD dwSizeOfFileBuffer = SizeOfFileBuffer(pNewFileBuffer);

	// ����(·��: NEW_EXE_PATH)
	WriteMemeryToFile(pNewFileBuffer, dwSizeOfFileBuffer, EXE_PATH);

	// ���!
	printf("DLL ע��ɹ�! \n�뽫 DLL �� EXE ����ͬһĿ¼�»� DLL ����ϵͳ����������!\n");
	system("pause");

	return 0;
}