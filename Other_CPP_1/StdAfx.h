// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F68CAC25_6E00_43F9_BEFA_A0D11804E96E__INCLUDED_)
#define AFX_STDAFX_H__F68CAC25_6E00_43F9_BEFA_A0D11804E96E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include<windows.h>
#include <iostream>
#include <stdio.h>


// TODO: reference additional headers your program requires here


//{{AFX_INSERT_LOCATION}}

//���ļ� �������ڴ�
//����OUT PVOID* pFileBuffer ����PVOID���͵� pFileBufferָ��
//����ֵΪ  ����ĳ���
DWORD CreateFileBuffer(IN LPSTR lpszFile, OUT PVOID* pFileBuffer);
//��ӡ����ͷ����Ϣ
//���� ���뻺��FileBufferָ��
void ToLoaderPE(IN PVOID pFileBuffer);

//��FileBuffer��������������ImageBuffer
//����1 ����FileBuffer�׵�ַָ��
//����2 ����ImageBuffer�׵�ַָ��
//����ֵ ImageBuffer�ĳ���
DWORD CopyFileBufferToImageBuffer(IN PVOID pFileBuffer, OUT PVOID* pImageBuffer);

//ImageBuffer�������ݰ��ļ���ʽ������NewBuffer
//����1 ����ImageBuffer�׵�ַָ��
//����2 ����NewBuffer�׵�ַָ��
//����ֵ NewBuffer�ĳ���
DWORD ImageBufferToNewBuffer(IN PVOID ImageBuffer, OUT PVOID* pNewBuffer);

//�ļ�����
//����1 ����NewBuffer��ָ��
//����2 ����NewBuffer ����
//����ֵ �ɹ�����1 ʧ�ܷ���0;
DWORD WriteMemeryToFile(IN LPVOID NewBuffer, IN DWORD file_size);

//RVA ת��FOA
void convertFoaToRva(IN LPSTR lpszFile);


//void ChangeImageBufferCode(IN LPSTR lpszFile, IN BYTE* CodeSize);
void ChangeImageBufferCode1(IN LPSTR lpszFile, IN BYTE* ShellCode, IN DWORD Codesize, IN DWORD Maddress);
 


// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F68CAC25_6E00_43F9_BEFA_A0D11804E96E__INCLUDED_)
