#include "stdafx.h"


void Function()					
{					
	int arr[5] = {1,2,3,4,5};				
					
	//..�˴���Ӵ��룬ʹ��ָ�룬�������ֵ����
	int temp;
	int* p = &arr[0];
	for(int i = 0, j = 4; i != j; i++, j--)
	{
		temp = *(p + i);
		*(p + i) = *(p + j);
		*(p + j) = temp;
	}
					
	//��ӡ����ֵ�Ĵ����Ѿ�д�꣬����Ҫ�޸�				
	for(int k = 0; k < 5; k++)				
	{				
		printf("%d\n",*(p+k));			
	}				
}

int main()
{ 
	Function();
	return 0;
}