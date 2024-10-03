#include "stdafx.h"
#include "string.h"

typedef struct PointOfCharacter 
{
	double x;
	double y;
	double z;
}Point;

typedef struct MonsterOfCosGame
{
	// ����ĸ��ֽ�ɫ��Ϣ
	int ID; // ����ID 1Ϊ���� 2ΪNPC 3Ϊ��ҽ�ɫ
	char name[12];  // �������� �������6������
	int level; // ����ȼ�
	Point Location; // ���� x-y-z ����
}Monster;

Monster MonsterArr[10];

void input()
{
	// �˺���ΪMonsterArr���鸳ֵ
	MonsterArr[0].ID = 1;
	strcpy(MonsterArr[0].name, "�������");
	MonsterArr[0].level = 6;
	MonsterArr[0].Location.x = 12.1;
	MonsterArr[0].Location.y = 11.3;
	MonsterArr[0].Location.z = 10.0;

	MonsterArr[1].ID = 1;
	strcpy(MonsterArr[1].name, "����˹̹");
	MonsterArr[1].level = 10;
	MonsterArr[1].Location.x = 17.5;
	MonsterArr[1].Location.y = 65.3;
	MonsterArr[1].Location.z = 10.0;

	MonsterArr[2].ID = 2;
	strcpy(MonsterArr[2].name, "�̵��ϰ�");
	MonsterArr[2].level = 1;
	MonsterArr[2].Location.x = 10.1;
	MonsterArr[2].Location.y = 11.2;
	MonsterArr[2].Location.z = 10.0;

	MonsterArr[3].ID = 2;
	strcpy(MonsterArr[3].name, "�ƹ�");
	MonsterArr[3].level = 1;
	MonsterArr[3].Location.x = 52.5;
	MonsterArr[3].Location.y = 75.3;
	MonsterArr[3].Location.z = 10.0;

	MonsterArr[4].ID = 3;
	strcpy(MonsterArr[4].name, "���1");
	MonsterArr[4].level = 3;
	MonsterArr[4].Location.x = 10.1;
	MonsterArr[4].Location.y = 11.2;
	MonsterArr[4].Location.z = 10.0;

	MonsterArr[5].ID = 3;
	strcpy(MonsterArr[5].name, "���2");
	MonsterArr[5].level = 2;
	MonsterArr[5].Location.x = 52.5;
	MonsterArr[5].Location.y = 75.3;
	MonsterArr[5].Location.z = 10.0;

	MonsterArr[6].ID = 1;
	strcpy(MonsterArr[6].name, "��ʴ��");
	MonsterArr[6].level = 10;
	MonsterArr[6].Location.x = 12.1;
	MonsterArr[6].Location.y = 11.3;
	MonsterArr[6].Location.z = 10.0;

	MonsterArr[7].ID = 1;
	strcpy(MonsterArr[7].name, "�����ʥ");
	MonsterArr[7].level = 10;
	MonsterArr[7].Location.x = 12.1;
	MonsterArr[7].Location.y = 11.3;
	MonsterArr[7].Location.z = 10.0;

	MonsterArr[8].ID = 1;
	strcpy(MonsterArr[8].name, "������");
	MonsterArr[8].level = 8;
	MonsterArr[8].Location.x = 12.1;
	MonsterArr[8].Location.y = 11.3;
	MonsterArr[8].Location.z = 10.0;

	MonsterArr[9].ID = 1;
	strcpy(MonsterArr[9].name, "�ŵ���");
	MonsterArr[9].level = 9;
	MonsterArr[9].Location.x = 12.1;
	MonsterArr[9].Location.y = 11.3;
	MonsterArr[9].Location.z = 10.0;
}

void output(int id)
{
	// �˺���ͨ������ID��ӡ�����������Ϣ
	for (int num = 0; num < 10; num++)
	{
		if (MonsterArr[num].ID == id)
		{
			printf("��������: %s\n����ȼ�: %d\n��������: x:%.1f  y:%.1f  z:%.1f\n\n", \
				MonsterArr[num].name, \
				MonsterArr[num].level, \
				MonsterArr[num].Location.x, \
				MonsterArr[num].Location.y, \
				MonsterArr[num].Location.z);
		}
	}
}

int main(int argc, char* argv[])
{
	input();
	output(1);  // ��������Ҫ��ӡ˭����Ϣ  1Ϊ���� 2ΪNPC 3Ϊ��ҽ�ɫ
	getchar();
	return 0;
}