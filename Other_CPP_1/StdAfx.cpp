// stdafx.cpp : source file that includes just the standard includes
//	Other_CPP_1.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// *******************************************************************************
//���ļ� �������ڴ�
//����OUT LPVOID* pFileBuffer ����LPVOID���͵� pFileBufferָ��
//����ֵΪ  ����ĳ���
DWORD CreateFileBuffer(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer) 
{
	FILE* pfile = 0;
	DWORD filesize = 0;
	LPVOID FileBuffer = 0;
	pfile = fopen(lpszFile, "rb");
	if (!pfile) {
		printf("�ļ���ʧ��!!");
		return 0;
	}

	//ָ��ָ��pfile�ļ�β��;
	fseek(pfile, 0, SEEK_END);
	//ȡ������

	filesize = ftell(pfile);

	//����ָ�� ָ��pfile�ļ�ͷ��
	fseek(pfile, 0, SEEK_SET);
	
	//�����ڴ� ���ж��Ƿ�ɹ�
	FileBuffer = malloc(filesize);
	if (!FileBuffer) {
		printf("�ڴ�����ʧ��!!");
		fclose(pfile);
		pfile = NULL;
		return 0;
	}

	memset(FileBuffer, 0, filesize);

	//�����ļ��� �ж�
	DWORD x = fread(FileBuffer, sizeof(CHAR), filesize, pfile);
	if (!x) {
		printf("�ļ�������pFileBufferʧ��!!");
		fclose(pfile);
		free(FileBuffer);
		return NULL;
	}

	//�ж��Ƿ����MZ���!!
	if (*((WORD*)FileBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		fclose(pfile);
		free(FileBuffer);
		return 0;
	}

	*pFileBuffer = FileBuffer;
	fclose(pfile);
	return filesize;
 }


// *******************************************************************************
//��FileBuffer��������������ImageBuffer
//����1 ���� FileBuffer �׵�ַָ��
//����2 ���� ImageBuffer �׵�ַָ��
//����ֵ ImageBuffer�ĳ���
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer) {

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

	//���� ImageBuffer ��Ҫ�����ڴ�ĳ���
	DWORD ffersize = pPIMAGE_OPTIONAL_HEADER32 -> SizeOfImage;

	//����ImageBuffer�ڴ� ���ж�
	LPVOID ImageBuffer = malloc(ffersize);
	if (!ImageBuffer) {
		printf("ImageBuffer�ڴ�����ʧ��!!\n");
		free(pFileBuffer);
		return 0;
	}

	//��ʼ������  ��������ͷ
	memset(ImageBuffer, 0, ffersize);
	memcpy(ImageBuffer, pFileBuffer, pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);

	//��ֵ�ڱ�ָ�� ѭ��������
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++) 
	{
		memcpy((LPVOID)((DWORD)ImageBuffer + pPIMAGE_SECTION_HEADER -> VirtualAddress), \
			(LPVOID)((DWORD)pFileBuffer + pPIMAGE_SECTION_HEADER -> PointerToRawData), \
			pPIMAGE_SECTION_HEADER -> SizeOfRawData);
		pPIMAGE_SECTION_HEADER++;
	}

	// �� pImageBuffer ָ�븳ֵ
	*pImageBuffer = ImageBuffer;

	return ffersize;
 }


// *******************************************************************************
//ImageBuffer�������ݰ��ļ���ʽ������NewBuffer
//����1 ����ImageBuffer�׵�ַָ��
//����2 ����NewBuffer�׵�ַָ��
//����ֵ NewBuffer�ĳ���
DWORD ImageBufferToNewBuffer(IN LPVOID ImageBuffer, OUT LPVOID* pNewBuffer) {

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pPIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)ImageBuffer;

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

	// ��λ�����һ����
	pPIMAGE_SECTION_HEADER += (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);

	//���� NewBuffer �����ڴ�ĳ���
	DWORD SizeOfNewBuffer = pPIMAGE_SECTION_HEADER -> PointerToRawData + pPIMAGE_SECTION_HEADER -> SizeOfRawData;

	//�����ڴ�
	LPVOID NewBuffer = malloc(SizeOfNewBuffer);
	if (!NewBuffer) {
		printf("NewBuffer �ڴ�����ʧ��!!");
		free(ImageBuffer);
		return 0;
	}

	// �ڱ�ṹ��ָ�븴λ
	pPIMAGE_SECTION_HEADER -= (pPIMAGE_FILE_HEADER -> NumberOfSections - 1);

	// ��ʼ��
	memset(NewBuffer, 0, SizeOfNewBuffer);

	// ����ͷ
	memcpy(NewBuffer, ImageBuffer, pPIMAGE_OPTIONAL_HEADER32 -> SizeOfHeaders);

	// ������
	for (int i = 0; i < pPIMAGE_FILE_HEADER -> NumberOfSections; i++) {
		memcpy((LPVOID)((DWORD)NewBuffer + pPIMAGE_SECTION_HEADER -> PointerToRawData), \
			(LPVOID)((DWORD)ImageBuffer + pPIMAGE_SECTION_HEADER -> VirtualAddress), \
			pPIMAGE_SECTION_HEADER -> SizeOfRawData);
		pPIMAGE_SECTION_HEADER++;
	}

	//free(ImageBuffer);
	*pNewBuffer = NewBuffer;
	return SizeOfNewBuffer;
}


// *******************************************************************************
//���̺���
//����1 ����NewBuffer��ָ��
//����2 ����NewBuffer ����
//����ֵ �ɹ�����1 ʧ�ܷ���0;

DWORD WriteMemeryToFile(IN LPVOID NewBuffer, IN DWORD file_size) 
{
	FILE* pf = fopen("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\NEW_notepad.exe", "wb");
	if (!pf) {
		printf("���̵��ļ�����ʧ��");
		return 0;
	}
	DWORD x = fwrite(NewBuffer, sizeof(CHAR), file_size, pf);
	if (!x) {
		printf("�ļ�����ʧ��");
		fclose(pf);
		return 0;
	}
	printf("�ļ����̳ɹ�");
	fclose(pf);
	return 1;
}



// *******************************************************************************


//RVA  FOA  VAת��
void convertFoaToRva(IN LPSTR lpszFile) {
	//���ļ�����Ϳ���ImageBuffer����
	PVOID FileBuffer = 0;
	PVOID ImageBuffer = 0;
	CreateFileBuffer(IN lpszFile,OUT &FileBuffer);
	CopyFileBufferToImageBuffer(IN FileBuffer, OUT &ImageBuffer);
	//�ж��Ƿ����MZ���!!
	if (*((WORD*)ImageBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		free(ImageBuffer);
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)ImageBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader->e_lfanew);
	if (*((DWORD*)pntheader) != IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		free(ImageBuffer);
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER) & (pntheader->FileHeader);
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER) & (pntheader->OptionalHeader);
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader->SizeOfOptionalHeader);
	
	
	//����ImageBuffer��ĳһ����ַ
	printf("pImageBuffer:%x\n", ImageBuffer);
	printf("������va��ַ:");
	DWORD Va = 0; 
	scanf("%x", &Va);
	DWORD Rva = Va - (DWORD)ImageBuffer;
	//printf("%x -%x=%x", Va, (DWORD)ImageBuffer,Rva);
	DWORD Foa = 0;
	DWORD base = 0;
	//�жϵ�ַ��������ͷ���滹���ڽ�������ĸ�λ��
   //��ӡ���ļ��ĵĵ�ַ
   //��ӡ������״̬�ĵ�ַ
	if (Va > (DWORD)ImageBuffer && Va < poptionHeader->SizeOfHeaders) {
		Foa = Rva;
		printf("Foa �ĵ�ַΪ:%x\n", Foa);
		printf("����״̬�ĵ�ַΪ:%x\n", Rva+poptionHeader->ImageBase);
	}if (Va>= (DWORD)ImageBuffer +poptionHeader->SizeOfHeaders && Va< (DWORD)ImageBuffer+poptionHeader->SizeOfImage) {
		for (size_t i = 0; i < ppeheader->NumberOfSections; i++,psectionHeader++) {
			if (Rva>=psectionHeader->VirtualAddress && Rva< psectionHeader->VirtualAddress+psectionHeader->SizeOfRawData)  {
				base = Rva + poptionHeader->ImageBase;
				Rva -= psectionHeader->VirtualAddress;
				Foa = Rva + psectionHeader->PointerToRawData;
				printf("Foa �ĵ�ַΪ:%x\n", Foa);
				printf("����״̬�ĵ�ַΪ:%x\n", base);
				break;
			}

		}
		free(ImageBuffer);
	}

}


// *******************************************************************************

void ChangeImageBufferCode1(IN LPSTR lpszFile, IN BYTE* ShellCode,IN DWORD Codesize,IN DWORD Maddress) 
{
	/*
		lpszFile		Ŀ�� EXE ����·��
		ShellCode		Ҫע��Ĵ����ָ��
		Codesize		Ҫע��Ĵ���ĳ���
		Maddress		MessageBoxA ������ַ
	*/

	PVOID pFileBuffer = 0;
	PVOID pImageBuffer = 0;
	CreateFileBuffer(IN lpszFile, OUT &pFileBuffer);
	CopyFileBufferToImageBuffer(IN pFileBuffer, OUT &pImageBuffer);
	if (*((WORD*)pImageBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader -> e_lfanew);
	if (*((DWORD*)pntheader) != IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER) & (pntheader -> FileHeader);
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER) & (pntheader -> OptionalHeader);
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader -> SizeOfOptionalHeader);
	//printf("%x", psectionHeader->Misc);
	//��λpFileBuffer����λ��
	PIMAGE_SECTION_HEADER pfileBufferpsp = (PIMAGE_SECTION_HEADER)((BYTE*)psectionHeader - (BYTE*)pImageBuffer + (BYTE*)pFileBuffer);
	//�ж�pFileBuffer �ļ������ڿհ׿ռ��Ƿ��㹻��Ӵ���
	if (pfileBufferpsp -> Misc.VirtualSize > pfileBufferpsp -> SizeOfRawData) {
		printf("�����޿��ÿ����ڴ治�����!!!!");
	}if (pfileBufferpsp -> SizeOfRawData - pfileBufferpsp -> Misc.VirtualSize < Codesize) {
		printf("�����ڴ���������Ȳ�����Ӹô���!!!!");
	}
	
	PBYTE Codbigin = (PBYTE)((DWORD)pImageBuffer + psectionHeader -> VirtualAddress + psectionHeader -> Misc.VirtualSize);
	// printf("%x+%x=%x\n", pImageBuffer, psectionHeader -> VirtualAddress + psectionHeader -> Misc.VirtualSize, Codbigin);
	memcpy(Codbigin, ShellCode, Codesize);

	/*
	DWORD calladdress = (Maddress - (((DWORD)(Codbigin+0xd) - (DWORD)pImageBuffer) + poptionHeader -> ImageBase));
	*(PDWORD)(Codbigin + 0x9) = calladdress;
	// ��д��
	// DWORD jmpsddress = (poptionHeader -> AddressOfEntryPoint - (((DWORD)(Codbigin + Codesize - 1) - (DWORD)pImageBuffer) + poptionHeader -> ImageBase));
	// �ҳ���
	DWORD jmpsddress = ((poptionHeader -> ImageBase + poptionHeader -> AddressOfEntryPoint) - (poptionHeader -> ImageBase + ((DWORD)Codbigin + Codesize - (DWORD)pImageBuffer)));
	*(PDWORD)(Codbigin + 0xe) = jmpsddress;
	*/
	
	// �ҵ� Codbigin ���ڴ��е�ƫ�Ƶ�ַ + ImageBase
	DWORD VirtualCodbigin = ((DWORD)Codbigin - (DWORD)pImageBuffer) + poptionHeader -> ImageBase;
	printf("%d\n", VirtualCodbigin);
	// ��У׼ E8 ����ĵ�ַ 
	DWORD calladdress = Maddress - (VirtualCodbigin + 0x8 + 0x5);
	printf("%x\n", Maddress);
	// У׼ E9 ����ĵ�ַ 
	DWORD jmpsddress = poptionHeader -> AddressOfEntryPoint + poptionHeader -> ImageBase - ((DWORD)VirtualCodbigin + 0x8 + 0x5 + 0x5);

	
	// �� У׼��� E8/E9�����ֵ д�� ImageBuffer ��Ӧλ��
	*(LPDWORD)(Codbigin + 0x9) = calladdress;
	*(LPDWORD)(Codbigin + 0xE) = jmpsddress;

	poptionHeader -> AddressOfEntryPoint = ((DWORD)Codbigin - (DWORD)pImageBuffer);
	//printf("%x-%x=%x\n", (DWORD) Codbigin, (DWORD)pImageBuffer, poptionHeader -> AddressOfEntryPoint);
	//���������ļ� �ڴ�����Ϊ�ļ�����
	PVOID pNewBuffer = 0;
	DWORD file_size = ImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);

	//�ļ�����
	WriteMemeryToFile(pNewBuffer, file_size);
	free(pFileBuffer);
	free(pImageBuffer);
	free(pNewBuffer);
}