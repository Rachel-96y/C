// B_CPP_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


typedef struct DateInfo
{
	int year; 
	int month;
	int day;

	DateInfo(int year, int month, int day)
	{
		this -> year = year;
		this -> month = month;
		this -> day = day;
	}

	DateInfo()
	{
		year = 2015;
		month = 4;
		day = 2;
	}

	void SetDay(int day)
	{
		this -> day = day;
		return;
	}

	int GetDay()
	{
		return day;
	}

	void SetMonth(int month)
	{
		this -> month = month;
		return;
	}

	int GetMonth()
	{
		return month;
	}
	
	void SetYear(int year)
	{
		this -> year = year;
		return;
	}
	
	int GetYear()
	{
		return year;
	}
	
} DI, *PDI;


typedef struct TimeInfo : DateInfo
{
	int Hour;
	int minute;
	int second;

	TimeInfo(int time, int minute, int second)
	{
		this -> Hour = Hour;
		this -> minute = minute;
		this -> second = second;
	}

	TimeInfo()
	{
		Hour = 23;
		minute = 13;
		second = 45;
	}

	int GetHour()
	{
		return Hour;
	}
	
	int GetMinute()
	{
		return minute;
	}

	int GetSecond()
	{
		return second;
	}

} TI, *PTI; 


typedef struct MyString
{
	LPVOID pFileBuffer;
	BYTE String[100];

	MyString(UINT SizeOfFileBuffer)
	{
		pFileBuffer = malloc(sizeof(CHAR) * SizeOfFileBuffer);
	}

	MyString()
	{
		pFileBuffer = malloc(sizeof(CHAR) * 1024);
	}

	~MyString()
	{
		free(pFileBuffer);
	}

	void SetString(LPSTR String)
	{
		strcpy((LPSTR)this -> String, String);
		return;
	}

	void PrintString()
	{
		printf("String: %s\n", String);
		return;
	}

	void AppendString(LPSTR String)
	{
		LPSTR pTemp = (LPSTR)this -> String;
		while(*pTemp++);
		strcpy(--pTemp, String);
		return;
	}
	
	int Size()
	{
		return sizeof(String);
	}

} MS, *PMS;


void Run()
{
	TI MyTimeInfo;
	PTI pMyTimeInfo = &MyTimeInfo;
	pMyTimeInfo -> year;
	pMyTimeInfo -> month;
	pMyTimeInfo -> day;
	pMyTimeInfo -> Hour;
	pMyTimeInfo -> minute;
	pMyTimeInfo -> second;

	PDI pMyDateInfo = &MyTimeInfo;
	pMyDateInfo -> year;
	pMyDateInfo -> month;
	pMyDateInfo -> day;

	return;
}


LPVOID Test(int whoami)
{
	MS MyStr_1(200);

	*(LPDWORD)MyStr_1.pFileBuffer = 0x12345678;
	MyStr_1.SetString("MyCode_1");
	MyStr_1.PrintString();
	MyStr_1.AppendString("HelloWorld");
	MyStr_1.PrintString();
	int result_1 = MyStr_1.Size();
	printf("%d\n", result_1);

	MS MyStr_2;

	*(LPDWORD)MyStr_2.pFileBuffer = 0x12345678;
	MyStr_2.SetString("MyCode_2");
	MyStr_2.PrintString();
	MyStr_2.AppendString("HelloWorld");
	MyStr_2.PrintString();
	int result_2 = MyStr_2.Size();
	printf("%d\n", result_2);

	if (!whoami)
	{
		return MyStr_1.pFileBuffer;
	}
	else
	{
		return MyStr_2.pFileBuffer;
	}	
}

int main(int argc, char* argv[])
{
	/*
		������ϰ��							
							
			1	���һ���ṹ DateInfo Ҫ������������Ҫ��							
   										
				(1) ��������Ա�� int year; int month; int day;							
				(2) Ҫ���и��������Ĺ��캯����������ֱ�Ϊ��Ӧ�ꡢ�¡��ա�							
				(3) ��һ���޲����Ĺ��캯�������ʼ���ꡢ�¡��շֱ�Ϊ��2015��4��2��							
				(4) Ҫ����һ����Ա����ʵ�����ڵ�����: SetDay(int day)							
				(5) Ҫ����һ����Ա����ʵ�����ڵĻ�ȡ: GetDay()							
				(6) Ҫ����һ����Ա����ʵ����ݵ�����: SetYear(int year)							
				(7) Ҫ����һ����Ա����ʵ����ݵĻ�ȡ: GetYear()							
				(8) Ҫ����һ����Ա����ʵ���·ݵ�����: SetMonth(int month)							
				(9) Ҫ����һ����Ա����ʵ���·ݵĻ�ȡ: GetMonth()							
										
										
			2	���һ���ṹ TimeInfo Ҫ������������Ҫ��							
				(1) �ýṹ�а�����ʾʱ���ʱ���֡��롣							
				(2) ���øýṹ��ʱ���֡���ĺ�����							
				(3) ��ȡ�ýṹ��ʱ���֡�������������� GetHour(), GetMinute() �� GetSecond()							
										
										
			3	�� TimeInfo �̳� DateInfo �ֱ�ʹ�� DataInfo �� TimeInfo ��ָ����� TimeInfo							
				����ĳ�Ա.							
										
			4	���һ���ṹ���� MyString ��Ҫ��ýṹ�ܹ�������¹��ܣ�							
				(1) ���캯���ܹ�����ʵ�ʴ���Ĳ�������ʵ�ʴ洢�ռ䣻							
				(2) �ṩһ���޲εĹ��캯����Ĭ�Ϸ����СΪ 1024 ���ֽڣ�							
				(3) ���������ͷŸÿռ䣻							
				(4) ��д��Ա���� SetString �����Խ�һ���ַ�����ֵ���ýṹ��							
				(5) ��д��Ա���� PrintString �����Խ��ýṹ�����ݴ�ӡ����Ļ�ϣ�							
				(6) ��д��Ա���� AppendString �����������е����ݺ���������ݣ�							
				(7) ��д��Ա���� Size �����ڵõ���ǰ���ݵ���ʵ���ȡ�							
				��д���Գ��򣬲�������ṹ��							

	*/
	
	Run();

	LPVOID pFileBuffer = Test(0);
	if (*(LPDWORD)pFileBuffer == 0xDDDDDDDD)
	{
		printf("������ MyStr_1.pFileBuffer / MyStr_1����������ִ�гɹ�!\n*(LPDWORD)pFileBuffer: %x\n", *(LPDWORD)pFileBuffer);
	}
	else
	{
		printf("������ MyStr_2.pFileBuffer /  \n *(LPDWORD)pFileBuffer��ֵ��: %x\n", *(LPDWORD)pFileBuffer);
	}

	getchar();


	return 0;
}

