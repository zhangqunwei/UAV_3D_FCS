#pragma once

#include "Label.h"
#include "afxwin.h"
#include"resource.h"
// CProcessDlg �Ի���

class CProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessDlg)

public:
	CProcessDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CLabel m_process;

	//BITMAP  m_Bitmap;		// Struct to hold info about the bitmap
	//HBITMAP m_hBitmap;		// Handle of the bitmap

	//void LoadPlaneImage();

	int m_timeCount = 2;

	CString m_strLabelText;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	void SetLabelText(CString text);

#define TRANSPARENTCOLOR RGB(255, 255, 255)
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnPaint();
};
