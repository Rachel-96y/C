#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct _IMAGE_DOS_HEADER 
{      
	// DOSͷ
    WORD   e_magic;                   
    WORD   e_cblp;                    
    WORD   e_cp;                       
    WORD   e_crlc;                 
    WORD   e_cparhdr;                   
    WORD   e_minalloc;                
    WORD   e_maxalloc;                 
    WORD   e_ss;                       
    WORD   e_sp;                      
    WORD   e_csum;                 
    WORD   e_ip;                        
    WORD   e_cs;                        
    WORD   e_lfarlc;                   
    WORD   e_ovno;                     
    WORD   e_res[4];                    
    WORD   e_oemid;                     
    WORD   e_oeminfo;                  
    WORD   e_res2[10];                  
    WORD   e_lfanew; 
	
} IMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER 
{
	// ��׼PEͷ
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;

}IMAGE_FILE_HEADER;

typedef struct _IMAGE_OPTIONAL_HEADER 
{
	// ��ѡPEͷ
    //
    // Standard fields.
    //

    WORD    Magic;
    BYTE    MajorLinkerVersion;
    BYTE    MinorLinkerVersion;
    DWORD   SizeOfCode;
    DWORD   SizeOfInitializedData;
    DWORD   SizeOfUninitializedData;
    DWORD   AddressOfEntryPoint;
    DWORD   BaseOfCode;
    DWORD   BaseOfData;

    //
    // NT additional fields.
    //

    DWORD   ImageBase;
    DWORD   SectionAlignment;
    DWORD   FileAlignment;
    WORD    MajorOperatingSystemVersion;
    WORD    MinorOperatingSystemVersion;
    WORD    MajorImageVersion;
    WORD    MinorImageVersion;
    WORD    MajorSubsystemVersion;
    WORD    MinorSubsystemVersion;
    DWORD   Win32VersionValue;
    DWORD   SizeOfImage;
    DWORD   SizeOfHeaders;
    DWORD   CheckSum;
    WORD    Subsystem;
    WORD    DllCharacteristics;
    DWORD   SizeOfStackReserve;
    DWORD   SizeOfStackCommit;
    DWORD   SizeOfHeapReserve;
    DWORD   SizeOfHeapCommit;
    DWORD   LoaderFlags;
    DWORD   NumberOfRvaAndSizes;

}IMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_SECTION_HEADER 
{
	// �ڱ�
    BYTE    Name[8];
    union {
            DWORD   PhysicalAddress;
            DWORD   VirtualSize;
    } Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;

}IMAGE_SECTION_HEADER;


IMAGE_DOS_HEADER* pIMAGE_DOS_HEADER = NULL;  // ���� dos ͷ�ṹ��ָ��
IMAGE_FILE_HEADER* pIMAGE_FILE_HEADER = NULL;  // ������׼ PE ͷ�ṹ��ָ��
IMAGE_OPTIONAL_HEADER32* pIMAGE_OPTIONAL_HEADER32 = NULL;  // ������ѡ PE ͷ�ṹ��ָ��
IMAGE_SECTION_HEADER* pIMAGE_SECTION_HEADER = NULL; // �����ڱ�ṹ��ָ��

_iobuf* pfileStream = NULL; // �����ļ��ܵ�ָ��
_iobuf* pNewfileStream = NULL; // �����µ��ļ��ܵ�ָ��

void* pMemoryOfFileBuffer = NULL; // ���� FileBuffer �ѿռ�ָ�� (�����ͷſռ�)
char* pPrinterOfFileBuffer = NULL; // ���� FileBuffer ָ�� (���ڼ���)

void* pMemoryOfImageBuffer = NULL; // ���� ImageBuffer �ѿռ�ָ�� (�����ͷſռ�)
char* pPrinterOfImageBuffer = NULL; // ���� ImageBuffer ָ��(���ڼ���)

void* pMemoryOfNewFileBuffer = NULL; // ���� ImageBuffer �ѿռ�ָ�� (�����ͷſռ�)
char* pPrinterOfNewFileBuffer = NULL; // ���� ImageBuffer ָ��(���ڼ���)
							
DWORD sizeOfFile = 0; // �ļ���С(�ֽ�)
			
DWORD ReadPEFile(char* FilePathOfPe)
{
	/* 
		ReadPEFile -> ���ļ���ȡ��������( FileBuffer )��Ϊ����PE�ṹ��ָ�븳ֵ
		����˵����
		FilePath -> �ļ�·��
		����ֵ -> ��������쳣�򷵻�0�����򷵻ض�ȡ���ļ���С
	*/

	pfileStream = fopen(FilePathOfPe, "rb");  // ���ļ�
	if (pfileStream == NULL)
	{
		("�ļ���ʧ��");
		return 0;
	}
	fseek(pfileStream, 0, SEEK_END);  // �����ļ�ָ�뵽ĩβ
	sizeOfFile = (DWORD)ftell(pfileStream);  // ����ļ���ռ�ֽ���
	fseek(pfileStream, 0, SEEK_SET);  // �����ļ�ָ�뵽��ͷ
	pMemoryOfFileBuffer = malloc(sizeof(char) * sizeOfFile);  // �����ڴ����
	if (pMemoryOfFileBuffer == NULL)
	{
		printf("�ڴ�����ʧ��");
		return 0;
	}
	memset(pMemoryOfFileBuffer, 0x00000000, sizeof(char) * sizeOfFile);  // ��ʼ�� FileBuffer �ڴ��ֵΪ0
	DWORD sizeOfReadFile = fread(pMemoryOfFileBuffer, sizeof(char), sizeOfFile, pfileStream);  // ��ȡ�ļ����ѿռ�
	fclose(pfileStream); // �ر��ļ�
	if (sizeOfReadFile != sizeOfFile)  
	{
		// �����ȡ�ļ����ֽ�������ȷ
		printf("�ļ���ȡʧ��!"); 
		return 0;
	}

	// Ϊ����PE�ṹ��ָ�븳ֵ
	pPrinterOfFileBuffer = (char*)pMemoryOfFileBuffer; // �ļ�ͷ��ַ��ֵ�� char* ָ�� �����ҵ�PE��־

	pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)(pMemoryOfFileBuffer);  // ΪDOSͷ�ṹ��ָ�븳ֵ

	pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)(pPrinterOfFileBuffer + \
		(pIMAGE_DOS_HEADER -> e_lfanew + 4));// Ϊ��׼PEͷ�ṹ��ָ�븳ֵ

	pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)(pPrinterOfFileBuffer + \
	(pIMAGE_DOS_HEADER -> e_lfanew + 4 + 20)); // Ϊ��ѡPEͷ�ṹ��ָ�븳ֵ

	pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)(pPrinterOfFileBuffer + \
	(pIMAGE_DOS_HEADER -> e_lfanew + 4 + 20 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader));  // Ϊ�ڱ�ṹ��ָ�븳ֵ

	if (pIMAGE_DOS_HEADER -> e_magic != 0x5A4D)
	{
		printf("������Ч��DOS_MZ��־!"); 
		return 0;
	}
	
	if (*(int*)(pPrinterOfFileBuffer + pIMAGE_DOS_HEADER -> e_lfanew) != 0x00004550) // ��ͷ��ʼ��
	{
		printf("������Ч��PE��ʶ");
		return 0;
	}
	if (*(short int*)(pPrinterOfFileBuffer + pIMAGE_DOS_HEADER -> e_lfanew + 4 + 20) != 0x010B)
	{
		printf("��ʱ��֧�ַ�32λ�ĳ���");
		return 0;
	}
	return sizeOfReadFile;
}

DWORD CopyFileBufferToImageBuffer(char* pFileBuffer)
{
	/*
		CopyFileBufferToImageBuffer -> ���ļ��� FileBuffer ���Ƶ� ImageBuffe
		����˵����
		pPrinterOfFileBuffer -> FileBuffer��ָ��
		����ֵ -> ��ȡʧ�ܷ���0  ���򷵻ظ��Ƶ��ֽ������ܴ�С		
	*/
	BYTE SizeOfReturnNumbers = 0;
	pMemoryOfImageBuffer = malloc(pIMAGE_OPTIONAL_HEADER32 -> SizeOfImage * sizeof(char));
	if (pMemoryOfImageBuffer == NULL)
	{
		// ��ȡʧ��
		printf("��ȡʧ��");
		return 0;
	}
	memset(pMemoryOfImageBuffer, 0x00000000, \
		pIMAGE_OPTIONAL_HEADER32 -> SizeOfImage * sizeof(char));  // ��ʼ�� ImageBuffe �ڴ��ֵΪ0
	pPrinterOfImageBuffer = (char*)pMemoryOfImageBuffer;
	// ���ȸ���SizeOfHeaders�Ĵ�С (����ͷ + �ڱ� �����ļ������Ĵ�С)
	memcpy((BYTE*)pMemoryOfImageBuffer, (BYTE*)pFileBuffer, \
		sizeof(char) * pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);
	SizeOfReturnNumbers += sizeof(char) * pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders;

	// ��ȡ�ڵ�����
	// ѭ����ȡÿ���ڵ� PointToRawData �� VirtualAddress ��ֵ
	// ѭ������ memcpy �������ڴ�
	int NumberOfSum = 0;
	for (int i = 0; i < pIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		memcpy((BYTE*)(pPrinterOfImageBuffer + pIMAGE_SECTION_HEADER -> VirtualAddress), \
			(BYTE*)(pFileBuffer + pIMAGE_SECTION_HEADER -> PointerToRawData), \
			sizeof(char) * pIMAGE_SECTION_HEADER -> SizeOfRawData);
		SizeOfReturnNumbers += sizeof(char) * pIMAGE_SECTION_HEADER -> SizeOfRawData;
		pIMAGE_SECTION_HEADER++;
		NumberOfSum++;
	}
	pIMAGE_SECTION_HEADER -= NumberOfSum;  // ���ڱ�ṹ��ָ���λ
	return SizeOfReturnNumbers;
}

DWORD CopyImageBufferToNewBuffer(char* pPrinterOfNewFileBuffer)
{
	// �� ImageBuffer ��ԭΪ NewFileBuffer
	// ��Ҫ ImageBuffer ָ��
	// ��Ҫ NewFileBuffer ָ��
	// ��Ҫ��ȡ ImageBuffer �Ĵ�С
	BYTE SizeOfReturnNumbers = 0;
	pMemoryOfNewFileBuffer = malloc(sizeof(char) * sizeOfFile);  // ���ٺ��ļ���С��ͬ�Ŀռ�
	if (pMemoryOfNewFileBuffer == NULL)
	{
		return 0;
	}
	memset(pMemoryOfNewFileBuffer, 0x00000000, sizeof(char) * sizeOfFile);  // ��ʼ�� ImageBuffe �ڴ��ֵΪ0
	pPrinterOfNewFileBuffer = (char*)pMemoryOfNewFileBuffer;
	// ������ͷ�ӽڱ��ļ������Ĵ�С���и���
	memcpy((BYTE*)pMemoryOfNewFileBuffer, (BYTE*)pPrinterOfImageBuffer, \
		(DWORD)(sizeof(char) * pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders));
	// ��ʼ���ƽ�

	int NumberOfSum = 0;
	for (int i = 0; i < pIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		memcpy((BYTE*)(pPrinterOfNewFileBuffer + pIMAGE_SECTION_HEADER -> PointerToRawData), \
			(BYTE*)(pPrinterOfImageBuffer + pIMAGE_SECTION_HEADER -> VirtualAddress), \
			sizeof(char) * pIMAGE_SECTION_HEADER -> SizeOfRawData);
		SizeOfReturnNumbers += sizeof(char) * pIMAGE_SECTION_HEADER -> SizeOfRawData;
		pIMAGE_SECTION_HEADER++;
		NumberOfSum++;
	}
	pIMAGE_SECTION_HEADER -= NumberOfSum;  // ���ڱ�ṹ��ָ���λ
	return SizeOfReturnNumbers;
}

void MemeryTOFile()
{
	pNewfileStream = fopen("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\NewNotepad.exe", "wb");
	// ����: ֱ�Ӵ����ļ�
	fwrite(pMemoryOfNewFileBuffer, sizeof(char), sizeof(char) * sizeOfFile, pNewfileStream);
	fclose(pNewfileStream);
}

DWORD RvaToFileOffset(char* pFileBuffer,char* dwRva)
{
	// RVAתFOA�ĺ���  dwRva: �ڴ��е�ƫ�� pFileBuffer�ļ��е�ƫ��

	// ����ַתΪDWORD���ͺ��ȥ�׵�ַ �õ�ƫ�Ƶ�ַ
	DWORD ResultOfRVA = (DWORD)dwRva;
	DWORD ResultOfImageBuffer = (DWORD)pPrinterOfImageBuffer;
	DWORD offsetRVA = ResultOfRVA - ResultOfImageBuffer; // ƫ�Ƶ�ַ
	int Sum = 0; // ����ֵ��ʾ offsetRVA ���ĸ���-1��
	// ���Ͻ��д�С�Ƚ�,�����ֵ���ĸ�����
	for (int i = 0; i < pIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		if (pIMAGE_SECTION_HEADER -> VirtualAddress	> offsetRVA && \
			++pIMAGE_SECTION_HEADER -> VirtualAddress < offsetRVA)
		{
			Sum = i + 1;
			break;
		}
		if (i + 1 == pIMAGE_FILE_HEADER -> NumberOfSections)
		{
			Sum = i + 1;
			break;
		}
	}
	pIMAGE_SECTION_HEADER -= Sum; // ��λ�ڱ�ṹ��ָ��
	DWORD offsetFOA = (pIMAGE_SECTION_HEADER->PointerToRawData + Sum - 1) + offsetRVA;  // �õ�FOA

	return offsetFOA;
}

/*

��ϰ��	
						
1��ʵ�����¹���

�ļ� -> FileBuffer -> ImageBuffer -> NewBuffer -> ����
		
2����дһ���������ܹ���RVA��ֵת����FOA.(Relative Virtual Address -> File Ofseet Address)

*/	

int main(int argc, char* argv[])
{
	// ���ļ�����������
	int isAvailable = ReadPEFile("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\notepad.exe");
	if (!isAvailable)
	{
		return 0;
	}
	// ���ļ��� FileBuffer ���Ƶ� ImageBuffer

	CopyFileBufferToImageBuffer(pPrinterOfFileBuffer);
	
	// �� ImageBuffer ���Ƶ� NewBuffer
	CopyImageBufferToNewBuffer(pPrinterOfNewFileBuffer);

	// �� NewBuffer д���ļ�
	MemeryTOFile();

	// �ͷ�����Ķѿռ�
	free(pMemoryOfFileBuffer); // �ͷ� FileBuffer �ѿռ�
	free(pMemoryOfImageBuffer); // �ͷ� ImageBuffer �ѿռ�
	free(pMemoryOfNewFileBuffer); // �ͷ� NewFileBuffer �ѿռ�

	// ��ʣ��ָ���ֵ��ΪNULL
	
	pfileStream = NULL; // �ļ��ܵ�ָ�� -> 0
	pNewfileStream = NULL; //���ļ��ܵ�ָ�� -> 0


	pMemoryOfFileBuffer = NULL; // void* ���͵� FileBuffer �ѿռ��ڴ�ָ�� -> 0
	pPrinterOfFileBuffer = NULL; // �� pMemoryOfFileBuffer ��ֵ��char*���͵�ָ�� -> 0

	pMemoryOfImageBuffer = NULL; // void* ���͵� ImageBuffer �ѿռ��ڴ�ָ�� -> 0
	pPrinterOfImageBuffer = NULL; // �� pMemoryOfImageBuffer ��ֵ��char*���͵�ָ�� -> 0

	pMemoryOfNewFileBuffer = NULL; // void* ���͵� NewFileBuffer �ѿռ�ָ�� -> 0
	pPrinterOfNewFileBuffer = NULL; //�� pMemoryOfNewFileBuffer ��ֵ��char*���͵�ָ�� -> 0
	

	pIMAGE_DOS_HEADER = NULL;  // DOSͷ�ṹ��ָ�� -> 0
	pIMAGE_FILE_HEADER = NULL;  // ��׼PEͷ�ṹ��ָ�� -> 0
	pIMAGE_OPTIONAL_HEADER32 = NULL;  // ��ѡPEͷ�ṹ��ָ�� -> 0
	pIMAGE_SECTION_HEADER = NULL; // �ڱ�ṹ��ָ�� -> 0

	system("pause");
	return 0;
}