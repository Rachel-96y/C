// X_Main_1.cpp : Defines the entry point for the console application.
//



/*
������ϰ		
		
1������һ����̬���ӿ⣬���ڴ�����ʹ��.		
		
2������һ����̬���ӿ⣬ʹ�����ַ�ʽ���е���(_declspec(dllexport)��.def�ļ�).		
		
3���ֱ�ʹ����ʽ���Ӻ���ʾ����ʹ��һ��DLL�ļ�.		
*/



/*
#include "stdafx.h"

#pragma comment(lib, "Static_Library_test_1.lib")

int main(int argc, char* argv[])

{	// ��̬���ӿ�ʹ��
	int a = function(1, 2, 3);
	printf("%d\n", a);
	getchar();
	return 0;
}
*/



/*
#include "stdafx.h"

extern "C" __declspec(dllimport) int __stdcall function(int x, int y, int z);

#pragma comment(lib, "Dynamic_Link.lib")

int main(int argc, char* argv[])

{	// ��̬���ӿ���ʽ����
	int a = function(1, 2, 3);
	printf("%d\n", a);
	getchar();
	return 0;
}
*/




#include "stdafx.h"

int main(int argc, char* argv[])
{
	// ��̬���ӿ���ʽ���� 

	// ����Ҫʹ�õ�ģ�����뵱ǰEXE���ڴ�
	HMODULE Hmodule = LoadLibrary("C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\Dynamic_Link_2.dll");

	// ��̬��ȡ��Ҫʹ�õĺ����ĵ�ǰ��ַ
	FARPROC FunctionAddress = GetProcAddress(Hmodule, "Sub");

	// ���庯��ָ�벢��ֵ
	int (__stdcall *pFunction)(int, int) = (int (__stdcall *)(int, int))FunctionAddress;

	int result = pFunction(5, 2);
	printf("%d\n", result);
	getchar();
	return 0;
}

