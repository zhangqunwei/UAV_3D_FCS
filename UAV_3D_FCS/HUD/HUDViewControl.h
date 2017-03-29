#pragma once

#include "HUD.h"
#include "../protocol/FCToPCProtocolConvertToRealData.h"

#include <mutex>


namespace HUDViewControlSpace {
	//HUD��ʱ��ID = 1
	const int HUDTimerID = 1;
	//HUD��ʱʱ�� = 200ms
	const int HUDTimerElapse = 200;
};




// CHUDViewControl ������ͼ

class CHUDViewControl : public CFormView
{
	DECLARE_DYNCREATE(CHUDViewControl)

protected:
	CHUDViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHUDViewControl();

public:
	enum { IDD = IDD_HUD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CHUD m_HUD;			//�ؼ�
	TSPIDC m_TSPIDC;	//��������
	bool m_DataIsComing = false;

	std::mutex m_MutexSendReq;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//�򿪶�ʱ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//��������
	void UpdateTSPIDC(const TSPIDC& tspidc);

	//��ʼ��
	virtual void OnInitialUpdate();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


