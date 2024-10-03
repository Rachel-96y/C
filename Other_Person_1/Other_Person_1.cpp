// Other_Person_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// readFile.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

DWORD fileSize = 0;

char f[80] = {0};
char write_file_path[80] = {0};


int FOAToRVA(PIMAGE_SECTION_HEADER pSectionHeader, int HeaderSize, int FOAaddress)
{
	int N = 0;
	int Count = 0;
	int RVAaddress = 0;
	int sectionNum = 0;
	int VirtualAddress = 0;
	PIMAGE_SECTION_HEADER pTemSectionHeader = pSectionHeader;
	int sizeOfRaw = 0;
	int actuallySize = 0;
	int pointerOfRaw = 0;
	int deviationAddress = 0;

	//D:\i4Tools7\avfilter-6.dll
	//������
	if(FOAaddress == 0){return 0;}
	else if(FOAaddress <= HeaderSize){return FOAaddress;}
	else
	{
		while(pTemSectionHeader -> Characteristics != 0)
		{
			sectionNum++;

			sizeOfRaw = pTemSectionHeader -> SizeOfRawData;
			actuallySize = pTemSectionHeader -> Misc.VirtualSize;
			pointerOfRaw = pTemSectionHeader -> PointerToRawData;
			VirtualAddress = pTemSectionHeader -> VirtualAddress;
			sizeOfRaw > actuallySize ? N = sizeOfRaw : N = actuallySize;

			//1����pointerOfRaw + sizeOfRaw����ȡ����ڵķ�Χ
			//2����FOA�������Χ�Ƚ�,ȷ�����ڽ�
			if(pointerOfRaw <= FOAaddress && FOAaddress <= (pointerOfRaw+sizeOfRaw))
			{
				/*
				Count = 1;
				printf("FOA���ڽ�: %d\n", sectionNum);
				printf("FOAaddress: 0x%X\n", FOAaddress);
				printf("pointerOfRaw: 0x%X\n", pointerOfRaw);
				printf("pointerOfRaw+sizeOfRaw: 0x%X\n\n", pointerOfRaw+sizeOfRaw);
				*/

				//3����FOA - �ýڵ�PointToRawData = RVAƫ��
			    deviationAddress = FOAaddress - pointerOfRaw;

				//4��RVAaddress = VirtualAddress + RVAƫ��
				RVAaddress = VirtualAddress + deviationAddress;
				//5���ж��Ƿ� VirtualAddress <= RVA < (VirtualAddress + N) 
				
				if(VirtualAddress <= RVAaddress && RVAaddress < (VirtualAddress + N))
				{
					return RVAaddress;
				}
			}
			// if(Count == 1){break;}
	
			pTemSectionHeader = (PIMAGE_SECTION_HEADER)((int)pTemSectionHeader + 40);
		}
	}
	return NULL;
}


int RVAToFOA(PIMAGE_SECTION_HEADER pSectionHeader, int HeaderSize, int RVAaddress)
{
	int N = 0;
	int Count = 0;
	int FOAaddress = 0;
	int sectionNum = 0;
	int VirtualAddress = 0;
	PIMAGE_SECTION_HEADER pTemSectionHeader = pSectionHeader;
	int sizeOfRaw = 0;
	int actuallySize = 0;


	//������
	if(RVAaddress == 0){return 0;}
	else if(RVAaddress <= HeaderSize){return RVAaddress;}
	else
	{
		while(pTemSectionHeader -> Characteristics != 0)
		{
			sectionNum++;
			//1���Ա�SizeOfRawData��Misc��ֵ,˭��ȡ˭

			sizeOfRaw = pTemSectionHeader -> SizeOfRawData;
			actuallySize = pTemSectionHeader -> Misc.VirtualSize;
			sizeOfRaw > actuallySize ? N=sizeOfRaw : N = actuallySize;
			VirtualAddress = pTemSectionHeader -> VirtualAddress;


			//2����VirtualAddress + N����ȡ����ڵķ�Χ
			//3����RVA�������Χ�Ƚ�,ȷ�����ڽ�
			if(VirtualAddress <= RVAaddress && RVAaddress <= (VirtualAddress + N))
			{
				/*
				Count = 1;
				printf("RVA���ڽ�: %d\n", sectionNum);
				printf("RVAaddress: 0x%X\n", RVAaddress);
				printf("VirtualAddress: 0x%X\n", VirtualAddress);
				printf("VirtualAddress + N: 0x%X\n\n", VirtualAddress + N);
				*/
				
				//4����ȡ�ھ����е�ƫ��λ��
				int deviationAddress = RVAaddress - VirtualAddress;
			
				//5���øýڵ�PointToRawData + RVA��ƫ�ƣ���RVA��FOA
				FOAaddress = pTemSectionHeader -> PointerToRawData + deviationAddress;
				return FOAaddress;
			}
			//if(Count == 1){break;}

			//�����ڣ���������һ����
			pTemSectionHeader = (PIMAGE_SECTION_HEADER)((int)pTemSectionHeader + 40);
		}
	}
	return NULL;
}

void tansformTimeStamp(time_t time)
{
	time_t PTime = 0;
    struct tm* timeP;

    PTime = time + (8 * 60 *60);
    timeP = localtime(&PTime);    // ת��
    printf("%d-%d-%d %d:%d:%d\n",1900 + timeP -> tm_year, 1 + timeP -> tm_mon, timeP -> tm_mday, \
		timeP -> tm_hour, timeP -> tm_min, timeP -> tm_sec);
}

int saveFile(PVOID NewFileBuffer, DWORD FileSize, char* FilePath)
{
	FILE* fp1 = fopen(FilePath, "wb");
	if(fp1 != NULL)
	{
		fwrite(NewFileBuffer, FileSize, 1, fp1);
	}
	fclose(fp1);
	return 1;

}

LPVOID readPEFile(LPSTR filePath)
{
	//�����ļ�ָ��
	FILE *pFile = NULL;
	
	LPVOID pFileBuffer = NULL;

	//���ļ�
	pFile = fopen(filePath, "rb");
	if(!pFile)
	{
		printf("�޷��򿪸ó���");
		return NULL;
	}

	//��ָ������ļ�ĩβ
	fseek(pFile, 0, SEEK_END);
	//��ȡ�ļ���С
	fileSize = ftell(pFile);
	
	//��ָ������ļ���ͷ
	fseek(pFile, 0, SEEK_SET);
	//���仺����
	pFileBuffer = malloc(fileSize);
	if(!pFileBuffer)
	{
		printf("�ڴ����ʧ�ܣ�");
		free(pFileBuffer);
		pFileBuffer = NULL;
		fclose(pFile);
		return NULL;
	}
	size_t flag = fread(pFileBuffer, fileSize, 1, pFile);
	if(!flag)
	{
		printf("���ݶ�ȡʧ�ܣ�");
		free(pFileBuffer);
		pFileBuffer = NULL;
		fclose(pFile);
		return NULL;
	}
	
	//��ȡ�ɹ���ر��ļ�
	fclose(pFile);
	return pFileBuffer;
}

//��������Ĵ�С
int countAlignment(int virtualSize, int alignmentNum)
{
	if(virtualSize % alignmentNum == 0)
	{
		return virtualSize;
	}else
	{
		return ((virtualSize/alignmentNum) + 1) * alignmentNum;
	}
}

//���ļ����� ��ȡ�� ���񻺳�����
//�������ļ�ָ�롢�����С��ͷ��С��DOSͷָ�롢��������ָ��
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, DWORD SizeOfImage, DWORD SizeOfHeaders, PIMAGE_DOS_HEADER pDOSHeader, \
								  DWORD NumberOfSection, PIMAGE_SECTION_HEADER pSectionHeader, OUT LPVOID* pImage)
{
	LPVOID pImageBuffer = malloc(SizeOfImage);
	//���ݾ����С����ռ�
	if(!pImageBuffer)
	{
		printf("�ڴ����ʧ�ܣ�");
		return 0;
	}
	//��ʼ��������,��ͷ��ʼ��0
	memset(pImageBuffer, 0, SizeOfImage); 
	//�Ȱ�ͷ���뻺������
	memcpy(pImageBuffer, pDOSHeader, SizeOfHeaders);
	//���ݽڱ���٣�ѭ��¼�룬�Ӵ����нڿ�ʼ�ĵط����ϴ����ж����Ĵ�С
	for(UINT i = 0; i<NumberOfSection; i++, pSectionHeader++)
	{
		memcpy((LPVOID)((DWORD)pImageBuffer + pSectionHeader -> VirtualAddress), \
			(LPVOID)((DWORD)pDOSHeader + pSectionHeader -> PointerToRawData), pSectionHeader -> SizeOfRawData);
	}

	*pImage = pImageBuffer;
	pImageBuffer = NULL;
	return SizeOfImage;
}

void printHeaders()
{
	LPVOID pFileBuffer = NULL;
	PIMAGE_DOS_HEADER pDOSHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeaders = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER  pSectionHeader = NULL;
	PIMAGE_EXPORT_DIRECTORY pExportTable = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = NULL;
	PIMAGE_BOUND_IMPORT_DESCRIPTOR pImportBondTable = NULL;
	PIMAGE_BOUND_FORWARDER_REF pBondRef = NULL;
	int* functionAddress = NULL;
	short* orderAddress = NULL;
	int* functionName = NULL;
	char* pName = NULL;

	

	pFileBuffer = readPEFile(f);
	if(!pFileBuffer)
	{
		printf("�޷��򿪸ó���");
		return;
	}

	//�ж��Ƿ���MZ��־
	if(*(PWORD)pFileBuffer != IMAGE_DOS_SIGNATURE)
	{
		printf("0x%X\n", *(PWORD)pFileBuffer);
		printf("������MZ��ʶ����ȷ�ϴ򿪵��ļ��Ƿ�Ϊ.exe .dll .sys�ļ�");
		//�ͷŶ��ڴ�	
		free(pFileBuffer);
		pFileBuffer = NULL;
		return;
	}

	printf("\n\n");

	pDOSHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	printf("MZ��ʶ: %c%c\n", pDOSHeader -> e_magic, *((char*)pFileBuffer+1));
	printf("PEƫ��: 0x%X\n", pDOSHeader -> e_lfanew);
	if(*((PWORD)((DWORD)pFileBuffer+pDOSHeader -> e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		printf("������PE��ʶ,�ļ���������");
		//�ͷŶ��ڴ�	
		free(pFileBuffer);
		pFileBuffer = NULL;
		return;
	}

	pNTHeaders = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDOSHeader -> e_lfanew);
	printf("NTͷ: %c%c\n", pNTHeaders -> Signature, *((char*)(pDOSHeader -> e_lfanew + (DWORD)pFileBuffer + 1)));
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeaders) + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);


	int HeaderSize = pOptionHeader -> SizeOfHeaders;
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader -> SizeOfOptionalHeader);


	int sectionStartingPosition = pDOSHeader -> e_lfanew+24 + pPEHeader -> SizeOfOptionalHeader;
	int sectionNum = 0;
	
	printf("=======================<<�ڱ�>>=======================\n\n");
	while((pSectionHeader -> Characteristics != 0) && (sectionNum < (pPEHeader -> NumberOfSections))){
		sectionNum++;
		pSectionHeader++; //��ȡ���һ���ڵĵ�ַ
	}
	char* mark = (char*)pSectionHeader;
	int count = 0;
	int flag = 1;
	
	for(int i = 0; i < 80; i++)
	{
		if(*mark != 0)
		{
			printf("���һ�ں�������.�ռ䲻�㹻��%d\n", sectionNum);
			flag = 0;
			break;
		}else{
			count++;
			mark++;
		}
	}
	if(count == 80)printf("�ռ��㹻,���������ڱ�\n\n");
	
	LPVOID pNewFileBuffer = NULL;
	PIMAGE_SECTION_HEADER pTemSectionHeader = NULL;
	PIMAGE_SECTION_HEADER pPreSectionHeader = NULL;
	PIMAGE_DOS_HEADER pNewDOSHeader = NULL;
	int SizeOfNewFileBuffer = 0;
	int virtualSize = 0x1200;
	

	printf("�ڱ����λ��: 0x%X\n", (int)pSectionHeader - (int)pFileBuffer);
	if(flag == 1)
	{	
		pPreSectionHeader = pSectionHeader - 1;


		//����
		strcpy((char*)pSectionHeader -> Name, (char*)".NewSec");
		pSectionHeader -> Misc.VirtualSize = virtualSize;
		pSectionHeader -> VirtualAddress = countAlignment(((pPreSectionHeader -> VirtualAddress) + \
			(pPreSectionHeader -> Misc.VirtualSize)), pOptionHeader -> SectionAlignment);
		pSectionHeader -> SizeOfRawData = countAlignment(pSectionHeader -> Misc.VirtualSize, pOptionHeader -> FileAlignment);
		pSectionHeader -> PointerToRawData = pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData;
		pSectionHeader -> Characteristics = 0xE0; 
		pPEHeader -> NumberOfSections = sectionNum + 1;


		//�޸ľ����С
		pOptionHeader -> SizeOfImage = pSectionHeader -> VirtualAddress + countAlignment(pSectionHeader -> Misc.VirtualSize, pOptionHeader -> SectionAlignment);
		

		printf("�����Ľڴ�С: 0x%X\n\n", countAlignment(pSectionHeader -> Misc.VirtualSize, pOptionHeader -> FileAlignment));

		SizeOfNewFileBuffer = (int)(pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData) + pSectionHeader -> SizeOfRawData;
		
		pNewFileBuffer = malloc(SizeOfNewFileBuffer);
		if(pNewFileBuffer == NULL)
		{
			printf("�½�������ʧ��\n\n");
			return;
		}

		//�½���֮ǰ��ֵȫ�����ƣ��½ڱ����Ѹı�
		memcpy(pNewFileBuffer, pFileBuffer, (int)(pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData));
 
		//�½���ȫ������
		memset((void *)((DWORD)pNewFileBuffer + pSectionHeader -> PointerToRawData), 0, pSectionHeader -> SizeOfRawData);
		

	}else
	{
		//�ռ䲻����������
		//1���½��Ļ�����
		int sizeOfRawData = 0;
		pPreSectionHeader = pSectionHeader - 1;
		sizeOfRawData = countAlignment(virtualSize,pOptionHeader -> FileAlignment);
		SizeOfNewFileBuffer = (int)(pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData) + sizeOfRawData;
		printf("���ļ�����ռ�: 0x%X\n\n", SizeOfNewFileBuffer);

		//�½���ȫ������
		pNewFileBuffer = malloc(SizeOfNewFileBuffer);
		memset(pNewFileBuffer, 0, SizeOfNewFileBuffer);
		if(pNewFileBuffer == NULL)
		{
			printf("�½�������ʧ��\n\n");
			return ;
		}

		//2������DOSͷ
		memcpy(pNewFileBuffer, pFileBuffer, 0x40);
		pNewDOSHeader = (PIMAGE_DOS_HEADER)((int)pNewFileBuffer + 0x40);


		//3����NTͷ���Ƶ����һ���ڱ�
		pPEHeader -> NumberOfSections = sectionNum + 1;
		memmove(pNewDOSHeader, pNTHeaders, (int)pSectionHeader - (int)pNTHeaders);


		//�������λ��
		int insertAddress = ((int)pSectionHeader - (int)pNTHeaders)+ 0x40;
		pTemSectionHeader = (PIMAGE_SECTION_HEADER)((int)pNewFileBuffer + insertAddress);
		pPreSectionHeader = pTemSectionHeader - 1;

		//printf("pSectionHeader - pNTHeaders: 0x%X\n", (int)pSectionHeader - (int)pNTHeaders);
		//printf("�ļ��нڱ����λ��: 0x%X\n", insertAddress);

		//4�������ڱ�
		strcpy((char*)pTemSectionHeader -> Name, (char*)".NewSec");
		pTemSectionHeader -> Misc.VirtualSize = virtualSize;
		pTemSectionHeader -> VirtualAddress = countAlignment(((pPreSectionHeader -> VirtualAddress) + (pPreSectionHeader -> Misc.VirtualSize)), pOptionHeader -> SectionAlignment);
		pTemSectionHeader -> SizeOfRawData = countAlignment(pTemSectionHeader -> Misc.VirtualSize, pOptionHeader -> FileAlignment);
		pTemSectionHeader -> PointerToRawData = pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData;
		pTemSectionHeader -> Characteristics = 0xE0; 
		((PIMAGE_DOS_HEADER)pNewFileBuffer) -> e_lfanew = 0x40;



		//�޸ľ����С
		pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((int)pNewDOSHeader + 0x18);
		printf("��ǰ��SizeOfImage: 0x%X\n", pOptionHeader -> SizeOfImage);
		pOptionHeader -> SizeOfImage = pTemSectionHeader -> VirtualAddress + countAlignment(pTemSectionHeader -> Misc.VirtualSize,pOptionHeader -> SectionAlignment);
		printf("pOptionHeader��ƫ��: 0x%X\n\n", (int)pOptionHeader - (int)pNewFileBuffer);
		printf("���һ�ڵ�VirtualAddress: 0x%X    �Լ������Ľڴ�С: 0x%X   ���յ�SizeOfImage: 0x%X\n\n", \
			pTemSectionHeader -> VirtualAddress, countAlignment(pTemSectionHeader -> Misc.VirtualSize, pOptionHeader -> SectionAlignment), pOptionHeader -> SizeOfImage);



		//5������ʣ������
		int offset = (int)pSectionHeader - (int)pFileBuffer; //�ڱ�ĩλ��ƫ��
		memmove((LPVOID)((int)pNewFileBuffer+offset), pSectionHeader, (pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData) - offset);

		sectionStartingPosition = ((int)pNewDOSHeader + 0x18 + pPEHeader -> SizeOfOptionalHeader) - (int)pNewFileBuffer;
		pSectionHeader = pTemSectionHeader;
	}

	
	printf("����ڱ�����: .NewSec\n\n");
	printf("�ڱ����ʼλ��: 0x%X\n\n", sectionStartingPosition);
	printf("�ڵ�ʵ�ʴ�С: 0x%X\n", pSectionHeader -> Misc.VirtualSize);
	printf("�ý����ڴ��е�ƫ�Ƶ�ַ: 0x%X\n", pSectionHeader -> VirtualAddress);
	printf("�ý��ڴ����е�ƫ�Ƶ�ַ: 0x%X\n", pSectionHeader -> PointerToRawData);
	printf("�ý��ڴ����ж����Ĵ�С: 0x%X\n", pSectionHeader -> SizeOfRawData);
	printf("�ý��ڴ����н���λ��: 0x%X\n\n", (pSectionHeader -> PointerToRawData + pSectionHeader -> SizeOfRawData) - 16);
	printf("ԭ�ļ��и��ƽ�ֹλ��: 0x%X\n\n", (int)(pPreSectionHeader -> PointerToRawData + pPreSectionHeader -> SizeOfRawData));

	//===========================�����ڽ���===========================

	
	PIMAGE_SECTION_HEADER pNewSecTable = (PIMAGE_SECTION_HEADER)(sectionStartingPosition + (DWORD)pNewFileBuffer);						//newBuffer�е�һ�Žڱ�ĵ�ַ
	PIMAGE_SECTION_HEADER pNewEndSecTable = (PIMAGE_SECTION_HEADER)((int)pNewSecTable + ((pPEHeader -> NumberOfSections) - 1) * 40);	//newBuffer�����һ���Žڱ�ĵ�ַ
	PIMAGE_OPTIONAL_HEADER32 pOpNewtionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pNewFileBuffer+pDOSHeader -> e_lfanew + 24);			//newBuffer�еĿ�ѡPEͷ
	LPVOID pNewSecStarPosition = NULL;

	int funAddressRVA = 0;
	int funOrderRVA = 0;
	int funNameRVA = 0;
	int exportTableRVA = 0;

	int* pTempFunctionName = NULL;
	int* dllName = NULL;


	//1����ȡ�������Լ����ڲ���Ϣ
	//������
	//�����������ھʹ�ӡ������
	if(((pOpNewtionHeader -> DataDirectory[0].VirtualAddress) != 0) && ((pOpNewtionHeader -> DataDirectory[0].VirtualAddress) != 0x1000))
	{
		//�Ѵ����б��λ�ø�ֵ��ָ��
		pExportTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pNewFileBuffer + (RVAToFOA(pNewSecTable, HeaderSize, pOpNewtionHeader -> DataDirectory[0].VirtualAddress)));

		printf("������RVA: 0x%X\n", pOpNewtionHeader -> DataDirectory[0].VirtualAddress);
		printf("������FOA: 0x%X\n\n", (RVAToFOA(pNewSecTable, HeaderSize, pOpNewtionHeader -> DataDirectory[0].VirtualAddress)));

		pName = (char*)((pExportTable -> Name + (DWORD)pNewFileBuffer) + 1);

		if(RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> Name) < (int)fileSize)
		{
			pName = (char*)( RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> Name) + (DWORD)pNewFileBuffer);
			printf("����������: ");

					while(*(pName) != 0)
					{
						printf("%c", *pName);
						pName++;
					}
					printf("\n");

		}else{printf("��������Ϣ����\n\n");}


		functionName = (int*)((DWORD)pNewFileBuffer + (RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> AddressOfNames)));            //�������ֱ��ַ
		orderAddress = (short*)((DWORD)pNewFileBuffer + (RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> AddressOfNameOrdinals)));   //��ű��ַ
		functionAddress = (int*)((DWORD)pNewFileBuffer + (RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> AddressOfFunctions)));	  //�������ַ
		int* pTemfunctionName = functionName;
		short* pTemOrderAddress = orderAddress;
		pTempFunctionName = functionName;		//�̶�ֵ

		int* tempFunctionName = functionName;

		printf("ԭ�ļ���С: 0x%X  %dKB\n", fileSize, fileSize / 1024);

		//�޸��ļ���С����ʱ�������ں�Ĵ�С
		fileSize = pNewEndSecTable -> PointerToRawData + pNewEndSecTable -> SizeOfRawData;
		printf("�����ں��ļ���С: 0x%X  %dKB\n\n", fileSize, fileSize / 1024);

		//�½���ʼλ�þ���NewFileBuffer+�½����ڴ��е�ƫ��	
		LPVOID pNewSecStarPosition = (LPVOID)((DWORD)pNewFileBuffer + pNewEndSecTable -> PointerToRawData);


		//2�����ݺ������С�ƶ�������  ��С=NumberOfFunctions*4  �ƶ�����������ʼλ��,����ָ��ָ��ĩβ
		memmove(pNewSecStarPosition, functionAddress, ((pExportTable -> NumberOfFunctions) * 4));
		funAddressRVA = FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer);
		printf("�ƶ�������ַ���FOA: 0x%X\n", (int)pNewSecStarPosition - (int)pNewFileBuffer);
		pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + (pExportTable -> NumberOfFunctions) * 4);
		


		//3���ں�������棬������ű�  ��С=NumberOfNames*2   ����ָ��ָ��ĩβ
		memmove(pNewSecStarPosition ,orderAddress, ((pExportTable -> NumberOfNames) * 2));
		funOrderRVA = FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer);
		printf("�ƶ�����ű��FOA: 0x%X\n", (int)pNewSecStarPosition - (int)pNewFileBuffer);
		pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + (pExportTable -> NumberOfNames) * 2);
		


		//4���ƶ��������ƣ�������ųƱ���� ֮���滻�������Ʊ��еĺ�������RVA
		for(int i = 0; i < (int)pExportTable -> NumberOfFunctions; i++)
		{
			//ƥ�亯�����Ʊ�
			for(int k = 0; k < (int)pExportTable -> NumberOfNames; k++)
			{
					
				if((*orderAddress) == k)
				{
			
					if(RVAToFOA(pNewSecTable, HeaderSize, *functionName) < (int)fileSize)
					{		
						//���ֵ���ʼ��ַRVA
						pName = (char*)(RVAToFOA(pNewSecTable, HeaderSize, *functionName) + (DWORD)pNewFileBuffer);

						//��ȡ���Ƶ�ַ��RVA
						funNameRVA = FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer);

						while(*(pName) != 0)
						{	
							//������һ�������ƹ�ȥ
							memmove(pNewSecStarPosition, pName, 1);
							pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + 1);
							pName++;
						}
						
						//���ָ�����Ϻ󣬰����ֵ�RVA�ŵ��������Ʊ���
						*functionName = funNameRVA;
						pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + 1);
							
					}

					functionName++;
					break;

				}else{
					tempFunctionName++;
				}
			}

			functionAddress++;
		}

		//5���ƶ�����������
		if(RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> Name) < (int)fileSize)
		{
			pName = (char*)( RVAToFOA(pNewSecTable, HeaderSize, pExportTable -> Name) + (DWORD)pNewFileBuffer );
			dllName =(int*)(FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer));

			while(*(pName) != 0)
			{
				memmove(pNewSecStarPosition, pName, 1);
				pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + 1);
				pName++;
			}
			pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + 1);

		}else{printf("��������Ϣ����\n\n");}

		//6���޸ĵ������е��������ֵ�ƫ��
		pExportTable -> Name = (int)dllName;

		//7���ƶ��������Ʊ��ƶ����������ֺ���  ��С=NumberOfNames*4
		memmove(pNewSecStarPosition, pTempFunctionName, (pExportTable -> NumberOfNames) * 4);
		funNameRVA = FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer);
		printf("�ƶ��������Ʊ�: 0x%X\n\n", (int)pNewSecStarPosition - (int)pNewFileBuffer);
		pNewSecStarPosition = (LPVOID)((int)pNewSecStarPosition + (pExportTable -> NumberOfNames) * 4);
		

		//8���޸��ƶ��󵼳����е� ������RVA����ű�RVA�����ֱ�RVA
		pExportTable -> AddressOfFunctions = funAddressRVA;
		pExportTable -> AddressOfNameOrdinals = funOrderRVA;
		pExportTable -> AddressOfNames = funNameRVA;

		//9�����ѵ������ƶ����������Ʊ����
		memmove(pNewSecStarPosition, pExportTable, 0x28);
		exportTableRVA = FOAToRVA(pNewSecTable, HeaderSize, (int)pNewSecStarPosition - (int)pNewFileBuffer);

		//10���޸�Ŀ¼���е������RVA
		pOpNewtionHeader -> DataDirectory[0].VirtualAddress = exportTableRVA;

		saveFile(pNewFileBuffer, SizeOfNewFileBuffer, write_file_path);
		printf("���̳ɹ���\n\n");

	}else{printf("���ļ�û�е�����\n\n");}




	//�ͷ�ָ��
	pOpNewtionHeader = NULL;
	pNewSecTable = NULL;
	pNewEndSecTable = NULL;
	pNewSecStarPosition = NULL;
	pTemSectionHeader = NULL;
	pPreSectionHeader = NULL;
    	pNewFileBuffer = NULL;
	pDOSHeader = NULL;
	pNTHeaders = NULL;
	pPEHeader = NULL;
	pOptionHeader = NULL;
	pSectionHeader = NULL;
	pExportTable = NULL;
	pImportTable = NULL;
	pImportBondTable = NULL;
	pBondRef = NULL;
	functionAddress = NULL;
	orderAddress = NULL;
	functionName = NULL;
	pName = NULL;

	free(pFileBuffer);
	pFileBuffer = NULL;

}

VOID SetNewFileName(IN LPSTR OldFilePath)
{
	/* 
		���ݴ�����ļ�·�� 
		��ԭ·������λһ���µ��ļ�·��(�������ļ���)
	*/

	if (!OldFilePath)
	{
		// ֵΪ���򷵻�
		return;
	}

	DWORD strLength = strlen(OldFilePath);
	LPSTR pOldFileName = NULL;

	// �ҵ����һ�� '\' �ĺ�һ���ֽڵ�λ��
	for (UINT i = 0; i < strLength; i++)
	{
		if (*OldFilePath++ == '\\')
		{
			pOldFileName = OldFilePath;
		}
	}
	
	char OldFileName[80] = {0};
	// ����ɵ��ļ����� OldFileName ��
	strcpy(OldFileName, pOldFileName);
	
	// ����ַ��� 'New' �� '\' ��
	strcpy(pOldFileName, "New");
	pOldFileName += 3;
	
	// ƴ�ӵõ�����·��
	strcpy(pOldFileName, OldFileName);

	return;
}

int main(int argc, char* argv[])
{
	printf("�����벻�����ո���ļ�·��: \n");
	scanf("%s", f);
 	strcpy(write_file_path, f);
	SetNewFileName(write_file_path);
	
	printHeaders();

	system("pause");
	return 0;
}





//ͷ��СС���ڴ����ʱ���ھʹ� �ڴ�����С��ʼ
//��ͷ��С�����ڴ����ʱ����ͷ��С%�ڴ��С��(��� + 1) * �ڴ��С��
//�������ж�Misc��Misc��ֵ�Ĵ�С�Ƿ񳬹��ڴ���룬�������ɵĺ�����һ��