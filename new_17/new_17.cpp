/*
������ϰ��
1���ҳ�����DOSͷ���ݣ���ͳ��DOSͷ��С.
2���ҳ����б�׼PEͷ���ݣ���ͳ�Ʊ�׼PEͷ��С.
3���ҳ����п�ѡPEͷ���ݣ���ͳ�ƿ�ѡPEͷ��С.
4������������Ҫ�ĳ�Ա���ĸ��ṹ����
*/

#include "stdafx.h"

/*
 ��ϰ��ʹ�õ�.exe�ļ�·��:   
"D:\study\C_X86\HD\���\6(��־�Ĵ���)\2015-01-19\CRACKME.EXE"
*/

/*
// DOSͷ
typedef struct _IMAGE_DOS_HEADER {      
    WORD   e_magic;						*		//	5A 4D
    WORD   e_cblp;								//	00 50
    WORD   e_cp;								//	00 02
    WORD   e_crlc;								//	00 00
    WORD   e_cparhdr;							//	00 04
    WORD   e_minalloc;							//	00 0F
    WORD   e_maxalloc;							//	FF FF
    WORD   e_ss;								//	00 00
    WORD   e_sp;								//	00 B8
    WORD   e_csum;								//	00 00
    WORD   e_ip;								//  00 00
    WORD   e_cs;								//	00 00
    WORD   e_lfarlc;							//	00 40
    WORD   e_ovno;								//  00 1A
    WORD   e_res[4];							//	00 00 00 00 00 00 00 00
    WORD   e_oemid;								//	00 00
    WORD   e_oeminfo;							//	00 00
    WORD   e_res2[10];							//	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    LONG   e_lfanew;					*		//	00 00 01 00
  } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;		//

DOSͷ��С: 64 ���ֽ�

// NTͷ
typedef struct _IMAGE_NT_HEADERS {
    DWORD Signature;					*		//	00 00 45 50
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

// ��׼PEͷ
typedef struct _IMAGE_FILE_HEADER {
    WORD    Machine;					*		//	01 4C
    WORD    NumberOfSections;			*		//	00 06
    DWORD   TimeDateStamp;				*		//	0A D9 24 29
    DWORD   PointerToSymbolTable;				//	00 00 00 00
    DWORD   NumberOfSymbols;					//	00 00 00 00
    WORD    SizeOfOptionalHeader;		*		//	00 E0
    WORD    Characteristics;			*		//	81 8E
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

��׼PEͷ��С: 20 ���ֽ�

// ��ѡPEͷ
typedef struct _IMAGE_OPTIONAL_HEADER {
    //
    // Standard fields.
    //

    WORD    Magic;						*		//	01 0B
    BYTE    MajorLinkerVersion;					//	02
    BYTE    MinorLinkerVersion;					//	19
    DWORD   SizeOfCode;					*		//	00 00 06 00
    DWORD   SizeOfInitializedData;		*		//	00 00 22 00
    DWORD   SizeOfUninitializedData;	*		//	00 00 00 00
    DWORD   AddressOfEntryPoint;		*		//	00 00 10 00
    DWORD   BaseOfCode;					*		//	00 00 10 00
    DWORD   BaseOfData;					*		//	00 00 20 00

    //
    // NT additional fields.
    //

    DWORD   ImageBase;					*		//	00 40 00 00
    DWORD   SectionAlignment;			*		//	00 00 10 00
    DWORD   FileAlignment;				*		//	00 00 02 00
    WORD    MajorOperatingSystemVersion;		//	00 01
    WORD    MinorOperatingSystemVersion;		//	00 00
    WORD    MajorImageVersion;					//	00 00
    WORD    MinorImageVersion;					//	00 00
    WORD    MajorSubsystemVersion;				//	00 03
    WORD    MinorSubsystemVersion;				//	00 0A
    DWORD   Win32VersionValue;					//	00 00 00 00
    DWORD   SizeOfImage;				*		//	00 00 80 00
    DWORD   SizeOfHeaders;				*		//	00 00 04 00
    DWORD   CheckSum;					*		//	00 00 00 00
    WORD    Subsystem;							//	00 02
    WORD    DllCharacteristics;					//	00 00
    DWORD   SizeOfStackReserve;			*		//	00 10 00 00
    DWORD   SizeOfStackCommit;			*		//	00 00 20 00
    DWORD   SizeOfHeapReserve;			*		//	00 10 00 00
    DWORD   SizeOfHeapCommit;			*		//	00 00 10 00
    DWORD   LoaderFlags;						//	00 00 00 00
    DWORD   NumberOfRvaAndSizes;				//	00 00 00 10
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

��ѡPEͷ��С: 96 ���ֽ� + 128���ֽ� �ܹ�224���ֽ�

*/
int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}