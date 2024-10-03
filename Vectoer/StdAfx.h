// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2CA63EA4_5C33_4AEF_A008_DAC3396AB0B6__INCLUDED_)
#define AFX_STDAFX_H__2CA63EA4_5C33_4AEF_A008_DAC3396AB0B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// ----------------------------- ���õ�ͷ�ļ� -----------------------------



#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>



// ----------------------------- ������ȫ�ֱ��� -----------------------------

// �����·��: 

// �����ĳ���: 


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


// ----------------------------- �����ĺ��� -----------------------------



// ============================================================================
LPVOID CreateFileBuffer(IN LPSTR pPeFilePath);
/*
��������˵��:
���ݸ������ļ�·�� ��ȡӲ���ϵ��ļ� ��ȡ�ļ���С
�����ļ���С����һ����ͬ��С���ڴ�ռ�
�ɴ�����Ŀռ䲻�ڴ˺��������ͷ�

����˵��:
pPeFilePath ָ���ļ�·����ָ��

����ֵ˵��:
���ִ�гɹ��򷵻��Ѿ�����Ŀռ���׵�ַָ�� ʧ���򷵻�0 
*/
// ****************************************************************************


// ============================================================================
DWORD MyAlignment(IN LPVOID pPeMemory, IN UINT FileOrSectionAlignment,IN UINT SizeOfCode);
/*
��������˵��:
�����ṩ�� pPeMemory �� ��Ҫ������ֽ��� �� ���뷽ʽ������������Ľ��

����˵��:
pPeMemory					PE �ļ����ڴ��е��׵�ַ
FileOrSectionAlignment		ָ��0Ϊ�ļ����� 1Ϊ�ڴ����
CodeSize					��Ҫ����Ĵ�����ֽ���

����ֵ˵��:
���ִ�гɹ��򷵻ض����Ľ�� ʧ���򷵻�0
*/ 
// ****************************************************************************

// ============================================================================
DWORD ReadPeFileToFileBuffer(IN LPSTR lpszFile, OUT LPVOID pFileBuffer);
/*
��������˵��:
���ݸ������ļ�·�� ��ȡӲ���ϵ��ļ�
�����ȡ��ָ�����ڴ�ռ�

����˵��:
pPeFilePath		Ӳ���ļ�·��
pFileBuffer		FileBuffer ������ָ��

����ֵ˵��:
�������ִ�гɹ��򷵻ض�ȡ���ļ��Ĵ�С(�ֽ�) ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
DWORD WriteMemeryToFile(IN LPVOID pMemBuffer, IN UINT SizeOfFile, OUT LPSTR lpszFile);
/*
��������˵��:
���ݸ����� pMemBuffer ���ļ�·������Ҫд����ļ���С
���ڴ��е�����д�뵽������

����˵��:
pMemBuffer		�ڴ滺����ָ��
SizeOfFile		Ҫд����ļ���С
lpszFile		Ҫд����̵�·��

����ֵ˵��:
������̳ɹ��򷵻�д�����ݵĴ�С ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
DWORD ChangeRvaToFoa(IN UINT RVA, IN LPVOID pFileBuffer);
/*
��������˵��:
�˺�������һ�� Rva ��һ�� FileBuffer ָ�� ����һ�� Foa

����˵��:
Rva				���ڴ��е�ƫ��
pFileBuffer		FileBuffer ������ָ��

����ֵ˵��:
���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� ʧ���򷵻�0
*/ 
// ****************************************************************************



// ============================================================================
DWORD ChangeFoaToRva(IN UINT FOA, IN LPVOID pFileBuffer);
/*
��������˵��:
�˺�������һ�� Foa ��һ�� FileBuffer ָ�� ����һ�� Rva

����˵��:
Foa				���ļ��е�ƫ��
pFileBuffer		FileBuffer ������ָ��

����ֵ˵��:
���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� ʧ���򷵻�0
*/ 
// ****************************************************************************



// ============================================================================
LPVOID GetFunctionAddrByName(IN LPVOID pFileBuffer, IN LPSTR FunctionName);
/*
��������˵��:
�������ֻ�ȡ������ģ���еĵ�ַ������

����˵��:
pFileBuffer		FileBufferָ��
FunctionName	������ָ��

����ֵ˵��:
����ִ�гɹ��򷵻����Һ����ĵ�ַ ʧ���򷵻�0
*/ 
// ****************************************************************************



// ============================================================================
LPVOID GetFunctionAddrByOrdinals(IN LPVOID pFileBuffer, IN UINT FunctionOrdinal);
/*
��������˵��:
������Ż�ȡ������ģ���еĵ�ַ������

����˵��:
pFileBuffer				FileBuffer ָ��
FunctionNameOrdinal		�������(2���ֽڵĿ��)

����ֵ˵��:
����ִ�гɹ��򷵻����Һ����ĵ�ַ ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
DWORD SizeOfDllFunctionLength(IN LPSTR DLL_PATH);
/*
��������˵��:
���ݸ����� DLL ·����ȡ���еĵ�һ���������ĳ���

����˵��:
DLL_PATH				DLL ·��

����ֵ˵��:
����ִ�гɹ��򷵻ص�һ���������Ƶĳ��� ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPVOID CleanPeData(IN LPVOID pFileBuffer, IN UINT SizeOfFileBuffer);
/*
��������˵��:
����ļ������ڲ����ص��ڴ��е����������´���һ�� NewFileBuffer
�� FileBuffer ����Ҫ���ص��ڴ��е����ݿ�����ȥ ���ͷ� FileBuffer �ռ�

����˵��:
pFileBuffer				FileBuffer ָ��
SizeOfFileBuffer		FileBuffer ��С

����ֵ˵��:
������������˿ռ� �򷵻� pFileBuffer ���򷵻� pNewFileBuffer ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
DWORD SizeOfCodeToInjectDll(IN LPVOID pFileBuffer, IN LPSTR DLL_PATH, IN UINT FunctionNameLength);
/*
��������˵��:
����ע��һ�� DLL ������Ҫ���ٿռ�
��Ҫ�ƶ���ȫ������� + �����ĵ���� + ȫ0�ṹ�ĵ���� + IAT + INT + _IMAGE_IMPORT_BY_NAME
���յĴ����ֽ��� = ���� DLL �ĵ�����С(�����հ׽ṹ�� 20 ���ֽڴ�С) + ������ 20 ���ֽڵĵ�����С + IAT + INT + (Dll������ + 1) + (���������� + 2 + 1)
����˵��:
pFileBuffer				FileBuffer ָ�� ( EXE �� pFileBuffer )
DLL_PATH				��Ҫע��� DLL ��·��
FunctionNameLength		��Ҫע��� DLL ��ĺ����ĳ���

����ֵ˵��:
���ִ�гɹ��򷵻� ��Ҫ�Ŀռ��С(δ�����ļ�����ǰ) ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPVOID IsEnoughSpace(IN LPVOID pFileBuffer, IN UINT SizeOfCodeToInjectDll);
/*
��������˵��:
�ж��Ƿ����㹻�Ŀռ�д�����(�����)

����˵��:
pFileBuffer				FileBuffer ָ�� ( EXE �� pFileBuffer )
SizeOfCodeToInjectDll	��Ҫд��Ĵ���Ĵ�С

����ֵ˵��:
����пռ����д���򷵻�Ҫ��ʼд���λ�õ�ָ��
*/ 
// ****************************************************************************


// ============================================================================
DWORD ImportDescriptorInjectDll(IN LPVOID pFileBuffer, IN LPVOID pCodeBegin, IN LPCSTR strDllFunctionNameAddr, IN LPSTR FileNameAddr, IN DWORD SizeOfFileBufferEx);
/*
��������˵��:
���ݸ����� pFileBuffer �Լ� pCodeBegin ����һ�������
�Ӷ�ʵ�� DLL ע���Ч��

����˵��:
pFileBuffer				FileBuffer ָ�� (EXE �� pFileBuffer)
pCodeBegin				Ҫ����ע��Ĵ�������￪ʼд���ָ��
strDllFunctionNameAddr	DLL �������Ƶ����ĵ�һ�����������Ƶĵ�ַ
FileNameAddr			ģ������
SizeOfFileBufferEx	Ϊ�仯ǰ�� FileBuffer ��С

����ֵ˵��:
ִ�гɹ��򷵻�1 ʧ���� pCodeBegin Ϊ NULL �򷵻�0 �Ѿ�ִ�й�һ���򷵻� -1
*/ 
// ****************************************************************************


// ============================================================================
DWORD SizeOfFileBuffer(IN LPVOID pFileBuffer);
/*
��������˵��:
���� FileBuffer �������ǰ FileBuffer �Ĵ�С

����˵��:
pFileBuffer				FileBuffer ָ�� ( EXE �� pFileBuffer )

����ֵ˵��:
���ִ�гɹ��򷵻ص�ǰ�� FileBuffer �Ĵ�С ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPVOID ExpandSection(IN UINT IsSuccess, IN LPVOID pFileBuffer, IN UINT SizeOfCodeAlignment);
/*
��������˵��:
���ݶ�������Ĵ�С�����

����˵��:
IsSuccess				Ϊ NULL ��֤������Ҫ�����
pFileBuffer				FileBuffer ָ�� ( EXE �� pFileBuffer )
SizeOfCodeAlignment		��Ҫд������ݽ����ļ������Ĵ�С

����ֵ˵��:
���ִ�гɹ��򷵻� pNewFileBuffer ָ�� ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPSTR DllFunctionName(IN LPSTR DLL_PATH);
/*
��������˵��:
���ݸ����� DLL ��ȡ����һ�������ĵ�ַ

����˵��:
DLL_PATH				DLL �ڴ����ϵ�·��

����ֵ˵��:
���ִ�гɹ��򷵻� DLL�к����ĵ�ַ ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPSTR GetFileName(IN LPSTR FilePath);
/*
��������˵��:
���ݴ�����ļ�·����ȡ�ļ����Ʋ�����

����˵��:
FilePath				�ļ��ڴ����ϵ�·��

����ֵ˵��:
���ִ�гɹ��򷵻��ļ����� ʧ���򷵻�0
*/ 
// ****************************************************************************



#endif // !defined(AFX_STDAFX_H__2CA63EA4_5C33_4AEF_A008_DAC3396AB0B6__INCLUDED_)