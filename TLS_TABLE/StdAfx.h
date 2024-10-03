// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E4C5A544_BD5D_44CC_85E9_64E49236BEAC__INCLUDED_)
#define AFX_STDAFX_H__E4C5A544_BD5D_44CC_85E9_64E49236BEAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #define PATH "E:\\study\\C_X86\\C_X86_2010\\test_2\\Release\\test_2.exe"
#define PATH "E:\\study\\C_X86\\test\\Win32Api_15\\Release\\Win32Api_15.exe"

// ʹ DbgPrintf ���� debug ģʽ������
#ifdef _DEBUG
#define DbgPrintf   OutputDebugStringF
#else
#define DbgPrintf
#endif

// ͨ�ñ�־λ
#define CALLBACK_UNCOMPLETED				0x00000000			// �ص�����δ����
#define CALLBACK_COMPLETED					0x00000001			// �ص������������
#define ERROR_MEMORY_REQUEST_FAILURE		0x00000002			// �ڴ�����ʧ��
#define ERROR_DOS_MZ						0x00000004			// �����DOS_MZͷ��־
#define ERROR_PE_SIGNATURE					0x00000008			// �����PEͷ��־
#define ERROR_OPEN_FILE						0x00000010			// �ļ���ʧ��
#define ERROR_READ_FILE						0x00000020			// �ļ���ȡʧ��
#define ERROR_CLOSE_FILE					0x00000040			// �ļ��ر�ʧ��
#define ERROR_PE_FILE_TOO_BIG				0x00000080			// PE�ļ���������ռ�ʧ��
#define FILE_OF_PE_UNKNOWN					0x00000100			// δ֪��ִ�г���
#define ERROR_CLICK							0x00000200			// ����ĵ����Ϣ
#define RETURN_FAILURE						0x00000400			// ����ִ��ʧ��
#define RETURN_SUCCESS						0x00000800			// ����ִ�гɹ�
#define FILE_MAX_SIZE						0x40000000			// �ܽ��ܵ�ʵ��PE�ļ����ֵ

// TODO: reference additional headers your program requires here
//////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

DWORD ChangeRvaToFoa32(IN DWORD RVA, IN LPVOID fpFileBuffer);
//////////////////////////////////////////////////////////////////////
// ��������˵��:
// �˺�������һ�� Rva ��һ�� FileBuffer ָ�� ����һ�� Foa
//
// ����˵��:
// Rva							���ڴ��е�ƫ��
// pFileBuffer					FileBuffer ������ָ��
//
// ����ֵ˵��:
// ���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� ʧ���򷵻�0
//////////////////////////////////////////////////////////////////////

DWORD ChangeRvaToFoa64(IN DWORD RVA, IN LPVOID fpFileBuffer);
//////////////////////////////////////////////////////////////////////
// ͬChangeRvaToFoa32
//////////////////////////////////////////////////////////////////////


DWORD ChangeFoaToRva32(IN UINT FOA, IN LPVOID fpFileBuffer);
//////////////////////////////////////////////////////////////////////
// ��������˵��:
// �˺�������һ�� Foa ��һ�� FileBuffer ָ�� ����һ�� Rva
//
// ����˵��:
// Foa							���ļ��е�ƫ��
// pFileBuffer					FileBuffer ������ָ��
//
// ����ֵ˵��:
// ���ִ�гɹ��򷵻ظ�ֵ���ļ��е�ƫ�� ʧ���򷵻�0
//////////////////////////////////////////////////////////////////////

DWORD ChangeFoaToRva64(IN UINT FOA, IN LPVOID fpFileBuffer);
//////////////////////////////////////////////////////////////////////
// ͬChangeFoaToRva32λ
//////////////////////////////////////////////////////////////////////

DWORD IsPeFile(IN LPTSTR lpszFilePath, OUT LPVOID* lpFileBuffer);
//////////////////////////////////////////////////////////////////////
// ��������˵��:
// ���ݴ�����ļ������� ����ļ��Ƿ���PE�ļ�
//
// ����˵��:
// szFilePath					�ļ����ڴ��еĻ�����ָ��
// g_pStTLS								
// 
// ����ֵ˵��:
// �����PE�ļ��򷵻�RETURN_SUCESS
// �������ERROR_DOS_MZ������Ǵ����DOS_MZͷ
// �������ERROR_PE_SIGNATURE������Ǵ����PE��ʶ
//////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_STDAFX_H__E4C5A544_BD5D_44CC_85E9_64E49236BEAC__INCLUDED_)
