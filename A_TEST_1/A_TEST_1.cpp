// A_TEST_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL PrintExport(LPVOID pFileBuffer)
{
	/* ��ӡ���еĵ�������Ϣ */

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

	// ������� FileBuffer �е������ʵ��ƫ�Ƶ�ַ(FOA) ���� FileBuffer �Ļ���ַ��ֵ��������ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);

	// ��ӡ����Ŀ¼�е������ֵ
	printf("����Ŀ¼(������):\nVirtualAddress:		%x\n", pPIMAGE_DATA_DIRECTORY -> VirtualAddress);
	printf("Size:			%x\n\n", pPIMAGE_DATA_DIRECTORY -> Size);

	// ��ӡ�����еĵ�������Ϣ
	printf("��������Ϣ:\nCharacteristics:	%d\n", pPIMAGE_EXPORT_DIRECTORY -> Characteristics);	// ������
	printf("TimeDateStamp:		%d\n", pPIMAGE_EXPORT_DIRECTORY -> TimeDateStamp);
	printf("MajorVersion:		%d\n", pPIMAGE_EXPORT_DIRECTORY -> MajorVersion);		// ������
	printf("MinorVersion:		%d\n", pPIMAGE_EXPORT_DIRECTORY -> MinorVersion);		// ������
	printf("Name:			%d\n", pPIMAGE_EXPORT_DIRECTORY -> Name);
	printf("Base:			%d\n", pPIMAGE_EXPORT_DIRECTORY -> Base);		// Base + ÿһ����ű��ֵ = ����ʱ����ű�
	printf("NumberOfFunctions:	%d\n", pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions);	// ���������ĸ���
	printf("NumberOfNames:		%d\n", pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames);		// �Ժ����������ĺ����ĸ���

	printf("AddressOfFunctions:	%x\n", pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions);		// ����������ַ���ַRVA
	printf("AddressOfNames:		%x\n", pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames);		// �����������Ʊ��ַRVA
	printf("AddressOfNameOrdinals:	%x\n", pPIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals);		// ����������ű��ַRVA
	// �������д洢������ַ�ĵ�ַ
	LPDWORD PointerToFunctions = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, pFileBuffer) + (DWORD)pFileBuffer);
	
	// ��ӡ�����к����ĵ�ַ
	for (UINT i = 0; i< pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions; i++)
	{
		printf("������ַ(RVAƫ��): %x\n", *(PointerToFunctions + i));
	}

	// �������д洢�������ֵ�ַ�ĵ�ַ
	LPDWORD PointerToNames = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pFileBuffer) + (DWORD)pFileBuffer);
	for (i = 0; i < pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions; i++)
	{
		// ע�� AddressOfNames �еĵ�ַ��ƫ�Ƶ�ַ ��Ҫ���� pFileBuffer
		// ע�� ���¡���ӡ ���������ھ��� NONAME ��ģ��
		printf("��������: %s\n", *(PointerToNames + i) + (DWORD)pFileBuffer);
	}

	// �������д洢�������еĵ�ַ  (����+base = ��������) 
	LPWORD PointerToNameOrdinals = (LPWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals, pFileBuffer) + (DWORD)pFileBuffer);
	for (i = 0; i < pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions; i++)
	{
		printf("�������: %x\n", *(PointerToNameOrdinals + i));
	}
	return 0;
}

int main(int argc, char* argv[])
{
	/*
		��ϰ��

		1����дһ�� RVA ת FOA �ĺ���

		2����д�����ӡ���еĵ�������Ϣ

		3��GetFunctionAddrByName(FileBufferָ�룬������ָ��)

		4��GetFunctionAddrByOrdinals(FileBufferָ�룬�������������)
	*/

	

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// �� PE �ļ���ȡ�� FileBuffer ��
	ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ��ӡ���еĵ��������Ϣ
	PrintExport(pFileBuffer);	

	// ����ָ�����������ҵ�������ģ���е�ƫ�Ƶ�ַ
	LPVOID FunctionAddr = GetFunctionAddrByName(pFileBuffer, "Sub"); 
	printf("%x\n", FunctionAddr);

	// ����ָ������ҵ�������ģ���е�ƫ�Ƶ�ַ
	LPVOID FunctionAddr2 = GetFunctionAddrByOrdinals(pFileBuffer, 13);
	printf("%x\n", FunctionAddr2);

	getchar();

	return 0;
}