// ����.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <VECTOR>
#include <LIST>
#include <SET>

#include <STRING>
#include <IOSTREAM>

using namespace std;

#pragma optimize("", off)
void MsgBox(int a, int b, int c, int d, int e)
{
	int arr[2];
	arr[4] = arr[3] + 3;			// ������������ƽջ/��ǰarr[3]��ԭ���ص�ַ
	arr[3] = (int)MessageBox;		// popʱ��ջ��/retʱ
	arr[5] = 0;						// esp+4
	arr[6] = (int)"������!";		// esp+8
	arr[7] = (int)"�ɹ�!";			// esp+0ch
	arr[8] = MB_OK;					// esp+10h
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MsgBox(0, 0, 0, 0, 0);

	MessageBox(0, 0, 0, 0);
	return 0;
}
#pragma optimize("", on)