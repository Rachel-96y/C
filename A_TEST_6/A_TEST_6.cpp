// A_TEST_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL PRINT_IMAGE_DATA_DIRECTORY(IN LPVOID pFileBuffer)
{
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
		printf("�ⲻ��һ����Ч��PE�ṹ: �����MZͷ��־");
		return NULL;
	}

	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ṹ: �����PE��־");
		return NULL;
	}

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pPIMAGE_OPTIONAL_HEADER32 -> DataDirectory);
	
	// ���嵼���ṹ��ָ��
	PIMAGE_IMPORT_DESCRIPTOR pPIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa((pPIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);
	
	// ����󶨵����ṹ��ָ��
	PIMAGE_BOUND_IMPORT_DESCRIPTOR pPIMAGE_BOUND_IMPORT_DESCRIPTOR = (IMAGE_BOUND_IMPORT_DESCRIPTOR*)(ChangeRvaToFoa((pPIMAGE_DATA_DIRECTORY + 11) -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);
	
	// �󶨵�����еĵ�һ���ṹ�� DESCRIPTOR ���� OffsetModuleName ���Եõ�ģ����
	DWORD dwNameBase = (DWORD)pPIMAGE_BOUND_IMPORT_DESCRIPTOR;

	// ��ӡ��һ���󶨵�����е�����ֵ
	printf("FirstTimeDateStamp: %x\n", pPIMAGE_BOUND_IMPORT_DESCRIPTOR -> TimeDateStamp);
	printf("FirstModuleName: %s\n", pPIMAGE_BOUND_IMPORT_DESCRIPTOR -> OffsetModuleName + dwNameBase);
	// ��ӡ��һ���󶨵������ NumberOfModuleForwarderRefs ���¼��ʣ������� ���ֵ���ܲ�׼(����Ϊ0)
	printf("FirstNumberOfModuleForwarderRefs: %x\n", pPIMAGE_BOUND_IMPORT_DESCRIPTOR -> NumberOfModuleForwarderRefs);
	printf("\n");

	// ����󶨵����� _IMAGE_BOUND_FORWARDER_REF �ṹ
	PIMAGE_BOUND_FORWARDER_REF pPIMAGE_BOUND_FORWARDER_REF = (IMAGE_BOUND_FORWARDER_REF*)++pPIMAGE_BOUND_IMPORT_DESCRIPTOR;

	do
	{
		// �����һ�������Ľṹ���ֵȫΪ0������
		if (!(pPIMAGE_BOUND_FORWARDER_REF ->TimeDateStamp  | \
			pPIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName | \
			pPIMAGE_BOUND_FORWARDER_REF -> Reserved))
			break;

		// �ж��Ƿ��ģ���а󶨵����
		if (!pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
		{
			// �����ģ��û�а󶨵����������
			pPIMAGE_IMPORT_DESCRIPTOR++;

			// ת����һ���󶨵����
			pPIMAGE_BOUND_FORWARDER_REF++;

			// û�ð󶨵�������ת����һ��
			continue;
		}

		// ��ӡ�󶨵����
		printf("TimeDateStamp: %x\n", pPIMAGE_BOUND_FORWARDER_REF -> TimeDateStamp);
		printf("ModuleName: %s\n", pPIMAGE_BOUND_FORWARDER_REF -> OffsetModuleName + dwNameBase);
		printf("Reserved: %x\n", pPIMAGE_BOUND_FORWARDER_REF -> Reserved);
		printf("\n");

		// ת����һ���󶨵����
		pPIMAGE_BOUND_FORWARDER_REF++;

		// ת����һ�������
		pPIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return NULL;
}

int main(int argc, char* argv[])
{
	/*
		��ϰ��
		��ӡ�󶨵����
	*/

	// PATH NEW_PATH 
	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(NEW_PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SIZE_OF_FILE_BUFFER = ReadPeFileToFileBuffer(NEW_PATH, pFileBuffer);

	// ��ӡ�󶨵����
	PRINT_IMAGE_DATA_DIRECTORY(pFileBuffer);

	getchar();

	return 0;
}

