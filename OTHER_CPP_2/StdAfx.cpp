// stdafx.cpp : source file that includes just the standard includes
//	OTHER_CPP_2.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
#include <iostream>
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

/*
// ************ ע�� ************
// 2���ƴ�ӡ����ʹ��		
void ����(IN PVOID Buffer, IN WORD file_size) {
	BYTE* y = (BYTE*)Buffer;
	for (size_t i = 0; i < file_size; i++) {
		if (i % 16 == 0) {
			printf("\n");
		}
		printf("%x ", *y++);
	}
}
*/

//���ļ� �������ڴ�
//����OUT PVOID* pFileBuffer ����PVOID���͵� pFileBufferָ��
//����ֵΪ  ����ĳ���
DWORD CreateFileBuffer(IN LPSTR lpszFile,OUT PVOID* pFileBuffer) {
	FILE* pfile = 0;
	// ************ ���� ************
	// WORD filesize = 0;		
	DWORD filesize = 0;
	PVOID FileBuffer = 0;
	pfile = fopen(lpszFile, "rb");
	if (!pfile) {
		printf("�ļ���ʧ��!!");
		pfile = 0;
		return 0;
	}

	//ָ��ָ��pfile�ļ�β��;
	fseek(pfile, 0, SEEK_END);
	//ȡ������
	filesize = ftell(pfile);
	//����ָ�� ָ��pfile�ļ�ͷ��
	fseek(pfile, 0,SEEK_SET);
	
	//�����ڴ� ���ж��Ƿ�ɹ�
	FileBuffer =malloc(filesize);
	if (!FileBuffer) {
		printf("�ڴ�����ʧ��!!");
		fclose(pfile);
		return 0;
	}
	memset(FileBuffer, 0, filesize);
	//�����ļ��� �ж�
	DWORD	x = fread(FileBuffer, filesize, 1, pfile);
	if (!x) {
		printf("�ļ�������pFileBufferʧ��!!");
		fclose(pfile);
		free(FileBuffer);
		return 0;
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


//��ӡ����ͷ����Ϣ
//���� ���뻺��FileBufferָ��
void ToLoaderPE(IN PVOID pFileBuffer) {
	FILE* pbfer = (FILE*)pFileBuffer;
	PIMAGE_DOS_HEADER  pdosheader = NULL;
	PIMAGE_NT_HEADERS pntheader = NULL;
	PIMAGE_FILE_HEADER ppeheader = NULL;
	PIMAGE_OPTIONAL_HEADER poptionheader = NULL;
	PIMAGE_SECTION_HEADER psectionheader = NULL;
	if (!pbfer) {
		printf("ָ���ȡʧ��!!");
		free(pbfer);
	}
	if (*((WORD*)pbfer) != IMAGE_DOS_SIGNATURE) {
		printf("������Ч���MZ���!!");
		free(pbfer);
	}
	pdosheader = (PIMAGE_DOS_HEADER)pbfer;
	printf("------------------DOS-----------------------\n");
	printf("MZ���  e_magic:   %x\n", pdosheader->e_magic);
	printf("PEͷ��ַ  e_lfanew:   %x\n", pdosheader->e_lfanew);
	printf("------------------NT-----------------------\n");
	if (*((DWORD*)((char*)pbfer + pdosheader->e_lfanew)) != IMAGE_NT_SIGNATURE) {
		printf("������Ч���PE���!!");
		free(pbfer);
	}
	pntheader = (PIMAGE_NT_HEADERS)((char*)pdosheader + pdosheader->e_lfanew);
	printf("Signature:%x\n", pntheader->Signature);
	printf("------------------PE-----------------------\n");
	ppeheader = (PIMAGE_FILE_HEADER) & (pntheader->FileHeader);
	printf("CPU�ͺ�  Machine:   %x\n", ppeheader->Machine);
	printf("�ڵ����� NumberOfSections:   %x\n", ppeheader->NumberOfSections);
	printf("ʱ���  TimeDateStamp:   %x\n", ppeheader->TimeDateStamp);
	printf("��ѡͷ��С  SizeOfOptionalHeader:   %x\n", ppeheader->SizeOfOptionalHeader);
	printf("ÿ��λ������  Characteristics:   %x\n", ppeheader->Characteristics);
	printf("------------------OPPE-----------------------\n");
	poptionheader = (PIMAGE_OPTIONAL_HEADER) & (pntheader->OptionalHeader);
	printf("����˵��  Magic:   %x\n", poptionheader->Magic);
	printf("���д���ڵĺ�  SizeOfCode:   %x\n", poptionheader->SizeOfCode);
	printf("�ѳ�ʼ������  SizeOfInitializedData:   %x\n", poptionheader->SizeOfInitializedData);
	printf("δʼ������  SizeOfUninitializedData:   %x\n", poptionheader->SizeOfUninitializedData);
	printf("�������  AddressOfEntryPoint:   %x\n", poptionheader->AddressOfEntryPoint);
	printf("����λ�ַ  BaseOfCode:   %x\n", poptionheader->BaseOfCode);
	printf("���ݶλ�ַ  BaseOfCode:   %x\n", poptionheader->BaseOfData);
	printf("�ڴ澵���ַ  ImageBase:   %x\n", poptionheader->ImageBase);
	printf("�ڴ����  SectionAlignment:   %x\n", poptionheader->SectionAlignment);
	printf("�ļ�����  FileAlignment:   %x\n", poptionheader->FileAlignment);
	printf("�ڴ�PEӳ��ߴ�  SizeOfImage:   %x\n", poptionheader->SizeOfImage);
	printf("ͷ+�ڱ��ļ�����  SizeOfHeaders:   %x\n", poptionheader->SizeOfHeaders);
	printf("У����ж��ļ��޸�  CheckSum:   %x\n", poptionheader->CheckSum);
	printf("��ʼ������ջ��С  SizeOfStackReserve:   %x\n", poptionheader->SizeOfStackReserve);
	printf("��ʼ��ʵ�ʴ�С  SizeOfStackCommit:   %x\n", poptionheader->SizeOfStackCommit);
	printf("��ʼ�������Ѵ�С  SizeOfHeapReserve:   %x\n", poptionheader->SizeOfHeapReserve);
	printf("��ʼ��ʵ�ʶѴ�С  SizeOfHeapCommit:   %x\n", poptionheader->SizeOfHeapCommit);
	printf("------------------�ڱ�-----------------------\n\n\n");
	psectionheader = (PIMAGE_SECTION_HEADER)((char*)poptionheader + ppeheader->SizeOfOptionalHeader);
	int x = 0;
	int z = 0;
	char y[7] = { 0 };
	//printf("%x", ppeheader->NumberOfSections);
	for (size_t i = 0; i < ppeheader->NumberOfSections; i++, psectionheader++) {
		printf("------------------�ڱ�%d-----------------------\n", ++z);
		printf("�ڵ�����  Name: ");
		while (x < 6) {
			y[x] = psectionheader->Name[x];
			printf("%c", y[x]);
			x++;
		}
		x = 0;
		printf("\n");
		printf("�ļ�δ����ߴ�  Misc:   %x\n", psectionheader->Misc);
		printf("�ڴ��ƫ�Ƶ�ַ  VirtualAddress:   %x\n", psectionheader->VirtualAddress);
		printf("�ļ������ߴ�  SizeOfRawData:   %x\n", psectionheader->SizeOfRawData);
		printf("�����ļ���ƫ��  PointerToRawData:   %x\n", psectionheader->PointerToRawData);
		printf("�ڵ�����  Characteristics:   %x\n", psectionheader->Characteristics);
	}

}

//��FileBuffer��������������ImageBuffer
//����1 ����FileBuffer�׵�ַָ��
//����2 ����ImageBuffer�׵�ַָ��
//����ֵ ImageBuffer�ĳ���

DWORD CopyFileBufferToImageBuffer(IN PVOID pFileBuffer, OUT PVOID* pImageBuffer) {

	//�ж��Ƿ����MZ���!!
	if (*((WORD*)pFileBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		free(pFileBuffer);
		return 0;
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader->e_lfanew);
	if (*((DWORD*)pntheader)!= IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		free(pFileBuffer);
		return 0;
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER) & (pntheader -> FileHeader);
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER) & (pntheader -> OptionalHeader);
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader -> SizeOfOptionalHeader);
	//����ImageBuffer��Ҫ�����ڴ�ĳ���
	DWORD ffersize = poptionHeader->SizeOfImage;
	//����ImageBuffer�ڴ� ���ж�
	PVOID ImageBuffer = malloc(ffersize);
	if (!ImageBuffer) {
		printf("ImageBuffer�ڴ�����ʧ��!!");
		free(pFileBuffer);
		return 0;
	}
	//��ʼ������  ��������ͷ
	memset(ImageBuffer, 0, ffersize);
	memcpy(ImageBuffer, pFileBuffer, poptionHeader -> SizeOfHeaders);
	//��ֵ�ڱ�ָ�� ѭ�������ڱ�
	PIMAGE_SECTION_HEADER psectionHeaderTemp = psectionHeader;
	for (size_t i = 0; i < ppeheader -> NumberOfSections; i++, psectionHeaderTemp++) {
		memcpy((PVOID)((BYTE*)ImageBuffer + psectionHeaderTemp->VirtualAddress),
			(PVOID)((BYTE*)pFileBuffer + psectionHeaderTemp->PointerToRawData), psectionHeaderTemp->SizeOfRawData);
	}
	*pImageBuffer = ImageBuffer;
	//free(pFileBuffer);
	return ffersize;
 }


//ImageBuffer�������ݰ��ļ���ʽ������NewBuffer
//����1 ����ImageBuffer�׵�ַָ��
//����2 ����NewBuffer�׵�ַָ��
//����ֵ NewBuffer�ĳ���

DWORD ImageBufferToNewBuffer(IN PVOID ImageBuffer, OUT PVOID* pNewBuffer) {
	//�ж��Ƿ����MZ���!!
	if (*((WORD*)ImageBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		free(ImageBuffer);
		return 0;
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)ImageBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader->e_lfanew);
	if (*((DWORD*)pntheader) != IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		free(ImageBuffer);
		return 0;
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER)&pntheader->FileHeader;
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER)&pntheader->OptionalHeader;
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader->SizeOfOptionalHeader);
	// ����NewBuffer�����ڴ�ĳ���

	PIMAGE_SECTION_HEADER psp = (PIMAGE_SECTION_HEADER)(psectionHeader + (ppeheader->NumberOfSections - 1));
	
	// ************ ���� ************
	// DWORD NewBuffersize = psp->PointerToRawData + poptionHeader->SizeOfHeaders+psectionHeader->SizeOfRawData;
	DWORD NewBuffersize = psp -> PointerToRawData + psp -> SizeOfRawData;
	// �����ڴ�
	PVOID NewBuffer = malloc(NewBuffersize);
	if (!NewBuffer) {
		printf("NewBuffer �ڴ�����ʧ��!!");
		free(ImageBuffer);
		return 0;
	}
	memset(NewBuffer, 0, NewBuffersize);
	memcpy(NewBuffer, ImageBuffer, poptionHeader->SizeOfHeaders);
	for (size_t i = 0; i < ppeheader->NumberOfSections; i++, psectionHeader++) {
		memcpy((PVOID)((BYTE*)NewBuffer + psectionHeader->PointerToRawData),
			(PVOID)((BYTE*)ImageBuffer + psectionHeader->VirtualAddress), psectionHeader->SizeOfRawData);
	}
	//free(ImageBuffer);
	*pNewBuffer = NewBuffer;
	return NewBuffersize;
}

//���̺���
//����1 ����NewBuffer��ָ��
//����2 ����NewBuffer ����
//����ֵ �ɹ�����1 ʧ�ܷ���0;
DWORD WriteMemeryToFile(IN PVOID NewBuffer, IN DWORD file_size) {
	// ************ ���� ************
	// FILE* pf = fopen("D:\\BaiduNetdiskDownload\\�ؼ���6.exe", "wb");		
	FILE* pf = fopen("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\NEW_notepad.exe", "wb");
	if (!pf) {
		printf("���̵��ļ�����ʧ��");
		return 0;
	}
	DWORD x = fwrite((FILE*)NewBuffer, file_size, 1, pf);
	if (!x) {
		printf("�ļ�����ʧ��");
		fclose(pf);
		return 0;
	}
	printf("�ļ����̳ɹ�");
	fclose(pf);
	return 1;
}

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

//���ڿհ�����Ӵ���
/*void ChangeImageBufferCode(IN LPSTR lpszFile, IN BYTE* CodeSize) {
	//���ļ�����Ϳ���ImageBuffer����
	PVOID FileBuffer = 0;
	PVOID pImageBuffer = 0;
	PVOID pNewBuffer = 0;
	CreateFileBuffer(IN lpszFile, OUT & FileBuffer);
	CopyFileBufferToImageBuffer(IN FileBuffer, OUT & pImageBuffer);
	
	//�ж��Ƿ����MZ���!!
	if (*((WORD*)pImageBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader->e_lfanew);
	if (*((DWORD*)pntheader) != IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER) & (pntheader->FileHeader);
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER) & (pntheader->OptionalHeader);
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader->SizeOfOptionalHeader);
	DWORD BoxA = 0x74C828B0;

	for (size_t i = 0; i < ppeheader->NumberOfSections; i++) {
		
		if (psectionHeader->Misc.VirtualSize < psectionHeader->SizeOfRawData && 
			psectionHeader->SizeOfRawData- psectionHeader->Misc.VirtualSize>19) {
			memcpy((PVOID)((BYTE*)pImageBuffer + psectionHeader->VirtualAddress + psectionHeader->Misc.VirtualSize), (FILE*)CodeSize, 18);
			DWORD* E8cod = (DWORD*)((BYTE*)pImageBuffer + psectionHeader->VirtualAddress + psectionHeader->Misc.VirtualSize + 9);
			DWORD codc = BoxA -(DWORD) ((BYTE*)E8cod + 4);
			*E8cod = codc;
			DWORD* E9cod = (DWORD*)((BYTE*)E8cod + 5);
			codc=poptionHeader->AddressOfEntryPoint - (DWORD)((BYTE*)E9cod + 4);
			*E9cod = codc;
			poptionHeader->AddressOfEntryPoint = poptionHeader->ImageBase + (DWORD)((BYTE*)pImageBuffer + psectionHeader->VirtualAddress + psectionHeader->Misc.VirtualSize);
			break;
		}
		DWORD file_size =ImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
		WriteMemeryToFile(IN pNewBuffer, IN  file_size);
		fclose((FILE*)pNewBuffer);
	}


}*/


// ************ ���� ************
// void ChangeImageBufferCode1(IN LPSTR lpszFile, IN BYTE* ShellCode,IN DWORD Codesize,IN WORD Maddress) {		
void ChangeImageBufferCode1(IN LPSTR lpszFile, IN BYTE* ShellCode,IN DWORD Codesize,IN DWORD Maddress) {
	PVOID pFileBuffer = 0;
	PVOID pImageBuffer = 0;
	CreateFileBuffer(IN lpszFile, OUT &pFileBuffer);
	CopyFileBufferToImageBuffer(IN pFileBuffer, OUT &pImageBuffer);
	if (*((WORD*)pImageBuffer) != IMAGE_DOS_SIGNATURE) {
		printf("���ļ�����MZ����ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_DOS_HEADER pdosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
	PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((BYTE*)pdosHeader + pdosHeader->e_lfanew);
	if (*((DWORD*)pntheader) != IMAGE_NT_SIGNATURE) {
		printf("���ļ�����PE��ʽ�ļ� ���ļ�����!!");
		fclose((FILE*)pImageBuffer);
	}
	PIMAGE_FILE_HEADER ppeheader = (PIMAGE_FILE_HEADER) & (pntheader->FileHeader);
	PIMAGE_OPTIONAL_HEADER poptionHeader = (PIMAGE_OPTIONAL_HEADER) & (pntheader->OptionalHeader);
	PIMAGE_SECTION_HEADER psectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)poptionHeader + ppeheader->SizeOfOptionalHeader);
	//printf("%x", psectionHeader->Misc);
	//��λpFileBuffer����λ��
	PIMAGE_SECTION_HEADER pfileBufferpsp = (PIMAGE_SECTION_HEADER)((BYTE*)psectionHeader - (BYTE*)pImageBuffer + (BYTE*)pFileBuffer);
	//�ж�pFileBuffer �ļ������ڿհ׿ռ��Ƿ��㹻��Ӵ���
	if (pfileBufferpsp->Misc.VirtualSize > pfileBufferpsp->SizeOfRawData) {
		printf("�����޿��ÿ����ڴ治�����!!!!");
	}if (pfileBufferpsp->SizeOfRawData-pfileBufferpsp->Misc.VirtualSize< Codesize) {
		printf("�����ڴ���������Ȳ�����Ӹô���!!!!");
	}
	
	PBYTE Codbigin = (PBYTE)((DWORD)pImageBuffer + psectionHeader -> VirtualAddress+psectionHeader -> Misc.VirtualSize);
	printf("%x+%x=%x\n", pImageBuffer, psectionHeader -> VirtualAddress + psectionHeader -> Misc.VirtualSize,Codbigin);
	memcpy(Codbigin, ShellCode, Codesize);
	DWORD calladdress = (Maddress - (((DWORD)(Codbigin + 0xd) - (DWORD)pImageBuffer) + poptionHeader -> ImageBase));
	*(PDWORD)(Codbigin + 0x9) = calladdress;
	// ��д��
	// DWORD jmpsddress = (poptionHeader->AddressOfEntryPoint - (((DWORD)(Codbigin + Codesize - 1) - (DWORD)pImageBuffer) + poptionHeader->ImageBase));
	// �ҳ���
	DWORD jmpsddress = ((poptionHeader -> ImageBase + poptionHeader -> AddressOfEntryPoint) - (poptionHeader -> ImageBase + ((DWORD)Codbigin + Codesize - (DWORD)pImageBuffer)));
	*(PDWORD)(Codbigin + 0xe) = jmpsddress;
	// poptionHeader -> AddressOfEntryPoint = (((DWORD)Codbigin - (DWORD)pImageBuffer - psectionHeader -> Misc.VirtualSize));(����)
	poptionHeader -> AddressOfEntryPoint = (((DWORD)Codbigin - (DWORD)pImageBuffer));
	//printf("%x-%x=%x\n",(DWORD) Codbigin, (DWORD)pImageBuffer, poptionHeader->AddressOfEntryPoint);
	//���������ļ� �ڴ�����Ϊ�ļ�����
	PVOID pNewBuffer = 0;
	DWORD file_size = ImageBufferToNewBuffer(IN  pImageBuffer, OUT  &pNewBuffer);
	//�ļ�����
	WriteMemeryToFile(IN  pNewBuffer, IN  file_size);
	free(pFileBuffer);
	free(pImageBuffer);
	free(pNewBuffer);

}