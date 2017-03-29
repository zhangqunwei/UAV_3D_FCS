/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�ConnectionViewControl.cpp
* ժ    Ҫ�����ڱ���Ŀ��ͨ������ģ�����ͼ���cpp�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/

#include "stdafx.h"
#include "../stdafx.h"
#include "../UAV_3D_FCS.h"
#include "ConnectionViewControl.h"


// CConnectionViewControl

IMPLEMENT_DYNCREATE(CConnectionViewControl, CFormView)

CConnectionViewControl::CConnectionViewControl()
	: CFormView(IDD_COMMUNICATION)
{

}

CConnectionViewControl::~CConnectionViewControl()
{
 
}

void CConnectionViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConnectionViewControl, CFormView)
	ON_BN_CLICKED(IDC_BTN_RESET, &CConnectionViewControl::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_TCP_CONNECT, &CConnectionViewControl::OnBnClickedBtnTcpConnect)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CConnectionViewControl ���

#ifdef _DEBUG
void CConnectionViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CConnectionViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CConnectionViewControl ��Ϣ�������


void CConnectionViewControl::OnBnClickedBtnReset()
{
	////��ȡ���õ�IP
	CString _ip;
	GetDlgItemText(IDC_TCP_IP, _ip);
	std::string ip;
	ip = (LPCSTR)CStringA(_ip);

	//��ȡ���õĶ˿�
	int port = GetDlgItemInt(IDC_TCP_PORT);

	//����ip��port
	m_TcpClient.SetConnectAddr(port, ip);

	MessageBox(_T("Reset ip and port success!"));
}


void CConnectionViewControl::OnBnClickedBtnTcpConnect()
{  
	//����TCP���� 

	m_TcpClient.StartTcpConnect();

	if (m_TcpClient.IsTcpConnecting())
	{
		MessageBox(_T("TCP connect success!"));
	} 
	else
	{
		MessageBox(_T("TCP connect fail!"));
	}
}


void CConnectionViewControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	 
	/* ��ʼ����Ϊ192.168.16.107 : 10002 */
	SetDlgItemInt(IDC_TCP_PORT, 10002);
	GetDlgItem(IDC_TCP_IP)->SetWindowText(_T("127.0.0.1"));   
}


void CConnectionViewControl::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	ShowScrollBar(SB_BOTH, FALSE);
}


void CConnectionViewControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	CRect  rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 0, 0));
}


HBRUSH CConnectionViewControl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if ((pWnd->GetDlgCtrlID() == (IDC_STATIC_IP)) || (pWnd->GetDlgCtrlID() == (IDC_STATIC_PORT)))
	{ 
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(225, 225, 225));
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}
