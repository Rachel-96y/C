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
#include <memory.h>



// ----------------------------- ������ȫ�ֱ��� -----------------------------

// �����ҵļ�����ϵ� MessageBoxA �ĵ�ַ ÿ�ιػ������ֵ���ᷢ���仯
// ��Ϊ�ⲻ�� ShellCode ������������������ֵ�ᷢ���仯
DWORD ToMessageBoxA = 0x77B509A0;

// ͳһ���� �����ڴ���ĳ���
#define CODE_LENGTH 18

// ���������·��: PATH ΪĿ��PE����·��	NEW_PATH Ϊ�����ɵ���Ӵ����ĳ���·��

#define PATH "C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\NewDynamicLink.dll"
#define NEW_PATH "C:\\Users\\Administrator.DESKTOP-PL8E08J\\Desktop\\IMAGE_DynamicLink.dll"



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
LPVOID CreateImageBuffer(IN LPVOID pFileBuffer);
/*
��������˵��:
���ݸ����� pFileBuffer ָ���ȡ�ڴ��е�����
��Ҫ���ж��Ƿ���PE�ļ�
�����PE�ļ������ ��ѡPEͷ�� SizeOfImage �Ĵ�С�������ڴ�ռ�

����˵��:
pFileBuffer ָ�� FileBuffer �ڴ滺������ָ��

����ֵ˵��:
���ִ�гɹ��򷵻�������Ŀռ��ָ�� pImageBuffer ʧ���򷵻�0
*/
// ****************************************************************************


// ============================================================================
LPVOID CreateNewBuffer(IN LPVOID pImageBuffer);
/*
��������˵��:
���ݸ����� ImageBuffer ����ó���ѹ����� NewBuffer �Ŀռ��С
�����ݴ˴�С�����Ӧ�Ŀռ�

����˵��:
pImageBuffer	ָ�� ImageBuffer �ڴ滺������ָ��

����ֵ˵��:
���ִ�гɹ��򷵻�������Ŀռ��ָ�� pNewBuffer ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPVOID CreateNewImageBuffer(IN LPVOID pImageBuffer, IN UINT SizeOfCode);
/*
��������˵��:
��������������Ҫ�Ŀռ�
���ݸ����� pImageBuffer ָ�� ����ó��Ƿ����㹻�Ŀռ����һ���ڱ� 
������㹻�Ŀռ����һ���ڱ� ��������ṩ�� SizeOfCode �Ĵ�С
����ó����ڴ����� ���� PE �ļ����ڴ��е��ܴ�С ���Դ�������ͬ��С�Ŀռ�

����˵��:
pImageBuffer			ָ�� ImageBuffer �ڴ滺������ָ��	
SizeOfSectionNumber		��Ҫ��ӵĴ���ĳ���

����ֵ˵��:
���ִ�гɹ��򷵻�������Ŀռ��ָ�� pNewImageBuffer ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
LPVOID CreateNewImageBufferEx(IN LPVOID pImageBuffer, IN UINT Size);
/*
��������˵��:
�������ṩ�� pImageBuffer �� Size ������һ��ռ�

����˵��:
pImageBuffer	ָ�� ImageBuffer ������
Size			Ҫ�����Ĵ����ڴ�����Ĵ�С

����ֵ˵��:
���ִ�гɹ��򷵻�������Ŀռ��ָ�� pNewImageBuffer ʧ���򷵻�0
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
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer,OUT LPVOID pImageBuffer);
/*
��������˵��:
���ݸ����� pFileBuffer �� pImageBuffer �������ݵĸ���
��Ҫ���ж��Ƿ���PE�ļ�
�����PE�ļ� �����������ָ�� �� FileBuffer �����ݸ��Ƶ� ImageBuffer ��

����˵��:
pFileBuffer		FileBuffer ������ָ��
pImageBuffer	ImageBuffer ������ָ��

����ֵ˵��:
��������ɹ��򷵻����������ֽ�����С ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer,OUT LPVOID pNewBuffer);
/*
��������˵��:
���ݸ����� pImageBuffer �� pNewBuffer �������ݵĸ���
��Ҫ���ж��Ƿ���PE�ļ�
�����PE�ļ� �����������ָ�� �� ImageBuffer �����ݸ��Ƶ� NewBuffer ��

����˵��:
pImageBuffer	ImageBuffer ������ָ��	
NewBuffer		NewBuffer	������ָ��	
	
����ֵ˵��:
��������ɹ��򷵻����������ֽ�����С ʧ���򷵻�0
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
BOOL AddCodeToImageBuffer(IN PUCHAR pCodeArray,IN UINT HowNumberOfSections, IN UINT SizeOfArray, OUT LPVOID pImageBuffer);
/*
��������˵��:
�˺������ھ�̬ע�����
���ݸ����� ָ�������ָ�� �� pImageBufferָ�� ���д���Ĳ���
��Ҫͬʱָ����������뵽��һ������ ��ָ������Ĵ�С

����˵��:
pCodeArray				ָ������ĵ�ָ��
HowNumberOfSections		Ҫ�����ĸ���(��1��ʼ)
SizeOfArray				���鳤��
pImageBuffer			ָ�� ImageBuffer �Ļ�����ָ��

����ֵ˵��:
����������ɹ�����TRUE ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
BOOL CopyImageBufferToNewImageBuffer(IN LPVOID pImageBuffer, OUT LPVOID pNewImageBuffer, IN UINT SizeOfCode, IN UINT IsExistMisc);
/*
��������˵��:
�˺�������������
�� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
У��������Ҫ������PEͷ���ֵ �������ƶ�PEͷ�ͽڱ�

����˵��:
pImageBuffer		ImageBuffer ������ָ��
pNewImageBuffer		NewImageBuffer ������ָ��
SizeOfCode			δ����ǰ�Ĵ����С
IsExistMisc			�Ƿ���� Misc ��ֵ 0������ ��������ֵ������ֵ����SizeOfRawData

����ֵ˵��:
���ִ�гɹ��򷵻�TRUE ʧ���򷵻�0
*/ 
// ****************************************************************************


// ============================================================================
BOOL CopyImageBufferToNewImageBufferEx(IN LPVOID pImageBuffer, OUT LPVOID pNewImageBuffer, IN UINT AlignNumber, IN UINT IsExistMisc, IN UINT CodeSize);
/*
��������˵��:
�˺������������
�� ImageBuffer �����ݸ��Ƶ� NewImageBuffer ��
У��������Ҫ������PEͷ���ֵ

����˵��:
pImageBuffer		ImageBuffer ������ָ��
pNewImageBuffer		NewImageBuffer ������ָ��
AlignNumber			Ҫ����Ľڶ����Ĵ�С
IsExistMisc			�Ƿ���� Misc ��ֵ 0������ 1����ֵΪ SizeOfRawData - CodeSize ��������ֵ������ֵ����SizeOfRawData
CodeSize			ָ���ӽڵ����￪ʼд������ ���ֵ��ΪҪע��Ĵ���ĳ��ȼ���

����ֵ˵��:
���ִ�гɹ��򷵻�TRUE ʧ���򷵻�0
*/ 
// ****************************************************************************



// ============================================================================
BOOL ChangeImageBufferData(IN LPVOID pImageBuffer, IN UINT IsExistMisc, IN UINT CodeSize);
/*
��������˵��:
�˺������ںϲ���
�� ImageBuffer ������ȫ������

����˵��:
pImageBuffer		ָ�� ImageBuffer ������ָ��
IsExistMisc			�Ƿ���� Misc ��ֵ 0������ 1����ֵΪ SizeOfRawData - CodeSize ��������ֵ������ֵ����SizeOfRawData
CodeSize			ָ���ӽڵ����￪ʼд������ ���ֵ��ΪҪע��Ĵ���ĳ��ȼ���

����ֵ˵��:
���ִ�гɹ��򷵻�TRUE ʧ���򷵻�0
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
pFileBuffer				FileBufferָ��
FunctionNameOrdinal		�������(2���ֽڵĿ��)

����ֵ˵��:
����ִ�гɹ��򷵻����Һ����ĵ�ַ ʧ���򷵻�0
*/ 
// ****************************************************************************




#endif // !defined(AFX_STDAFX_H__2CA63EA4_5C33_4AEF_A008_DAC3396AB0B6__INCLUDED_)