#include "stdafx.h"

/*
	��ϰ��								
								
								
1������һ���ṹ��Gamer�����洢һ����Ϸ�еĽ�ɫ����Ϣ������Ѫֵ���ȼ����������Ϣ								
								
Ҫ��								
								
	(1) ���������Щ��Ϣ�������							
					
																
	(2) ����Щ�����������У�����Ҫ��һ����Ա�ǽṹ������		
								
2������һ������������������ṹ�������ֵ.								
								
3������һ��������������ʾ����ṹ����������г�Ա��Ϣ.								
								

*/

struct Point
{
	// ����Ľṹ��
	double x;
	double y;
	double z;
};

struct Gamer
{
	// ��Ϸ��ɫ�ṹ��
	int blood;
	int part;
	Point location;
};


Gamer charactor;  // ����Gamer���͵�ȫ�ֱ���


void input()
{
	// ���ṹ�������ֵ
	charactor.blood = 100;
	charactor.part = 50;
	charactor.location.x = 25.3;
	charactor.location.y = 30.2;
	charactor.location.z = 10.9;
}


void output()
{
	// ��ʾ�ṹ����������г�Ա��Ϣ
	printf("Ѫ��: %d\n", charactor.blood);
	printf("�ȼ�: %d\n", charactor.part);
	printf("x - y - z ����: %.1f - %.1f - %.1f\n", \
		charactor.location.x, \
		charactor.location.y, \
		charactor.location.z);
}


int main()
{
	input();
	output();
	getchar();
	return 0;
}
