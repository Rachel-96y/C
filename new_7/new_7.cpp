#include "stdafx.h"

void SwitchFunctionOne(int x = 3)
{
	// ���������Ҳ������С��
	switch(x)
	{
		case 1:
			printf("1");
			break;
		case 2:
			printf("2");
			break;
		case 3:
			printf("3");
			break;
		default:
			printf("Error");
	}
	return;
}


void SwitchFunctionTwo(int x = 4)
{
	// ֻ���ɴ��
	switch(x)
	{
		case 1:
			printf("1");
			break;
		case 2:
			printf("2");
			break;
		case 3:
			printf("3");
			break;
		case 4:
			printf("4");
			break;
		default:
			printf("Error");
	}
	return;
}

void SwitchFunctionThree(int x = 8)
{
	// ���ɴ���С��
	switch(x)
	{
		case 1:
			printf("1");
			break;
		case 2:
			printf("2");
			break;
		case 9:
			printf("9");
		case 10:
			printf("10");
		default:
			printf("Error");
	}
	return;
}

void SwitchFunctionFour(int x = 225)
{
	// ��������С�� ͬʱʹ�ö�����
	switch(x)
	{
		case 10:
			printf("10");
			break;
		case 22:
			printf("22");
			break;
		case 3:
			printf("3");
			break;
		case 11:
			printf("11");
			break;
		case 27:
			printf("27");
			break;
		case 2:
			printf("2");
			break;
		case 44465:
			printf("44465");
			break;
		case 44:
			printf("44");
			break;
		case 60:
			printf("60");
			break;
		case 99:
			printf("99");
			break;
		default:
			printf("Error");
	}
	return;
}

int main()
{
	// SwitchFunctionOne();
	
	// SwitchFunctionTwo();
	// SwitchFunctionThree();

	// SwitchFunctionFour();
	return 0;
}

