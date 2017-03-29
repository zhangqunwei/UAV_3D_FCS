#pragma once

#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "GridCtrl/GridCtrl.h"
#include "GridCtrl/CMyGridCtrl.h"
#include "Server/ServerSQLOperation.h"
#include "DisplayControl/OwnSliderCtrl.h"
#include "ProcessDlg.h"

// CTimesDlg �Ի���

using namespace boost::xpressive;
/*class CTimeFormat
{
public:
	CTimeFormat(void);
	~CTimeFormat(void);
	static BOOL IsLeapYear(INT year);
	static DWORD YMDHMSToStartDay(SYSTEMTIME time);
	static DWORD YMDHMSToEndDay(SYSTEMTIME time);
	static DWORD YEndToYStart(INT year_start, INT year_end);
	static Time HMSAddHMS(Time t1, Time t2);
	static Time HMSSubHMS(Time t1, Time t2);
	static void YMDHMSToTime(Time &time, SYSTEMTIME start_time, SYSTEMTIME end_time);
	static DWORD YMDHMSToSecond(SYSTEMTIME start_time, SYSTEMTIME end_time);
	static DWORD HMSToSecond(DWORD hour, DWORD minute, DWORD second);
	static DWORD HMSToSecond(Time time);
	static void SecondToHMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD srcsecond);
	static void SecondToHMS(Time &time, DWORD src_second);

	static void MillSecondToHMSMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD &mill_second, DWORD src_mill_second);
	static void MillSecondToHMSMS(Time & time, DWORD src_mill_second);
	static void HMSMSToMillSecond(DWORD &mill_sercond, Time time);
	static void HMSMSToMillSecond(DWORD &mill_sercond, DWORD hour, DWORD minute, DWORD second, DWORD mill_second);
	static DWORD HMSMSToMillSecond(Time time);
	static DWORD HMSMSToMillSecond(DWORD hour, DWORD minute, DWORD second, DWORD mill_second);

	static DWORD HMSToSecond(DOUBLE hour, DOUBLE minute, DOUBLE second);
	static void SecondToHMS(DWORD &hour, DWORD &minute, DWORD &second, DOUBLE srcsecond);
	static void SecondToHMS(Time &time, DOUBLE srcsecond);
	static void MillSecondToHMSMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD &mill_second, DOUBLE src_mill_second);
	static void MillSecondToHMSMS(Time & time, DOUBLE src_mill_second);
};*/
class CTimesDlg : public CDialogEx
{
#define START_DATE_YEAR		2
#define START_DATE_MONTH	3
#define START_DATE_DAY		4
#define START_TIME_HOUR		5
#define START_TIME_MINUTE	6
#define START_TIME_SECOND	7

#define END_DATE_YEAR		8
#define END_DATE_MONTH		9
#define END_DATE_DAY		10
#define END_TIME_HOUR		11
#define END_TIME_MINUTE		12
#define END_TIME_SECOND		13
	DECLARE_DYNAMIC(CTimesDlg)

public:
	CTimesDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTimesDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TIMES_VIEW };


	/*********************�ӿں���**************************/
	//���ñ���
	VOID SetTitle(vector<CString> titles);
	//���������ַ���
	VOID SetConnectionString(CString strConnection);
	//�������ݿ��˺�
	VOID SetUserString(CString strUser);
	//�������ݿ�����
	VOID SetPasswordString(CString strPassword);
	//�������ݿ�����
	VOID SetDatabaseString(CString strDatabase);
	//��ȡ���ݿ�����
	VOID GetDatabaseString(CString &strDatabase);
	CString GetDatabaseString();
	//����Զ�����ݿ�IP
	VOID SetDatabaseIPString(CString strDatabaseIP);
	//����Զ�����ݿ�˿�
	VOID SetDatabasePortString(CString strDatabasePort);
	//��������ַ���
	CString GetConnectinString();
	//������ݿ��˺�
	CString GetUserStirng();
	//������ݿ�����
	CString GetPasswordString();
	//�����ı�����
	VOID SetTexts(vector<CString> texts);
	//���ѡ��ķɻ����
	CString GetSelectedID();
	//���ѡ��ı����
	CString GetSelectedTable();
	CString GetDatabaseIPString();
	CString GetDatabasePortString();
	//������ݿ��е�����
	void GetTableDatas(vector<CString> &datas);
	//���ѡ���Ĳ���ʱ���
	DISPLAY_INFO GetDisplayInfo();
	//���ѡ���ı��ľ��岥��ʱ���
	DISPLAY_INFO GetRealDisplayInfo();
	//���ѡ���ı��ľ��岥��ʱ��
	VOID GetRealRecordTime(string &tar_start_time, string &tar_end_time, CString table_name);
	VOID GetRealRecordTime(Time &tar_start_time, Time &tar_end_time, CString table_name);
	VOID GetRealRecordTime(DWORD &tar_start_time, DWORD &tar_end_time, CString table_name);
	//�ж��Ƿ���ѡ��
	BOOL HasSelected();
	VOID SetSlelected(BOOL bSelected);
	//��������
	VOID AnalyseSqlData(Time &time, string strJson);
	//��ʼ��ʱ��
	VOID InitTime(Time &time);
	/********************************************************/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//���ݿ�����
	CString m_strDatabase;
	//Զ�����ݿ�IP��ַ
	CString m_strDatabaseIP;
	//Զ�����ݿ�˿�
	CString m_strDatabasePort;
	//���ݿ������ַ���
	CString m_strConnection;
	//���ݿ��˺�
	CString m_strUser;
	//���ݿ�����
	CString m_strPassword;
	//�б����
	vector<CString> m_Titles;
	//�����б���
	vector<CString> m_TablesTitles;
	//�б�����
	UINT m_uRowNums;
	//�����б�����
	UINT m_uTableRowNums;
	//�и�
	UINT m_RowHeight;
	//���ⱳ��ɫ
	COLORREF m_TitleBkColor;
	//���ڶ�̬�б�
	CGridCtrl *m_Grid;
	//������̬�б�
	CMyGridCtrl *m_GridCtrl;
	//���ݿ��������
	SQLOperation m_Sql;
	//ԭʼ����
	vector<CString> m_TableNames;
	//���ظ�ʱ��
	vector<CString> m_UniqueDateTimes;
	//��ʾ�������ı�
	vector<CString> m_Texts;
	//ѡ��Ļطű���
	CString m_SelectedTableName;
	//ѡ��Ļطŷɻ����
	CString m_SelectedID;
	//�����ƥ��
	cregex m_TableMatch;
	//�Ƿ���ѡ��
	BOOL m_bSelected;
	//ѡ�������ʱ����
	INT m_SelectedDateTimeIndex;
	//����ʱ��
	vector<SYSTEMTIME> m_StartTimes;
	vector<SYSTEMTIME> m_EndTimes;
	//GRID��ɫ
	COLORREF m_GridBkColor;

	CProcessDlg m_ProcessDlg;

	//��ʼ���б�
	BOOL InitTimesGrid();
	//��ʼ�������б�
	BOOL InitTablesGrid();
	//��ȡ���б�񲢴�������
	BOOL GetTableNamesFromSql(vector<CString> &table_names);
	//��������������ʱ��
	BOOL TableNameToDateTime(CString str_table_name, SYSTEMTIME &start_time, SYSTEMTIME &end_time);
	//�����ڵ���ʱ���ַ���
	VOID DateTimeToString(SYSTEMTIME start_time, SYSTEMTIME end_time, CString &tar_str);
	//�����ڵ���ʱ���ַ���
	VOID DateTimesToStrings(vector<SYSTEMTIME> start_times, vector<SYSTEMTIME> end_times, vector<CString> &tar_strs);
	//��ʱ���ַ�����������
	BOOL StringToDateTime(CString src_str, SYSTEMTIME &start_time, SYSTEMTIME &end_time);
	//��ʱ���ַ�����������
	BOOL StringsToDateTimes(vector<CString> src_strs, vector<SYSTEMTIME> &start_times, vector<SYSTEMTIME> &end_times);
	//�������������ʱ��
	VOID TableNamesToDateTimes(vector<CString> str_table_names, vector<SYSTEMTIME> &start_times, vector<SYSTEMTIME> &end_times);
	//ʱ���ַ���ȥ�غ���
	VOID DeleteSameStrings(vector<CString> src_strs, vector<CString> &tar_strs);
	//������ȡʱ��ȥ��
	BOOL DeleteSameTimeInTableNames(vector<CString> src_str_table_names, vector<CString> &tar_strs);
	//��õ�����������ڲ���
	BOOL GetDateTimeInTableName(CString str_table_name, CString &str_date_time);
	//���ָ������ʱ��ı���
	VOID GetSpecifiedTableNames(vector<CString> src_table_names, CString src_date_time, vector<CString> &tar_table_names);
	//������ת��Ϊ������ʾ�ı�
	VOID DateTimesToTexts(vector<SYSTEMTIME> start_times, vector<SYSTEMTIME> end_times, vector<CString> &texts);
	//����ʾ�ı����뵽ʱ��ָ����
	VOID InsertIntoSpecifiedCol(INT index);
	//���ָ��ʱ������б����
	VOID GetTableNamesByDateTimes(SYSTEMTIME start_time, SYSTEMTIME end_time, vector<CString> &tar_strs);
	//���ָ��ʱ�������ID��
	VOID GetTableNamesByDateTimes(CString date_time, vector<CString> &tar_ids);
	//����ʾ�ı����뵽���
	VOID InsertIntoSpecifiedTableCol(vector<CString> str_ids, CString str_date_times);
	VOID InsertIntoSpecifiedTableCol(vector<CString> texts);
	//�жϱ��Ƿ����
	BOOL IsTableExist(CString table_name, CString database);
	//�ж������Ƿ����
	BOOL IsColExist(CString col_name, CString table_name, CString database);
	//��֪�ɻ���ź�����ʱ�������
	VOID GetTableNameByIDAndDateTime(vector<CString> &tar_table_names, vector<CString> src_ids, CString src_date_time);
	//���ѡ�����
	VOID GetSelectedItem();
	//�����º���
	BOOL Update();
	//������ʾ��ʽ��
	VOID FormatTableName(CString str_table_name, CString &str_format_table_name);
	DECLARE_MESSAGE_MAP()
public:
	//���ݿ�������
	vector<CString> m_SqlColNames;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};