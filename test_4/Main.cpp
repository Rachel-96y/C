#include <stdio.h>

#pragma pack(1)   //�����趨������N�ֽڽ��ж���
struct test_1{
	char x1;
	int x2;
};
#pragma pack()

void main()
{
	test_1 a = {1,2};
	printf("%d\n", sizeof(a));  //Ĭ��������ֽڶ����ʹ�õĿռ���:8�ֽ�   
	return;      //�ṹ���ܴ�С��N�ı���   N = Min(����Ա,�������)
}

