#include "stdafx.h"
#include "myfunctions.h"

/*
������ϰ��						
				
			
1����ʮ�������ı��༭������һ�����±���.exe�ļ����ٴ����ڴ��еļ��±�						
���̣���¼���������ļ��Ĳ�ͬ.						
			
2�������±���.exe�ļ���ȡ���ڴ棬�����ض�ȡ�����ڴ��еĵ�ַ.						
				
3�����ڴ��е����ݴ洢��һ���ļ��У�(.exe��ʽ)��Ȼ��˫���򿪣����Ƿ��ܹ�ʹ��.						
				
				
1�����ļ�						
				
2���õ��ļ��Ĵ�С						
				
3�������ڴ�						
				
4�����ļ��е����ݶ�ȡ���ڴ��� 						
				
5�������ڴ���	


1��fopen����

2��fseek����

3��ftell����

4��fclose����

5��fread����


*/


// 1����ʮ�������ı��༭������һ�����±���.exe�ļ����ٴ����ڴ��еļ��±�						
// ���̣���¼���������ļ��Ĳ�ͬ.
// ǰ��Ĳ��ֶ�����ͬ��  ����Ĳ����ڴ��еļ��±��հײ��ָ���  ���ݱ�������


int main(int argc, char* argv[])
{
	Data* FileSizeResult = GetFileSize("D:\\study\\C_X86\\HD\\���\\6(��־�Ĵ���)\\2015-01-19\\��ҵ\\NEW_CRACKME.EXE");  
	// ��ָ�����ļ��� FileSizeResult Ϊ��ȡ���ļ���С

	char* pMemory = RequestMemory(FileSizeResult -> SizeOfFile);  // ��������ռ������ڴ�

	char* pMemoryAddress = ReadFileToMemory(pMemory, sizeof(char), \
		FileSizeResult -> SizeOfFile, FileSizeResult -> FileStream);  // ���ļ��е����ݶ�ȡ���ڴ��в������ڴ���

	if (pMemoryAddress == NULL)
	{
		printf("�ļ���ȡʧ��\n");
	}
	else
	{
		printf("�ļ���ȡ�ɹ�,�����ڴ��ַ�ı����: %x\n", pMemoryAddress);
	}
	
	CloseFileStream(FileSizeResult -> FileStream);  // �رն��ļ����ܵ�

	// ------------------ BEGIN �����������޸�PE�ļ�������------------------

	// PrintFormatOfPe(FileSizeResult -> SizeOfFile, pMemoryAddress);  // ��ӡ�ڶ��е�PE�ļ�����


	// ------------------ END �����������޸�PE�ļ�������------------------
	/* 
	int result = WriteMemoryToNewFile(pMemoryAddress, sizeof(char), FileSizeResult->SizeOfFile, \
		"C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\new.exe");  // ��������д�뵽�ļ�
	
	if (result)
	{
		printf("������д���ļ�����\n");
	}
	else
	{
		printf("������д���ļ��ɹ�\n");
	}

	CloseFileStream(FileSizeResult->WriteFileStream);  // �ر�д�ļ����ܵ�
	*/

	getchar(); // δ�ͷ��ڴ�ռ��ʱ��,��ʱPE�ļ��ڴ�δ����

	FreeMemory(pMemory);  // �ͷŶѿռ� ��ʼ����ָ��

	pMemoryAddress = NULL;  // ��ʼ��ָ���ֵ

	getchar();

	return 0;
}