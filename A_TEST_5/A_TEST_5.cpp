// A_TEST_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL PrintImportDescriptor(LPVOID pFileBuffer)
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

	/*
	�ҵ�����������
	LPSTR DLL_NAME_PTR = (LPSTR)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> Name, pFileBuffer) + (DWORD)pFileBuffer);
	printf("%s\n", DLL_NAME_PTR);

	DWORD pPIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk, pFileBuffer) + (DWORD)pFileBuffer);
	printf("%x\n", pPIMAGE_THUNK_DATA32);
	PIMAGE_IMPORT_BY_NAME pPIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa(*(LPDWORD)pPIMAGE_THUNK_DATA32, pFileBuffer) + (DWORD)pFileBuffer);
	printf("%s\n", pPIMAGE_IMPORT_BY_NAME -> Name);
	*/

	// ��������ṹ��ָ����ֵ��ʼ��ӡ
	if (!pPIMAGE_IMPORT_DESCRIPTOR)
	{
		return NULL;
	}

	do
	{
		// �ж��Ƿ�������ṹ���� ����������
		if (!(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk | pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp |\
			pPIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain | pPIMAGE_IMPORT_DESCRIPTOR -> Name | \
			pPIMAGE_IMPORT_DESCRIPTOR -> FirstThunk))
			break;

		// ������Ҫ�����ȫ���� DLL ѭ����ӡ _IMAGE_IMPORT_DESCRIPTOR �������Ϣ
		printf("---------------------------------------------------------------------------\n");
		printf("OriginalFirstThunk: %x\n", pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk);
		printf("TimeDateStamp: %x\n", pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp);
		printf("ForwarderChain: %x\n", pPIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain);
		printf("ָ��Ҫʹ�õ�DLL�����ֵĵ�ַ: %x\n", pPIMAGE_IMPORT_DESCRIPTOR -> Name);
		printf("FirstThunk: %x\n", pPIMAGE_IMPORT_DESCRIPTOR -> FirstThunk);

		// ��ӡģ������
		LPSTR DLL_NAME_PTR = (LPSTR)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> Name, pFileBuffer) + (DWORD)pFileBuffer);
		printf("DLL����: %s\n", DLL_NAME_PTR);
		printf("\n");

		// ��ӡ���ṹ

		// ��ӡ INT ��
		// �ҵ� PIMAGE_THUNK_DATA32 �� FOA (4�ֽ�)
		DWORD pINT_PIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk, pFileBuffer) + (DWORD)pFileBuffer);
		while(*(LPDWORD)pINT_PIMAGE_THUNK_DATA32 != 0)
		{
			// ֵΪ0��ѭ������
			
			// �ж����λ�Ƿ�Ϊ1
			if (*(LPDWORD)pINT_PIMAGE_THUNK_DATA32 & IMAGE_ORDINAL_FLAG32)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				DWORD Original = *(LPDWORD)pINT_PIMAGE_THUNK_DATA32 & ~IMAGE_ORDINAL_FLAG32;
				printf("�������(INT): %x\n", Original);
			}
			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{	// ��ӡ INT ��
				PIMAGE_IMPORT_BY_NAME pINT_PIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa(*(LPDWORD)pINT_PIMAGE_THUNK_DATA32, pFileBuffer) + (DWORD)pFileBuffer);
				printf("��������(INT): %s\n", pINT_PIMAGE_IMPORT_BY_NAME -> Name);
				
			}

			// �ҵ���һ����ַ
			pINT_PIMAGE_THUNK_DATA32 += 4;
		}

		// ��ӡ IAT ��
		// �ҵ� PIMAGE_THUNK_DATA32 �� FOA (4�ֽ�)
		DWORD pPIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> FirstThunk, pFileBuffer) + (DWORD)pFileBuffer);
		
		printf("\n\n");

		// ���� IAT ��ṹ��ָ�� FirstThunk ָ�� IAT ��
		while(*(LPDWORD)pPIMAGE_THUNK_DATA32 != 0)
		{
			// ֵΪ0��ѭ������

			// �жϴ�DLL�Ƿ񱻰� �������ֱ�Ӵ�ӡ������ַ
			if (pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp)
			{
				printf("������ַ(Bound): %x\n", *(LPDWORD)pPIMAGE_THUNK_DATA32);

				// �ҵ���һ����ַ
				pPIMAGE_THUNK_DATA32 += 4;
				continue;
			}

			// �ж����λ�Ƿ�Ϊ1
			if (*(LPDWORD)pPIMAGE_THUNK_DATA32 & IMAGE_ORDINAL_FLAG32)
			{
				// ���Ϊ1 ��ô��ȥ���λ��ֵ ���Ǻ����ĵ������
				DWORD Original = *(LPDWORD)pPIMAGE_THUNK_DATA32 & ~IMAGE_ORDINAL_FLAG32;
				printf("�������(IAT): %x\n", Original);
			}

			// ������ǣ���ô���ֵ��һ��RVA ָ�� IMAGE_IMPORT_BY_NAME 
			else
			{
				PIMAGE_IMPORT_BY_NAME pPIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa(*(LPDWORD)pPIMAGE_THUNK_DATA32, pFileBuffer) + (DWORD)pFileBuffer);
				printf("��������(IAT): %s\n", pPIMAGE_IMPORT_BY_NAME -> Name);
				
			}

			// �ҵ���һ����ַ
			pPIMAGE_THUNK_DATA32 += 4;
		}

		// �ҵ���һ��ģ��
		pPIMAGE_IMPORT_DESCRIPTOR++;
	}
	while(TRUE);

	return NULL;

}



int main(int argc, char* argv[])
{
	/*
		ʵ�֣�							
		1��ʹ��OD��һ���������exe���򣬶�λ��ĳ��DLL��API									
		2����û�м��ص�EXE���ҵ����λ�ã��۲����ǰ�������					

		��ϰ��
		1����ӡ ipmsg.exe ������ȫ����Ϣ
		2����ӡ notepad.exe ������ȫ����Ϣ
		3���۲����� EXE �� IAT ���ڼ���ǰ��ʲô����
	*/

	// PATH NEW_PATH
	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(NEW_PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SIZE_OF_FILE_BUFFER = ReadPeFileToFileBuffer(NEW_PATH, pFileBuffer);

	// ��ӡ�����
	PrintImportDescriptor(pFileBuffer);

	getchar();

	return 0;
}