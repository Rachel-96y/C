#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>

char* function(void)
{
	/* ʹ��malloc�ڶ��ж�̬�����ڴ� */

	int* pMemory = (int*)malloc(sizeof(int)*128);

	if (pMemory == NULL)  // �ж��Ƿ�ѿռ�����ɹ�
	{
		exit(0);  // ����Ϊ0������ȷ�˳�
	}

	void* pMemset = memset(pMemory, 0xCCCCCCCC, sizeof(int)*128);  // ��ʼ��Ҫʹ�õĿռ�

	char* pArrayFirstMemory = (char*)(pMemory + 5);  // ����һ��char*���͵�ָ�� ָ���pMemory���20��int��λ��

	char (*pArray)[2] = (char (*)[2])pArrayFirstMemory;  // ��������ָ�� ֵΪpArrayFirstMemory

	for (int i = 0; i < 10; i++)
	{
		*(pArrayFirstMemory + i) = i;   // Ϊ���鸳ֵ  0 - 9
	}

	*(pArrayFirstMemory + i) = 0x00;  // ������־

	i = 0; // ��ʼ��i

	do
	{
		printf("%d\n", *(*(pArray + 0) + i++));
	}
	while (*(*(pArray + 0) + i));

	free(pMemory);  // �ͷſռ�

	pMemory = NULL;  //��ָ����Ϊ NULL

	return pArrayFirstMemory;
}

int main(int argc, char* argv[])
{
	char* pArrayFirstMemory = function();

	return 0;
}