// MirrorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../UAV_3D_FCS.h"
#include "MirrorDlg.h"
#include "afxdialogex.h"


// CMirrorDlg �Ի���

IMPLEMENT_DYNAMIC(CMirrorDlg, CDialogEx)

CMirrorDlg::CMirrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMirrorDlg::IDD, pParent)
{

}

CMirrorDlg::~CMirrorDlg()
{
}

void CMirrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMirrorDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMirrorDlg ��Ϣ�������


void CMirrorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
