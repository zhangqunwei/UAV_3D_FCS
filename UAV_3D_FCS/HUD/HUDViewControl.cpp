// HUDViewControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../stdafx.h"
#include "../UAV_3D_FCS.h"
#include "HUDViewControl.h"


// CHUDViewControl


extern MessageBus g_Bus;

IMPLEMENT_DYNCREATE(CHUDViewControl, CFormView)

CHUDViewControl::CHUDViewControl()
	: CFormView(CHUDViewControl::IDD)
{
	/* ����g_Bus�ϵ����ݰ� */
	g_Bus.Attach([this](const TSPIDC& tspidc){ UpdateTSPIDC(tspidc); }, "TSPIDC");

	memset(&m_TSPIDC, 0, sizeof(m_TSPIDC));
}

CHUDViewControl::~CHUDViewControl()
{
	if (m_DataIsComing)
	{
		//������ݵ�������϶������˶�ʱ����������Ҫ�ͷŵ�
		KillTimer(HUDViewControlSpace::HUDTimerID);
	}
	
	/* �ͷ�g_Bus�ϵ����ݰ� */
	g_Bus.Remove<void, const TSPIDC&>("TSPIDC");
}

void CHUDViewControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_HUD, m_HUD);
}

BEGIN_MESSAGE_MAP(CHUDViewControl, CFormView)
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHUDViewControl ���

#ifdef _DEBUG
void CHUDViewControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHUDViewControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHUDViewControl ��Ϣ�������


void CHUDViewControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���ݸ���
	m_HUD.SetCurrentData(m_TSPIDC);


	//�򿪶�ʱ��
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
void CHUDViewControl::UpdateTSPIDC(const TSPIDC& tspidc)
{
	if (!m_DataIsComing)
	{
		/* ��ʹ�ûص����� */
		SetTimer(HUDViewControlSpace::HUDTimerID, HUDViewControlSpace::HUDTimerElapse, NULL);

		//�����Ѿ�������ʹ�������Ƿ�ֹ�ظ�������ʱ��
		m_DataIsComing = true;
	}
	

	{
		std::lock_guard<std::mutex>  locker(m_MutexSendReq);
		m_TSPIDC = tspidc; 
	}
}



void CHUDViewControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	 
}


void CHUDViewControl::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	ShowScrollBar(SB_BOTH, FALSE);
}
