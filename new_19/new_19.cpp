#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct _IMAGE_DOS_HEADER 
{      // DOS .EXE header
    WORD   e_magic;                     // Magic number
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    WORD   e_lfanew;                    // File address of new exe header
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

/*

��ϰ��							
							
1����д�����ӡ�ڱ��е���Ϣ.				  	
							
2�����ݽڱ��е���Ϣ�����ļ����ҵ����еĽڣ��۲�ڵĿ�ʼλ�����С�Ƿ�							
��ڱ��е�����һ��(ʹ��notepad.exe����ϰ).							

*/

int PrintOfPeHeaders(char* filePath)
{
	IMAGE_DOS_HEADER* pIMAGE_DOS_HEADER;  // ����dosͷָ�� ***
	IMAGE_FILE_HEADER* pIMAGE_FILE_HEADER;  // ������׼PEͷָ�� ***
	IMAGE_OPTIONAL_HEADER32* pIMAGE_OPTIONAL_HEADER32;  // ������ѡPEͷָ�� ***
	IMAGE_SECTION_HEADER* pIMAGE_SECTION_HEADER; // �����ڱ�ָ�� *** 

	_iobuf* pfileStream = fopen(filePath, "rb");  // ���ļ� ***
	if (pfileStream == NULL)
	{
		printf("�ļ���ʧ��");
		return NULL;
	}
	fseek(pfileStream, 0, SEEK_END);  // �����ļ�ָ�뵽ĩβ
	DWORD sizeOfFile = (DWORD)ftell(pfileStream);  // ����ļ���ռ�ֽ���
	fseek(pfileStream, 0, SEEK_SET);  // �����ļ�ָ�뵽��ͷ
	void* pMemory = malloc(sizeof(char)*sizeOfFile);  // �����ڴ���� ***
	if (pMemory == NULL)
	{
		printf("�ڴ�����ʧ��");
		return NULL;
	}
	DWORD sizeOfReadFile = fread(pMemory, sizeof(char), sizeOfFile, pfileStream);  // ��ȡ�ļ����ѿռ�
	fclose(pfileStream); // �ر��ļ�
	pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pMemory;  // �ҵ�DOSͷ 64���ֽ� @@@
	if (sizeOfReadFile != sizeOfFile)  
	{
		// �����ȡ�ļ����ֽ�������ȷ
		printf("�ļ���ȡʧ��!"); 
		return NULL;
	}
	if (pIMAGE_DOS_HEADER -> e_magic != 0x5A4D)
	{
		printf("������Ч��DOS_MZ��־!"); 
		return NULL;
	}
	char* pPrinterOfPE = (char*)pMemory; // �ļ�ͷ��ַ��ֵ��char*ָ�� �����ҵ�PE��־ ***
	if(*(int*)(pPrinterOfPE + pIMAGE_DOS_HEADER -> e_lfanew) != 0x00004550) // ��ͷ��ʼ��
	{
		printf("������Ч��PE��ʶ");
		return NULL;
	}
	pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)\
		(pPrinterOfPE + (pIMAGE_DOS_HEADER -> e_lfanew) + 4);  // �ҵ���׼PEͷ 20���ֽ� ��ֵ @@@ 
	
	pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)\
		(pPrinterOfPE + (pIMAGE_DOS_HEADER -> e_lfanew) + 4 + 20); // �ҵ���չPEͷ x86 Լ224���ֽ� ��ֵ @@@
		
	pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)\
		(pPrinterOfPE + (pIMAGE_DOS_HEADER -> e_lfanew) \
		+ 4 + 20 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);// �ҵ��ڱ� ÿ���ڱ�40���ֽ�  ��ֵ @@@

	/* -------------------------------  ���ڱ�ĳ�Ա��Ϣ��ӡ����  ------------------------------- */
	// ͬ�ڲ��Ե��ļ�·��: C:\\Windows\\System32\\notepad.exe
	
	BYTE NameArr[9];  // ������������ȷ��ӡ�ڱ��г�ԱName��ֵ (8���ֽ�)
	NameArr[8] = 0x00;  // �����һ��ֵ��ֵΪ0����printf��������%s��ӡ
	for (int i = 0; i < pIMAGE_FILE_HEADER -> NumberOfSections; i++)  // NumberOfSections ָ�����ж��ٸ���
	{
		for (int j = 0; j < 8; j++)
		{
			NameArr[j] = pIMAGE_SECTION_HEADER -> Name[j];  // ΪNameArr���鸳ֵ
		}
		printf("\n��%d���ڵ���Ϣ:\n", i + 1);
		printf("Name��ֵ��: %s\n", NameArr);
		printf("MISC��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> Misc);
		printf("VirtualAddress��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> VirtualAddress);
		printf("SizeOfRawData��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> SizeOfRawData);
		printf("PointerToRawData��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> PointerToRawData);
		printf("PointerToRelocations��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> PointerToRelocations);
		printf("PointerToLinenumbers��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> PointerToLinenumbers);
		printf("NumberOfRelocations��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> NumberOfRelocations);
		printf("NumberOfLinenumbers��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> NumberOfLinenumbers);
		printf("Characteristics��ֵ��: %x\n", pIMAGE_SECTION_HEADER -> Characteristics);

		pIMAGE_SECTION_HEADER++; // ���������ṹ�� �ҵ���һ���ṹ��
	}
	printf("\n");
	free(pMemory); // �ͷŶѿռ�
	// ��ʼ��ȫ��ָ��
	pMemory = NULL; // void*���͵Ķѿռ��ڴ�ָ�� -> 0
	pPrinterOfPE = NULL; // ��pMemory��ֵ��char*���͵�ָ�� -> 0
	pfileStream = NULL; // �ļ��ܵ�ָ�� -> 0
	pIMAGE_DOS_HEADER = NULL;  // DOSͷ�ṹ��ָ�� -> 0
	pIMAGE_FILE_HEADER = NULL;  // ��׼PEͷ�ṹ��ָ�� -> 0
	pIMAGE_OPTIONAL_HEADER32 = NULL;  // ��ѡPEͷ�ṹ��ָ�� -> 0
	pIMAGE_SECTION_HEADER = NULL; // �ڱ�ָ�� -> 0

	return 0;
}

int main(int argc, char* argv[])
{
	// ������е�PEͷ��Ϣ
	printf("�������ļ�·��: ( ��: C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\notepad.exe )\n");
	char PathOfValue[200]; 
	scanf("%s", PathOfValue);
	char* result = PathOfValue;
	PrintOfPeHeaders(result);
	system("pause");
	return 0;
}