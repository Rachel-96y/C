
#if !defined(This_is_about_the_identifier_of_the_structure_DataOfFile__AroundTheWorld__C)
#define This_is_about_the_identifier_of_the_structure_DataOfFile__AroundTheWorld__C

typedef struct DataOfFile
{	
	unsigned int SizeOfFile;  // �ļ���С ��λ �ֽ�

	_iobuf* FileStream;  // Դ�ļ�ָ��

	_iobuf* WriteFileStream;  // Ŀ���ļ�ָ��

}Data;

#endif




Data* GetFileSize(char* PATH);  // ��ȡ�ļ���С

char* RequestMemory(int fileSize);  // ���������ֵ�����ڴ�

char* ReadFileToMemory(char* pMemory, unsigned int SizeOfFile,  unsigned int ReadSizeMax, _iobuf* pFileStream);
// ��ȡ�ļ��������ݵ�ָ�����ڴ�ռ�

void FreeMemory(char* pMemory); // ����ָ���ͷ��ڴ�

int CloseFileStream(_iobuf* pFileOpen);  // ����ָ��ر��ļ���

int WriteMemoryToNewFile(char* pMemory, unsigned int SizeOfFile, unsigned int ReadSizeMax, char* PATH); 
 // �����е�����д�뵽Ӳ�̵�ָ��λ��

void PrintFormatOfPe(unsigned int number, char* pMemoryAddress);  // ��ʽ����ӡPE�ļ������� 