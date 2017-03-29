
// MessageSourceDlg.h : ͷ�ļ�
//

#pragma once
#include "protocol/FCToPCProtocolConvertToRealData.h"
#include "protocol/FCToPCProtocolStruct.hpp"
#include "kapok/Serializer.hpp"
#include "TcpServer.h"


#define TIMER_SEND	0

// CMessageSourceDlg �Ի���
class CMessageSourceDlg : public CDialogEx
{
// ����
public:
	CMessageSourceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MESSAGESOURCE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	unsigned int m_ID;				 //�ɻ����  3��4
	unsigned int m_DID;				 //Ŀ�ı��  5��6
	double m_LOTD;                   //��ʱ����  7��8��9��10
	double m_LATD;                   //��ʱγ��  11��12��13��14
	double m_SPH;                    //��׼��ѹ�߶�  15��16
	double m_PRH;                    //��ѹ�����߶�  17��18
	double m_RH;                     //���ߵ�߶�  19��20
	double m_VS;                     //�����  21��22
	double m_IVS;                    //ָʾ����  23��24
	double m_TH;                     //�溽��  25��26
	double m_ANGP;                   //������  27��28
	double m_ANGR;                   //�����  29��30
	double m_ANGPS;                  //����������  31��32
	double m_ANGRS;                  //���������  33��34

	CString m_strMsg;
	DWORD m_dwTimInterval;

	TSPI m_TSPI;
	TSPIDC m_TSPIDC;

	CTcpServer m_TcpServer;
	Serializer m_Sr;

	bool m_bState;

	int	m_ixoldpos;
	int m_iyoldpos;
// ʵ��
protected:
	HICON m_hIcon;
	void SetScroll(CRect page, CRect range);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSendSpecifiedMsg();
	afx_msg void OnBnClickedButtonSendGenerateMsg();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonStatus();
	afx_msg void OnBnClickedButtonSetIpPort();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnKillfocusEditTimeInterval();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	void SendTSPIMessage();
};
