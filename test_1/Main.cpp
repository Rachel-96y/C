#include <stdio.h>
#include <Windows.h>
void main()  //��ڳ���   ����ʼִ�еĵط�
{
	//�ж������ֵ�Ƿ�����ȷ��
	char arry[6] = {'1', '5', '6', '7', '4', '9'};
	char c = 0;
	char i = 0;
	printf("����������:\n");
	while(1){
		c = getchar();
		if(c == '\n' && i == 6){
			printf("������ȷ!");
			Sleep(2000);
			return;
		}
		if (c != arry[i]){
			printf("�������!");
			Sleep(2000);
			return;
		}
		i++;
	}
}