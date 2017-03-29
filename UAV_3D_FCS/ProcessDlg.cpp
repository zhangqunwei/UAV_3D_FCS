// ProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessDlg.h"
#include "afxdialogex.h"


// CProcessDlg �Ի���

IMPLEMENT_DYNAMIC(CProcessDlg, CDialog)

CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDlg::IDD, pParent)
{
	m_strLabelText = _T("Configure is being updated. Please wait a moment...");
}

CProcessDlg::~CProcessDlg()
{
}

void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PROCESS, m_process);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//ON_WM_SIZE()
	//ON_WM_PAINT()
END_MESSAGE_MAP()


// CProcessDlg ��Ϣ�������


void CProcessDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strProcess;

	if (101012 == nIDEvent)
	{
		strProcess.Format(_T("%s %ds"),
			m_strLabelText, m_timeCount);
		m_process.SetText(strProcess);
	}

	m_timeCount++;

	CDialog::OnTimer(nIDEvent);
}


void CProcessDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_timeCount = 2;
	CDialog::OnClose();
}


BOOL CProcessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_process.SetBkColor(RGB(0XFD, 0XF5, 0XE6));
	m_process.SetFontSize(19);
	m_process.SetTextColor(RGB(0, 0, 0));
	m_process.SetText(m_strLabelText);

	SetTimer(101012, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CProcessDlg::SetLabelText(CString text)
{
	m_strLabelText = text;
}