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

LPVOID CreateImageBuffer(IN LPVOID pFileBuffer)
{
	/*
		���ݸ����� pFileBuffer ָ���ȡ�ڴ��е�����
		��Ҫ���ж��Ƿ���PE�ļ�
		�����PE�ļ������ ��ѡPEͷ�� SizeOfImage �Ĵ�С�������ڴ�ռ�
		���ִ�гɹ��򷵻�������Ŀռ�� pImageBuffer ʧ���򷵻�0
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
		printf("�ⲻ��һ����Ч��PE�ļ�: �����MZͷ��־");
		return NULL;
	}

	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ļ�: �����PE��־");
		return NULL;
	}
	LPVOID pImageBuffer = malloc(sizeof(CHAR) * pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage); 
	if (pImageBuffer == NULL)
	{
		printf(" ImageBuffer �ռ�����ʧ��\n");
		return NULL;
	}

	return pImageBuffer;
}

// ************************************************************************

LPVOID CreateNewBuffer(IN LPVOID pImageBuffer)
{
	/*
		���ݸ����� ImageBuffer ����ó���ѹ����� NewBuffer �Ŀռ��С
		�����ݴ˴�С�����Ӧ�Ŀռ�
		���ִ�гɹ��򷵻�������Ŀռ��ָ�� pNewBuffer ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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
	
	// SizeOfNewBuffer ���յ�ֵΪ��Ҫ������ڴ�ռ��С
	DWORD SizeOfNewBuffer = pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders;
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		SizeOfNewBuffer += pPIMAGE_SECTION_HEADER -> SizeOfRawData;
		pPIMAGE_SECTION_HEADER++;
	}

	LPVOID pNewBuffer = malloc(sizeof(CHAR) * SizeOfNewBuffer); 
	if (pNewBuffer == NULL)
	{
		printf(" NewBuffer �ռ�����ʧ��");
		return NULL;
	}

	return pNewBuffer;
}

// ************************************************************************

LPVOID CreateNewImageBuffer(IN LPVOID pImageBuffer, IN UINT SizeOfCode)
{
	/*
		��������������Ҫ�Ŀռ�
		���ݸ����� pImageBuffer ָ�� ����ó��Ƿ����㹻�Ŀռ����һ���ڱ� 
		������㹻�Ŀռ����һ���ڱ� ��������ṩ�� SizeOfCode �Ĵ�С
		����ó����ڴ����� ���� PE �ļ����ڴ��е��ܴ�С ���Դ�������ͬ��С�Ŀռ�
		���ִ�гɹ��򷵻�������Ŀռ��void*���͵�ָ�� pNewImageBuffer ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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

	// ���������ڱ�Ŀռ��Ƿ��㹻 ���ս���洢�� SizeOfAddNewSection ��
	DWORD SizeOfAddNewSection = 0;
	
	// �ۼ�DOS���еĿռ�  64ΪDOSͷ�Ĵ�С
	SizeOfAddNewSection += ((DWORD)pPIMAGE_NT_HEADERS32 - (DWORD)pPIMAGE_DOS_HEADER - (DWORD)64);
 
	// �ۼ����һ���ڱ��Ŀ��ÿռ� 
	DWORD TempNumber = (pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders -  ((DWORD)pPIMAGE_SECTION_HEADER - (DWORD)pPIMAGE_DOS_HEADER + IMAGE_SIZEOF_SECTION_HEADER * pPIMAGE_FILE_HEADER -> NumberOfSections));

	for (UINT i = 0; i < TempNumber; i++)
	{
		if ((*((PUCHAR)(((DWORD)pPIMAGE_SECTION_HEADER) + IMAGE_SIZEOF_SECTION_HEADER * pPIMAGE_FILE_HEADER -> NumberOfSections) + i)))
		{
			// ������һ���ڱ����ֵ������ѭ�� �����ۼ�
			break;
		}
		SizeOfAddNewSection += 1;
	}

	// ����ܿռ䲻��80���ֽ��򷵻�NULL
	if (SizeOfAddNewSection < IMAGE_SIZEOF_SECTION_HEADER * 2)
	{
		// �ռ䲻�� �޷������� ����NULL
		printf("��PE�ļ� �ռ䲻��������һ����");
		return NULL;
	}

	// ����ռ��㹻����һ���ڱ� ��ʼ�������յ� SizeOfImage �Ĵ�С
	// SizeOfCodeSectionAlignment �����ڴ����Ĵ�С ����˶δ�����Ҫ������ٿռ�  
	DWORD SizeOfCodeSectionAlignment = 0x00000000;
	if (!(SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
	{
		// ����ڴ����Ĵ�С ����Ҫд��Ĵ���Ĵ�С ��Ҫ��ӵĴ����С�����ڴ����Ĵ�С����
		SizeOfCodeSectionAlignment = pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
	}
	if (SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
	{
		// ����ڴ����Ĵ�С С��Ҫд��Ĵ���Ĵ�С ����Ҫ���м���  
		if (!(SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
		{
			// ����պ����ڴ����������� ��Ҫд��Ĵ���Ĵ�С�͵��ڴ˴�С
			SizeOfCodeSectionAlignment = SizeOfCode;
		}
		if (SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
		{
			// �������Ĵ��볤�� �����ڴ�����ֵ ���Ҳ����ڴ����������� 
			// ��Ҫд��Ĵ���Ĵ�С ��������Ĵ����С�����ڴ�����ֵ�Ľ�� + 1 �ٳ����ڴ����Ĳ���
			SizeOfCodeSectionAlignment =  ((SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment) + 1) * pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
		}
	}

	// ��ʱ�� SizeOfCodeSectionAlignment Ϊ����Ҫ��ӵĽڵ����ݵĴ�С
	// ������Ҫ������ڴ�ռ�Ĵ�С����� SizeOfCodeSectionAlignment + SizeOfImage �Ĵ�С
	SizeOfCodeSectionAlignment += pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage;

	// ��������ȷ���Ĵ�С���� NewImageBuffer �Ŀռ�
	LPVOID pNewImageBuffer = malloc(sizeof(CHAR) * SizeOfCodeSectionAlignment);
	if (pNewImageBuffer == NULL)
	{
		printf("pNewImageBuffer �ռ�����ʧ��\n");
		return NULL;
	}

	// ������Ŀռ��ڵ����ݳ�ʼ��Ϊ 0
	memset(pNewImageBuffer, 0x00000000, sizeof(CHAR) * SizeOfCodeSectionAlignment);

	return pNewImageBuffer;
}

// ************************************************************************


LPVOID CreateNewImageBufferEx(IN LPVOID pImageBuffer, IN UINT Size)
{
	/*
		�������ṩ�� pImageBuffer �� Size ������һ��ռ�
		���ִ�гɹ��򷵻�������Ŀռ��ָ�� pNewImageBuffer ʧ���򷵻�0
	*/ 

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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
	
	LPVOID pNewImageBuffer = malloc(sizeof(CHAR) * (pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage + Size));
	if (pNewImageBuffer == NULL)
	{
		// ����ռ�ʧ�ܷ���NULL
		printf("�ռ�����ʧ��");
		return NULL;
	}

	// ������Ŀռ��ڵ����ݳ�ʼ��Ϊ 0
	memset(pNewImageBuffer, 0x00000000, sizeof(CHAR) * (pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage + Size));

	return pNewImageBuffer;
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

DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID pImageBuffer)
{
	/*
		��Ҫ���ж��Ƿ���PE�ļ�
		����������ָ�� �� FileBuffer �����ݸ��Ƶ� ImageBuffer ��
		��������ɹ��򷵻����������ֽ�����С ʧ���򷵻�0
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
		printf("�ⲻ��һ����Ч��PE�ļ�: �����MZͷ��־");
		return NULL;
	}
	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ļ�: �����PE��־");
		return NULL;
	}
	// ���彫���ص�ֵ �������ֽ�����С
	DWORD SizeOfCopyByte = 0x00000000;

	// ��PE�ļ�ͷ��(����ͷ�ӽڱ����ļ�����Ĵ�С)�� FileBuffer ������ ImageBuffer
	memcpy(pImageBuffer, pFileBuffer, pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);

	// ��������ͷ�ӽڱ����ļ�����󿽱��Ĵ�С
	SizeOfCopyByte += pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders;

	// ѭ����PE�ļ� �����ݿ�������Ӧλ��
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		// �� pFileBuffer + PointerToRawData ��λ�� ������ pImageBuffer + VirtualAddress ��λ��
		memcpy(LPVOID((DWORD)pImageBuffer + pPIMAGE_SECTION_HEADER -> VirtualAddress), \
			LPVOID((DWORD)pFileBuffer + pPIMAGE_SECTION_HEADER -> PointerToRawData), \
			pPIMAGE_SECTION_HEADER -> SizeOfRawData);
		// ����ÿ�����ļ�����󿽱��Ĵ�С
		SizeOfCopyByte += pPIMAGE_SECTION_HEADER -> SizeOfRawData;
		pPIMAGE_SECTION_HEADER++;
	}

	return SizeOfCopyByte;
}

// ************************************************************************

DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer,OUT LPVOID pNewBuffer)
{
	/*
		��Ҫ���ж��Ƿ���PE�ļ�
		�����PE�ļ� �����������ָ�� �� ImageBuffer �����ݸ��Ƶ� NewBuffer ��
		��������ɹ��򷵻����������ֽ�����С ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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
	// ���彫���ص�ֵ �������ֽ�����С
	DWORD SizeOfCopyByte = 0x00000000;

	// ��PE�ļ�ͷ��(����ͷ�ӽڱ����ļ�����Ĵ�С)�� ImageBuffer ������ NewBuffer
	memcpy(pNewBuffer, pImageBuffer, pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);

	// ��������ͷ�ӽڱ����ļ�����󿽱��Ĵ�С
	SizeOfCopyByte += pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders;

	// ѭ����PE�ļ� �����ݿ�������Ӧλ��
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		// �� pImageBuffer + VirtualAddress ��λ�� ��λ�� ������ pNewBuffer + PointerToRawData ��λ��
		memcpy(LPVOID((DWORD)pNewBuffer + pPIMAGE_SECTION_HEADER -> PointerToRawData), \
			LPVOID((DWORD)pImageBuffer + pPIMAGE_SECTION_HEADER -> VirtualAddress), \
			pPIMAGE_SECTION_HEADER -> SizeOfRawData);
		// ����ÿ�����ļ�����󿽱��Ĵ�С
		SizeOfCopyByte += pPIMAGE_SECTION_HEADER -> SizeOfRawData;
		pPIMAGE_SECTION_HEADER++;
	}

	return SizeOfCopyByte;
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
BOOL AddCodeToImageBuffer(IN PUCHAR pCodeArray,IN UINT HowNumberOfSections, IN UINT SizeOfArray, OUT LPVOID pImageBuffer)
{
	/*
		�˺������ھ�̬ע�����
		���ݸ����� ָ�������ָ�� �� pImageBufferָ�� ���д���Ĳ���
		��Ҫͬʱָ����������뵽��һ������ ��ָ������Ĵ�С
		����������ɹ�����TRUE ʧ���򷵻�0

	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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

	// �ж��Ƿ��д˽�
	if ((HowNumberOfSections > pPIMAGE_FILE_HEADER -> NumberOfSections) || (HowNumberOfSections <= 0))
	{
		printf("û�д˽�\n");
		return NULL;
	}

	// ���������������ֵ �����һ
	HowNumberOfSections -= 1;

	// �ڱ�ṹ��ָ����ת����Ҫ��Ӵ���Ľ�
	pPIMAGE_SECTION_HEADER += HowNumberOfSections; 

	// ����˽��Ƿ����㹻�Ŀռ�д�����
	if ((INT)(pPIMAGE_SECTION_HEADER -> SizeOfRawData - pPIMAGE_SECTION_HEADER -> Misc.VirtualSize) < (INT)SizeOfArray)
	{
		// û���㹻�Ŀռ����˳�
		printf("�˽�û���㹻�Ŀռ���Ӵ���\n");
		return NULL;
	}
	
	// �жϴ˽ڵ����� ȷ����Ϊ��ִ�е� ��������������
	DWORD TempCharacter = pPIMAGE_SECTION_HEADER -> Characteristics;
	if (!((TempCharacter & IMAGE_SCN_MEM_EXECUTE) == IMAGE_SCN_MEM_EXECUTE))
	{
		pPIMAGE_SECTION_HEADER -> Characteristics |= IMAGE_SCN_MEM_EXECUTE;
	}
	
	// �ҵ�Ҫд������λ��
	PUCHAR CODE_BEGIN = (PUCHAR)(pPIMAGE_SECTION_HEADER -> VirtualAddress + pPIMAGE_SECTION_HEADER -> Misc.VirtualSize + (DWORD)pImageBuffer);

	// �Ƚ������ֵд��ָ��λ��
	for (UINT i = 0; i < SizeOfArray; i++)
	{
		*(CODE_BEGIN + i) = *(pCodeArray + i);
	}
	
	// У�� call �� jmp ����ĵ�ַ  (����(Win10)�� MessageBoxA ������ַ: 0x760D09A0 / 0x760E09A0)
	// ����Ҫ��ת�ĵ�ַ = E8/E9 ����һ�е�ַ + X
	// ��: X = ����Ҫ��ת�ĵ�ַ - E8/E9 ����һ�е�ַ
	// ��ʱ�� E8/E9 �ĵ�ǰ��ַ Ӧ��ȡƫ�Ƶ�ַ + ImageBase
	
	// ��ȡ CODE_BEGIN ���ڴ��е�ƫ�Ƶ�ַ + ImageBase 
	DWORD VIRTUAL_CODE_BEGIN = ((DWORD)CODE_BEGIN - (DWORD)pImageBuffer) + pPIMAGE_OPTIONAL_HEADER32 -> ImageBase;

	// ��У׼ E8 ����ĵ�ַ 
	DWORD E8_Calibration = ToMessageBoxA - (VIRTUAL_CODE_BEGIN + 0x8 + 0x5);
	// У׼ E9 ����ĵ�ַ 
	DWORD E9_Calibration = pPIMAGE_OPTIONAL_HEADER32 -> AddressOfEntryPoint + pPIMAGE_OPTIONAL_HEADER32 -> ImageBase - (VIRTUAL_CODE_BEGIN + 0x8 + 0x5 + 0x5);

	// �� У׼��� E8/E9�����ֵ д�� ImageBuffer ��Ӧλ��
	*(LPDWORD)(CODE_BEGIN + 0x9) = E8_Calibration;
	*(LPDWORD)(CODE_BEGIN + 0xE) = E9_Calibration;

	//������ڵ��ֵ Ϊ��ǰ�� ���뿪ʼ��ƫ��ֵ
	pPIMAGE_OPTIONAL_HEADER32 -> AddressOfEntryPoint =  pPIMAGE_SECTION_HEADER -> VirtualAddress + pPIMAGE_SECTION_HEADER -> Misc.VirtualSize;

	return TRUE;
}

// ************************************************************************

BOOL CopyImageBufferToNewImageBuffer(IN LPVOID pImageBuffer, OUT LPVOID pNewImageBuffer, IN UINT SizeOfCode, IN UINT IsExistMisc)
{
	/*
		�˺�������������
		�� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
		У��������Ҫ������PEͷ���ֵ �������ƶ�PEͷ�ͽڱ�
		��������ɹ��򷵻�TURE ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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

	// �� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
	memcpy(pNewImageBuffer, pImageBuffer, sizeof(CHAR) * pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage);

	// ���¸��ṹ��ָ�븳ֵΪ NewImageBuffer �еĵ�ַ

	// DOSͷ�ṹ��ָ��
	pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pNewImageBuffer;

	// NTͷ�ṹ��ָ��
	pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// ��׼PEͷ�ṹ��ָ��
	pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));

	// ��ѡPEͷ�ṹ��ָ��
	pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// �ڱ�ṹ��ָ��
	pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);


	// SizeOfCodeSectionAlignment �����ڴ����Ĵ�С ����˶δ�����Ҫ������ٿռ�  
	DWORD SizeOfCodeSectionAlignment = 0x00000000;
	if (!(SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
	{
		// ����ڴ����Ĵ�С ����Ҫд��Ĵ���Ĵ�С ��Ҫ��ӵĴ����С�����ڴ����Ĵ�С����
		SizeOfCodeSectionAlignment = pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
	}
	if (SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
	{
		// ����ڴ����Ĵ�С С��Ҫд��Ĵ���Ĵ�С ����Ҫ���м���  
		if (!(SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
		{
			// ����պ����ڴ����������� ��Ҫд��Ĵ���Ĵ�С�͵��ڴ˴�С
			SizeOfCodeSectionAlignment = SizeOfCode;
		}
		if (SizeOfCode % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment)
		{
			// �������Ĵ��볤�� �����ڴ�����ֵ ���Ҳ����ڴ����������� 
			// ��Ҫд��Ĵ���Ĵ�С ��������Ĵ����С�����ڴ�����ֵ�Ľ�� + 1 �ٳ����ڴ����Ĳ���
			SizeOfCodeSectionAlignment =  ((SizeOfCode / pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment) + 1) * pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
			// ��ʱ�� SizeOfCodeSectionAlignment Ϊ����Ҫ��ӵĽڵ����ݵĴ�С
		}
	}

	// ����΢��DOS��Ĵ�С ���ս���洢�� SizeOfAddNewSection �� 64ΪDOSͷ�Ĵ�С
	DWORD MS_DOS_STUB = 0;
	MS_DOS_STUB += ((DWORD)pPIMAGE_NT_HEADERS32 - (DWORD)pPIMAGE_DOS_HEADER - (DWORD)64);

	// ��DOS��Ŀռ���ȫ���� 
	// Ҫ���Ƶ���λ��
	PUCHAR pTempNewPeHeader = (PUCHAR)((DWORD)pPIMAGE_NT_HEADERS32 - MS_DOS_STUB);
	// ��NTͷ��ʼ����
	PUCHAR pTempOldPeHeader = (PUCHAR)(pPIMAGE_NT_HEADERS32);

	// ����Ҫ���ƵĴ�С
	DWORD TempSize = sizeof(pPIMAGE_NT_HEADERS32 -> Signature) + IMAGE_SIZEOF_FILE_HEADER + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader + pPIMAGE_FILE_HEADER -> NumberOfSections * IMAGE_SIZEOF_SECTION_HEADER;
	// ������ PE ͷ�ӽڱ��������� 
	memcpy((LPVOID)pTempNewPeHeader, (LPVOID)pTempOldPeHeader, TempSize);

	// e_lfanew ָ�����ĺ�һ���ֽ�
	pPIMAGE_DOS_HEADER -> e_lfanew = (DWORD)64;

	// Ϊ��DOSͷ�ṹ��ָ����������ṹ��ָ�����¸�ֵ

	// NTͷ�ṹ��ָ��
	pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// ��׼PEͷ�ṹ��ָ��
	pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));

	// ��ѡPEͷ�ṹ��ָ��
	pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// �ڱ�ṹ��ָ��
	pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);


	// �����ڱ�(��������һ���ڱ���������һ���ڱ�Ŀռ���Ϊ0)
	pPIMAGE_SECTION_HEADER += pPIMAGE_FILE_HEADER -> NumberOfSections;

	for (int i = 0; i < IMAGE_SIZEOF_SECTION_HEADER * 2; i++)
	{
		// �ܹ� 80 ���ֽ�ȫ����Ϊ 0
		*((PUCHAR)pPIMAGE_SECTION_HEADER + i) = 0;
	}
	
	// У������ Ŀǰ pPIMAGE_SECTION_HEADER �ڱ�ָ��պ�ָ�������Ľ�

	// �����ڵ�����
	pPIMAGE_SECTION_HEADER -> Name[0] = '.';
	pPIMAGE_SECTION_HEADER -> Name[1] = 'M';
	pPIMAGE_SECTION_HEADER -> Name[2] = 'y';
	pPIMAGE_SECTION_HEADER -> Name[3] = 'C';
	pPIMAGE_SECTION_HEADER -> Name[4] = 'o';
	pPIMAGE_SECTION_HEADER -> Name[5] = 'd';
	pPIMAGE_SECTION_HEADER -> Name[6] = 'e';
	pPIMAGE_SECTION_HEADER -> Name[7] = '\0';

	// �����ڶ���ǰ�ĳߴ� ���ݴ���� IsExistMisc ��ֵ��д��
	// 0���� Misc ��ֵΪ0 ��������ֵ������ֵ����SizeOfRawData
	if (!IsExistMisc)
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = 0;
	}
	else
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = SizeOfCodeSectionAlignment;
	}

	// ���������ڴ��е�ʱ���ƫ��
	pPIMAGE_SECTION_HEADER -> VirtualAddress = pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage;

	// �����ڵ� SizeOfRawData
	pPIMAGE_SECTION_HEADER -> SizeOfRawData = SizeOfCodeSectionAlignment;

	// �����ڵ� PointerToRawData ������һ���ڵ� PointerToRawData + ��һ���ڵ� Misc.VirtualSize
	pPIMAGE_SECTION_HEADER--;
	DWORD TempPointerToRawData = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;
	pPIMAGE_SECTION_HEADER++;
	pPIMAGE_SECTION_HEADER -> PointerToRawData = TempPointerToRawData;

	// �����ڵ����Ը�Ϊ �ɶ� / ��ִ�� / ������ִ�д���
    pPIMAGE_SECTION_HEADER -> Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE;

	// ����׼PEͷ�� NumberOfSections ��Ա�Ľ�����1
	pPIMAGE_FILE_HEADER -> NumberOfSections += 1;

	// TempNumber ��ֵ���� VirtualAddress + Misc.VirtualSize �� PointerToRawData ֮��ϴ��ֵ
	DWORD TempNumber = 0x00000000;
	TempNumber = pPIMAGE_SECTION_HEADER ->VirtualAddress + \
		(pPIMAGE_SECTION_HEADER -> Misc.VirtualSize > pPIMAGE_SECTION_HEADER -> PointerToRawData ? \
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize : pPIMAGE_SECTION_HEADER -> PointerToRawData);

	// TempNumber �����ڴ����
	if (!(TempNumber % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment))
	{
		pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage = TempNumber - (TempNumber % pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment) + pPIMAGE_OPTIONAL_HEADER32 -> SectionAlignment;
	}
	else
	{
		pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage = TempNumber;
	}

	return TRUE;
}

// ************************************************************************

BOOL CopyImageBufferToNewImageBufferEx(IN LPVOID pImageBuffer, OUT LPVOID pNewImageBuffer, IN UINT AlignNumber, IN UINT IsExistMisc, IN UINT CodeSize)
{
	/*
		�˺������������
		�� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
		У��������Ҫ������PEͷ���ֵ
		���ִ�гɹ��򷵻�TRUE ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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

	// �� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
	memcpy(pNewImageBuffer, pImageBuffer, sizeof(CHAR) * pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage);

	// ���¸��ṹ��ָ�븳ֵΪ NewImageBuffer �еĵ�ַ

	// DOSͷ�ṹ��ָ��
	pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pNewImageBuffer;

	// NTͷ�ṹ��ָ��
	pPIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew);

	// ��׼PEͷ�ṹ��ָ��
	pPIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pPIMAGE_NT_HEADERS32 + sizeof(pPIMAGE_NT_HEADERS32 -> Signature));

	// ��ѡPEͷ�ṹ��ָ��
	pPIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pPIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// �ڱ�ṹ��ָ��
	pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// У׼����
	// ��ת�����һ����
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER ->NumberOfSections - 1);

	// ���ֿ��Բ������޸�
	// ����ڶ���ǰ�ĳߴ� ���ݴ���� IsExistMisc ��ֵ��д��
	if (!IsExistMisc)
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = 0;
	}
	else if (IsExistMisc == 1)
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = (pPIMAGE_SECTION_HEADER -> SizeOfRawData + AlignNumber - CodeSize);
	}
	else
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = (pPIMAGE_SECTION_HEADER -> SizeOfRawData + AlignNumber);
	}

	// VirtualAddress ��ֵ����
	// SizeOfRawData ��ֵ��Ϊ SizeOfRawData + AlignNumber
	pPIMAGE_SECTION_HEADER -> SizeOfRawData = pPIMAGE_SECTION_HEADER -> SizeOfRawData + AlignNumber;
	// PointerToRawData ��ֵ����Ҫ��
	// ����ڵ����Ը�Ϊ �ɶ� / ��д / ��ִ�� / ������ִ�д���
    pPIMAGE_SECTION_HEADER -> Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE;

	// ���� SizeOfImage �е�ֵ
	pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage += AlignNumber;

	return TRUE;
}

// ************************************************************************

BOOL ChangeImageBufferData(IN LPVOID pImageBuffer, IN UINT IsExistMisc, IN UINT CodeSize)
{
	/*
		�˺������ںϲ���
		�� ImageBuffer ������ȫ������
		���ִ�гɹ��򷵻�TRUE ʧ���򷵻�0
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pImageBuffer;

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

	// �ж��Ƿ�ֻ��һ����
	if (pPIMAGE_FILE_HEADER -> NumberOfSections <= 1)
	{
		// ���ֻ��һ������ֱ�ӷ���NULL
		return NULL;
	}

	// �޸ĵ�һ���ڵ�����
	// name ���Բ��ø�
	// PointerToRawData ����ԭ����ֵ
	// VirtualAddress ����ԭ����ֵ
	// SizeOfImage ����ԭ����ֵ

	if (!IsExistMisc)
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = 0;
	}
	else if (IsExistMisc == 1)
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = (pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage - pPIMAGE_SECTION_HEADER -> VirtualAddress - CodeSize);
	}
	else
	{
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = (pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage - pPIMAGE_SECTION_HEADER -> VirtualAddress);
	}

	// SizeOfRawData ��ֵ���� SizeOfImage - VirtualAddress
	pPIMAGE_SECTION_HEADER -> SizeOfRawData = pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage - pPIMAGE_SECTION_HEADER -> VirtualAddress;

	// Characteristics ��Ϊ ���������ڵ�ȫ������
	DWORD TempCharacteristics = 0x00000000;
	int TempNumber;
	for (TempNumber = 0; TempNumber < pPIMAGE_FILE_HEADER -> NumberOfSections; TempNumber++)
	{
		TempCharacteristics |= pPIMAGE_SECTION_HEADER -> Characteristics;
		pPIMAGE_SECTION_HEADER++;
	}
	// ���ڱ�ָ�뻹ԭ
	pPIMAGE_SECTION_HEADER -= TempNumber;

	// Ϊ�ڱ� Characteristics ���� ��ֵ
	pPIMAGE_SECTION_HEADER -> Characteristics = TempCharacteristics;

	// �޸� NumberOfSections ��ֵΪ1
	pPIMAGE_FILE_HEADER -> NumberOfSections = 1;

	// �� ��һ���ں���� 40 ���ֽ�ȫ����Ϊ0
	pPIMAGE_SECTION_HEADER++;
	for (int i = 0; i < IMAGE_SIZEOF_SECTION_HEADER; i++)
	{
		*((PUCHAR)pPIMAGE_SECTION_HEADER + i) = 0;
	}
	
	return TRUE;  
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
