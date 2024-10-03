// A_TEST_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


VOID TestPrintPeFormat(IN LPVOID pMemory, IN UINT Size)
{
	/* 
		�˺������ڴ�ӡPE�ļ������� 
		��ʮ�����Ƶĸ�ʽ��ʾ
		��Ҫ���� Size ��ʾ�Ĵ�С �� pMemory ָ��
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pMemory;

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
		return;
	}

	// �ж�PE��ʶ�Ƿ���Ч
	if (*(PDWORD)((DWORD)pPIMAGE_DOS_HEADER + pPIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ļ�: �����PE��־");
		return;
	}

	for (unsigned int i = 0; i < Size; i++)
	{

		if (i != 0 && i % 0x10 == 0)
		{
			printf("\n");
		}

		switch(*((char*)pMemory + i))
		{
			case 0x00:
				printf("00    ");
				break;
			case 0x01:
				printf("01    ");
				break;
			case 0x02:
				printf("02    ");
				break;
			case 0x03:
				printf("03    ");
				break;
			case 0x04:
				printf("04    ");
				break;
			case 0x05:
				printf("05    ");
				break;
			case 0x06:
				printf("06    ");
				break;
			case 0x07:
				printf("07    ");
				break;
			case 0x08:
				printf("08    ");
				break;
			case 0x09:
				printf("09    ");
				break;
			case 0x0A:
				printf("0a    ");
				break;
			case 0x0B:
				printf("0b    ");
				break;
			case 0x0C:
				printf("0c    ");
				break;
			case 0x0D:
				printf("0d    ");
				break;
			case 0x0E:
				printf("0e    ");
				break;
			case 0x0F:
				printf("0f    ");
				break;
			default:
				printf("%x    ", (unsigned char)*((char*)pMemory + i));
		}
	}
	
}


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


DWORD SizeOfNewDll(IN LPVOID pFileBuffer)
{
	/* ���������ɵ�DLL��Ҫ���ٿռ� */

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
	
	// ������� FileBuffer �е������ʵ��ƫ�Ƶ�ַ(FOA) ���� FileBuffer ��ֵ ��ֵ��������ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);
	
	// ������ض�λ��� FOA ������ pFileBuffer ��ֵ ��ֵ���ض�λ��ṹ��ָ��
	PIMAGE_BASE_RELOCATION pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)(ChangeRvaToFoa((pPIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);
	
	// �ȼ��㵼������������ݵĴ�С
	// ��������� SizeOf_IMAGE_EXPORT_DIRECTORY ��
	// ȫ��������ռ���ֽ��� �ȴ���� NumberOfAllNames ��
	DWORD NumberOfAllNames = 0;
	for (UINT i = 0; i < pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames; i++)
	{
		// ����� AddressOfNames ���е�ƫ�Ƶ�ַ ��Ҫ���� pFileBuffer
		LPDWORD TEMP_NUMBER = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pFileBuffer) + i * 4 + (DWORD)pFileBuffer);

		// �������Щƫ�Ƶ�ַ�е�ֵ�� Rva + pFileBuffer �õ���ֵ ������ת��Ϊ LPCSTR ���� ʹ�� strlen �������ַ�е��ַ�������
		NumberOfAllNames += strlen((LPCSTR)(ChangeRvaToFoa(*TEMP_NUMBER, pFileBuffer) + (DWORD)pFileBuffer));
	}

	// ������ SizeOf_IMAGE_EXPORT_DIRECTORY ���ܴ�С = AddressOfFunctions + AddressOfNames + AddressOfNameOrdinals + IMAGE_EXPORT_DIRECTORY + NumberOfAllNames
	DWORD SizeOf_IMAGE_EXPORT_DIRECTORY = pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions * sizeof(UINT) + pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames * sizeof(UINT) + \
	pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames * sizeof(USHORT) + sizeof(IMAGE_EXPORT_DIRECTORY) + NumberOfAllNames;
	
	// �ټ����ض�λ����������ݵĴ�С
	// ��������� SizeOf_IMAGE_BASE_RELOCATION ��
	DWORD SizeOf_IMAGE_BASE_RELOCATION = 0;

	// �ж��Ƿ��һ������ֵ
	if (!(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress))
		// ����ض�λ��û��ֵ�� ������ռ�õĴ�С������Ҫ����Ŀռ���ܴ�С
		return SizeOf_IMAGE_EXPORT_DIRECTORY;

	// �ض�λ����ܴ�С = ÿ����Ĵ�С���
	do
	{
		// ��� VirtualAddress ���� SizeOfBlock ��ֵΪ0 ���ض�λ�����
		 SizeOf_IMAGE_BASE_RELOCATION += pPIMAGE_BASE_RELOCATION -> SizeOfBlock;

		// ����һ�����ȫ����ַ ע�����ﲻ��Ҫ�� IMAGE_SIZEOF_BASE_RELOCATION
		pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pPIMAGE_BASE_RELOCATION + pPIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}
	while(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress);

	// �ܴ�С = SizeOf_IMAGE_EXPORT_DIRECTORY + SizeOf_IMAGE_BASE_RELOCATION
	return SizeOf_IMAGE_EXPORT_DIRECTORY + SizeOf_IMAGE_BASE_RELOCATION;
}


LPVOID CopyFileBufferToNewFileBuffer(IN LPVOID pFileBuffer, IN UINT SizeOfNewFileBuffer, IN UINT SizeOfOldFileBuffer)
{
	/* ����ռ䲢�������� */

	// SizeOfNewFileBuffer ��Ϊ������Ҫ����Ŀռ��С (�����ں�Ĵ�С)
	LPVOID pNewFileBuffer = malloc(sizeof(CHAR) * SizeOfNewFileBuffer);
	if (pNewFileBuffer == NULL)
	{
		// �ռ�����ʧ����ֱ�ӷ���
		return NULL;
	}

	memset(pNewFileBuffer, 0x00000000, SizeOfNewFileBuffer);

	// �� pFileBuffer �����ݸ��Ƶ� pNewFileBuffer ��
	memcpy(pNewFileBuffer, pFileBuffer, sizeof(CHAR) * SizeOfOldFileBuffer);

	return pNewFileBuffer;
}


DWORD AddNewSection(IN LPVOID pNewFileBuffer, IN UINT SizeOfNewDll_FileAlignment, IN UINT SizeOfNewDll_ImageAlignment, IN UINT SizeOfOldFileBuffer)
{
	/* �˺�����������һ���ڲ��������� */

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

	// ����һ���ڱ� (��������������ж��Ƿ��пռ�����һ���ڱ� ����ʡ��)
	// �ҵ���Ҫ�����Ľڱ��λ��
	pPIMAGE_SECTION_HEADER += pPIMAGE_FILE_HEADER -> NumberOfSections;

	// ���Ĵ˽ڱ������

	// ������
	pPIMAGE_SECTION_HEADER -> Name[0] = '.';
	pPIMAGE_SECTION_HEADER -> Name[1] = 'M';
	pPIMAGE_SECTION_HEADER -> Name[2] = 'y';
	pPIMAGE_SECTION_HEADER -> Name[3] = 'C';
	pPIMAGE_SECTION_HEADER -> Name[4] = 'o';
	pPIMAGE_SECTION_HEADER -> Name[5] = 'd';
	pPIMAGE_SECTION_HEADER -> Name[6] = 'e';
	pPIMAGE_SECTION_HEADER -> Name[7] = '\0';


	// VirtualSize �Ĵ�С���������ĽڵĴ�С ���ֵ���Բ�׼ȷ
	pPIMAGE_SECTION_HEADER -> Misc.VirtualSize = SizeOfNewDll_FileAlignment;

	// NewVirtualAddress ���ڴ洢���յ� VirtualAddress ��ֵ
	DWORD NewVirtualAddress = 0;
	// ת����һ����
	pPIMAGE_SECTION_HEADER--;
	// VirtualAddress ����ʼλ���� ��һ���ڵ� VirtualAddress + ��һ���ڵ� Misc.VirtualSize �� SizeOfRawData �е����ֵ
	NewVirtualAddress = pPIMAGE_SECTION_HEADER -> VirtualAddress + \
		(pPIMAGE_SECTION_HEADER -> Misc.VirtualSize > pPIMAGE_SECTION_HEADER -> SizeOfRawData ? \
		pPIMAGE_SECTION_HEADER -> Misc.VirtualSize : pPIMAGE_SECTION_HEADER -> SizeOfRawData);
	// ת����ǰ��
	pPIMAGE_SECTION_HEADER++;
	// Ϊ��ǰ�ڵ� VirtualAddress ��ֵ
	pPIMAGE_SECTION_HEADER -> VirtualAddress = NewVirtualAddress;

	// SizeOfRawData �Ĵ�С���������ĽڵĴ�С Ҳ���� VirtualSize �Ĵ�С
	pPIMAGE_SECTION_HEADER -> SizeOfRawData = SizeOfNewDll_FileAlignment;

	// �����ڵ� PointerToRawData ����ʼλ�õ�����һ���ڵ� PointerToRawData + ��һ���ڵ� SizeOfRawData
	pPIMAGE_SECTION_HEADER--;
	DWORD TempPointerToRawData = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;
	pPIMAGE_SECTION_HEADER++;
	pPIMAGE_SECTION_HEADER -> PointerToRawData = TempPointerToRawData;

	// ���ڱ�ṹ��ָ������ָ���һ���� �������нڵ����� �������Ľڵ����Ը�Ϊ�����ڵ����Եĺ�
	pPIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pPIMAGE_OPTIONAL_HEADER32 + pPIMAGE_FILE_HEADER -> SizeOfOptionalHeader);
	DWORD AllSectionCharacters = 0;
	
	// ���Ľ�����
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++)
	{
		// �����нڵ����Դ洢�� AllSectionCharacter ��
		AllSectionCharacters |= pPIMAGE_SECTION_HEADER++ -> Characteristics;
	}
	// ���ڱ�ṹ��ָ��ָ�������ڲ���ֵ
	++pPIMAGE_SECTION_HEADER -> Characteristics = AllSectionCharacters;

	// ����׼ PE ͷ�� NumberOfSection ��ֵ��1
	pPIMAGE_FILE_HEADER -> NumberOfSections += 1;

	// ���Ŀ�ѡ PE ͷ�� SizeOfImage ��ֵ Ϊ�����Ľ��ڴ�����Ĵ�С + ������ SizeOfImage �Ĵ�С
	pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage += SizeOfNewDll_ImageAlignment;

	return pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage;
}


LPVOID ChangeDLL_IMAGE_EXPORT_DIRECTORY(IN LPVOID pNewFileBuffer)
{
	/* �˺��������ƶ��������������Ľ��ﲢ������λ���� */

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
	
	// ������� FileBuffer �е������ʵ��ƫ�Ƶ�ַ(FOA) ���� FileBuffer ��ֵ ��ֵ��������ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pNewFileBuffer) + (DWORD)pNewFileBuffer);
	

	// ------ �ƶ� AddressOfFunctions �����е�ַ���ֵ ------


	// �����ĽڵĿ�ʼλ�� FileBuffer ����ʼλ�� + ���һ���ڵ� PointerToRawData + ���һ���ڵ� SizeOfRawData

	// ת�������ڵĽڱ� ����� 1 ����Ϊ�Ѿ�������һ���� �˲����Ḳ�ǵ����һ�������ݺ��ֵ (��Ҫȷ����Щֵ��û�õ�)
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);

	LPVOID PointerToNewSection = (LPVOID)(pPIMAGE_SECTION_HEADER -> PointerToRawData + (DWORD)pNewFileBuffer);

	pPIMAGE_SECTION_HEADER -= pPIMAGE_FILE_HEADER -> NumberOfSections;

	// NewAddressOfFunctions �洢�µ� AddressOfFunctions ��ֵ FOA
	UINT NewAddressOfFunctions = (DWORD)PointerToNewSection - (DWORD)pNewFileBuffer;

	//  SizeOfFunctions Ҫ���ƵĴ�С�� NumberOfFunctions * 4
	UINT SizeOfFunctions = pPIMAGE_EXPORT_DIRECTORY -> NumberOfFunctions * sizeof(UINT);

	// �� AddressOfFunctions ����ʼλ�ø��Ƶ� PointerToNewSection ��λ��
	memcpy(PointerToNewSection, (LPVOID)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions, pNewFileBuffer) + (DWORD)pNewFileBuffer), SizeOfFunctions);
	
	// ���㵱ǰָ��λ�� (�Ѹ��� AddressOfFunctions)
	PointerToNewSection = (LPVOID)((DWORD)PointerToNewSection + SizeOfFunctions);


	// ------ �ƶ� AddressOfNames �����е�ַ���ֵ ------
	

	// NewAddressOfNames �洢�µ� AddressOfNames �Ŀ�ʼ��ַ FOA
	UINT NewAddressOfNames = (DWORD)PointerToNewSection - (DWORD)pNewFileBuffer;
	
	// SizeOfNames Ҫ���ƵĴ�С�� NumberOfNames * 4
	UINT SizeOfNames = pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames * sizeof(UINT);
	
	// ��ʼ�������� 
	memcpy(PointerToNewSection, (LPVOID)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pNewFileBuffer) + (DWORD)pNewFileBuffer), SizeOfNames);
	
	// ���㵱ǰָ��λ�� (�Ѹ��� AddressOfFunctions �� AddressOfNames)
	PointerToNewSection = (LPVOID)((DWORD)PointerToNewSection + SizeOfNames);


	// ------ �ƶ� AddressOfNameOrdinals �����е�ַ���ֵ ------


	// NewAddressOfNameOrdinals �洢�µ� AddressOfNameOrdinals �Ŀ�ʼ��ַ FOA
	UINT NewAddressOfNameOrdinals = (DWORD)PointerToNewSection - (DWORD)pNewFileBuffer;

	// SizeOfNameOrdinals Ҫ���ƵĴ�С�� NumberOfNames * 2
	UINT SizeOfNameOrdinals = pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames * sizeof(SHORT);
	
	// �������Ľ��еĿ�ʼλ����Ŀǰ�� PointerToNewSection
	memcpy(PointerToNewSection, (LPVOID)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals, pNewFileBuffer) + (DWORD)pNewFileBuffer), SizeOfNameOrdinals);
	
	// ���㵱ǰָ��λ�� (�Ѹ��� AddressOfFunctions �� AddressOfNames �� AddressOfNameOrdinals)
	PointerToNewSection = (LPVOID)((DWORD)PointerToNewSection + SizeOfNameOrdinals);


	// ------ �ƶ� AddressOfNames �����е�ַ���ֵ��ָ������� ------
	// ע�� �ƶ����ֵ�ʱ����Ҫÿ�ƶ�һ�� �����ֱ����


	// �õ� NewAddressOfFunctionNames ���ļ��еĵ�ַ FOA + pNewFileBuffer (�������е����ֱ���׵�ַ)
	DWORD NewAddressOfFunctionNames = NewAddressOfNames + (DWORD)pNewFileBuffer;

	// AddressOfNames ���׵�ַ (ԭ���ֱ���׵�ַ)
	LPDWORD AddressOfNamesFoa = (LPDWORD)(ChangeRvaToFoa(pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames, pNewFileBuffer) + (DWORD)pNewFileBuffer);

	for(UINT i = 0; i < pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames; i++)
	{
		// ���ָ��� = pPIMAGE_EXPORT_DIRECTORY -> NumberOfNames

		// ȡ�� NumberOfNames �е�ÿ��ֵ��תΪ FOA �� ���� pNewFileBuffer(����ַ) �õ��ַ�������ʼ��ַ
		LPSTR pNamesFoa = (LPSTR)(ChangeRvaToFoa(*(AddressOfNamesFoa + i), pNewFileBuffer) + (DWORD)pNewFileBuffer);

		// ��ȡ���ֳ��� ����ƫ��ָ��
		UINT NameLength = strlen(pNamesFoa);

		// �������ֵ���������
		strcpy((LPSTR)PointerToNewSection, (LPCSTR)pNamesFoa);

		// �ҵ���ǰָ��λ�� ��������ֵ��µ��׵�ַд�����ֵ�ַ�� ��ҪתΪRVA
		*(LPDWORD)NewAddressOfFunctionNames = ChangeFoaToRva((DWORD)PointerToNewSection - (DWORD)pNewFileBuffer, pNewFileBuffer);

		// ����һ�����ֵĳ���
		PointerToNewSection = LPVOID((DWORD)PointerToNewSection + NameLength + 1);

		// �����ֵ�ַ��ָ��ƫ��4�ֽڵĳ���
		NewAddressOfFunctionNames += sizeof(UINT);

	}


	// ------ �ƶ� ������ _IMAGE_EXPORT_DIRECTORY �����г�Ա ------
	// PointerToNewSection Ϊ��ǰָ�� (ָ�����һ������ĩβ)
	// �ҵ� _IMAGE_EXPORT_DIRECTORY ����ʼλ��Ϊ: pPIMAGE_EXPORT_DIRECTORY д�뵽 PointerToNewSection ��λ�� д 40 ���ֽڵĴ�С
	memcpy(PointerToNewSection, pPIMAGE_EXPORT_DIRECTORY, sizeof(_IMAGE_EXPORT_DIRECTORY));

	// ���� ָ�� _IMAGE_EXPORT_DIRECTORY ��ֵ (����Ŀ¼�е������ RVA ) ������Ϊ��һ�� pPIMAGE_DATA_DIRECTORY �ṹ
	pPIMAGE_DATA_DIRECTORY -> VirtualAddress = ChangeFoaToRva((DWORD)PointerToNewSection - (DWORD)pNewFileBuffer, pNewFileBuffer);

	// ���¸� pPIMAGE_EXPORT_DIRECTORY ��ֵ
	pPIMAGE_EXPORT_DIRECTORY = (IMAGE_EXPORT_DIRECTORY*)(ChangeRvaToFoa(pPIMAGE_DATA_DIRECTORY -> VirtualAddress, pNewFileBuffer) + (DWORD)pNewFileBuffer);

	// ����ָ�� ע�� NewAddressOfFunctions NewAddressOfNameOrdinals NewAddressOfNames ���ֵ��ҪתΪ RVA
	// AddressOfFunctions
	pPIMAGE_EXPORT_DIRECTORY -> AddressOfFunctions = ChangeFoaToRva(NewAddressOfFunctions, pNewFileBuffer);

	// AddressOfNames
	pPIMAGE_EXPORT_DIRECTORY -> AddressOfNames = ChangeFoaToRva(NewAddressOfNames, pNewFileBuffer);

	// AddressOfNameOrdinals
	pPIMAGE_EXPORT_DIRECTORY -> AddressOfNameOrdinals = ChangeFoaToRva(NewAddressOfNameOrdinals, pNewFileBuffer);

	// ���㵱ǰָ��λ�� ������ (�Ѽ����� pNewFileBuffer )
	PointerToNewSection = LPVOID((DWORD)PointerToNewSection + sizeof(_IMAGE_EXPORT_DIRECTORY));

	return PointerToNewSection;
}


VOID ChangeDll_IMAGE_BASE_RELOCATION(IN LPVOID pNewFileBuffer, IN LPVOID PointerToNewSection)
{
	/* �˺��������ƶ��ض�λ���������� */
	
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

	// �����ض�λ����ܴ�С �����д�� SizeOf_IMAGE_BASE_RELOCATION ��
	UINT SizeOf_IMAGE_BASE_RELOCATION = 0;

	// ��Ҫ�� pNEW_PIMAGE_BASE_RELOCATION ��ʼ��ȡ д�뵽 PointerToNewSection ��λ��
	LPVOID pNEW_PIMAGE_BASE_RELOCATION = (LPVOID)pPIMAGE_BASE_RELOCATION;

	// �ж��Ƿ��һ������ֵ
	if (!(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress))
		// ����ض�λ��û��ֵ�� �ܴ�СΪ 0
		SizeOf_IMAGE_BASE_RELOCATION = 0;

	// �ض�λ����ܴ�С = ÿ����Ĵ�С���
	do
	{
		// ��� VirtualAddress ���� SizeOfBlock ��ֵΪ0 ���ض�λ�����
		 SizeOf_IMAGE_BASE_RELOCATION += pPIMAGE_BASE_RELOCATION -> SizeOfBlock;

		// ����һ�����ȫ����ַ ע�����ﲻ��Ҫ�� IMAGE_SIZEOF_BASE_RELOCATION
		pPIMAGE_BASE_RELOCATION = (IMAGE_BASE_RELOCATION*)((DWORD)pPIMAGE_BASE_RELOCATION + pPIMAGE_BASE_RELOCATION -> SizeOfBlock);
	}
	while(pPIMAGE_BASE_RELOCATION -> SizeOfBlock && pPIMAGE_BASE_RELOCATION -> VirtualAddress);

	// �ƶ��ض�λ�� PointerToNewSection
	memcpy(PointerToNewSection, pNEW_PIMAGE_BASE_RELOCATION, SizeOf_IMAGE_BASE_RELOCATION);

	// ���� ָ�� _IMAGE_BASE_RELOCATION ��ֵ (����Ŀ¼�е������ RVA ) 
	(pPIMAGE_DATA_DIRECTORY + 5) -> VirtualAddress = ChangeFoaToRva((DWORD)PointerToNewSection - (DWORD)pNewFileBuffer, pNewFileBuffer);

	return;
}


int main(int argc, char* argv[])
{
	/*
		������ϰ��
		1����DLL����һ���ڣ�������������Ϣ�ƶ�������µĽ���.
		2��ʹ�ù��ߴ��޸ĺ��DLL ���ܷ���������.
		3����DLL������һ���ڣ������ض�λ���ƶ�������µĽ���.
		4���޸�DLL��ImageBase,�����ض�λ��������Ȼ�����.��DLL�Ƿ����ʹ��.(д������һ����Ŀ��)
	*/


	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SIZE_OF_FILE_BUFFER = ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ���㽫Ҫ���ɵ�DLL��Ҫ���Ӷ����ֽ�
	DWORD SIZE_OF_NEW_DLL = SizeOfNewDll(pFileBuffer);

	// ���������Ľڶ������Ҫ���ٿռ� (�ļ�����/�ڴ����)
	DWORD SizeOfNewDll_FileAlignment = MyAlignment(pFileBuffer, 0, SIZE_OF_NEW_DLL);
	DWORD SizeOfNewDll_ImageAlignment = MyAlignment(pFileBuffer, 1, SIZE_OF_NEW_DLL);

	// SizeOfNewDll_FileAlignment Ϊ������Ҫ����Ŀռ��С (�������ض�λ���ļ������Ĵ�СҲ���������ں�Ĵ�С)
	DWORD SIZE_OF_ALL_FILE_BUFFER = SizeOfNewDll_FileAlignment + SIZE_OF_FILE_BUFFER;

	// ����ռ䲢�������� �ܹ�����Ҫ����Ĵ�С��: ԭʼ���ļ���С + �����������ļ������Ĵ�С ����ֵ�� NewFileBuffer ��ָ��
	LPVOID pNewFileBuffer = CopyFileBufferToNewFileBuffer(pFileBuffer, SIZE_OF_ALL_FILE_BUFFER, SIZE_OF_FILE_BUFFER);
	
	// �����ڲ�У׼����
	DWORD SizeOfNewImageBuffer = AddNewSection(pNewFileBuffer, SizeOfNewDll_FileAlignment, SizeOfNewDll_ImageAlignment, SIZE_OF_FILE_BUFFER);

	// �ƶ�������У׼����
	LPVOID PointerToNewSection = ChangeDLL_IMAGE_EXPORT_DIRECTORY(pNewFileBuffer);

	// �ƶ��ض�λ��У׼����
	ChangeDll_IMAGE_BASE_RELOCATION(pNewFileBuffer, PointerToNewSection);

	// ����
	WriteMemeryToFile(pNewFileBuffer, SIZE_OF_ALL_FILE_BUFFER, NEW_PATH);


	// ----------------------------------------------------
	// ����DLL�Ƿ��������ʹ��
	TestDll();  // NEW_PATH
	// ----------------------------------------------------
	
	getchar();


	return 0;
}