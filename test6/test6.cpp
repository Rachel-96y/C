#include "stdafx.h"

void func_1()
{
	// ������������ֵ����
	int i = 2;
	int j = 3;
	i = i + j;
	j = i - j;
	i = i - j;
	printf("%d__%d", i, j);
}

void func_2()
{
	// ��һ�������е����������
	int arr[5] = {1, 2, 3, 4, 5};
	for (int i = 4; i >= 0; i--)
	{
		printf("%d", arr[i]);
	}
}

int func_3()
{
	// �ҳ�������������ֵ,������
	int arr[5] = {3, 9, 3, 7, 5};
	int temp = arr[0];
	for (int i = 0; i < 5; i++)
	{
		if (temp < arr[i])
		{
			temp = arr[i];
		}
	}

	return temp;
}

int func_4()
{
	// ���������е�Ԫ�����,���������
	int arr[5] = {3, 9, 3, 7, 5};
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += arr[i];
	}

	return sum;
}

void func_5()
{
	/* �������ȳ�������ͬλ�õ�ֵ���
	 �洢������һ���ȳ������� */
	int arr_1[5] = {2, 3, 9, 5, 4};
	int arr_2[5] = {7, 8, 5, 2, 6};
	int arr[5];
	for (int i = 0; i < 5; i++)
	{
		arr[i] = arr_1[i] + arr_2[i];
	}
}

int func_6(int x)
{
	// ��� x �������򷵻�1,���򷵻�0
	for (int i = 2; i < x; i++)
	{
		if (x % i == 0)
		{
			// ����1�ͱ������⻹��������������
			return 0;
		}
	}
	return 1;
}

void func_7()
{
	// �����Ƚ������ֵ��������һ���洢����������һ��λ��
	int arr[5] = {2, 3, 9, 5, 4};
	for (int i = 0; i <5; i++)
	{
		if (arr[i] > arr[i + 1])
		{
			// ��ʹ���м������н���
			arr[i] = arr[i] + arr[i + 1];
			arr[i + 1] = arr[i] - arr[i + 1];
			arr[i] = arr[i] - arr[i + 1];
		}
	}
	printf("%d\n", arr[4]);
	
}

void func_8()
{
	// ��д����ʵ��һ��ð��������㷨
	int arr[5] = {7, 2, 4, 9, 3};
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (arr[i] > arr[j])
			{
				arr[i] = arr[i] + arr[j];
				arr[j] = arr[i] - arr[j];
				arr[i] = arr[i] - arr[j];
			}
		}
	}

	for (int x = 0; x < 5; x++)
	{
		printf("%d\n", arr[x]);
	}
}

int func_9()
{
	// �ж������Ƿ��ǶԳƵģ�����Ƿ���1�����Ƿ���0
	int arr[5] = {6, 3, 4, 3, 6};
	for (int i = 0; i < 2; i++)
	{
		for (int j = 4 - i; j + i == 4; j--)
		{
			if (arr[i] != arr[j])
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	// func_1();
	// func_2();
	// int num = func_3();
	// int num = func_4();
	// func_5();
	// int x = func_6(5);
	// func_7();
	// func_8();
	// int x = func_9();

	return 0;
}