#include <Windows.h>

void main()
{
	int (__stdcall *p_func_msg)(int,int,int,int,int);   //���庯��ָ�����͵ı���

	p_func_msg = (int (__stdcall *)(int,int,int,int,int))0x75B636C0;  //��ֵ

	MessageBox(0,0,0,0);

	p_func_msg(0,0,0,0,0);

	return;
}
