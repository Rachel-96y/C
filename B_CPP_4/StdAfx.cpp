// stdafx.cpp : source file that includes just the standard includes
//	project_1.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// ------����Ϊ����ʵ��------


// ************************************************************************

LPVOID CreateFileBuffer(IN LPSTR lpszFile)
{
	/* 
		���ݸ������ļ�·����ȡӲ���ϵ��ļ�
		��ȡ�ļ���С(�ֽ�) 
		�����ļ���С����һ����ͬ��С���ڴ�ռ�
		�ɴ�����Ŀռ䲻�ڴ˺��������ͷ�
		���ִ�гɹ��򷵻��Ѿ�����Ŀռ���׵�ַָ�� ���򷵻�0 
	*/

	// �����ļ�·��(char*)�򿪴��ļ��Ĺܵ� ����ֵ��ָ���ļ��ṹ��ָ��
	FILE* pOpenFile = fopen(lpszFile, "rb");
	if (pOpenFile == NULL)
	{
		// ���ؿ�ָ������ļ��򿪳��ִ���
		printf("�ļ��򿪳��ִ���\n");
		return NULL;
	}

	// �����ļ�ָ�����ļ�ĩβ
	fseek(pOpenFile, 0, SEEK_END);

	// ��ȡ�ļ���С
	DWORD SizeOfFile = ftell(pOpenFile);

	if (SizeOfFile == -1L)
	{
		// ftell ����ֵΪ-1L����˺���ִ�г��ִ���
		printf(" ftell ����ִ��ʧ��\n");
		return NULL;
	}

	// �����ļ�ָ�����ļ���ͷ
	fseek(pOpenFile, 0, SEEK_SET);

	// �ر��ļ��ܵ�
	DWORD FcloseReturnValue = fclose(pOpenFile);

	if (FcloseReturnValue)
	{
		printf(" �ļ��ܵ��ر�ʧ��\n");
		return NULL;
	}

	// Ϊ���ļ�����һ����ͬ��С�Ŀռ�
	LPVOID pFileBuffer = malloc(sizeof(CHAR) * (UINT)SizeOfFile); 
	if (pFileBuffer == NULL)
	{
		printf("�ռ�����ʧ��\n");
		return NULL;
	}
	// ������Ŀռ��ڵ����ݳ�ʼ��Ϊ 0
	memset(pFileBuffer, 0x00000000, sizeof(CHAR) * (UINT)SizeOfFile);

	return pFileBuffer;
}

// ************************************************************************

DWORD MyAlignment(IN LPVOID pPeMemory, IN UINT FileOrSectionAlignment,IN UINT SizeOfCode)
{
	/*
		�����ṩ�� pPeMemory �� ��Ҫ������ֽ��� �� ���뷽ʽ������������Ľ��
		���ִ�гɹ��򷵻ض����Ľ�� ʧ���򷵻�0
	*/
	
	// ��ȡ pPeMemory ��ָ����ڴ��PE�ļ������ֶ������

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pPeMemory;

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

	// ���ݶ�����������뷽ʽ���м��㲢���ؽ��
	DWORD AlignmentNumber = 0x00000000;

	if (!FileOrSectionAlignment)
	{
		// ���ļ�����Ĳ������� FileOrSectionAlignment == 0
		if (!(SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment))
		{
			// ����ڴ����Ĵ�С ����Ҫд��Ĵ���Ĵ�С ��Ҫ��ӵĴ����С�����ڴ����Ĵ�С����
			AlignmentNumber = pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment;
		}
		if (SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment)
		{
			// ����ڴ����Ĵ�С С��Ҫд��Ĵ���Ĵ�С ����Ҫ���м���  
			if (!(SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment))
			{
				// ����պ����ڴ����������� ��Ҫд��Ĵ���Ĵ�С�͵��ڴ˴�С
				AlignmentNumber = SizeOfCode;
			}
			if (SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment)
			{
				// �������Ĵ��볤�� �����ڴ�����ֵ ���Ҳ����ڴ����������� 
				// ��Ҫд��Ĵ���Ĵ�С ��������Ĵ����С�����ڴ�����ֵ�Ľ�� + 1 �ٳ����ڴ����Ĳ���
				AlignmentNumber =  ((SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment) + 1) * pPIMAGE_OPTIONAL_HEADER32 -> FileAlignment;
			}
		}

		return AlignmentNumber;
	}
	else
	{
		// ���ڴ����Ĳ������� FileOrSectionAlignment != 0
		if (!(SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
		{
			// ����ڴ����Ĵ�С ����Ҫд��Ĵ���Ĵ�С ��Ҫ��ӵĴ����С�����ڴ����Ĵ�С����
			AlignmentNumber = pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
		}
		if (SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
		{
			// ����ڴ����Ĵ�С С��Ҫд��Ĵ���Ĵ�С ����Ҫ���м���  
			if (!(SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
			{
				// ����պ����ڴ����������� ��Ҫд��Ĵ���Ĵ�С�͵��ڴ˴�С
				AlignmentNumber = SizeOfCode;
			}
			if (SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
			{
				// �������Ĵ��볤�� �����ڴ�����ֵ ���Ҳ����ڴ����������� 
				// ��Ҫд��Ĵ���Ĵ�С ��������Ĵ����С�����ڴ�����ֵ�Ľ�� + 1 �ٳ����ڴ����Ĳ���
				AlignmentNumber =  ((SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment) + 1) * pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
				// ��ʱ�� SizeOfCodeSectionAlignment Ϊ����Ҫ��ӵĽڵ����ݵĴ�С
		
			}
		}

		return AlignmentNumber;
	}

}

// ************************************************************************

DWORD ReadPeFileToFileBuffer(IN LPSTR pPeFilePath, OUT LPVOID pFileBuffer)
{
	/* 
		���ݸ������ļ�·����ȡӲ���ϵ��ļ�
		�����ȡ��ָ�����ڴ�ռ�
		�������ִ�гɹ��򷵻ض�ȡ���ļ��Ĵ�С(�ֽ�) ʧ�ܷ���0
	*/

	FILE* pOpenFile = fopen(pPeFilePath, "rb");
	if (pOpenFile == NULL)
	{
		// ���ؿ�ָ������ļ��򿪳��ִ���
		printf("�ļ���ʧ��\n");
		return NULL;
	}

	// �����ļ�ָ�����ļ�ĩβ
	fseek(pOpenFile, 0, SEEK_END);

	// ��ȡ�ļ���С
	DWORD SizeOfFile = ftell(pOpenFile);
	if (SizeOfFile == -1L)
	{
		// ftell ����ֵΪ-1L����˺���ִ�г��ִ���
		printf(" ftell ����ִ��ʧ��\n");
		return NULL;
	}
	// �����ļ�ָ�����ļ���ͷ
	fseek(pOpenFile, 0, SEEK_SET);

	DWORD SizeOFReadFile = fread(OUT pFileBuffer, sizeof(CHAR), sizeof(CHAR) * SizeOfFile, IN pOpenFile);
	
	// �ر��ļ��ܵ�
	DWORD FileCloseReturnValue = fclose(pOpenFile);
	if (FileCloseReturnValue)
	{
		printf("�ļ��ܵ��ر�ʧ��\n");
		return NULL;
	}

	return SizeOFReadFile;
}

// ************************************************************************

DWORD WriteMemeryToFile(IN LPVOID pMemBuffer, IN UINT SizeOfFile, OUT LPSTR lpszFile)
{
	/*
		���ݸ����� pMemBuffer ���ļ�·������Ҫд����ļ���С
		���ڴ��е�����д�뵽������
		������̳ɹ��򷵻�д�����ݵĴ�С ʧ���򷵻�0
	*/
	FILE* pOpenFile = fopen(lpszFile, "wb");
	if (pOpenFile == NULL)
	{
		// ���ؿ�ָ������ļ��򿪳��ִ���
		printf("�ļ���ʧ��");
		return NULL;
	}

	// �����ļ�ָ�����ļ���ͷ
	fseek(pOpenFile, 0, SEEK_SET);

	// ���ڴ��е�����д�뵽ָ��Ӳ��·��
	DWORD SizeOfWriteDate = fwrite(pMemBuffer, sizeof(CHAR), sizeof(CHAR) * SizeOfFile, pOpenFile);
	if (SizeOfWriteDate != SizeOfFile)
	{
		printf("д��ʧ��");
		return NULL;
	}

	// �ر��ļ��ܵ�
	DWORD FileCloseReturnValue = fclose(pOpenFile);
	if (FileCloseReturnValue)
	{
		printf("�ļ��ܵ��ر�ʧ��\n");
		return NULL;
	}

	return SizeOfWriteDate;
}

// ************************************************************************

DWORD ChangeRvaToFoa(IN UINT RVA, IN LPVOID pFileBuffer)
{
	/*
		�˺�������һ�� RVA ��һ�� FileBuffer ָ�� ����һ�� FOA
		���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� FOA ʧ���򷵻�0
	*/

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

	// ����һ�� Foa ���ڴ洢���յĽ��
	DWORD FOA = 0;

	// ���� Rva �� pImageBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0; 

	// �ж���������� Rva ������ ImageBuffer �е���һ������
	if (RVA < pPIMAGE_SECTION_HEADER -> VirtualAddress)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		FOA = RVA;
		return FOA;
	}

	for (int i = 0; i < (pPIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (RVA >= (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress)
		{
			// ���� Rva �����һ���ڵ� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress;

			// Foa ��ֵΪ ���һ���ڵ� PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData + TempNumber;
		}

		// ������ڳ����һ���������������
		if (RVA >= (pPIMAGE_SECTION_HEADER + i) -> VirtualAddress && RVA < (pPIMAGE_SECTION_HEADER + i + 1) -> VirtualAddress)
		{
			// ���� Rva �� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pPIMAGE_SECTION_HEADER + i) -> VirtualAddress;

			// Foa ��ֵΪ PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pPIMAGE_SECTION_HEADER + i) -> PointerToRawData + TempNumber;
			
		}
	}

	return FOA;
}

// ************************************************************************

DWORD ChangeFoaToRva(IN UINT FOA, IN LPVOID pFileBuffer)
{
	/*
		�˺�������һ�� FOA ��һ�� FileBuffer ָ�� ����һ�� RVA
		���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� RVA ʧ���򷵻�0
	*/

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

	// ����һ�� Rva ���ڴ洢���յĽ��
	DWORD RVA = 0;

	// ���� Foa �� pFileBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0; 

	// �ж���������� Foa ������ FileBuffer �е���һ������
	if (FOA < pPIMAGE_SECTION_HEADER -> PointerToRawData)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		RVA = FOA;
		return RVA;
	}

	for (int i = 0; i < (pPIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (FOA >= (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData)
		{
			// ���� Foa �����һ���ڵ� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData;

			// RVA ��ֵΪ ���һ���ڵ� VirtualAddress + TempNumber
			RVA = (pPIMAGE_SECTION_HEADER + pPIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress + TempNumber;
		}

		// ������ڳ����һ���������������
		if (FOA >= (pPIMAGE_SECTION_HEADER + i) -> PointerToRawData && FOA < (pPIMAGE_SECTION_HEADER + i + 1) -> PointerToRawData)
		{
			// ���� FOA �� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pPIMAGE_SECTION_HEADER + i) -> PointerToRawData;

			// RVA ��ֵΪ VirtualAddress + TempNumber
			RVA = (pPIMAGE_SECTION_HEADER + i) -> VirtualAddress + TempNumber;
			
		}
	}


	return RVA;
}

// ************************************************************************

LPVOID GetFunctionAddrByName(IN LPVOID pFileBuffer, IN LPSTR FunctionName)
{
	/*
		�������ֻ�ȡ������ģ���еĵ�ַ������
		����ִ�гɹ��򷵻����Һ����ĵ�ַ ʧ���򷵻�0
	*/

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

	// ������� FileBuffer �е������ʵ��ƫ�Ƶ�ַ(FOA) ���� FileBuffer �Ļ���ַ��ֵ��������ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);

	// �ҵ�������� AddressOfNames ����ʼ��ַ 
	LPDWORD PointerToNames = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pFileBuffer) + (DWORD)pFileBuffer);

	for (UINT i = 0; i < pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames; i++)
	{
		// ���� NumberOfNames ��, �ҵ���ָ������������ͬ��ֵ
		if (strcmp(FunctionName + i, (LPSTR)(*(PointerToNames + i) + (DWORD)pFileBuffer)) == 0)
		{
			//������������ҵ�������һ������ ���ٸ������ȥ��ű�����
			// �ҵ� AddressOfNameOrdinals ����ʼ��ַ
			LPWORD PointerToNameOrdinals = (LPWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals, pFileBuffer) + (DWORD)pFileBuffer);

			// �� i ��ֵΪ�±� ��ȡ����Ӧ����ű��ֵ
			WORD SubScript = (WORD)*(PointerToNameOrdinals + i);

			// �ҵ� AddressOfFunctions ����ʼ��ַ
			LPDWORD PointerToFunctions = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, pFileBuffer) + (DWORD)pFileBuffer);

			// �Ի�ȡ������ű����ֵ Ϊ�±� ��ȡ����Ӧ�ĺ����ĵ�ַ
			LPVOID FunctionAddr = (LPVOID)*(PointerToFunctions + SubScript);

			return FunctionAddr;
		}
	}
	
	return NULL;
}

// ************************************************************************

LPVOID GetFunctionAddrByOrdinals(IN LPVOID pFileBuffer, IN UINT FunctionOrdinal)
{
	/*
		������Ż�ȡ������ģ���еĵ�ַ������
		����ִ�гɹ��򷵻����Һ����ĵ�ַ ʧ���򷵻�0
	*/

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

	// ������� FileBuffer �е������ʵ��ƫ�Ƶ�ַ(FOA) ���� FileBuffer �Ļ���ַ��ֵ��������ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);

	// �ҵ�������� AddressOfFunctions ����ʼ��ַ 
	LPDWORD* PointerToFunctions = (LPDWORD*)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, pFileBuffer) + (DWORD)pFileBuffer);

	// ������������� �ҳ������ĵ�ַ
	LPVOID FunctionAddr = (LPVOID)*(PointerToFunctions + (FunctionOrdinal - pPIMAGE_EXPORT_DIRECTORY -> Base));

	return FunctionAddr;
}

// ************************************************************************

DWORD SizeOfDllFunctionLength(IN LPSTR DLL_PATH)
{
	/*
		���ݸ����� DLL ·����ȡ���еĵ�һ���������ĳ���
	*/

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer_DLL = CreateFileBuffer(DLL_PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SizeOf_ReadPeFileToFileBuffer = ReadPeFileToFileBuffer(DLL_PATH, pFileBuffer_DLL);
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pFileBuffer_DLL;

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

	// ������� DLL �ļ��򷵻� NULL 
	if (!(pPIMAGE_FILE_HEADER -> Characteristics & 0x2000))
	{
		printf("�ⲻ��һ����Ч�� DLL �ļ�");
		return NULL;
	}

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pPIMAGE_OPTIONAL_HEADER32 -> DataDirectory);
	
	// ���嵼����ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL);
	
	// �жϴ� DLL �Ƿ��е����ĺ��� û���򷵻� NULL
	if (!pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames)
	{
		// Ŀǰ��֧�������ֵ����ĺ����� DLL ����ע��
		printf("�� DLL û�������ֵ����ĺ���");
		return NULL;
	}
		
	// ����������ֵ����ĺ������ҵ���������ַ�ĵ�ַ
	LPDWORD dwFunctionNameAddr = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL);
	
	// �õ��������ĵ�ַ�� FOA ��������������ĺ���������
	DWORD dwFunctionNameLength = strlen((LPSTR)(ChangeRvaToFoa(*dwFunctionNameAddr, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL));

	return dwFunctionNameLength;
}

// ************************************************************************

LPVOID CleanPeData(IN LPVOID pFileBuffer, IN UINT SizeOfFileBuffer)
{
	/*
		����ļ������ڲ����ص��ڴ��е����������´���һ�� NewFileBuffer
		�� FileBuffer ����Ҫ���ص��ڴ��е����ݿ�����ȥ ���ͷ� FileBuffer �ռ�
	*/

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

	// ��λ�����һ���ڱ�
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);
	
	// �õ�����ڱ������λ�� = PointerToRawDate + SizeOfRawData (��: FileBuffer �����Ĵ�С)
	DWORD TrueSizeOfFileBuffer = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;

	// �ж� SizeOfFileBuffer �� TrueSizeOfFileBuffer ��С�Ƿ���� 
	if (SizeOfFileBuffer == TrueSizeOfFileBuffer) 
	{

		// �������򷵻� pFileBuffer ָ��
		return pFileBuffer;
	}
	else
	{
		// ��������һ���ڴ�
		LPVOID pNewFileBuffer = malloc(sizeof(CHAR) * TrueSizeOfFileBuffer);

		if (pNewFileBuffer == NULL)
		{
			// ����ռ�ʧ���򷵻� NULL
			return NULL;
		}

		// ��������Ŀռ��е�ֵ��Ϊ0
		memset(pNewFileBuffer, 0x00000000, sizeof(CHAR) * TrueSizeOfFileBuffer);

		// �����ݸ��ƹ�ȥ
		memcpy(pNewFileBuffer, pFileBuffer, sizeof(CHAR) * TrueSizeOfFileBuffer);
		
		// �ͷžɵ� FileBuffer ������
		free(pFileBuffer);

		// �� pFileBuffer ָ��ָ�� NULL
		pFileBuffer = NULL;

		//���� pNewFileBuffer ָ��
		return pNewFileBuffer;
	}
}

// ************************************************************************

DWORD SizeOfCodeToInjectDll(IN LPVOID pFileBuffer, IN LPSTR DLL_PATH, IN UINT FunctionNameLength)
{
	/* 
		����ע��һ�� DLL ������Ҫ���ٿռ�
		��Ҫ�ƶ���ȫ������� + �����ĵ���� + ȫ0�ṹ�ĵ���� + \
		ÿ�� DLL �������ӽṹ ( IAT ���������ƶ�)
	*/ 
	
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

	// ���� _IMAGE_THUNK_DATA32 �ṹ��ָ��
	DWORD pPIMAGE_THUNK_DATA32 = (DWORD)(ChangeRvaToFoa(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk, pFileBuffer) + (DWORD)pFileBuffer);

	// ���� _IMAGE_IMPORT_BY_NAME �ṹ��ָ��
	PIMAGE_IMPORT_BY_NAME pPIMAGE_IMPORT_BY_NAME  = (IMAGE_IMPORT_BY_NAME*)(ChangeRvaToFoa(*(LPDWORD)pPIMAGE_THUNK_DATA32, pFileBuffer) + (DWORD)pFileBuffer);

	// ���յĴ����ֽ��� = ���� DLL �ĵ�����С(�����հ׽ṹ�� 20 ���ֽڴ�С) + ������ 20 ���ֽڵĵ�����С + IAT + INT + (Dll������ + 1) + (���������� + 2 + 1)
	DWORD dwSizeOfCodeToInjectDll = (pPIMAGE_DATA_DIRECTORY + 1) -> Size + sizeof(IMAGE_IMPORT_DESCRIPTOR) + \
		sizeof(IMAGE_THUNK_DATA32) * 4 + strlen(DLL_PATH) + sizeof(CHAR) + FunctionNameLength + sizeof(pPIMAGE_IMPORT_BY_NAME -> Hint) + sizeof(CHAR);


	return dwSizeOfCodeToInjectDll;
}

// ************************************************************************

LPVOID IsEnoughSpace(IN LPVOID pFileBuffer, IN UINT SizeOfCodeToInjectDll)
{
	/*
		�ж��Ƿ����㹻�Ŀռ�д������
	*/

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

	// ���� CodeBegin ָ��
	LPVOID pCodeBegin = NULL;
	
	// �ж�ÿ���ڵĿհ����Ƿ������Ҫд������ݴ�С
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		// �����ر���Ҫע�� ���ָ����������ıȽ� Ҫ���з�����
		if ((INT)(pPIMAGE_SECTION_HEADER -> SizeOfRawData - pPIMAGE_SECTION_HEADER -> Misc.VirtualSize) > (INT)SizeOfCodeToInjectDll)
		{
			pCodeBegin= (LPVOID)(pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> Misc.VirtualSize + (DWORD)pFileBuffer);
			break;
		}
		pPIMAGE_SECTION_HEADER++;
	}

	// ���û���κ�һ�������㹻�Ŀռ�д�������򷵻� NULL
	if (!pCodeBegin)
	{
		return NULL;
	}

	// �жϴ˽��Ƿ������ǿɶ���д�� ������������޸�
	if (!(pPIMAGE_SECTION_HEADER -> Characteristics & IMAGE_SCN_MEM_READ))
	{
		// ���ɶ����Ϊ�ɶ�
		pPIMAGE_SECTION_HEADER -> Characteristics &= IMAGE_SCN_MEM_READ;
	}
	
	if (!(pPIMAGE_SECTION_HEADER -> Characteristics & IMAGE_SCN_MEM_WRITE))
	{
		// ����д���Ϊ��д
		pPIMAGE_SECTION_HEADER -> Characteristics &= IMAGE_SCN_MEM_WRITE;
	}
	

	return pCodeBegin;
}

// ************************************************************************

DWORD SizeOfFileBuffer(IN LPVOID pFileBuffer)
{
	/* ���� FileBuffer �������ǰ FileBuffer �Ĵ�С */

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

	// ���ڱ�ṹ��ָ��ƫ�������һ���ڱ�
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);

	// ��ǰ�� FileBuffer �ܴ�С = ���һ���ڵ� PointerToRawData + SizeOfRawData
	DWORD dwSizeOfFileBuffer = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;
		
	return dwSizeOfFileBuffer;
}

// ************************************************************************

DWORD ImportDescriptorInjectDll(IN LPVOID pFileBuffer, IN LPVOID pCodeBegin, IN LPCSTR strDllFunctionNameAddr, IN LPSTR FileNameAddr, IN DWORD SizeOfFileBufferEx)
{
	/* ͨ�������ע�� DLL */

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

	// �����ж� pCodeBegin �Ƿ�Ϊ NULL
	if (!pCodeBegin)
	{
		// ��� pCodeBegin ��ֵΪ NULL ������ڵĿ�����û���㹻�Ŀռ�
		return 0xFFFFFFFF;
	}

	// �ж� pCodeBegin �Ƿ�Ϊ -1
	if ((DWORD)pCodeBegin == 0xFFFFFFFF)
	{	
		// ��ǰ��Ҫд�����ݵ�λ�� = SizeOfFileBufferEx + pFileBuffer
		LPVOID pNewCodeBegin = (LPVOID)(SizeOfFileBufferEx + (DWORD)pFileBuffer);

		// ��������Ŀ¼�еĵ�����ָ��
		(pPIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		// ���ν���������ṹ���Ƶ��µ�λ��
		do
		{
			// �ж��Ƿ�������ṹ���� ����������
			if (!(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk | pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp |\
				pPIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain | pPIMAGE_IMPORT_DESCRIPTOR -> Name | \
				pPIMAGE_IMPORT_DESCRIPTOR -> FirstThunk))
				break;

			// �� pPIMAGE_IMPORT_DESCRIPTOR ���Ƶ� pNewCodeBegin
			memcpy(pNewCodeBegin, pPIMAGE_IMPORT_DESCRIPTOR, sizeof(CHAR) * sizeof(_IMAGE_IMPORT_DESCRIPTOR));

			// �ҵ���һ��ģ��
			pPIMAGE_IMPORT_DESCRIPTOR++;

			// pNewCodeBegin ָ�����ƫ��һ���ṹ���С
			pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR));
		}
		while(TRUE);

		// �µ�DLL�� INT�� ����ʼλ�� FOA (�������� _IMAGE_IMPORT_DESCRIPTOR �ṹ)
		LPVOID pINT_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 - (DWORD)pFileBuffer);
		// �µ�DLL�� IAT�� ����ʼλ�� FOA
		LPVOID pIAT_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 + sizeof(UINT) * 2 - (DWORD)pFileBuffer);
		// �µ�DLL�� NAME ����ʼλ�� FOA
		LPVOID pNAME_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 + sizeof(UINT) * 4 - (DWORD)pFileBuffer);

		// ����һ�� DLL �ĵ���� ������Ա��ֵ
		PIMAGE_IMPORT_DESCRIPTOR pNEW_PIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)pNewCodeBegin;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk = ChangeFoaToRva((DWORD)pINT_FOA, pFileBuffer);
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp = 0;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain = 0;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> Name = ChangeFoaToRva((DWORD)pNAME_FOA, pFileBuffer);
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> FirstThunk = ChangeFoaToRva((DWORD)pIAT_FOA, pFileBuffer);
		// ��β��һ���ṹ���ȫ0�ṹ

		// ���������� DLL �����һ��ȫ0�ṹ
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2);

		// �����˴���ָ���ֵ�Ա�ʹ��
		LPVOID pINT_F0A_ADD_FileBuffer = pNewCodeBegin;

		// ���������� INT ��
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(UINT) * 2);

		// �����˴���ָ���ֵ�Ա�ʹ��
		LPVOID pIAT_F0A_ADD_FileBuffer = pNewCodeBegin;

		// ���������� IAT ��
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(UINT) * 2);

		// �õ� DLL �����ֵĳ���
		DWORD DllNameLength = strlen(FileNameAddr);

		// ��� DLL ����
		strcpy((LPSTR)pNewCodeBegin, (LPCSTR)FileNameAddr);

		// ���� DLL ���Ƶĳ���
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + DllNameLength);
		
		// ����һ�� _IMAGE_IMPORT_BY_NAME �ṹ
		PIMAGE_IMPORT_BY_NAME pPIMAGE_IMPORT_BY_NAME = (IMAGE_IMPORT_BY_NAME*)pNewCodeBegin;

		// _IMAGE_IMPORT_BY_NAME �е� Hint ��Աֵ����Ϊ0
		pPIMAGE_IMPORT_BY_NAME -> Hint = 0;

		// �� DLL �еĺ������Ƹ��Ƶ�ָ��λ��
		strcpy((LPSTR)&pPIMAGE_IMPORT_BY_NAME -> Name, (LPCSTR)strDllFunctionNameAddr);

		// ���� INT ���ֵ
		*(LPDWORD)pINT_F0A_ADD_FileBuffer = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		// ���� IAT ���ֵ
		*(LPDWORD)pIAT_F0A_ADD_FileBuffer = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		return NULL;
	}
	else
	{
		// ��� pCodeBegin ��ֵ��Ϊ NULL �� -1 ��ô pCodeBegin ��ֵ���ǽ�Ҫ����д�����ݵ��׵�ַ
		LPVOID pNewCodeBegin = pCodeBegin;

		// ��������Ŀ¼�еĵ�����ָ��
		(pPIMAGE_DATA_DIRECTORY + 1) -> VirtualAddress = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		// ���ν���������ṹ���Ƶ��µ�λ��
		do
		{
			// �ж��Ƿ�������ṹ���� ����������
			if (!(pPIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk | pPIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp |\
				pPIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain | pPIMAGE_IMPORT_DESCRIPTOR -> Name | \
				pPIMAGE_IMPORT_DESCRIPTOR -> FirstThunk))
				break;

			// �� pPIMAGE_IMPORT_DESCRIPTOR ���Ƶ� pNewCodeBegin
			memcpy(pNewCodeBegin, pPIMAGE_IMPORT_DESCRIPTOR, sizeof(CHAR) * sizeof(_IMAGE_IMPORT_DESCRIPTOR));

			// �ҵ���һ��ģ��
			pPIMAGE_IMPORT_DESCRIPTOR++;

			// pNewCodeBegin ָ�����ƫ��һ���ṹ���С
			pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR));
		}
		while(TRUE);

		// �µ�DLL�� INT�� ����ʼλ�� FOA (�������� _IMAGE_IMPORT_DESCRIPTOR �ṹ)
		LPVOID pINT_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 - (DWORD)pFileBuffer);
		// �µ�DLL�� IAT�� ����ʼλ�� FOA
		LPVOID pIAT_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 + sizeof(UINT) * 2 - (DWORD)pFileBuffer);
		// �µ�DLL�� NAME ����ʼλ�� FOA
		LPVOID pNAME_FOA = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2 + sizeof(UINT) * 4 - (DWORD)pFileBuffer);

		// ����һ�� DLL �ĵ���� ������Ա��ֵ
		PIMAGE_IMPORT_DESCRIPTOR pNEW_PIMAGE_IMPORT_DESCRIPTOR = (IMAGE_IMPORT_DESCRIPTOR*)pNewCodeBegin;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> OriginalFirstThunk = ChangeFoaToRva((DWORD)pINT_FOA, pFileBuffer);
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> TimeDateStamp = 0;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> ForwarderChain = 0;
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> Name = ChangeFoaToRva((DWORD)pNAME_FOA, pFileBuffer);
		pNEW_PIMAGE_IMPORT_DESCRIPTOR -> FirstThunk = ChangeFoaToRva((DWORD)pIAT_FOA, pFileBuffer);
		// ��β��һ���ṹ���ȫ0�ṹ

		// ���������� DLL �����һ��ȫ0�ṹ
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2);

		// �����˴���ָ���ֵ�Ա�ʹ��
		LPVOID pINT_F0A_ADD_FileBuffer = pNewCodeBegin;

		// ���������� INT ��
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(UINT) * 2);

		// �����˴���ָ���ֵ�Ա�ʹ��
		LPVOID pIAT_F0A_ADD_FileBuffer = pNewCodeBegin;

		// ���������� IAT ��
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + sizeof(UINT) * 2);

		// �õ� DLL �����ֵĳ���
		DWORD DllNameLength = strlen(FileNameAddr);

		// ��� DLL ����
		strcpy((LPSTR)pNewCodeBegin, (LPCSTR)FileNameAddr);

		// ���� DLL ���Ƶĳ���
		pNewCodeBegin = (LPVOID)((DWORD)pNewCodeBegin + DllNameLength);
		
		// ����һ�� _IMAGE_IMPORT_BY_NAME �ṹ
		PIMAGE_IMPORT_BY_NAME pPIMAGE_IMPORT_BY_NAME = (IMAGE_IMPORT_BY_NAME*)pNewCodeBegin;

		// _IMAGE_IMPORT_BY_NAME �е� Hint ��Աֵ����Ϊ0
		pPIMAGE_IMPORT_BY_NAME -> Hint = 0;

		// �� DLL �еĺ������Ƹ��Ƶ�ָ��λ��
		strcpy((LPSTR)&pPIMAGE_IMPORT_BY_NAME -> Name, (LPCSTR)strDllFunctionNameAddr);

		// ���� INT ���ֵ
		*(LPDWORD)pINT_F0A_ADD_FileBuffer = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		// ���� IAT ���ֵ
		*(LPDWORD)pIAT_F0A_ADD_FileBuffer = ChangeFoaToRva((DWORD)pNewCodeBegin - (DWORD)pFileBuffer, pFileBuffer);

		return NULL;
	}

}

// ************************************************************************

LPVOID ExpandSection(IN UINT IsSuccess, IN LPVOID pFileBuffer, IN UINT SizeOfCodeAlignment)
{
	/*
		���ݶ�������Ĵ�С�����
	*/
	
	// �ж���������� IsSuccess
	if (!IsSuccess)
	{
		// ������������ IsSuccess ��ֵ�� NULL ��ô�����������
		return pFileBuffer;
	}

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

	// ��ȡ��ǰ�� FileBuffer ��С
	// ��λ�����һ���ڱ�
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);

	// FileBuffer ��С
	DWORD SizeOfFileBuffer = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;
	
	// ������ NewFileBuffer ��С = FileBuffer + SizeOfCodeAlignment
	DWORD SizeOfNewFileBuffer = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData + SizeOfCodeAlignment;

	// �����µĿռ�
	LPVOID pNewFileBuffer = malloc(sizeof(CHAR) * SizeOfNewFileBuffer);

	if (pNewFileBuffer == NULL)
	{
		// ʧ��
		printf(" NewFileBuffer �ռ䴴��ʧ��");
		return NULL;
	}

	// ��ʼ��Ϊ��
	memset(pNewFileBuffer, 0x00000000, sizeof(CHAR) * SizeOfNewFileBuffer);

	// ����ǰ���ݸ��Ƶ��µ�λ��
	memcpy(pNewFileBuffer, pFileBuffer, sizeof(CHAR) * SizeOfFileBuffer);

	// �ͷŵ�ǰ�Ŀռ� ��ʼ�� pFileBuffer ָ��
	free(pFileBuffer);
	pFileBuffer = NULL;

	// �� PE ָ�����¶���

	// ����DOSͷ�ṹ��ָ��
	pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pNewFileBuffer;

	// ����NTͷ�ṹ��ָ��
	pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));
	
	// �����ѡPEͷ�ṹ��ָ��
	pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// У׼����
	// ��ת�����һ����
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);
	
	// Name ��ֵ����Ҫ��

	// VirtualAddress ��ֵ����

	// SizeOfRawData ��ֵ��Ϊ SizeOfRawData + AlignNumber
	pPIMAGE_SECTION_HEADER -> SizeOfRawData = pPIMAGE_SECTION_HEADER -> SizeOfRawData + SizeOfCodeAlignment;

	// Misc ��ֵ����Ϊ�͵�ǰ�� SizeOfRawData һ��
	pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = pPIMAGE_SECTION_HEADER -> SizeOfRawData;

	// PointerToRawData ��ֵ����

	// ����ڵ����Ը�Ϊ �ɶ� / ��д / ��ִ�� / ������ִ�д���
    pPIMAGE_SECTION_HEADER -> Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE;

	// ���� SizeOfImage �е�ֵ
	pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage += SizeOfCodeAlignment;


	return pNewFileBuffer;
}

// ************************************************************************

LPSTR DllFunctionName(IN LPSTR DLL_PATH)
{
	/*
		���ݸ����� DLL ·����ȡ���еĵ�һ��������
	*/

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer_DLL = CreateFileBuffer(DLL_PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SizeOf_ReadPeFileToFileBuffer = ReadPeFileToFileBuffer(DLL_PATH, pFileBuffer_DLL);
	
	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pFileBuffer_DLL;

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

	// ������� DLL �ļ��򷵻� NULL 
	if (!(pPIMAGE_FILE_HEADER -> Characteristics & 0x2000))
	{
		printf("�ⲻ��һ����Ч�� DLL �ļ�");
		return NULL;
	}

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pPIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pPIMAGE_OPTIONAL_HEADER32 -> DataDirectory);
	
	// ���嵼����ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL);
	
	// �жϴ� DLL �Ƿ��е����ĺ��� û���򷵻� NULL
	if (!pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames)
	{
		// Ŀǰ��֧�������ֵ����ĺ����� DLL ����ע��
		printf("�� DLL û�������ֵ����ĺ���");
		return NULL;
	}
		
	// ����������ֵ����ĺ������ҵ���������ַ�ĵ�ַ
	LPDWORD dwFunctionNameAddr = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL);
	
	// �õ��������ĵ�ַ���洢����������
	LPSTR strFunctionNameLength = (LPSTR)(ChangeRvaToFoa(*dwFunctionNameAddr, pFileBuffer_DLL) + (DWORD)pFileBuffer_DLL);

	return strFunctionNameLength;
}

// ************************************************************************

LPSTR GetFileName(IN LPSTR FilePath)
{
	/* 
		���ݴ�����ļ�·����ȡ�ļ����Ʋ�����
	*/

	if (!FilePath)
	{
		return NULL;
	}

	DWORD strLength = strlen(FilePath);
	LPSTR pFileName = NULL;

	for (UINT i = 0; i < strLength; i++)
	{
		if (*FilePath++ == '\\')
		{
			pFileName = FilePath;
		}
	}

	return pFileName;
}

