// B_CPP_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct TestStruct
{

private:

	int x;
	int y;

	void MyFunction()
	{
		printf("MyFunction ִ����\nx:%d y:%d", x, y);
	}

public:

	void SetNumber(int x, int y)
	{
		this -> x = x;
		this -> y = y;
	}

}TS, *PTS;


int main(int argc, char* argv[])
{
	/* 
		ʹ��ָ����з����ڽṹ���е�
		���ó�˽�����Եĳ�Ա��������Ա���� 
	*/

	TestStruct Test;
	Test.SetNumber(2, 3);
	LPDWORD pTest = (LPDWORD)&Test;
	printf("%d\n%d\n", *pTest, *(pTest + 1));


	void(__cdecl *pFunc)(void) = (void(__cdecl *)(void))&Test.MyFunction;
	pFunc();

	getchar();
	return 0;
}