#include "stdafx.h"

void function()
{
	// Ͱ����
	int arr[10] = {4, 3, 5, 6, 5, 3, 7, 8, 9, 2};  // ԭ����
	int arr_2[10] = {0};  // 10Ϊ���������ֵ��1
	int arr_3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // ��־����
	int arr_4[10]; // Ŀ������
	

	for (int i = 0; i < 10; i++)
	{
		arr_2[arr[i]]++;    // �õ�arr_2 
	}  

	/*

		{4, 3, 5, 6, 5, 3, 7, 8, 9, 2}  ԭ���� arr

		{0, 0, 1, 2, 1, 2, 1, 1, 1, 1}  arr_2
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}  ��־���� arr_3

		{                            }  arr_4 Ŀ������
	
	*/



	for (int j = 0, k = 0; j < 10; j++)
	{
		if (arr_2[j] == 0)
		{
			continue;
		}
		for (int z = 0; z < arr_2[j];z++)
		{
		arr_4[k++] = arr_3[j];  // �ؼ�����
		}
	}



	for (int num = 0; num < 10; num++)
	{
		printf("%d\n", arr_4[num]);
	}  
	// ��ӡĿ������������ֵ
}

int main(int argc, char* argv[])
{
	function();
	return 0;
}

