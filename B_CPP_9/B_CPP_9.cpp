// B_CPP_9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct MyStruct
{
	int x;
	int y;
	
	MyStruct()
	{
		x = 5;
		y = 6;
	}

	bool operator>(const MyStruct& p)
	{
		if ((this -> x > p.x) && (this -> y > p.y))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	MyStruct operator=(const MyStruct& p)
	{
		this -> x = p.x;
		this -> y = p.y;
		return *this;
	}

} MS, *PMS; 

template <class Exchange> VOID WINAPI swap(Exchange x, Exchange y)
{
	Exchange temp = x;
	x = y;
	y = temp;
}
	
template <class Generics, class OldGenerics> void Sort(Generics arr, int nLength, OldGenerics temp)				
{				
	int i;			
	int k;			
	for(i = 0; i < nLength - 1; i++)			
	{			
		for(k = 0; k < nLength - 1 - i; k++)		
		{		
			if(arr[k] > arr[k + 1])	
			{	
				temp = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = temp;
			}
		}		
	}			
}			
		
template <class T> void Print(T arr, int nLength)				
{				
	int i;			
	for(i = 0; i < nLength; i++)			
	{			
		printf("%d\n", arr[i]);		
	}			
}				

template <class T, class E> int Find(T arr, int nLength, E nElement)						
{						
	int nBegin = 0, nEnd = nLength - 1, nIndex;					
	while(nBegin <= nEnd)					
	{					
		nIndex = (nBegin + nEnd) >> 1; // (nBegin+nEnd) / 2				
		if(nElement > arr[nIndex])				
		{				
			nBegin = nIndex + 1;			
		}				
		else if(nElement < arr[nIndex])				
		{				
			nEnd = nIndex - 1;			
		}				
		else				
		{				
			return nIndex;			
		}				
	}					
	return 0xFFFFFFFF;					
}						


int main(int argc, char* argv[])
{
	/*
		������ϰ��
			1��ʹ��ģ��ʵ�� swap(x, y) ���������ܣ����� x, y ��ֵ.
			2��ð�����򣺶Խṹ���������������������ʵ�֣��ҳ���������.
			3��ʵ��һ���ܹ����������ͽ����۰���ҵĺ���(������).
			(����޷�ʵ�֣����ҳ������������)
			4���۲���������Sort�����ķ�������(���ڴ��ַ������)��
			int arr[] = {2, 6, 1, 5, 4};
			char arr1[] = {2, 6, 1, 5, 4};
			Sort(arr, 5);
			Sort(arr1, 5);
	*/

	MS A, B, C, D;
	MS StructArr[4] = {A, B, C, D};
	int MyArr[] = {1, 2, 5, 6, 7, 8, 9, 10};
	Sort(&StructArr[0], sizeof(StructArr) / sizeof(StructArr[0]), *StructArr);
	Print(StructArr, sizeof(StructArr) / sizeof(StructArr[0]));

	// Find(StructArr, sizeof(StructArr) / sizeof(StructArr[0]), StructArr[1]);
	// int result = Find(MyArr, sizeof(MyArr) / sizeof(MyArr[0]), 12);
	// printf("�±���: %d\n", result);

	getchar();
	return 0;
}