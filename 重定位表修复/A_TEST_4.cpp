// A_TEST_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


VOID TestDll()
{
	/* �˺������ڲ��Ա��޸ĺ��DLL�ܲ�������ִ�� */

	HMODULE hmodule = LoadLibrary(NEW_PATH);

	int (__stdcall *pPlus) (int, int) = (int (__stdcall *) (int, int))GetProcAddress(hmodule, "_Plus@8");
	int (__stdcall *pSub) (int, int) = (int (__stdcall *) (int, int))GetProcAddress(hmodule, "_Sub@8");
	int (__stdcall *pMul) (int, int) = (int (__stdcall *) (int, int))GetProcAddress(hmodule, "_Mul@8");
	int (__stdcall *pDiv) (int, int) = (int (__stdcall *) (int, int))GetProcAddress(hmodule, "_Div@8");

	int ret1 = pPlus(4, 3);
	int ret2 = pSub(7, 2);
	int ret3 = pMul(6, 4);
	int ret4 = pDiv(9, 3);

	printf("%d\n%d\n%d\n%d", ret1, ret2, ret3, ret4);
	
	return;
}


VOID ChangeImageBase(IN LPVOID pNewFileBuffer)
{
	/* �޸�DLL��ImageBase,�����ض�λ������ */
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pNewFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pPIMAGE_OPTIONAL_HEADER32 -> DataDirectory);
	
	// ������ض�λ��� FOA ������ pFileBuffer ��ֵ ��ֵ���ض�λ��ṹ��ָ��
	PIMAGE_BASE_RELOCATION pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)(ChangeRvaToFoa((pPIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress, pNewFileBuffer) + (DWORD)pNewFileBuffer);

	
	// ���� ImageBase ��ֵ ƫ��Ϊ 64K �ı���
	pPIMAGE_OPTIONAL_HEADER32 -> ImageBase += 0x10000;

	// �ж��Ƿ��һ������ֵ
	if (!(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress))
	{
		// ����ض�λ��û��ֵ�� ֱ�ӷ���
		return;
	}

	do
	{
		// ��Ϊ ImageBase ��ֵ���� 0x10000 �ʽ��ض�λ���еĵ�ַָ��ĵ�ַ��ֵ����Ҫ�� 0x10000 (64K �ı���)

		// ÿ���������ҪУ׼�ĵ�һ����ַ
		LPWORD BASE_RELOCATION_PTR = (LPWORD)((DWORD)pPIMAGE_BASE_RELOCATION + IMAGE_SIZEOF_BASE_RELOCATION);

		// ���ṹ���������Ա�� �����ж�����Ŀ
		DWORD NumberOfBaseRelocation = (pPIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / 2;

		for (UINT i = 0; i < NumberOfBaseRelocation; i++)
		{
			// �������������(ǰ 4 λ����0011)
			if ((*BASE_RELOCATION_PTR & 0x3000) == 0x3000)
			{
				// ��ֵȡ�������м���
				UINT TEMP_NUMBER = *BASE_RELOCATION_PTR;
				
				// ���� 4 λ����
				TEMP_NUMBER &= 0x0FFF;

				// �ҵ���Ҫ�޸ĵĵ�ַ ��ҪתΪFOA
				LPDWORD RelocationNumber = (LPDWORD)(ChangeRvaToFoa(TEMP_NUMBER + pPIMAGE_BASE_RELOCATION -> VirtualAddress, pNewFileBuffer) + (DWORD) pNewFileBuffer);
				*RelocationNumber += 0x10000;
			}

			BASE_RELOCATION_PTR++;
		}
		
		// ����һ�����ȫ����ַ ע�����ﲻ��Ҫ�� IMAGE_SIZEOF_BASE_RELOCATION
		pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pPIMAGE_BASE_RELOCATION + pPIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}	
	// ��� VirtualAddress ���� SizeOfBlock ��ֵΪ0 ���ض�λ�����
	while(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress);


	return;
}



int main(int argc, char const *argv[])
{
	/* �޸�DLL��ImageBase,�����ض�λ��������Ȼ�����.��DLL�Ƿ����ʹ��. */



	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SIZE_OF_FILE_BUFFER = ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// �޸�DLL��ImageBase,�����ض�λ������
	ChangeImageBase(pFileBuffer);

	// ����
	WriteMemeryToFile(pFileBuffer, SIZE_OF_FILE_BUFFER, NEW_PATH);

	// ----------------------------------------------------
	// ����DLL�Ƿ��������ʹ��
	TestDll();  // NEW_PATH
	// ----------------------------------------------------
	
	getchar();

	return 0;
}
