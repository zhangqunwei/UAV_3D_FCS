#pragma once
#include"../resource.h"

// CMirrorDlg �Ի���

class CMirrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMirrorDlg)

public:
	CMirrorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMirrorDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MIRROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
