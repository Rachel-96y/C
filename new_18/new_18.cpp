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

/*

��ϰ��

1����д�����ȡһ��.exe�ļ���������е�PEͷ��Ϣ.

2��ʹ�õ�������PE���ߣ��Ա���Ϣ�����Ƿ�һ��

*/

int PrintOfPeHeaders(char* filePath)
{
	IMAGE_DOS_HEADER* pIMAGE_DOS_HEADER;  // dosͷ ***
	IMAGE_FILE_HEADER* pIMAGE_FILE_HEADER;  // ��׼PEͷ ***
	IMAGE_OPTIONAL_HEADER32* pIMAGE_OPTIONAL_HEADER32;  // ��ѡPEͷ ***

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
		(pPrinterOfPE + (pIMAGE_DOS_HEADER -> e_lfanew) + 4);  // �ҵ���׼PEͷ 20���ֽ�  @@@
	
	pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)\
		(pPrinterOfPE + (pIMAGE_DOS_HEADER -> e_lfanew) + 4 + 20); // �ҵ���չPEͷ x86Լ224���ֽ� @@@
	
	/* -------------------------------  ���ؼ��ĳ�Ա��Ϣ��ӡ����  ------------------------------- */
	// DOS ͷ
	printf("************************* DOS MZ ��ʶ ********************************\n");
	printf("%x\n", pIMAGE_DOS_HEADER -> e_magic);

	printf("************************* PE ƫ�� ********************************\n");
	printf("%x\n", pIMAGE_DOS_HEADER -> e_lfanew);
	// -------------------------------------------------------------------------------------
	/* NT ͷ */

	// PE ��ʶ
	printf("************************* PE ��ʶ ********************************\n");
	printf("%x\n", *(int*)(pPrinterOfPE + pIMAGE_DOS_HEADER -> e_lfanew));

	// ��׼ PE ͷ
	printf("************************* �������е�CPU�ͺ� ********************************\n");
	printf("%x\n", pIMAGE_FILE_HEADER -> Machine);

	printf("************************* �ļ��д��ڵĽ����� ********************************\n");
	printf("%x\n", pIMAGE_FILE_HEADER -> NumberOfSections);

	printf("************************* ʱ��� ********************************\n");
	printf("%x\n", pIMAGE_FILE_HEADER -> TimeDateStamp);

	printf("************************* ��ѡPEͷ��С ********************************\n");
	printf("%x\n", pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	printf("************************* �������� ********************************\n");
	printf("%x\n", pIMAGE_FILE_HEADER -> Characteristics);

	// ��ѡ PE ͷ
	printf("************************* ˵���ļ�����(10B:32λ�µ�PE�ļ�|20B:64λ�µ�PE�ļ�) ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> Magic);

	printf("************************* ���д���ڵĺ� ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfCode);

	printf("************************* �ѳ�ʼ�������С�ĺ� ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfInitializedData);

	printf("************************* δ��ʼ�������С�ĺ� ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfUninitializedData);

	printf("************************* ������ڵ��ַ ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> AddressOfEntryPoint);

	printf("************************* ���뿪ʼ�Ļ�ַ ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> BaseOfCode);

	printf("************************* ���ݿ�ʼ�Ļ�ַ ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> BaseOfData);

	printf("************************* �ڴ澵���ַ ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> ImageBase);

	printf("************************* �ڴ����(�ڶ���) ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SectionAlignment);

	printf("************************* �ļ�����(�ڶ���) ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> FileAlignment);

	printf("************************* �ڴ�������PE��ӳ���С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfImage);

	printf("************************* ����ͷ�ӽڱ����ļ������Ĵ�С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);

	printf("************************* У��� ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> CheckSum);

	printf("************************* ��ʼ��ʱ������ջ��С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfStackReserve);

	printf("************************* ��ʼ��ʱʵ���ύ��ջ��С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfStackCommit);

	printf("************************* ��ʼ��ʱ�����ĶѴ�С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeapReserve);

	printf("************************* ��ʼ��ʱʵ���ύ�ĶѴ�С ********************************\n");
	printf("%x\n", pIMAGE_OPTIONAL_HEADER32 -> SizeOfHeapCommit);

	free(pMemory); // �ͷŶѿռ�

	// ��ʼ��ȫ��ָ��
	pMemory = NULL; // �ѿռ��ڴ�ָ�� -> 0
	pPrinterOfPE = NULL; // ��pMemory��ֵ��char*���͵�ָ�� -> 0
	pfileStream = NULL; // �ļ��ܵ�ָ�� -> 0
	pIMAGE_DOS_HEADER = NULL;  // DOSͷ�ṹ��ָ�� -> 0
	pIMAGE_FILE_HEADER = NULL;  // ��׼PEͷ�ṹ��ָ�� -> 0
	pIMAGE_OPTIONAL_HEADER32 = NULL;  // ��ѡPEͷ�ṹ��ָ�� -> 0

	return 0;
}

int main(int argc, char* argv[])
{
	// ������е�PEͷ��Ϣ
	printf("�������ļ�·��: (��: C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\notepad.exe)\n");
	char PathOfValue[200]; 
	scanf("%s", PathOfValue);
	char* result = PathOfValue;
	PrintOfPeHeaders(result);
	system("pause");
	return 0;
}