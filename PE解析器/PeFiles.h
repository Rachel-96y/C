// PeFiles.h: interface for the PeFiles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEFILES_H__4CB7594F_38DA_4A00_831C_9449AB0744FC__INCLUDED_)
#define AFX_PEFILES_H__4CB7594F_38DA_4A00_831C_9449AB0744FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

DWORD IsPeFile(IN LPTSTR szFilePath, IN PTLSDirectory g_pStTLS);
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

#endif // !defined(AFX_PEFILES_H__4CB7594F_38DA_4A00_831C_9449AB0744FC__INCLUDED_)
