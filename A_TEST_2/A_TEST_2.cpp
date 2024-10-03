// A_TEST_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

VOID PRINT_BASE_RELOCATION(IN LPVOID pFileBuffer)
{
	/* ��ӡ�����ض�λ����Ҫ�޸ĵ�ֵ����Ϣ */

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

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pPIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// ������ض�λ��� FOA ������ pFileBuffer ��ֵ ��ֵ���ض�λ��ṹ��ָ��
	PIMAGE_BASE_RELOCATION pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)(ChangeRvaToFoa((pPIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);
	
	// ��ʼ��ӡ�ض�λ�������
	while((pPIMAGE_BASE_RELOCATION + 1) -> SizeOfBlock && (pPIMAGE_BASE_RELOCATION + 1) -> VirtualAddress)
	{
		// ��� VirtualAddress ���� SizeOfBlock ��ֵΪ0 ���ض�λ�����

		// SizeOfBlock ���С 
		printf("RVA:%x\t���С:%x\n", pPIMAGE_BASE_RELOCATION -> VirtualAddress, pPIMAGE_BASE_RELOCATION -> SizeOfBlock);

		// items ��Ŀ��
		printf("��Ŀ��: %xH\n", (pPIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / 2);

		printf("������: (��ҪУ׼�ĵ�ַ��ƫ��)\n");
		// ��ӡ���ڵ� ��ҪУ׼�ĵ�ַ��ֵ (���ڶ����ֵ�����)  ���ﲻ��Ҫ��ӡ2���ֽ� ֻ��Ҫ 12 λ����
		for (UINT i = 0; i < (pPIMAGE_BASE_RELOCATION -> SizeOfBlock - IMAGE_SIZEOF_BASE_RELOCATION) / 2; i++)
		{
			// �����ж�ǰ 4 λ�Ƿ��� 0011 ����������ӡ��ƫ��
			// if (*(LPWORD)((DWORD)(pPIMAGE_BASE_RELOCATION) + IMAGE_SIZEOF_BASE_RELOCATION + i * sizeof(USHORT)) & 0x3000 == 0x3000);

			// ����Ҫ��ӡ��ֵȥ���� 4 λ���ӡ������ RVA �� FOA
			USHORT TEMP_RVA = *(LPWORD)((DWORD)(pPIMAGE_BASE_RELOCATION) + IMAGE_SIZEOF_BASE_RELOCATION + i * sizeof(USHORT));

			// ���� 4 λ����
			TEMP_RVA &= 0x0FFF;
			// �޷��������ʹ�� >> �൱�� SHR ���� SAR 
			// TEMP_RVA <<= 4;
			// TEMP_RVA >>= 4;

			// ���е�ƫ�������� VirtualAddress ���������� VirtualAddress
			printf("Rva : %x\t", TEMP_RVA + pPIMAGE_BASE_RELOCATION -> VirtualAddress);
			printf("Foa : %x\t", ChangeRvaToFoa(TEMP_RVA + pPIMAGE_BASE_RELOCATION -> VirtualAddress, pFileBuffer));

			// ����� Address ���ܲ������������
			printf("Address : %x\n", ChangeRvaToFoa(TEMP_RVA + pPIMAGE_BASE_RELOCATION -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);

		}
		printf("--------------------------------------------------------------------------------------\n");

		// ����һ�����ȫ����ַ ע�����ﲻ��Ҫ�� IMAGE_SIZEOF_BASE_RELOCATION
		pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pPIMAGE_BASE_RELOCATION + pPIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}

	return;
}

int main(int argc, char* argv[])
{
	/*
		������ϰ��

		1����ӡ�����ض�λ��Ϣ

		2���ض�λ�����������ʲô�ô�
	*/

	// �ض�λ��������Ƶĺô��ǽ�ʡ�ڴ�

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// �� PE �ļ���ȡ�� FileBuffer ��
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ��ӡ�����ض�λ����Ҫ�޸ĵ�ֵ����Ϣ
	PRINT_BASE_RELOCATION(pFileBuffer);

	getchar();
	
	return 0;
}