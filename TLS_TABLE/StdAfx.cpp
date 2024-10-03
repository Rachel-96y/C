// stdafx.cpp : source file that includes just the standard includes
//	TLS_TABLE.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//////////////////////////////////////////////////////////////////////
// ���ļ��ṩ���� PE �ļ��ĺ���
//////////////////////////////////////////////////////////////////////

DWORD ChangeRvaToFoa32(IN DWORD RVA, IN LPVOID fpFileBuffer)
{
	/*
		�˺���Ϊ32λPE�ļ�RVAתFOA
		�˺�������һ�� RVA ��һ�� FileBuffer ָ�� ����һ�� FOA
		���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� FOA ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ����һ�� Foa ���ڴ洢���յĽ��
	DWORD FOA = 0;

	// ���� Rva �� pImageBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0;

	// �ж���������� Rva ������ ImageBuffer �е���һ������
	if (RVA < pIMAGE_SECTION_HEADER -> VirtualAddress)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		FOA = RVA;
		return FOA;
	}

	for (int i = 0; i < (pIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (RVA >= (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress)
		{
			// ���� Rva �����һ���ڵ� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress;

			// Foa ��ֵΪ ���һ���ڵ� PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData + TempNumber;
		}

		// ������ڳ����һ���������������
		if (RVA >= (pIMAGE_SECTION_HEADER + i) -> VirtualAddress && RVA < (pIMAGE_SECTION_HEADER + i + 1) -> VirtualAddress)
		{
			// ���� Rva �� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pIMAGE_SECTION_HEADER + i) -> VirtualAddress;

			// Foa ��ֵΪ PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pIMAGE_SECTION_HEADER + i) -> PointerToRawData + TempNumber;
			
		}
	}

	return FOA;
}

//////////////////////////////////////////////////////////////////////
DWORD ChangeRvaToFoa64(IN DWORD RVA, IN LPVOID fpFileBuffer)
{
	/*
		�˺���Ϊ64λPE�ļ�RVAתFOA
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER64 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ����һ�� Foa ���ڴ洢���յĽ��
	DWORD FOA = 0;

	// ���� Rva �� pImageBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0;

	// �ж���������� Rva ������ ImageBuffer �е���һ������
	if (RVA < pIMAGE_SECTION_HEADER -> VirtualAddress)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		FOA = RVA;
		return FOA;
	}

	for (int i = 0; i < (pIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (RVA >= (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress)
		{
			// ���� Rva �����һ���ڵ� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress;

			// Foa ��ֵΪ ���һ���ڵ� PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData + TempNumber;
		}

		// ������ڳ����һ���������������
		if (RVA >= (pIMAGE_SECTION_HEADER + i) -> VirtualAddress && RVA < (pIMAGE_SECTION_HEADER + i + 1) -> VirtualAddress)
		{
			// ���� Rva �� VirtualAddress ֮���ƫ��
			TempNumber = RVA - (pIMAGE_SECTION_HEADER + i) -> VirtualAddress;

			// Foa ��ֵΪ PointerToRawData ���� Rva �� VirtualAddress ֮���ƫ��
			FOA = (pIMAGE_SECTION_HEADER + i) -> PointerToRawData + TempNumber;
			
		}
	}

	return FOA;
}

//////////////////////////////////////////////////////////////////////

DWORD ChangeFoaToRva32(IN UINT FOA, IN LPVOID fpFileBuffer)
{
	/*
		�˺�������һ�� FOA ��һ�� FileBuffer ָ�� ����һ�� RVA
		���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� RVA ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ����һ�� Rva ���ڴ洢���յĽ��
	DWORD RVA = 0;

	// ���� Foa �� pFileBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0; 

	// �ж���������� Foa ������ FileBuffer �е���һ������
	if (FOA < pIMAGE_SECTION_HEADER -> PointerToRawData)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		RVA = FOA;
		return RVA;
	}

	for (int i = 0; i < (pIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (FOA >= (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData)
		{
			// ���� Foa �����һ���ڵ� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData;

			// RVA ��ֵΪ ���һ���ڵ� VirtualAddress + TempNumber
			RVA = (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress + TempNumber;
		}

		// ������ڳ����һ���������������
		if (FOA >= (pIMAGE_SECTION_HEADER + i) -> PointerToRawData && FOA < (pIMAGE_SECTION_HEADER + i + 1) -> PointerToRawData)
		{
			// ���� FOA �� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pIMAGE_SECTION_HEADER + i) -> PointerToRawData;

			// RVA ��ֵΪ VirtualAddress + TempNumber
			RVA = (pIMAGE_SECTION_HEADER + i) -> VirtualAddress + TempNumber;
			
		}
	}

	return RVA;
}

//////////////////////////////////////////////////////////////////////
DWORD ChangeFoaToRva64(IN UINT FOA, IN LPVOID fpFileBuffer)
{
	/*
		�˺���Ϊ64λPE�ļ�FOAתRVA
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)fpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS64 pIMAGE_NT_HEADERS64 = (IMAGE_NT_HEADERS64*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS64 + sizeof(pIMAGE_NT_HEADERS64 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER64 pIMAGE_OPTIONAL_HEADER64 = (IMAGE_OPTIONAL_HEADER64*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER64 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ����һ�� Rva ���ڴ洢���յĽ��
	DWORD RVA = 0;

	// ���� Foa �� pFileBuffer ֮���ƫ�� �洢�� TempNumber ��
	DWORD TempNumber = 0; 

	// �ж���������� Foa ������ FileBuffer �е���һ������
	if (FOA < pIMAGE_SECTION_HEADER -> PointerToRawData)
	{
		// ������ڵ�һ����֮�� �����ֵ����Foa
		RVA = FOA;
		return RVA;
	}

	for (int i = 0; i < (pIMAGE_FILE_HEADER -> NumberOfSections - 1); i++)
	{
		// ����������һ������
		if (FOA >= (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData)
		{
			// ���� Foa �����һ���ڵ� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> PointerToRawData;

			// RVA ��ֵΪ ���һ���ڵ� VirtualAddress + TempNumber
			RVA = (pIMAGE_SECTION_HEADER + pIMAGE_FILE_HEADER -> NumberOfSections - 1) -> VirtualAddress + TempNumber;
		}

		// ������ڳ����һ���������������
		if (FOA >= (pIMAGE_SECTION_HEADER + i) -> PointerToRawData && FOA < (pIMAGE_SECTION_HEADER + i + 1) -> PointerToRawData)
		{
			// ���� FOA �� PointerToRawData ֮���ƫ��
			TempNumber = FOA - (pIMAGE_SECTION_HEADER + i) -> PointerToRawData;

			// RVA ��ֵΪ VirtualAddress + TempNumber
			RVA = (pIMAGE_SECTION_HEADER + i) -> VirtualAddress + TempNumber;
			
		}
	}

	return RVA;
}

//////////////////////////////////////////////////////////////////////

DWORD IsPeFile(IN LPTSTR lpszFilePath, OUT LPVOID* lpFileBuffer)
{
	/*
		����ļ��Ƿ���PE�ļ�
		�����PE�ļ��������Ч��PE�ļ���С���ж�ȡ
	*/

	// �Զ������Ƶķ�ʽ���ļ���
	FILE* lpszFileStream = fopen(lpszFilePath, "rb");
	if (!lpszFileStream)
	{
		// ���ؿ�ָ��������ļ��򿪳��ִ���
		return ERROR_OPEN_FILE;
	}

	// ���ڴ洢��Ҫ�жϵ�����
	DWORD dwSignature = 0;

	// ���ȶ�ȡ2���ֽ�
	DWORD dwFreadCount = fread(&dwSignature, sizeof(CHAR), sizeof(WORD), lpszFileStream);
	if (dwFreadCount != sizeof(WORD))
	{
		// �ļ���ȡʧ��
		return ERROR_READ_FILE;
	}
	
	// ����Ƿ�����Ч��DOS_MZ��־
	if (LOWORD(dwSignature) != IMAGE_DOS_SIGNATURE)
	{
		// �����DOS_MZͷ
		return ERROR_DOS_MZ;
	}

	// ���DOS_MZͷ��ֵ��ȷ,���ļ�ָ�����ƫ��0x3A�ĳ���
	fseek(lpszFileStream, 0x3A, SEEK_CUR);

	// ��ȡ4���ֽڵĳ���,�õ�e_lfanew��ֵ
	dwFreadCount = fread(&dwSignature, sizeof(CHAR), sizeof(DWORD), lpszFileStream);
	if (dwFreadCount != sizeof(DWORD))
	{
		return ERROR_READ_FILE;
	}
	
	// �ļ�ָ����ļ���ͷ���ƫ��e_lfanew�Ĵ�С
	fseek(lpszFileStream, dwSignature, SEEK_SET);

	// �ٶ�ȡ4���ֽڵĳ���,�õ�IMAGE_NT_SIGNATURE
	dwFreadCount = fread(&dwSignature, sizeof(CHAR), sizeof(DWORD), lpszFileStream);
	if (dwFreadCount != sizeof(DWORD))
	{
		return ERROR_READ_FILE;
	}

	// ���PE��־�Ƿ���ȷ
	if (dwSignature != IMAGE_NT_SIGNATURE)
	{
		// �����PE��־
		return ERROR_PE_SIGNATURE;
	}

	//	�ļ�ָ�������ƫ��20���ֽ�
	fseek(lpszFileStream, IMAGE_SIZEOF_FILE_HEADER, SEEK_CUR);

	// ��ȡ2���ֽ�
	dwFreadCount = fread(&dwSignature, sizeof(CHAR), sizeof(WORD), lpszFileStream);
	if (dwFreadCount != sizeof(WORD))
	{
		return ERROR_READ_FILE;
	}

	// Ĭ����32λ�ĳ���

	// ȡ��SizeOfHeaders��ֵ
	dwFreadCount = fread(&dwSignature, sizeof(CHAR), sizeof(DWORD), lpszFileStream);
	if (dwFreadCount != sizeof(DWORD))
	{
		return ERROR_READ_FILE;
	}
	
	// �ȸ��ݴ˴�С����ռ�
	LPVOID lpszFileBuffer = malloc(sizeof(CHAR) * dwSignature);
	if (!lpszFileBuffer)
	{
		// �ڴ�����ʧ��
		return ERROR_MEMORY_REQUEST_FAILURE;
	}
	memset(lpszFileBuffer, 0x00000000, sizeof(CHAR) * dwSignature);
	fseek(lpszFileStream, 0, SEEK_SET);
	fread(lpszFileBuffer, sizeof(CHAR), sizeof(CHAR) * dwSignature, lpszFileStream);

	// ����32λPE�ļ�����ָ��

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)lpszFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ת�����һ����
	pIMAGE_SECTION_HEADER += (pIMAGE_FILE_HEADER -> NumberOfSections - 1);
	
	// �õ����һ���ڵ�PointerToRawData + SizeOfRawData�Ĵ�С
	dwSignature = pIMAGE_SECTION_HEADER -> PointerToRawData + pIMAGE_SECTION_HEADER -> SizeOfRawData;

	// �ͷŵ�ǰ�ռ�
	free(lpszFileBuffer);

	// ���PE�ļ���ʵ����Ч��С����1G�򷵻�
	if (dwSignature >= FILE_MAX_SIZE)
	{
		return ERROR_PE_FILE_TOO_BIG;
	}
	
	// ����������Ч��PE�ļ���С+0x10���ֽ�(�Է�ֹ�ض�λ�����ʧ��)
	lpszFileBuffer = malloc(sizeof(CHAR) * dwSignature + 0x10);
	if (!lpszFileBuffer)
	{
		// �ڴ�����ʧ��
		return ERROR_MEMORY_REQUEST_FAILURE;
	}
	memset(lpszFileBuffer, 0x00000000, sizeof(CHAR) * dwSignature + 0x10);
	fseek(lpszFileStream, 0, SEEK_SET);
	fread(lpszFileBuffer, sizeof(CHAR), sizeof(CHAR) * dwSignature, lpszFileStream);

	// ���ļ�ָ�뷵����ָ����λ��
	*(LPDWORD*)lpFileBuffer = (LPDWORD)lpszFileBuffer;

	// �ر��ļ���
	dwFreadCount = fclose(lpszFileStream);
	if (dwFreadCount)
	{
		// �ļ��ر�ʧ��
		free(lpszFileBuffer);
		lpszFileBuffer = NULL;
		return ERROR_CLOSE_FILE;
	}

	return RETURN_SUCCESS;
}

//////////////////////////////////////////////////////////////////////


