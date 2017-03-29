
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#include <mutex>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <atomic>
#include "protocol/FCToPCProtocolStruct.hpp"
#include "protocol/FCToPCProtocolConvertToRealData.h"
#include "MessageBus/MessageBus.hpp"
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "Server/ServerSQLOperation.h"
typedef struct _ACCOUNT_INFOR
{
	CString Server;
	CString Port;
	CString UserId;
	CString UserPassword;
	CString DatabaseName;
	CString TableName;
	CString AccountTitle;
	CString PasswordTitle;
	CString AuthorityTitle;
	CString Account;
	CString Password;
	INT	Authority;
}ACCOUNT_INFOR;
typedef struct _Time{
	DWORD Hour;
	DWORD Minute;
	DWORD Second;
	DWORD MillSecond;
}Time;

typedef struct _DISPLAY_INFO{
	Time Origin;
	Time Begin;
	Time End;
	Time RangeBegin;
	Time RangeEnd;
}DISPLAY_INFO;


#define SHOW_MAINWINDOW         (WM_USER + 105)

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


