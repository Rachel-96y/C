/*
������ϰ��								
								
1������һ�� unsigned char ���ͣ�ͨ������Ϊ��3��5��7λ��ֵ,��ֵʱ����								
Ӱ�쵽����λԭ����ֵ.								
(ʹ��λ����ָ����磺& | ~ ^ << >>��)								
								
2���ж�ĳ��λ��ֵ�Ƿ�Ϊ1.								
(ʹ��λ����ָ����磺& | ~ ^ << >>��)								
								
3����ȡ��7��6��5λ��ֵ����ʮ������ʾ(unsigned).								
(ʹ��λ����ָ����磺& | ~ ^ << >>��)								
								
4����ʮ�������ı��༭���ֱ��һ��.exe��.dll��.sys��.txt��.doc								
.jpg��.pdf�Ƚ�ǰ�ĸ��ֽ�д������.								
								
5����һ����ʮ�����Ʊ༭���д򿪵�.exe�ļ�����ק�����
�۲��ļ��еĴ�С��Ӳ���ϵĴ�С.	
							
(����һ��WinHex)								
*/

#include "stdafx.h"


void function()
{	
	// 1������һ�� unsigned char ���ͣ�ͨ������Ϊ��3��5��7λ��ֵ
	// ��ֵʱ����Ӱ�쵽����λԭ����ֵ.

	unsigned char num;
	num = 0x01;		// 0000 0001  ����
	unsigned char Flag;
	Flag = 0x04;	// 0000 0100
	num |= Flag;
	printf("%x\n", num);

	Flag = 0x10;	// 0001 0000
	num |= Flag;
	printf("%x\n", num);

	Flag = 0x40;	// 0100 0000
	num |= Flag;  
	printf("%x\n", num);

	Flag = 0x40;
	if (num & Flag)
		num ^= Flag;
	printf("%x\n", num);

	Flag = 0x10;
	if (num & Flag)
		num ^= Flag;
	printf("%x\n", num);

	Flag = 0x04;
	if (num & Flag)
		num ^= Flag;
	printf("%x\n", num);



	// 2���ж�ĳ��λ��ֵ�Ƿ�Ϊ1.   �жϵ�4λ
	Flag = 0x08;   // 0000 1000
	if (Flag & num)
		printf("��4λ��ֵΪ1\n");
	else
		printf("��4λ��ֵΪ0\n");



	// 3����ȡ��7��6��5λ��ֵ����ʮ������ʾ(unsigned).
	num = 0xEA;   // 1110 1010
	Flag = 0x70;  // 0111 0000 
	num &= Flag;
	num >>= 4;   // �з��������Ƹ�λ������λ,�޷�������0
	printf("%d\n", num);

}

// 4����ʮ�������ı��༭���ֱ��һ��.exe��.dll��.sys��.txt��.doc��
// .jpg��.pdf�Ƚ�ǰ�ĸ��ֽ�д������.	

// (hex)
// .exe  4D 5A 90 00
// .dll  4D 5A 90 00
// .sys  4D 5A 90 00
// .txt  43 6F 70 79  /  43 61 74 61  / 20 20 4C 49 (Ϊд����ı�)
// .doc  D0 CF 11 E0
// .docx 50 4B 03 04
// .jpg  FF D8 FF E0
// .pdf  25 50 44 46
// .ini  FF FE 0D 00


// 5����һ����ʮ�����Ʊ༭���д򿪵�.exe�ļ�����ק�����
// �۲��ļ��еĴ�С��Ӳ���ϵĴ�С.	

// �ļ���С(0xBCB2)�� 47.1 KB (48,306 �ֽ�)  ռ�ÿռ�(Ӳ���ϵĴ�С)��48.0 KB (49,152 �ֽ�)
// ���ļ��еĴ�С��ռ�ÿռ��С


int main(int argc, char* argv[])
{

	function();
	getchar();
	return 0;
}