/***************************************************************
* Copyright (c) 2016, �µ���
* All rights reserved.
*
* �ļ����ƣ�FlightSysViewControl.cpp
* ժ    Ҫ�����ڱ���Ŀ�ķ��п���ģ�����ͼ���cpp�ļ�
*
* ��ǰ�汾��1.0
* ��    �ߣ��µ���
* ������ڣ�2016-10-21
***************************************************************/

#include "stdafx.h"
#include "../stdafx.h"
#include "../UAV_3D_FCS.h"
#include "FlightSysViewControl.h"


// CFlightSysViewControl
extern MessageBus g_Bus;
IMPLEMENT_DYNCREATE(CFlightSysViewControl, CFormView)

CFlightSysViewControl::CFlightSysViewControl()
	: CFormView(IDD_FCS)
{
	/* ����g_Bus�ϵ����ݰ� */
	g_Bus.Attach([this](const TSPIDC& tspidc){ UpdateTSPIDC(tspidc); }, "TSPIDC");

	memset(&m_TSPIDC, 0, sizeof(m_TSPIDC));

	//m_VSMeter.UpdateNeedle(0.0);
}

CFlightSysViewControl::~CFlightSysViewControl()
{
	if (m_DataIsComing)
	{
		//������ݵ�������϶������˶�ʱ����������Ҫ�ͷŵ�
		KillTimer(FlightSysViewControlSpace::HUDTimerID);
	}

	/* �ͷ�g_Bus�ϵ����ݰ� */
	g_Bus.Remove<void, const TSPIDC&>("TSPIDC");
}

void CFlightSysViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GPS, m_GPS);
	DDX_Control(pDX, IDC_VS, m_VSMeter);
	DDX_Control(pDX, IDC_IVS, m_IVSMeter);
	DDX_Control(pDX, IDC_NSWE, m_Compass);
}

BEGIN_MESSAGE_MAP(CFlightSysViewControl, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CFlightSysViewControl ���

#ifdef _DEBUG
void CFlightSysViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFlightSysViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFlightSysViewControl ��Ϣ�������


void CFlightSysViewControl::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	ShowScrollBar(SB_BOTH, FALSE);
}


void CFlightSysViewControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ݸ���
	m_GPS.SetCurrentData(m_TSPIDC);
	m_VSMeter.UpdateNeedle(m_TSPIDC.m_VS);
	m_IVSMeter.UpdateNeedle(m_TSPIDC.m_IVS);
	m_Compass.SetCurrentData(m_TSPIDC);
	CFormView::OnTimer(nIDEvent);
}


/*! @function
********************************************************************************
* ������   : UpdateTSPIDC
* ����     : ������Ϣ�����ϵ�TSPIDC����
* ����     : tspidc ���յ���TSPIDC���ݰ�
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2017-03-04
*******************************************************************************/
void CFlightSysViewControl::UpdateTSPIDC(const TSPIDC& tspidc)
{
	if (!m_DataIsComing)
	{
		/* ��ʹ�ûص����� */
		SetTimer(FlightSysViewControlSpace::HUDTimerID, FlightSysViewControlSpace::HUDTimerElapse, NULL);

		//�����Ѿ�������ʹ�������Ƿ�ֹ�ظ�������ʱ��
		m_DataIsComing = true;
	}


	{
		std::lock_guard<std::mutex>  locker(m_MutexSendReq);
		m_TSPIDC = tspidc;
	}
}


void CFlightSysViewControl::InitMeter()
{
	MeterAttribute vs_attr;
	vs_attr.meterStyle = ZMETERSTYLE::N1;
	vs_attr.StartAngleDeg = 270;
	vs_attr.EndAngleDeg = 360 + 45;
	vs_attr.Ticks = 0;
	vs_attr.SubTicks = 5;
	vs_attr.MaxValue = 1080.0;
	vs_attr.MinValue = 0.0;
	vs_attr.CurrentValue = 0.0;
	vs_attr.ScaleDecimals = 1;
	vs_attr.ValueDecimals = 1;
	vs_attr.colorNeedle = RGB(0, 255, 0);
	vs_attr.strUnits = _T("VS");
	vs_attr.bColorTick = TRUE;
	vs_attr.meterUnit = _T("");
	vs_attr.colorTable[0] = RGB(0, 255, 0);
	vs_attr.colorTable[1] = RGB(255, 255, 0);
	vs_attr.colorTable[2] = RGB(255, 0, 0);
	vs_attr.space_3[0] = 700;
	vs_attr.space_3[1] = 100;
	vs_attr.space_3[2] = 100;
	vs_attr.valueRange[0] = 0.0;
	vs_attr.valueRange[1] = 795;
	vs_attr.valueRange[2] = 805;
	vs_attr.valueRange[3] = 1080;
	m_VSMeter.SetMeterAttribute(vs_attr);

	MeterAttribute ivs_attr;
	ivs_attr.meterStyle = ZMETERSTYLE::N2;
	ivs_attr.StartAngleDeg = 270;
	ivs_attr.EndAngleDeg = 360 + 45;
	ivs_attr.Ticks = 0;
	ivs_attr.SubTicks = 5;
	ivs_attr.MaxValue = 1080.0;
	ivs_attr.MinValue = 0.0;
	ivs_attr.CurrentValue = 0.0;
	ivs_attr.ScaleDecimals = 1;
	ivs_attr.ValueDecimals = 1;
	ivs_attr.colorNeedle = RGB(0, 255, 0);
	ivs_attr.strUnits = _T("IVS");
	ivs_attr.bColorTick = TRUE;
	ivs_attr.meterUnit = _T("");
	ivs_attr.colorTable[0] = RGB(0, 255, 0);
	ivs_attr.colorTable[1] = RGB(255, 255, 0);
	ivs_attr.colorTable[2] = RGB(255, 0, 0);
	ivs_attr.space_3[0] = 700;
	ivs_attr.space_3[1] = 100;
	ivs_attr.space_3[2] = 100;
	ivs_attr.valueRange[0] = 0.0;
	ivs_attr.valueRange[1] = 795;
	ivs_attr.valueRange[2] = 805;
	ivs_attr.valueRange[3] = 1080;
	m_IVSMeter.SetMeterAttribute(ivs_attr);
}

void CFlightSysViewControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	InitMeter();
}


void CFlightSysViewControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	CRect  rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0, 0, 0));
}
