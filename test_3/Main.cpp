//����Ҳ�������Ǻڿ�: (��gcc����vc6�±���)(32λ)

#include <stdio.h>

void func_2(){
	printf("���Ͱ�!\n");
	return;
}

void func_1(){
	int arr[10];
	arr[11] = (int)&func_2;   //����ebp+4��ֵ
	return;
}

void main()
{
	func_1();
	return;
}