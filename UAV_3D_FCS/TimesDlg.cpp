// TimesViewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include"resource.h"
#include "TimesDlg.h"
#include "afxdialogex.h"
#include <thread>


extern std::atomic<int> g_PID;
// CTimesDlg �Ի���

IMPLEMENT_DYNAMIC(CTimesDlg, CDialogEx)

CTimesDlg::CTimesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimesDlg::IDD, pParent)
{
	//�������ʽ��ID([0-9]*)_([0-9]{4})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})_([0-9]{4})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})
	//0-ƥ���ַ���
	//1-�ɻ����
	//2-��ʼ���
	//3-��ʼ�·�
	//4-��ʼ��
	//5-��ʼʱ
	//6-��ʼ��
	//7-��ʼ��
	//8-��ֹ���
	//9-��ֹ�·�
	//10-��ֹ��
	//11-��ֹʱ
	//12-��ֹ��
	//13-��ֹ��
	m_TableMatch = cregex::compile("[a-z|A-Z]{2}([0-9]{3,4})[_][0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[_][0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}");
	//Ĭ��ֻ��1��
	m_Titles.push_back(TEXT("RECORDED TIME"));
	//Ĭ����2��
	m_TablesTitles.push_back(TEXT("PLANE ID"));
	m_TablesTitles.push_back(TEXT("RECORD TIME FRAGMENT"));
	m_TablesTitles.push_back(TEXT("SELECT"));
	//Ĭ��0��
	m_uRowNums = 0;
	m_uTableRowNums = 0;
	//
	m_Grid = NULL;
	m_GridCtrl = NULL;
	//Ĭ�ϱ��ⱳ��ɫΪ���ɫ
	m_TitleBkColor = RGB(200, 100, 100);
	//Ĭ��Ϊ��
	m_Texts.clear();
	//Ĭ�ϰ�ɫ
	m_GridBkColor = RGB(255, 255, 255);
	//Ĭ��ѡ��Ϊ��
	m_SelectedTableName = TEXT("");
	m_SelectedID = TEXT("");

	//Ĭ���и�
	m_RowHeight = 35;
	//Ĭ���˺�
	m_strUser = TEXT("root");
	//Ĭ������
	m_strPassword = TEXT("");
	//Ĭ�����ݿ�����
	m_strDatabase = TEXT("NCHDDISPATCH");
	//Ĭ�����ݿ�IP
	m_strDatabaseIP = TEXT("192.168.1.33");//TEXT("192.168.1.33");
	//Ĭ�϶˿�
	m_strDatabasePort = TEXT("3306");
	//Ĭ�������ַ���
	m_strConnection = TEXT("Provider=MSDASQL.1;Persist Security Info=False;Extended Properties=\"DSN=NCHDDISPATCH;SERVER=") + m_strDatabaseIP
		+ _T(";DATABASE=") + m_strDatabase
		+ _T(";PORT=") + m_strDatabasePort + TEXT("\"");
	m_SelectedTableName = TEXT("");
	//ָ�����ݿ�������
	//0����
	m_SqlColNames.push_back(TEXT("ID"));
	//1����
	m_SqlColNames.push_back(TEXT("totalMilliSeconds"));
	//1����
	m_SqlColNames.push_back(TEXT("strJson"));
	//Ĭ����ѡ��
	m_bSelected = FALSE;
}

CTimesDlg::~CTimesDlg()
{
}

void CTimesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimesDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTimesDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTimesDlg::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CTimesDlg ��Ϣ�������

//����������ʱ��
BOOL CTimesDlg::TableNameToDateTime(CString str_table_name, SYSTEMTIME &start_time, SYSTEMTIME &end_time)
{
	//UNICODEתASCII
	char *c_str_table_name = NULL;
	int length = 0;
	string temp_date_time;
	cmatch result;

	length = WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, NULL, 0, NULL, 0);
	c_str_table_name = new char[length];
	memset(c_str_table_name, '\0', length);
	WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, c_str_table_name, length, NULL, 0);

	if(!regex_match(c_str_table_name, result, m_TableMatch))return FALSE;

	if (result.size() <= 0)return FALSE;

	temp_date_time = result[START_DATE_YEAR].str();
	start_time.wYear = atoi(temp_date_time.c_str());
	temp_date_time = result[START_DATE_MONTH].str();
	start_time.wMonth = atoi(temp_date_time.c_str());
	temp_date_time = result[START_DATE_DAY].str();
	start_time.wDay = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_HOUR].str();
	start_time.wHour = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_MINUTE].str();
	start_time.wMinute = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_SECOND].str();
	start_time.wSecond = atoi(temp_date_time.c_str());
	start_time.wMilliseconds = start_time.wSecond * 1000;

	temp_date_time = result[END_DATE_YEAR].str();
	end_time.wYear = atoi(temp_date_time.c_str());
	temp_date_time = result[END_DATE_MONTH].str();
	end_time.wMonth = atoi(temp_date_time.c_str());
	temp_date_time = result[END_DATE_DAY].str();
	end_time.wDay = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_HOUR].str();
	end_time.wHour = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_MINUTE].str();
	end_time.wMinute = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_SECOND].str();
	end_time.wSecond = atoi(temp_date_time.c_str());
	end_time.wMilliseconds = end_time.wSecond * 1000;

	delete c_str_table_name;
	c_str_table_name = NULL;
	return TRUE;
}

//�������������ʱ��
VOID CTimesDlg::TableNamesToDateTimes(vector<CString> str_table_names, vector<SYSTEMTIME> &start_times, vector<SYSTEMTIME> &end_times)
{
	//���ԭ����
	start_times.clear();
	end_times.clear();

	vector<CString>::iterator vsit;
	SYSTEMTIME start_time, end_time;
	for (vsit = str_table_names.begin(); vsit != str_table_names.end(); vsit++)
	{
		start_time.wYear = 0;
		start_time.wMonth = 0;
		start_time.wDay = 0;
		start_time.wHour = 0;
		start_time.wMinute = 0;
		start_time.wSecond = 0;
		start_time.wMilliseconds = 0;
		start_time.wDayOfWeek = 0;

		end_time.wYear = 0;
		end_time.wMonth = 0;
		end_time.wDay = 0;
		end_time.wHour = 0;
		end_time.wMinute = 0;
		end_time.wSecond = 0;
		end_time.wMilliseconds = 0;
		end_time.wDayOfWeek = 0;

		if (TableNameToDateTime(*vsit, start_time, end_time))
		{
			start_times.push_back(start_time);
			end_times.push_back(end_time);
		}
	}
}

//�ַ���ȥ�غ���
VOID CTimesDlg::DeleteSameStrings(vector<CString> src_str, vector<CString> &tar_str)
{
	vector<CString> temp_tar_strs;
	vector<CString>::iterator vsiti, vsitj;
	vector<UINT> signs;
	vector<UINT>::iterator vuit;
	for (vsiti = src_str.begin(); vsiti != src_str.end(); vsiti++)
	{
		BOOL has_same = FALSE;
		//���������ڱ�ʶ�����Ѵ��ڣ���˵��ǰ������Ԫ�������ظ�
		//��ֹ��μ�¼
		for (vuit = signs.begin(); vuit != signs.end(); vuit++)
		{
			if (vsiti - src_str.begin() == *vuit)
			{
				has_same = TRUE;
				break;
			}
		}

		if (has_same)continue;

		for (vsitj = vsiti + 1; vsitj != src_str.end(); vsitj++)
		{
			if (!vsiti->Compare(*vsitj))
			{
				//�ظ�
				signs.push_back(vsitj - src_str.begin());
			}
		}
	}

	for (vsiti = src_str.begin(); vsiti != src_str.end(); vsiti++)
	{
		BOOL has_same = FALSE;
		for (vuit = signs.begin(); vuit != signs.end(); vuit++)
		{
			if (vsiti - src_str.begin() == *vuit)
			{
				has_same = TRUE;
				break;
			}
		}
		if (has_same)continue;
		temp_tar_strs.push_back(*vsiti);
	}
	tar_str.clear();
	tar_str = temp_tar_strs;
}

//���ַ�����������
BOOL CTimesDlg::StringToDateTime(CString src_str, SYSTEMTIME &start_time, SYSTEMTIME &end_time)
{
	cregex match = cregex::compile("([0-9]{1,4})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})[_]([0-9]{1,4})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})([0-9]{1,2})");
	//UNICODEתASCII
	char *c_str_name = NULL;
	int length = 0;
	string temp_date_time;
	cmatch result;

	length = WideCharToMultiByte(CP_ACP, 0, src_str, -1, NULL, 0, NULL, 0);
	c_str_name = new char[length];
	memset(c_str_name, '\0', length);
	WideCharToMultiByte(CP_ACP, 0, src_str, -1, c_str_name, length, NULL, 0);

	if (!regex_match(c_str_name, result, match))return FALSE;

	if (result.size() <= 0)return FALSE;

	temp_date_time = result[START_DATE_YEAR - 1].str();
	start_time.wYear = atoi(temp_date_time.c_str());
	temp_date_time = result[START_DATE_MONTH - 1].str();
	start_time.wMonth = atoi(temp_date_time.c_str());
	temp_date_time = result[START_DATE_DAY - 1].str();
	start_time.wDay = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_HOUR - 1].str();
	start_time.wHour = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_MINUTE - 1].str();
	start_time.wMinute = atoi(temp_date_time.c_str());
	temp_date_time = result[START_TIME_SECOND - 1].str();
	start_time.wSecond = atoi(temp_date_time.c_str());
	start_time.wMilliseconds = start_time.wSecond * 1000;

	temp_date_time = result[END_DATE_YEAR - 1].str();
	end_time.wYear = atoi(temp_date_time.c_str());
	temp_date_time = result[END_DATE_MONTH - 1].str();
	end_time.wMonth = atoi(temp_date_time.c_str());
	temp_date_time = result[END_DATE_DAY - 1].str();
	end_time.wDay = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_HOUR - 1].str();
	end_time.wHour = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_MINUTE - 1].str();
	end_time.wMinute = atoi(temp_date_time.c_str());
	temp_date_time = result[END_TIME_SECOND - 1].str();
	end_time.wSecond = atoi(temp_date_time.c_str());
	end_time.wMilliseconds = end_time.wSecond * 1000;
	return TRUE;
}

//��ʱ���ַ�����������
BOOL CTimesDlg::StringsToDateTimes(vector<CString> src_strs,
	vector<SYSTEMTIME> &start_times, 
	vector<SYSTEMTIME> &end_times)
{
	vector<CString>::iterator vsit;
	SYSTEMTIME start_time, end_time;
	vector<SYSTEMTIME> temp_start_times, temp_end_times;
	for (vsit = src_strs.begin(); vsit != src_strs.end(); vsit++)
	{
		start_time.wYear = 0;
		start_time.wMonth = 0;
		start_time.wDay = 0;
		start_time.wHour = 0;
		start_time.wMinute = 0;
		start_time.wSecond = 0;
		start_time.wMilliseconds = 0;
		start_time.wDayOfWeek = 0;

		end_time.wYear = 0;
		end_time.wMonth = 0;
		end_time.wDay = 0;
		end_time.wHour = 0;
		end_time.wMinute = 0;
		end_time.wSecond = 0;
		end_time.wMilliseconds = 0;
		end_time.wDayOfWeek = 0;
		if (!StringToDateTime(*vsit, start_time, end_time))continue;
		temp_start_times.push_back(start_time);
		temp_end_times.push_back(end_time);
	}
	if ((INT)temp_start_times.size() > 0)start_times = temp_start_times;
	else return FALSE;
	if ((INT)temp_end_times.size() > 0)end_times = temp_end_times;
	else return FALSE;
	return TRUE;
}

//�����ڵ����ַ���
VOID CTimesDlg::DateTimeToString(SYSTEMTIME start_time, SYSTEMTIME end_time, CString &tar_str)
{
	CString sing = TEXT("_");
	CString text_format = TEXT("");
	text_format.Format(TEXT("%4d%s%2d%s%2d%s%2d%s%2d%s%2d%s%4d%s%2d%s%2d%s%2d%s%2d%s%2d"), 
		start_time.wYear, 
		sing,
		start_time.wMonth,
		sing,
		start_time.wDay,
		sing,
		start_time.wHour,
		sing,
		start_time.wMinute,
		sing,
		start_time.wSecond,
		sing,
		end_time.wYear,
		sing,
		end_time.wMonth,
		sing,
		end_time.wDay,
		sing,
		end_time.wHour,
		sing,
		end_time.wMinute,
		sing,
		end_time.wSecond);
	tar_str = text_format;
}

//�����ڵ���ʱ���ַ���
VOID CTimesDlg::DateTimesToStrings(vector<SYSTEMTIME> start_times,
	vector<SYSTEMTIME> end_times, vector<CString> &tar_strs)
{
	VERIFY(start_times.size() == end_times.size());
	vector<SYSTEMTIME>::iterator vstit;
	CString tar_src;
	vector<CString> temp_tar_strs;
	for (vstit = start_times.begin(); vstit != start_times.end(); vstit++)
	{
		tar_src = TEXT("");
		DateTimeToString(start_times[vstit - start_times.begin()],
			end_times[vstit - start_times.begin()], tar_src);
		temp_tar_strs.push_back(tar_src);
	}
	tar_strs = temp_tar_strs;
}

//��õ�����������ڲ���
BOOL CTimesDlg::GetDateTimeInTableName(CString str_table_name, CString &str_date_time)
{
	cregex match = cregex::compile("[a-z|A-Z]{2}[0-9]+[_](.*)"); 

	char *c_str_table_name = NULL;
	wchar_t *c_wstr_date_time = NULL;
	const char *c_str_date_time = NULL;
	const char *tc = NULL;
	int length = 0;
	cmatch result;
	string temp_str;
	CString temp_str_date_time = TEXT("");

	//UNICODEתASCII
	length = WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, NULL, 0, NULL, 0);
	c_str_table_name = new char[length];
	memset(c_str_table_name, '\0', length);
	WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, c_str_table_name, length, NULL, 0);

	//ƥ������ʱ��
	if (regex_match(c_str_table_name, result, match) == FALSE)return FALSE;

	//ƥ�䵽֮��1������Ϊ����ʱ��
	temp_str = result[1].str();
	c_str_date_time = temp_str.c_str();

	//ASCIIתUNICODE
	length = MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, NULL, 0);
	c_wstr_date_time = new wchar_t[length];
	memset(c_wstr_date_time, '\0', length * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, c_wstr_date_time, length);
	temp_str_date_time.Format(TEXT("%s"), c_wstr_date_time);

	str_date_time = temp_str_date_time;
	return TRUE;
}

//���ָ������ʱ��ı���
VOID CTimesDlg::GetSpecifiedTableNames(vector<CString> src_table_names,
	CString src_date_time, vector<CString> &tar_table_names)
{
	/*
	cregex match = cregex::compile("[a-z|A-Z]{2}[_][0-9]+[_]([0-9]{1,4}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,4}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2}[_][0-9]{1,2})");
*/	
	vector<CString>::iterator vsit;
	vector<CString> temp_tar_table_names;

	for (vsit = src_table_names.begin(); vsit != src_table_names.end(); vsit++)
	{
		SYSTEMTIME start_time, end_time;
		CString date_time = TEXT("");
		start_time.wYear = 0;
		start_time.wMonth = 0;
		start_time.wDay = 0;
		start_time.wHour = 0;
		start_time.wMinute = 0;
		start_time.wSecond = 0;
		start_time.wMilliseconds = 0;
		start_time.wDayOfWeek = 0;

		end_time.wYear = 0;
		end_time.wMonth = 0;
		end_time.wDay = 0;
		end_time.wHour = 0;
		end_time.wMinute = 0;
		end_time.wSecond = 0;
		end_time.wMilliseconds = 0;
		end_time.wDayOfWeek = 0;

		//������ת��Ϊ��׼��ʽ
		TableNameToDateTime(*vsit, start_time, end_time);
		DateTimeToString(start_time, end_time, date_time);
		if (date_time.Compare(src_date_time) == 0)
		{
			//���
			temp_tar_table_names.push_back(*vsit);
		}

		//char *c_str_table_name = NULL;
		//wchar_t *c_wstr_date_time = NULL;
		//const char *c_str_date_time = NULL;
		//const char *tc = NULL;
		//int length = 0;
		//cmatch result;
		//string temp_str;
		//CString temp_str_date_time = TEXT("");
		////UNICODEתASCII
		//length = WideCharToMultiByte(CP_ACP, 0, *vsit, -1, NULL, 0, NULL, 0);
		//c_str_table_name = new char[length];
		//memset(c_str_table_name, '\0', length);
		//WideCharToMultiByte(CP_ACP, 0, *vsit, -1, c_str_table_name, length, NULL, 0);
		////ƥ������ʱ��
		//if (regex_match(c_str_table_name, result, match) == FALSE)continue;
		//
		////ƥ�䵽֮��1������Ϊ����ʱ��
		//temp_str = result[1].str();
		//c_str_date_time = temp_str.c_str();
		////ASCIIתUNCIODE
		//length = MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, NULL, 0);
		//c_wstr_date_time = new wchar_t[length];
		//memset(c_wstr_date_time, '\0', length * sizeof(wchar_t));
		//MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, c_wstr_date_time, length);
		//temp_str_date_time.Format(TEXT("%s"), c_wstr_date_time);
		////�ж��Ƿ����
		//if (temp_str_date_time.Compare(src_date_time) == 0)
		//{
		//	//���
		//	temp_tar_table_names.push_back(*vsit);
		//}
		//delete c_str_table_name;
		//delete c_wstr_date_time;
		//c_str_table_name = NULL;
		//c_wstr_date_time = NULL;
	}
	if ((INT)temp_tar_table_names.size() > 0)tar_table_names = temp_tar_table_names;
}

//������ȡʱ��ȥ��
BOOL CTimesDlg::DeleteSameTimeInTableNames(vector<CString> src_str_table_names, 
	vector<CString> &tar_strs)
{
	vector<CString>::iterator vsit;
	vector<CString> date_times, unique_date_time;
	for (vsit = src_str_table_names.begin(); vsit != src_str_table_names.end(); vsit++)
	{
		CString date_time = TEXT("");
		if(!GetDateTimeInTableName(*vsit, date_time))continue;
		date_times.push_back(date_time);
	}
	DeleteSameStrings(date_times, unique_date_time);
	if ((INT)unique_date_time.size() > 0)tar_strs = unique_date_time;
	else return FALSE;
	return TRUE;
}

//���ñ���
VOID CTimesDlg::SetTitle(vector<CString> titles)
{
	m_Titles.clear();
	m_Titles = titles;
}

//���������ַ���
VOID CTimesDlg::SetConnectionString(CString strConnection)
{
	m_strConnection = strConnection;
}

//�������ݿ��˺�
VOID CTimesDlg::SetUserString(CString strUser)
{
	m_strUser = strUser;
}

//�������ݿ�����
VOID CTimesDlg::SetPasswordString(CString strPassword)
{
	m_strPassword = strPassword;
}

//�������ݿ�����
VOID CTimesDlg::SetDatabaseString(CString strDatabase)
{
	m_strDatabase = strDatabase;
}

//����Զ�����ݿ�IP
VOID CTimesDlg::SetDatabaseIPString(CString strDatabaseIP)
{
	m_strDatabaseIP = strDatabaseIP;
	m_strConnection = TEXT("Provider=MSDASQL.1;Persist Security Info=False;Extended Properties=\"DSN=NCHDDISPATCH;SERVER=") + m_strDatabaseIP
		+ _T(";DATABASE=") + m_strDatabase
		+ _T(";PORT=") + m_strDatabasePort + TEXT("\"");
}

//����Զ�����ݿ�˿�
VOID CTimesDlg::SetDatabasePortString(CString strDatabasePort)
{
	m_strDatabasePort = strDatabasePort;
	m_strConnection = TEXT("Provider=MSDASQL.1;Persist Security Info=False;Extended Properties=\"DSN=NCHDDISPATCH;SERVER=") + m_strDatabaseIP
		+ _T(";DATABASE=") + m_strDatabase
		+ _T(";PORT=") + m_strDatabasePort + TEXT("\"");
}

//���ѡ��ķɻ����
CString CTimesDlg::GetSelectedID()
{
	return m_SelectedID;
}

//���ѡ��ı����
CString CTimesDlg::GetSelectedTable()
{
	return m_SelectedTableName;
}

//��ȡ���ݿ�����
CString CTimesDlg::GetDatabaseIPString()
{
	return m_strDatabaseIP;
}
CString CTimesDlg::GetDatabasePortString()
{
	return m_strDatabasePort;
}

//���ѡ���Ĳ���ʱ���
DISPLAY_INFO CTimesDlg::GetDisplayInfo()
{
	SYSTEMTIME start_time, end_time;
	DISPLAY_INFO display_info;

	start_time.wYear = 0;
	start_time.wMonth = 0;
	start_time.wDay = 0;
	start_time.wHour = 0;
	start_time.wMinute = 0;
	start_time.wSecond = 0;
	start_time.wMilliseconds = 0;
	start_time.wDayOfWeek = 0;

	end_time.wYear = 0;
	end_time.wMonth = 0;
	end_time.wDay = 0;
	end_time.wHour = 0;
	end_time.wMinute = 0;
	end_time.wSecond = 0;
	end_time.wMilliseconds = 0;
	end_time.wDayOfWeek = 0;


	display_info.Begin.Hour = 0;
	display_info.Begin.Minute = 0;
	display_info.Begin.Second = 0;
	display_info.RangeBegin.Hour = 0;
	display_info.RangeBegin.Minute = 0;
	display_info.RangeBegin.Second = 0;

	display_info.End.Hour = 0;
	display_info.End.Minute = 0;
	display_info.End.Second = 0;
	display_info.RangeEnd.Hour = 0;
	display_info.RangeEnd.Minute = 0;
	display_info.RangeEnd.Second = 0;

	if (m_SelectedTableName.GetLength() == 0)
	{
		return display_info;
	}
	TableNameToDateTime(m_SelectedTableName, start_time, end_time);

	display_info.Begin.Hour = start_time.wHour;
	display_info.Begin.Minute = start_time.wMinute;
	display_info.Begin.Second = start_time.wSecond;
	display_info.RangeBegin.Hour = 0;
	display_info.RangeBegin.Minute = 0;
	display_info.RangeBegin.Second = 0;
	display_info.RangeBegin.MillSecond = 0;

	Time time;
	CTimeFormat::MillSecondToHMSMS(time, CTimeFormat::YMDHMSToSecond(start_time, end_time) * 1000);

	display_info.RangeEnd.Hour = time.Hour;
	display_info.RangeEnd.Minute = time.Minute;
	display_info.RangeEnd.Second = time.Second;
	display_info.RangeEnd.MillSecond = time.MillSecond;

	time = CTimeFormat::HMSAddHMS(display_info.Begin, time);

	display_info.End.Hour = time.Hour;
	display_info.End.Minute = time.Minute;
	display_info.End.Second = time.Second;
	display_info.End.MillSecond = time.MillSecond;

	return display_info;
}


//���ѡ���ı��ľ��岥��ʱ���
DISPLAY_INFO CTimesDlg::GetRealDisplayInfo()
{
	DWORD start_time = 0, end_time = 0;
	DISPLAY_INFO display_info;

	display_info.Begin.Hour = 0;
	display_info.Begin.Minute = 0;
	display_info.Begin.Second = 0;
	display_info.RangeBegin.Hour = 0;
	display_info.RangeBegin.Minute = 0;
	display_info.RangeBegin.Second = 0;

	display_info.End.Hour = 0;
	display_info.End.Minute = 0;
	display_info.End.Second = 0;
	display_info.RangeEnd.Hour = 0;
	display_info.RangeEnd.Minute = 0;
	display_info.RangeEnd.Second = 0;

	if (m_SelectedTableName.GetLength() == 0)
	{
		return display_info;
	}
	GetRealRecordTime(start_time, end_time, m_SelectedTableName);
	//��ʱ������
	DWORD mill_seconds = end_time - start_time;
	//����ת��ΪTime
	Time time;
	CTimeFormat::MillSecondToHMSMS(time, mill_seconds);
	CTimeFormat::MillSecondToHMSMS(display_info.Origin, start_time);
	display_info.Begin.Hour = 0;
	display_info.Begin.Minute = 0;
	display_info.Begin.Second = 0;
	display_info.Begin.MillSecond = 0;

	display_info.RangeBegin.Hour = 0;
	display_info.RangeBegin.Minute = 0;
	display_info.RangeBegin.Second = 0;
	display_info.RangeBegin.MillSecond = 0;

	display_info.End.Hour = time.Hour;
	display_info.End.Minute = time.Minute;
	display_info.End.Second = time.Second;
	display_info.End.MillSecond = time.MillSecond;

	display_info.RangeEnd.Hour = time.Hour;
	display_info.RangeEnd.Minute = time.Minute;
	display_info.RangeEnd.Second = time.Second;
	display_info.RangeEnd.MillSecond = time.MillSecond;
	return display_info;
}

//��ʼ���б�
BOOL CTimesDlg::InitTimesGrid()
{
	if (m_Titles.size() == 0)
	{
		return FALSE;
	}

	if (m_Grid && m_Grid->GetSafeHwnd())
	{
		m_Grid->DestroyWindow();
		m_Grid = NULL;
	}

	CWnd *pWnd = NULL;
	CRect rect;
	vector<CString>::iterator vsit;
	vector<SYSTEMTIME>::iterator vstit;
	CString text = TEXT("");
	//���ԭ����
	if (m_Grid && m_Grid->GetRowCount())
	{
		m_Grid->DeleteRow(m_Grid->GetRowCount());
	}
	pWnd = GetDlgItem(IDC_TIMES_GRID_TIME);
	if(pWnd == NULL)return FALSE;
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	m_Grid = new CGridCtrl();

	m_Grid->Create(rect, this, IDC_TIMES_GRID, WS_VISIBLE | WS_TABSTOP);
	if(m_Grid == NULL)return FALSE;
	
	//������ʽ
	m_Grid->EnableDragAndDrop(FALSE);
	m_Grid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(255, 255, 255));

	LOGFONT logFont;

	logFont.lfHeight = 14;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_EXTRABOLD;
	logFont.lfItalic = FALSE;
	logFont.lfUnderline = FALSE;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = DEFAULT_QUALITY;
	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	lstrcpy(logFont.lfFaceName, _T("����"));

	m_Grid->SetFixedBkColor(m_TitleBkColor);
	m_Grid->GetDefaultCell(FALSE, FALSE)->SetFont(&logFont);
	m_Grid->GetDefaultCell(FALSE, FALSE)->SetTextClr(RGB(0, 0, 0));
	m_Grid->SetListMode(TRUE);
	m_Grid->SetSingleRowSelection(TRUE);
	m_Grid->SetEditable(FALSE);

	//���ù̶�����
	m_Grid->SetFixedRowCount(1);
	//��������
	m_Grid->SetColumnCount((UINT)m_Titles.size());
	//�����п�
	for (vsit = m_Titles.begin(); vsit != m_Titles.end(); vsit++)
	{
		m_Grid->SetColumnWidth(vsit - m_Titles.begin(), rect.Width() / (DOUBLE)m_Titles.size() - 5);
	}
	//���ñ���
	m_Grid->SetBkColor(m_GridBkColor);
	//��������
	m_uRowNums = (UINT)m_UniqueDateTimes.size() + 1;
	if (m_uRowNums > 0)m_Grid->SetRowCount((UINT)m_uRowNums);
	for (size_t i = 0; i < m_uRowNums; i++)
	{
		m_Grid->SetRowHeight((INT)i, m_RowHeight);
	}
	//���ñ���
	for (vsit = m_Titles.begin(); vsit != m_Titles.end(); vsit++)
	{
		m_Grid->SetItemText(0, vsit - m_Titles.begin(), *vsit);
		m_Grid->SetItemFormat(0, vsit - m_Titles.begin(), DT_CENTER | DT_VCENTER);
	}
	return TRUE;
}

//��ʼ�������б�
BOOL CTimesDlg::InitTablesGrid()
{
	if (m_TablesTitles.size() == 0)
	{
		return TRUE;
	}

	if (m_GridCtrl && m_GridCtrl->GetSafeHwnd())
	{
		m_GridCtrl->DestroyWindow();
		m_GridCtrl = NULL;
	}

	CWnd *pWnd = NULL;
	CRect rect;
	vector<CString>::iterator vsit;
	vector<SYSTEMTIME>::iterator vstit;
	CString text = TEXT("");
	//���ԭ����
	if (m_GridCtrl && m_GridCtrl->GetRowCount())
	{
		m_GridCtrl->DeleteRow(m_GridCtrl->GetRowCount());
	}
	pWnd = GetDlgItem(IDC_TIMES_GRID_TABLE);
	if(pWnd == NULL)return FALSE;
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);

	m_GridCtrl = new CMyGridCtrl();

	m_GridCtrl->Create(rect, this, IDC_TIMES_GRID, WS_VISIBLE | WS_TABSTOP);
	if(m_GridCtrl == NULL)return FALSE;

	//������ʽ
	m_GridCtrl->EnableDragAndDrop(FALSE);
	m_GridCtrl->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(255, 255, 255));

	LOGFONT logFont;

	logFont.lfHeight = 15;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_EXTRABOLD;
	logFont.lfItalic = FALSE;
	logFont.lfUnderline = FALSE;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = ANSI_CHARSET;
	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logFont.lfQuality = DEFAULT_QUALITY;
	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	lstrcpy(logFont.lfFaceName, _T("����"));

	//���ñ���
	m_GridCtrl->SetBkColor(m_GridBkColor);
	m_GridCtrl->SetFixedBkColor(m_TitleBkColor);
	m_GridCtrl->GetDefaultCell(FALSE, FALSE)->SetFont(&logFont);
	m_GridCtrl->GetDefaultCell(FALSE, FALSE)->SetTextClr(RGB(0, 0, 0));
	m_GridCtrl->SetListMode(TRUE);
	m_GridCtrl->SetSingleRowSelection(TRUE);
	m_GridCtrl->SetEditable(FALSE);

	//���ù̶�����
	m_GridCtrl->SetFixedRowCount(1);
	//��������
	m_GridCtrl->SetColumnCount((UINT)m_TablesTitles.size());
	//�����п�
	m_GridCtrl->SetColumnWidth(0, rect.Width() * 1.0 / 7);
	m_GridCtrl->SetColumnWidth(1, rect.Width() * 5.0 / 7);
	m_GridCtrl->SetColumnWidth(2, rect.Width() - (INT)(rect.Width() * 6.0 / 7) - 4);

	m_GridCtrl->SetRowCount((UINT)m_uTableRowNums + 1);
	for (size_t i = 0; i < m_uTableRowNums + 1; i++)
	{
		m_GridCtrl->SetRowHeight((INT)i, m_RowHeight);
	}
	//���ñ���
	for (vsit = m_TablesTitles.begin(); vsit != m_TablesTitles.end(); vsit++)
	{
		m_GridCtrl->SetItemText(0, vsit - m_TablesTitles.begin(), *vsit);
		m_GridCtrl->SetItemFormat(0, vsit - m_TablesTitles.begin(), DT_CENTER | DT_VCENTER);
	}
	return TRUE;
}

//������ת��Ϊ������ʾ�ı�
VOID CTimesDlg::DateTimesToTexts(vector<SYSTEMTIME> start_times, 
	vector<SYSTEMTIME> end_times, 
	vector<CString> &texts)
{
	INT rows = m_Grid->GetRowCount(), row_index;
	CString start_time = TEXT(""), end_time = TEXT(""), text = TEXT("");
	for (row_index = 1; row_index < rows; row_index++)
	{
		if (row_index - 1 < (INT)m_StartTimes.size())
		{
			start_time.Format(TEXT("%4dY%2dM%2dD%2dH%2dMIN%2dSEC"),
				m_StartTimes[row_index - 1].wYear,
				m_StartTimes[row_index - 1].wMonth,
				m_StartTimes[row_index - 1].wDay,
				m_StartTimes[row_index - 1].wHour,
				m_StartTimes[row_index - 1].wMinute,
				m_StartTimes[row_index - 1].wSecond);
		}
		if (row_index - 1 < (INT)m_EndTimes.size())
		{
			end_time.Format(TEXT("%4dY%2dM%2dD%2dH%2dMIN%2dSEC"),
				m_EndTimes[row_index - 1].wYear,
				m_EndTimes[row_index - 1].wMonth,
				m_EndTimes[row_index - 1].wDay,
				m_EndTimes[row_index - 1].wHour,
				m_EndTimes[row_index - 1].wMinute,
				m_EndTimes[row_index - 1].wSecond);
		}
		text = start_time + TEXT("-") + end_time;
		//���뵽index����
		m_Texts.push_back(text);
	}
}


//����ʾ�ı����뵽ָ����
VOID CTimesDlg::InsertIntoSpecifiedCol(INT index)
{
	VERIFY(index < (INT)m_Titles.size());
	if (m_Grid->GetSafeHwnd() == NULL)return;

	INT rows = m_Grid->GetRowCount(), row_index;
	for (row_index = 1; row_index < rows; row_index++)
	{
		if (row_index - 1 >= (INT)m_UniqueDateTimes.size())break;
		if ((INT)m_UniqueDateTimes.size() > row_index - 1)
		{
			//m_Grid->SetItemText(row_index, index, m_Texts[row_index - 1]);
			//�����ظ�����ʱ����뵽�б���
			CString str = TEXT("");
			FormatTableName(m_UniqueDateTimes[row_index - 1], str);
			m_Grid->SetItemText(row_index, index, str);
		}
		else
		{
			m_Grid->SetItemText(row_index, index, TEXT(""));
		}
		m_Grid->SetItemState(row_index, index, GVIS_READONLY);
		m_Grid->SetItemFormat(row_index, index, DT_CENTER | DT_VCENTER);
	}
}

VOID CTimesDlg::InsertIntoSpecifiedTableCol(vector<CString> texts, CString str_date_times)
{
	//ȱ�ٲ�����¼ʱ���
	m_GridCtrl->SetRowCount((INT)texts.size() + 1);
	//0��-��ʾ�ɻ����
	//1��-��ʾ����
	//2����ʾ��ѡ��
	vector<CString>::iterator vsit;
	INT index = 0;
	CString table_name = TEXT("");
	for (vsit = texts.begin(); vsit != texts.end(); vsit++)
	{
		CString record_time = TEXT("");
		Time start_time_, end_time_;

		index = (INT)(vsit - texts.begin() + 1);

		m_GridCtrl->SetRowHeight(index, m_RowHeight);
		m_GridCtrl->SetItemText(index, 0, *vsit);
		m_GridCtrl->SetItemState(index, 0, GVIS_READONLY);
		m_GridCtrl->SetItemFormat(index, 0, DT_CENTER | DT_VCENTER);

		InitTime(start_time_);
		InitTime(end_time_);
		table_name = *vsit;
		GetRealRecordTime(start_time_, end_time_, TEXT("ID_") + *vsit + TEXT("_") + str_date_times);
		record_time.Format(TEXT("%02d:%02d:%02d.%03d-%02d:%02d:%02d.%03d"),
			start_time_.Hour,
			start_time_.Minute,
			start_time_.Second,
			start_time_.MillSecond,
			end_time_.Hour,
			end_time_.Minute,
			end_time_.Second,
			end_time_.MillSecond);
		m_GridCtrl->SetRowHeight(index, m_RowHeight);
		m_GridCtrl->SetItemText(index, 1, record_time);
		m_GridCtrl->SetItemState(index, 1, GVIS_READONLY);
		m_GridCtrl->SetItemFormat(index, 1, DT_CENTER | DT_VCENTER);

		m_GridCtrl->SetCellType(index, 2, RUNTIME_CLASS(CGridCellCheck));
		m_GridCtrl->SetItemState(index, 2, GVIS_READONLY);
		m_GridCtrl->SetCellCheck(index, 2, FALSE);
		m_GridCtrl->SetCellRadio(index, 2, TRUE);

	}
}

////����ʾ�ı����뵽���
VOID CTimesDlg::InsertIntoSpecifiedTableCol(vector<CString> texts)
{
	m_GridCtrl->SetRowCount((INT)texts.size() + 1);
	//0��-��ʾ�ɻ����
	//1��-��ʾ����
	//2����ʾ��ѡ��
	vector<CString>::iterator vsit;
	INT index = 0;
	cregex match = cregex::compile("[a-z|A-Z]{2}([0-9]{3,4})[_][0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[_][0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}");
	cmatch result;
	for (vsit = texts.begin(); vsit != texts.end(); vsit++)
	{
		INT length = 0;
		string temp;
		wchar_t *c_wstr_id = NULL;
		const char *c_str_id = NULL;
		char *c_str_table_name = NULL;
		CString str_id = TEXT("");
		//string start_time = "", end_time = "";
		Time t_start_time, t_end_time;
		DWORD start_time = 0, end_time = 0;
		CString record_time = TEXT("");

		//UNICODEתASSCII
		length = WideCharToMultiByte(CP_ACP, 0, *vsit, -1, NULL, 0, NULL, 0);
		c_str_table_name = new char[length];
		memset(c_str_table_name, '\0', length);
		WideCharToMultiByte(CP_ACP, 0, *vsit, -1, c_str_table_name, length, NULL, 0);

		if (!regex_match(c_str_table_name, result, match))continue;
		temp = result[1].str();
		c_str_id = temp.c_str();

		//ASSCIIתUNICODE
		length = MultiByteToWideChar(CP_ACP, 0, c_str_id, -1, NULL, 0);
		c_wstr_id = new wchar_t[length];
		memset(c_wstr_id, '\0', length * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, c_str_id, -1, c_wstr_id, length);
		str_id.Format(TEXT("%s"), c_wstr_id);

		index = (INT)(vsit - texts.begin() + 1);

		m_GridCtrl->SetRowHeight(index, m_RowHeight);
		m_GridCtrl->SetItemText(index, 0, str_id);
		m_GridCtrl->SetItemState(index, 0, GVIS_READONLY);
		m_GridCtrl->SetItemFormat(index, 0, DT_CENTER | DT_VCENTER);

		//��þ���ʱ��
		GetRealRecordTime(start_time, end_time, *vsit);

		InitTime(t_start_time);
		InitTime(t_end_time);
		CTimeFormat::MillSecondToHMSMS(t_start_time, start_time);
		CTimeFormat::MillSecondToHMSMS(t_end_time, end_time);
		record_time.Format(TEXT("%d:%d:%d.%d-%d:%d:%d.%d"), 
			t_start_time.Hour, t_start_time.Minute, t_start_time.Second, t_start_time.MillSecond, 
			t_end_time.Hour, t_end_time.Minute, t_end_time.Second, t_end_time.MillSecond);

		m_GridCtrl->SetRowHeight(index, m_RowHeight);
		m_GridCtrl->SetItemText(index, 1, record_time);
		m_GridCtrl->SetItemState(index, 1, GVIS_READONLY);
		m_GridCtrl->SetItemFormat(index, 1, DT_CENTER | DT_VCENTER);

		m_GridCtrl->SetCellType(index, 2, RUNTIME_CLASS(CGridCellCheck));
		m_GridCtrl->SetItemState(index, 2, GVIS_READONLY);
		m_GridCtrl->SetCellCheck(index, 2, FALSE);
		m_GridCtrl->SetCellRadio(index, 2, TRUE);

		delete c_str_table_name;
		delete c_wstr_id;
		c_str_table_name = NULL;
		c_wstr_id = NULL;
	}
}

VOID CTimesDlg::InitTime(Time &time)
{
	time.Hour = 0;
	time.Minute = 0;
	time.Second = 0;
	time.MillSecond = 0;
}

//�ж������Ƿ����
BOOL CTimesDlg::IsColExist(CString col_name, CString table_name, CString database)
{
	//�������ݿ�
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		//����ִ�����,��ǰִ�����Ϊ��ѯ�ƶ����ݿ������еı��
		CString command = TEXT("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='") + database + TEXT("' AND TABLE_NAME='") + table_name + TEXT("' AND COLUMN_NAME='") + col_name + TEXT("';");
		//��������ֵ
		_variant_t varColName(TEXT("COLUMN_NAME"));
		//��ʼִ��SQL���
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount())
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�жϱ��Ƿ����
BOOL CTimesDlg::IsTableExist(CString table_name, CString database)
{
	//�������ݿ�
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		//����ִ�����,��ǰִ�����Ϊ��ѯ�ƶ����ݿ������еı��
		CString command = TEXT("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='") + database + TEXT("' AND TABLE_NAME='") + table_name + TEXT("';");
		//��������ֵ
		_variant_t varColName(TEXT("TABLE_NAME"));
		//��ʼִ��SQL���
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount())
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}
VOID CTimesDlg::GetDatabaseString(CString &strDatabase)
{
	strDatabase = m_strDatabase;
}

CString CTimesDlg::GetDatabaseString()
{
	return m_strDatabase;
}

//��ȡ���б�񲢴�������
BOOL CTimesDlg::GetTableNamesFromSql(vector<CString> &table_names)
{
	//��վɱ���
	m_TableNames.clear();
	m_ProcessDlg.SetLabelText(TEXT("Connecting Database..."));
	std::thread t([this](){m_ProcessDlg.DoModal(); });
	t.detach();

	//�������ݿ�
	m_Sql.OpenDataBase(m_strConnection, m_strUser, m_strPassword);

	m_ProcessDlg.SendMessage(WM_CLOSE);

	//vector<CString>::iterator vsit;
	//for (vsit = m_SqlColNames.begin(); vsit != m_SqlColNames.end(); vsit++)
	//{
	//	if (!IsColExist(*vsit, GetSelectedTable(), GetDatabaseString()))
	//	{
	//		if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	//		{
	//			m_Sql.CloseDataBase();
	//		}
	//		AfxMessageBox(TEXT("Wrong database format.\n\rYou'd better check wheter database column names are respond to the column names in direct schema"));
	//		return FALSE;
	//	}
	//}
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		//����ִ�����,��ǰִ�����Ϊ��ѯ�ƶ����ݿ������еı��
		CString command = TEXT("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='") + m_strDatabase + TEXT("';");
		//��������ֵ
		_variant_t varColName(TEXT("TABLE_NAME"));
		//��ʼִ��SQL���
		VERIFY(m_Sql.Select(command));
		//�������н��,�����浽ԭʼ����������
		while (!m_Sql.m_pRecordSet->adoEOF)
		{
			//�鿴�����Ƿ�ƥ��
			//UNICODEתASCII
			char *c_str_table_name = NULL;
			int length = 0;
			string temp_date_time;
			cmatch result;
			CString str_table_name = m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal;

			length = WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, NULL, 0, NULL, 0);
			c_str_table_name = new char[length];
			memset(c_str_table_name, '\0', length);
			WideCharToMultiByte(CP_ACP, 0, str_table_name, -1, c_str_table_name, length, NULL, 0);

			if (regex_match(c_str_table_name, result, m_TableMatch))
			{
				m_TableNames.push_back(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			m_Sql.m_pRecordSet->MoveNext();
			delete c_str_table_name;
			c_str_table_name = NULL;
		}
		//�ر����ݿ�
		m_Sql.CloseDataBase();
	}
	else
	{
		AfxMessageBox(TEXT("Open database fail!"));
		return FALSE;
	}
	return TRUE;
}

//���ѡ���ı��ľ�����ϲ���ʱ��
VOID CTimesDlg::GetRealRecordTime(string &tar_start_time, string &tar_end_time, CString table_name)
{
	//ȡ�ڶ��ж���ʱ���
	//ǰ�᣺�ڶ�����ʱ��
	//DISPLAY_INFO display_info;
	CString command = TEXT("");
	_variant_t varColName(m_SqlColNames.at(1));

	if (table_name.GetLength() == 0)
	{
		return;// display_info;
	}

	//�����ݿ�
	m_Sql.OpenDataBase(m_strConnection, m_strUser, m_strPassword);
	//ȡ��ID����С�������е�ʱ��
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		command = TEXT("SELECT * FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MIN(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				tar_start_time = (LPCSTR)CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
				//start_data = CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//ȡ��ID�����������е�ʱ��
		command = TEXT("SELECT ") + m_SqlColNames.at(1)
			+ TEXT(" FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MAX(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				tar_end_time = (LPCSTR)CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
				//end_data = CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//�ر����ݿ�
		m_Sql.CloseDataBase();
	}
	return;// display_info;
}

//���ָ��ʱ�������ID��
VOID CTimesDlg::GetTableNamesByDateTimes(CString date_time, vector<CString> &tar_ids)
{
	if (tar_ids.size() > 0) tar_ids.clear();
	vector<CString>::iterator vsit;
	cregex match = cregex::compile("[a-z|A-Z]{2}([0-9]{3,4})[_]([0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[_][0-9]{4}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2}[0-9]{2})");
	cmatch result;
	for (vsit = m_TableNames.begin(); vsit != m_TableNames.end(); vsit++)
	{
		INT length = 0;
		string temp;
		wchar_t *c_wstr_id = NULL, *c_wstr_date_time = NULL;
		const char *c_str_id = NULL, *c_str_date_time = NULL;
		char *c_str_table_name = NULL;
		CString str_id = TEXT(""), str_date_time = TEXT("");
		string start_time = "", end_time = "";
		CString record_time = TEXT("");

		//UNICODEתASSCII
		length = WideCharToMultiByte(CP_ACP, 0, *vsit, -1, NULL, 0, NULL, 0);
		c_str_table_name = new char[length];
		memset(c_str_table_name, '\0', length);
		WideCharToMultiByte(CP_ACP, 0, *vsit, -1, c_str_table_name, length, NULL, 0);

		if (regex_match(c_str_table_name, result, match))
		{
			temp = result[2].str();
			c_str_date_time = temp.c_str();

			//ASSCIIתUNICODE
			length = MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, NULL, 0);
			c_wstr_date_time = new wchar_t[length];
			memset(c_wstr_date_time, '\0', length * sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 0, c_str_date_time, -1, c_wstr_date_time, length);
			str_date_time.Format(TEXT("%s"), c_wstr_date_time);

			if (!str_date_time.Compare(date_time))
			{
				temp = result[1].str();
				c_str_id = temp.c_str();

				//ASSCIIתUNICODE
				length = MultiByteToWideChar(CP_ACP, 0, c_str_id, -1, NULL, 0);
				c_wstr_id = new wchar_t[length];
				memset(c_wstr_id, '\0', length * sizeof(wchar_t));
				MultiByteToWideChar(CP_ACP, 0, c_str_id, -1, c_wstr_id, length);
				str_id.Format(TEXT("%s"), c_wstr_id);
				tar_ids.push_back(c_wstr_id);
				delete c_wstr_id;
			}
			delete c_wstr_date_time;
		}
		delete c_str_table_name;
	}
}

//���ѡ���ı��ľ�����ϲ���ʱ��
VOID CTimesDlg::GetRealRecordTime(Time &tar_start_time, Time &tar_end_time, CString table_name)
{
	//ȡ��������������ʱ��
	//ǰ��ڶ��д��ʱ��
	//DISPLAY_INFO display_info;
	CString command = TEXT("");
	string start_data = "", end_data = "";
	_variant_t varColName(m_SqlColNames.at(1));

	if (table_name.GetLength() == 0)
	{
		return;// display_info;
	}
	unsigned int start_time = 0, end_time = 0;
	//�����ݿ�
	m_Sql.OpenDataBase(m_strConnection, m_strUser, m_strPassword);
	//ȡ��ID����С�������е�ʱ��
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		command = TEXT("SELECT * FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MIN(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				//start_data = (LPCSTR)CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//ȡ��ID�����������е�ʱ��
		command = TEXT("SELECT * FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MAX(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				end_data = (LPCSTR)CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//�ر����ݿ�
		m_Sql.CloseDataBase();
	}

	//������Ϣ�岢���ʱ���
	AnalyseSqlData(tar_start_time, start_data);
	AnalyseSqlData(tar_end_time, end_data);
	return;// display_info;
}

VOID CTimesDlg::GetRealRecordTime(DWORD &tar_start_time, DWORD &tar_end_time, CString table_name)
{
	//ȡ�ڶ��ж���ʱ���
	//ǰ�᣺�ڶ�����ʱ��
	//DISPLAY_INFO display_info;
	CString command = TEXT("");
	_variant_t varColName(m_SqlColNames.at(1));

	if (table_name.GetLength() == 0)
	{
		return;// display_info;
	}

	//�����ݿ�
	m_Sql.OpenDataBase(m_strConnection, m_strUser, m_strPassword);
	//ȡ��ID����С�������е�ʱ��
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		command = TEXT("SELECT * FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MIN(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				tar_start_time = m_Sql.m_pRecordSet->GetCollect(varColName).uintVal;
				//start_data = CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//ȡ��ID�����������е�ʱ��
		command = TEXT("SELECT ") + m_SqlColNames.at(1)
			+ TEXT(" FROM ") + table_name
			+ TEXT(" WHERE ") + m_SqlColNames.at(0) + TEXT("=")
			+ TEXT("(SELECT MAX(") + m_SqlColNames.at(0)
			+ TEXT(") FROM ") + table_name + TEXT(");");
		if (m_Sql.Select(command))
		{
			if (m_Sql.m_pRecordSet->GetRecordCount() == 1)
			{
				tar_end_time = m_Sql.m_pRecordSet->GetCollect(varColName).uintVal;
				//end_data = CStringA(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			}
			else if (m_Sql.m_pRecordSet->GetRecordCount() == 0)
			{
				CString error = TEXT("");
				error.Format(TEXT("There is no specified id in table��%s"), table_name);
				MessageBox(error);
				return;
			}
			else
			{
				CString error = TEXT("");
				error.Format(TEXT("There is repeat id in table��%s"), table_name);
				MessageBox(error);
				return;// display_info;
			}
		}
		//�ر����ݿ�
		m_Sql.CloseDataBase();
	}
	return;// display_info;
}

VOID CTimesDlg::AnalyseSqlData(Time &time, string strJson)
{
	//�����л���������Ϣ
	//������Ϣ��С����ʽ���ͣ�����Ҫ��������Ժ��������沢����
	if (strJson.compare("") == 0)
	{
		return;
	}
	DeSerializer dr;
	if (std::string::npos != strJson.find("TSPI"))
	{
		TSPI tspi;
		dr.Parse(strJson.c_str());
		dr.Deserialize(tspi, "TSPI");
		if (tspi.m_MessageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = tspi.m_MessageHeader.hour;
			time.Minute = tspi.m_MessageHeader.minute;
			time.Second = tspi.m_MessageHeader.second;
			time.MillSecond = tspi.m_MessageHeader.millSecond;
		}
	}
	/*if (std::string::npos != strJson.find("AFCSD"))
	{
		AFCSD afcsd;
		dr.Parse(strJson.c_str());
		dr.Deserialize(afcsd, "AFCSD");
		if (afcsd.m_messageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = afcsd.m_messageHeader.hour;
			time.Minute = afcsd.m_messageHeader.minute;
			time.Second = afcsd.m_messageHeader.second;
			time.MillSecond = afcsd.m_messageHeader.millSecond;
		}
	}
	if (std::string::npos != strJson.find("LOSD"))
	{
		LOSD losd;
		dr.Parse(strJson.c_str());
		dr.Deserialize(losd, "LOSD");
		if (losd.m_messageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = losd.m_messageHeader.hour;
			time.Minute = losd.m_messageHeader.minute;
			time.Second = losd.m_messageHeader.second;
			time.MillSecond = losd.m_messageHeader.millSecond;
		}
	}
	if (std::string::npos != strJson.find("ESD"))
	{
		ESD esd;
		dr.Parse(strJson.c_str());
		dr.Deserialize(esd, "ESD");
		if (esd.m_messageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = esd.m_messageHeader.hour;
			time.Minute = esd.m_messageHeader.minute;
			time.Second = esd.m_messageHeader.second;
			time.MillSecond = esd.m_messageHeader.millSecond;
		}
	}
	if (std::string::npos != strJson.find("AMD"))
	{
		AMD amd;
		dr.Parse(strJson.c_str());
		dr.Deserialize(amd, "AMD");
		if (amd.m_messageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = amd.m_messageHeader.hour;
			time.Minute = amd.m_messageHeader.minute;
			time.Second = amd.m_messageHeader.second;
			time.MillSecond = amd.m_messageHeader.millSecond;
		}
	}
	if (std::string::npos != strJson.find("ASD"))
	{
		ASD asd;
		dr.Parse(strJson.c_str());
		dr.Deserialize(asd, "ASD");
		if (asd.m_messageHeader.COMM_SOURCE_ADDR == g_PID)
		{
			time.Hour = asd.m_messageHeader.hour;
			time.Minute = asd.m_messageHeader.minute;
			time.Second = asd.m_messageHeader.second;
			time.MillSecond = asd.m_messageHeader.millSecond;
		}
	}*/
}

BOOL CTimesDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO:  �ڴ����ר�ô����/����û���
	INT id = (INT)wParam;
	HWND hwnd;
	if (hwnd = m_Grid->GetSafeHwnd())
	{
		NM_GRIDVIEW *pNmgv = (NM_GRIDVIEW *)lParam;
		if (hwnd == pNmgv->hdr.hwndFrom && pNmgv->hdr.code == NM_DBLCLK)
		{
			vector<CString> table_ids;
			vector<CString> table_names;
			//��ʼ�������б�
			InitTablesGrid();
			//���ָ���ı��
			//GetTableNamesByDateTimes(m_StartTimes[pNmgv->iRow - 1], m_EndTimes[pNmgv->iRow - 1], table_names);
			//��ѡ�е�����ʱ�䱣�浽��ѡ�б����ַ�����
			m_SelectedDateTimeIndex = pNmgv->iRow - 1;
			GetTableNamesByDateTimes(m_UniqueDateTimes[pNmgv->iRow - 1], table_ids);
			GetTableNameByIDAndDateTime(table_names, table_ids, m_UniqueDateTimes[pNmgv->iRow - 1]);
			InsertIntoSpecifiedTableCol(table_names);
			//���뵽���GRID
			//InsertIntoSpecifiedTableCol(table_ids, m_UniqueDateTimes[pNmgv->iRow - 1]);
		}
	}
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}

//��֪�ɻ���ź�����ʱ�������
VOID CTimesDlg::GetTableNameByIDAndDateTime(vector<CString> &tar_table_names, vector<CString> src_ids, CString src_date_time)
{
	vector<CString>::iterator vsit;
	tar_table_names.clear();
	for (vsit = src_ids.begin(); vsit != src_ids.end(); vsit++)
	{
		tar_table_names.push_back(TEXT("id") + *vsit + TEXT("_") + src_date_time);
	}
}

//��ʾָ��ʱ������б�����Ի���
VOID CTimesDlg::GetTableNamesByDateTimes(SYSTEMTIME start_time, SYSTEMTIME end_time, vector<CString> &tar_strs)
{
	CString str_date_time = TEXT("");
	vector<CString> str_table_names;
	DateTimeToString(start_time, end_time, str_date_time);
	GetSpecifiedTableNames(m_TableNames, str_date_time, str_table_names);
	tar_strs = str_table_names;
}

//�����ı�����
VOID CTimesDlg::SetTexts(vector<CString> texts)
{
	VERIFY((INT)texts.size() > 0);
	m_Texts.clear();
	m_Texts = texts;
	m_uRowNums = (UINT)m_Texts.size();
}

//�����º���
BOOL CTimesDlg::Update()
{
	//���ָ�����ݿ����б���
	if (!GetTableNamesFromSql(m_TableNames))return FALSE;
	//ɾ�������ظ��ı���
	DeleteSameTimeInTableNames(m_TableNames, m_UniqueDateTimes);
	//�����ڲ��ظ��ı����е����ڴ洢���ṹ��
	//StringsToDateTimes(m_UniqueDateTimes, m_StartTimes, m_EndTimes);
	//����GRID
	if (!InitTimesGrid())return FALSE;
	//������ת��Ϊָ������ʾ��ʽ
	//DateTimesToTexts(m_StartTimes, m_EndTimes, m_UniqueDateTimes);
	//�����յ���ʾ�ı����뵽GRID��
	InsertIntoSpecifiedCol(0);
	//��ʼ�������б�
	if (!InitTablesGrid())return FALSE;
	return TRUE;
}

void CTimesDlg::GetSelectedItem()
{
	//0����Ϊ�ɻ����
	//1����Ϊ����
	//2����Ϊ��ѡ��
	m_bSelected = FALSE;
	int index_row = 1, rows = m_GridCtrl->GetRowCount();
	for (index_row = 1; index_row < rows; index_row++)
	{
		CGridCellBase *pGridCheck;
		pGridCheck = m_GridCtrl->GetCell(index_row, 2);
		if (pGridCheck == NULL || !pGridCheck->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
		{
			return;
		}
		if (((CGridCellCheck *)pGridCheck)->GetCheck())
		{
			m_bSelected = TRUE;
			//��ʱ�䵽���ַ���
			m_SelectedID = m_GridCtrl->GetCell(index_row, 0)->GetText();
			//ת���ر����
			m_SelectedTableName = TEXT("id") + m_SelectedID + TEXT("_") + m_UniqueDateTimes[m_SelectedDateTimeIndex];
			break;
		}
	}
}

void CTimesDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	//{
		/*******************�ڲ�����**************/
	GetSelectedItem();
		/*******************�ڲ�����**************/
	//}
	//else
	//{
	//	AfxMessageBox(TEXT("Database has been closed"));
	//}

	/*******************�ⲿ����**************/
	//vector<CString> datas;
	//DISPLAY_INFO display_info;
	//GetTableDatas(datas);
	//display_info = GetDisplayInfo();
	/*******************�ⲿ����**************/

	CDialogEx::OnOK();
}

//������ݿ��е�����
void CTimesDlg::GetTableDatas(vector<CString> &datas)
{
	if(m_SelectedTableName.GetLength() == 0)return;

	vector<CString> temp_datas;
	//�������ݿ�
	m_Sql.OpenDataBase(m_strConnection, m_strUser, m_strPassword);
	if (m_Sql.m_pConnection && m_Sql.m_pConnection->GetState() == adStateOpen)
	{
		//����ִ�����,��ǰִ�����Ϊ��ѯ�ƶ����ݿ������еı��
		CString command = TEXT("");
		command = TEXT("USE ") + m_strDatabase + TEXT(";");
		//ѡ��ָ�����ݿ�
		VERIFY(m_Sql.Execute(command));
		command = TEXT("SELECT * FROM ") + m_SelectedTableName + TEXT(";");
		//��������ֵ
		_variant_t varColName(TEXT("strDateTimeMill"));
		//��ʼִ��SQL���
		VERIFY(m_Sql.Select(command));
		//�������н��,�����浽ԭʼ����������
		while (!m_Sql.m_pRecordSet->adoEOF)
		{
			temp_datas.push_back(m_Sql.m_pRecordSet->GetCollect(varColName).bstrVal);
			m_Sql.m_pRecordSet->MoveNext();
		}
		//�ر����ݿ�
		m_Sql.CloseDataBase();
		if ((INT)temp_datas.size() > 0)datas = temp_datas;
	}
	else
	{
		AfxMessageBox(TEXT("Open database fail!"));
		return;
	}
}

void CTimesDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CTimesDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  �ڴ˴������Ϣ����������
	if (!Update())
	{
		SendMessage(WM_CLOSE);
	}
}

//��������ַ���
CString CTimesDlg::GetConnectinString()
{
	return m_strConnection;
}

//������ݿ��˺�
CString CTimesDlg::GetUserStirng()
{
	return m_strUser;
}

//������ݿ�����
CString CTimesDlg::GetPasswordString()
{
	return m_strPassword;
}
//�ж��Ƿ���ѡ��
BOOL CTimesDlg::HasSelected()
{
	return m_bSelected;
}

//����ѡ��
VOID CTimesDlg::SetSlelected(BOOL bSelected)
{
	m_bSelected = bSelected;
}
//������ʾ��ʽ��
VOID CTimesDlg::FormatTableName(CString str_table_name, CString &str_format_table_name)
{
	SYSTEMTIME start_time, end_time;
	StringToDateTime(str_table_name, start_time, end_time);
	str_format_table_name.Empty();
	str_format_table_name.Format(TEXT("%04d/%02d/%02d %02d:%02d:%02d-%04d/%02d/%02d %02d:%02d:%02d"),
		start_time.wYear, start_time.wMonth, start_time.wDay, start_time.wHour, start_time.wMinute, start_time.wSecond,
		end_time.wYear, end_time.wMonth, end_time.wDay, end_time.wHour, end_time.wMinute, end_time.wSecond);
}