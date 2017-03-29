#pragma once

#include <mutex>
#include "../GPS.h"
#include "../Meter.h"
#include "C:\Users\God-is-fool\Documents\Visual Studio 2013\Projects\UAV_3D_FCS\UAV_3D_FCS\UAV_3D_FCS\Meter.h"
#include "C:\Users\God-is-fool\Documents\Visual Studio 2013\Projects\UAV_3D_FCS\UAV_3D_FCS\UAV_3D_FCS\Compass.h"
//#include "C:\Users\Administrator\Desktop\Work\UAV_3D_FCS\UAV_3D_FCS\UAV_3D_FCS\Meter.h"
//#include "C:\Users\Administrator\Desktop\Work\UAV_3D_FCS\UAV_3D_FCS\UAV_3D_FCS\Compass.h"

/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FlightSysViewControl.h
* ժ    Ҫ�����ڱ���Ŀ�ķ��п���ģ�����ͼ���ͷ�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/


// CFlightSysViewControl ������ͼ
namespace FlightSysViewControlSpace {
	//HUD��ʱ��ID = 1
	const int HUDTimerID = 1;
	//HUD��ʱʱ�� = 200ms
	const int HUDTimerElapse = 200;
};

class CFlightSysViewControl : public CFormView
{
	DECLARE_DYNCREATE(CFlightSysViewControl)

protected:
	CFlightSysViewControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFlightSysViewControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCS };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	//GPS�ؼ�
	CGPS m_GPS;
	//����ٱ���
	CMeter m_VSMeter;
	//ָʾ���ٱ���
	CMeter m_IVSMeter;
	//ָ����ؼ�
	CCompass m_Compass;

	TSPIDC m_TSPIDC;	//��������
	bool m_DataIsComing = false;

	std::mutex m_MutexSendReq;

private:
	//��ʼ������
	void InitMeter();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	 
	//��������
	void UpdateTSPIDC(const TSPIDC& tspidc);
	//��ʼ��
	//virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	virtual void OnInitialUpdate(); 
	afx_msg void OnPaint(); 
};


