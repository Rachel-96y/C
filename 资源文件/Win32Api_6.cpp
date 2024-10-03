// Win32Api_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

char PATH[80];

BOOL Modification(LPVOID pFileBuffer)
{
	/*
		�޸ĶԻ������
	*/

	return NULL;
}

BOOL ExtractionIcon(LPVOID pFileBuffer)
{
	/*
		��ȡͼ��
	*/

	return NULL;
}

BOOL PrintResource(LPVOID pFileBuffer)
{
	/*
		��ӡ��Դ����Ϣ
	*/

	// ����DOSͷ�ṹ��ָ��
	PIMAGE_DOS_HEADER pIMAGE_DOS_HEADER = (IMAGE_DOS_HEADER*)pFileBuffer;

	// ����NTͷ�ṹ��ָ��
	PIMAGE_NT_HEADERS32 pIMAGE_NT_HEADERS32 = (IMAGE_NT_HEADERS32*)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew);

	// �����׼PEͷ�ṹ��ָ��
	PIMAGE_FILE_HEADER pIMAGE_FILE_HEADER = (IMAGE_FILE_HEADER*)((DWORD)pIMAGE_NT_HEADERS32 + sizeof(pIMAGE_NT_HEADERS32 -> Signature));

	// �����ѡPEͷ�ṹ��ָ��
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL_HEADER32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pIMAGE_FILE_HEADER + IMAGE_SIZEOF_FILE_HEADER); 

	// ����ڱ�ṹ��ָ��
	PIMAGE_SECTION_HEADER pIMAGE_SECTION_HEADER = (IMAGE_SECTION_HEADER*)((DWORD)pIMAGE_OPTIONAL_HEADER32 + pIMAGE_FILE_HEADER -> SizeOfOptionalHeader);

	// �ж�DOS_MZͷ�Ƿ���Ч
	if (pIMAGE_DOS_HEADER -> e_magic != IMAGE_DOS_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ṹ: �����MZͷ��־");
		return NULL;
	}

	// �ж�PE��ʶ�Ƿ���Ч
	if (*(LPDWORD)((DWORD)pIMAGE_DOS_HEADER + pIMAGE_DOS_HEADER -> e_lfanew) != IMAGE_NT_SIGNATURE)
	{
		printf("�ⲻ��һ����Ч��PE�ṹ: �����PE��־");
		return NULL;
	}

	// ��������Ŀ¼�ṹ��ָ��
	PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)(pIMAGE_OPTIONAL_HEADER32 -> DataDirectory);

	// ������Դ��ṹ��ͷ��ָ��
	PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY = (IMAGE_RESOURCE_DIRECTORY*)(ChangeRvaToFoa((pIMAGE_DATA_DIRECTORY + 2) -> VirtualAddress, pFileBuffer) + (DWORD)pFileBuffer);

	// �ҵ��ж��ٸ���ͬ����Դ����
	DWORD dwNumberOfTypes = pIMAGE_RESOURCE_DIRECTORY -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY -> NumberOfNamedEntries;

	// ���û���κ�������ֱ�ӷ���
	if (dwNumberOfTypes == 0x0000FFFF || *(LPWORD)pIMAGE_RESOURCE_DIRECTORY == IMAGE_DOS_SIGNATURE)
	{
		// ������������� 0xFFFF ����Դ��ṹ��ͷ��ָ�� ��ַ�е�ֵ�� DOS ͷ���(0x4d5a) �����û����Դ
		printf("û����Դ!\n");
		return NULL;
	}

	// ������Դ����ָ��
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY + 1);
	do
	{ 
		// �����ж����ֲ�ͬ����Դ����

		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameIsString)
		{
			// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���͵�ID
			printf("******************************************************\n");
			printf("��Դ����(ID):%d\t", pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset);
			switch(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset)
			{

			case RT_CURSOR:
				{
					printf("(���)\n");
					break;
				}
			case RT_BITMAP:
				{
					printf("(λͼ)\n");
					break;
				}
			case RT_ICON:
				{
					printf("(ͼ��)\n");
					break;
				}
			case RT_MENU:
				{
					printf("(�˵�)\n");
					break;
				}
			case RT_DIALOG:
				{
					printf("(�Ի���)\n");
					break;
				}
			case RT_STRING:
				{
					printf("(�ַ�����)\n");
					break;
				}
			case RT_FONTDIR:
				{
					printf("(����Ŀ¼)\n");
					break;
				}
			case RT_FONT:
				{
					printf("(����)\n");
					break;
				}
			case RT_ACCELERATOR:
				{
					printf("(��������)\n");
					break;
				}
			case RT_RCDATA:
				{
					printf("(�Զ�����Դ)\n");
					break;
				}
			case RT_MESSAGETABLE:
				{
					printf("(��Ϣ��)\n");
					break;
				}
			case RT_GROUP_CURSOR:
				{
					printf("(ͼ����)\n");
					break;
				}
			case RT_GROUP_ICON:
				{
					printf("(�����)\n");
					break;
				}
			case RT_DLGINCLUDE:
				{
					printf("(��ȡ��Դ)\n");
					break;
				}
			case RT_VERSION:
				{
					printf("(�汾��Ϣ)\n");
					break;
				}
			case RT_PLUGPLAY:
				{
					printf("(���弴����Դ)\n");
					break;
				}
			case RT_VXD:
				{
					printf("(VXD)\n");
					break;
				}
			case RT_ANICURSOR:
				{
					printf("(��̬���)\n");
					break;
				}
			case RT_ANIICON:
				{
					printf("(��̬ͼ��)\n");
					break;
				}
			case RT_HTML:
				{
					printf("(HTML�ĵ�)\n");
					break;
				}
			default:
				{
					printf("(δ֪��Դ����)\n");
				}
			};
		}
		else
		{
			// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ���;����Զ���� ��һ���ַ���
			PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

			// ��Դ���͵��ַ�������
			DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

			// ��Դ���͵���ʼλ��
			PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

			printf("��Դ����(����): ");
			do
			{
				printf("%s", StringOfResource);
				StringOfResource += 2;
			}
			while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
			printf("\n");
		}
		
		// ��ʼ������һ��(���)
		if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY -> DataIsDirectory)
		{
			// �����λ��0
			printf("����һ������0\n");
		}
		else
		{
			// �����λ��1 �ҵ���һ��Ŀ¼�ڵ����ʼλ�� (��ŵ���ʼ��ַ)
			PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_Digit = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY -> OffsetToDirectory);
			
			// �������
			DWORD dwNumberOfDigit = pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_Digit -> NumberOfNamedEntries;

			// �ҵ��ڶ������Դ�������
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_Digit + 1);
			do
			{
				if (!pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameIsString)
				{
					// �����λΪ0 ���4���ֽڵĺ�31λ���� ��Դ���
					printf("��Դ�����:%d\n", pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset);
				}	
				else
				{
					// �����λΪ1 ��ָ�� _IMAGE_RESOURCE_DIR_STRING_U �ṹ ��Դ��ž����Զ���� ��һ���ַ���
					PIMAGE_RESOURCE_DIR_STRING_U pIMAGE_RESOURCE_DIR_STRING_U = (IMAGE_RESOURCE_DIR_STRING_U*)(pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> NameOffset + (DWORD)pIMAGE_RESOURCE_DIRECTORY);

					// ��Դ���͵��ַ�������
					DWORD IMAGE_RESOURCE_DIR_STRING_U_Length = pIMAGE_RESOURCE_DIR_STRING_U -> Length;

					// ��Դ���͵���ʼλ��
					PTCHAR StringOfResource = (PTCHAR)(&pIMAGE_RESOURCE_DIR_STRING_U -> NameString);

					printf("��Դ���(����): ");
					do
					{
						printf("%s", StringOfResource);
						StringOfResource += 2;
					}
					while(--IMAGE_RESOURCE_DIR_STRING_U_Length);
					printf("\n");
				}

				// �ҵ�����ҳ
				PIMAGE_RESOURCE_DIRECTORY pIMAGE_RESOURCE_DIRECTORY_CodePage = (IMAGE_RESOURCE_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element -> OffsetToDirectory);

				// ����ҳ����
				DWORD dwNumberOfCodePage = pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfIdEntries + pIMAGE_RESOURCE_DIRECTORY_CodePage -> NumberOfNamedEntries;
				// �ҵ�������Ĵ���ҳ����
				PIMAGE_RESOURCE_DIRECTORY_ENTRY pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pIMAGE_RESOURCE_DIRECTORY_CodePage + 1);
				do
				{
					// printf("������� DataIsDirectory :%d\n", pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> DataIsDirectory);

					printf("����ҳ:%d", pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset);
					switch (pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> NameOffset)
					{
					case 1033:
						{
							printf("(Ӣ��)\n");
							break;
						}
					case 2052:
						{
							printf("(����)\n");
							break;
						}
					default:
						{
							printf("(��������)\n");
						}
					};
					// �ҵ��ڵ�
					PIMAGE_DATA_DIRECTORY pIMAGE_DATA_DIRECTORY = (IMAGE_DATA_DIRECTORY*)((DWORD)pIMAGE_RESOURCE_DIRECTORY + pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage -> OffsetToDirectory);
					
					printf("Rva: %x\n", pIMAGE_DATA_DIRECTORY -> VirtualAddress);
					printf("OffSet: %x\n", ChangeRvaToFoa(pIMAGE_DATA_DIRECTORY -> VirtualAddress, pFileBuffer));
					printf("Size: %x\n\n", pIMAGE_DATA_DIRECTORY -> Size);
					
					pIMAGE_RESOURCE_DIRECTORY_ENTRY_CodePage++;
				}
				while(--dwNumberOfCodePage);

				// �ҵ���һ����Դ��ŵ���ʼλ��
				pIMAGE_RESOURCE_DIRECTORY_ENTRY_Digit_Element++;
			}
			while(--dwNumberOfDigit);
			
		}
		
		// �ҵ���һ����Դ���͵���ʼλ��
		pIMAGE_RESOURCE_DIRECTORY_ENTRY++;
	}
	while(--dwNumberOfTypes);
}

int main(int argc, char* argv[])
{
	/*
		��ϰ��
			1����д���򣬶�λĳ����Դ��PE�ļ��е�λ��.
			2����д������ȡ����ͼ����Դ.(��ʱ����)
			3����д�����޸ĶԻ������.(��ʱ����)
	*/
	
	printf("�����벻�����ո���ļ�·��: \n");
	scanf("%s",PATH);

	// �����ļ���С����һ���ڴ�
	LPVOID pFileBuffer = CreateFileBuffer(PATH);

	// �� PE �ļ���ȡ�� FileBuffer �� ����ֵ���ļ���ʵ�ʴ�С
	DWORD SIZE_OF_FILE_BUFFER = ReadPeFileToFileBuffer(PATH, pFileBuffer);

	// ��ӡָ���������Դ��
	PrintResource(pFileBuffer);

	// ��ȡָ�������ͼ����Դ
	// ExtractionIcon(pFileBuffer);

	// �޸�ָ������ĶԻ������
	// Modification(pFileBuffer);
	
	system("pause");

	return 0;
}