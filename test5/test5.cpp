#include "stdafx.h"

// ��������ʱδ���

void StrFunction(int n)
{
	char* g_n = "china�й�verygood�쳯nice";
	/* ������ַ����Ļ���������������ַ���
	���ڶ�ջ�������� ebp -4 λ�õ��Ǵ��ַ������ڵĵ�ַ��
	����g_n��ǰ4���ֽ�Ϊһ����Ч��ַ��
	������ֱ�����ַ�����ֵ��*/	
}

int main(int argc, char* argv[])
{
	StrFunction(6);  // ��ȡ�����Ľ��Ӧ����: china��
	return 0;
}
