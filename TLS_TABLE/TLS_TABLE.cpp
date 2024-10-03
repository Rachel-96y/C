// TLS_TABLE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

DWORD PrintTLS(LPVOID lpFileBuffer)
{
	// ��ӡ32λ��TLS��

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)lpFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// �����ж�PE�ļ��Ƿ���TLS��
	if (!(pIMAGE_DATA_DIRECTORY + 9) -> VirtualAddress)
	{
		printf("��PE�ļ�û��TLS��");
		return RETURN_FAILURE;
	}

	// ��ӡTLS��RVA����С
	printf("TLS������λ��RVA:%x\nTLS���С:%x\n", (pIMAGE_DATA_DIRECTORY + 9) -> VirtualAddress, (pIMAGE_DATA_DIRECTORY + 9) -> Size);

	// ����TLS��ṹ��ָ��
	PIMAGE_TLS_DIRECTORY32 pIMAGE_TLS_DIRECTORY32 = (IMAGE_TLS_DIRECTORY32*)(ChangeRvaToFoa32((pIMAGE_DATA_DIRECTORY + 9) -> VirtualAddress, lpFileBuffer) + (DWORD)lpFileBuffer);
	
	// TLS������
	printf("��ʼ�����ݵ���ʼ��ַ:%x\n", pIMAGE_TLS_DIRECTORY32 -> StartAddressOfRawData);
	printf("��ʼ�����ݵĽ�����ַ:%x\n", pIMAGE_TLS_DIRECTORY32 -> EndAddressOfRawData);
	printf("����λ��:%x\n", pIMAGE_TLS_DIRECTORY32 -> AddressOfIndex);
	printf("�ص���������ָ��:%x\n", pIMAGE_TLS_DIRECTORY32 -> AddressOfCallBacks);
	printf("���0�ĸ���:%x\n", pIMAGE_TLS_DIRECTORY32 -> SizeOfZeroFill);
	printf("�����ֶ�:%x\n", pIMAGE_TLS_DIRECTORY32 -> Characteristics);

	DWORD dwNumber = 0;
	printf("����������һ��׼ȷ\n");
	// TLS��ص�������ַ
	do
	{
		printf("������ַ�洢λ��: %x\n", pIMAGE_TLS_DIRECTORY32 -> AddressOfCallBacks + dwNumber);
	}
	while(*(pIMAGE_TLS_DIRECTORY32 -> AddressOfCallBacks + ++dwNumber));

	return RETURN_SUCCESS;
}

int main(int argc, char* argv[])
{
	// ��ӡTLS�� (����Ŀ¼�е�10��[�±�Ϊ9])
	LPVOID lpFileBuffer = NULL;
	IsPeFile(PATH, &lpFileBuffer);
	PrintTLS(lpFileBuffer);

	system("pause");
	return 0;
}