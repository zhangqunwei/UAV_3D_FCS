#include "stdafx.h"
#include "GPS.h"


CGPS::CGPS()
{
}


CGPS::~CGPS()
{
}

 

/*! @function
********************************************************************************
* ������   : DrawStaticBackground
* ����     : ����GPS�ľ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ�������ƣ���ʾ�����������ݵľ�̬���ֲ���
			 m_LOTD                 //��ʱ����(��) 
			 m_LATD                 //��ʱγ��(��)
			 m_SPH                  //��׼��ѹ�߶�(ft)
			 m_PRH                  //��ѹ�����߶�(ft)
			 m_RH                   //���ߵ�߶�(ft)
			 ��ʾ��ʽ��
				�������ƣ�����ֵ
			 �ؼ�Ϊ��ɫ����
*******************************************************************************/
void CGPS::DrawStaticBackground(CDC *pDC)
{ 

	GetClientRect(&m_rectCtrl);
	CString show_str("GPS"); 
	int start_x = m_rectCtrl.left;
	int start_y = m_rectCtrl.top; 

	//Show "GPS"
	DrawUavText(pDC, show_str, start_x + GPSPace::title_x_offset, start_y, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::WHITE);

	show_str = "Lat:";
	DrawUavText(pDC, show_str, start_x + GPSPace::x_offset, start_y + 20, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str = "Lot:";
	DrawUavText(pDC, show_str, start_x + GPSPace::x_offset, start_y + 35, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str = "SPH:";
	DrawUavText(pDC, show_str, start_x + GPSPace::x_offset, start_y + 50, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str = "PRH:";
	DrawUavText(pDC, show_str, start_x + GPSPace::x_offset, start_y + 65, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str = " RH:";
	DrawUavText(pDC, show_str, start_x + GPSPace::x_offset, start_y + 80, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

}



/*! @function
********************************************************************************
* ������   : DrawDynamicBackground
* ����     : ����GPS�Ķ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ�������ƣ���ʾ�����������ݵĶ�̬��������
			m_LOTD                 //��ʱ����(��)
			m_LATD                 //��ʱγ��(��)
			m_SPH                  //��׼��ѹ�߶�(ft)
			m_PRH                  //��ѹ�����߶�(ft)
			m_RH                   //���ߵ�߶�(ft)
			��ʾ��ʽ��
				�������ƣ�����ֵ
			�ؼ�Ϊ��ɫ����
*******************************************************************************/
void CGPS::DrawDynamicBackground(CDC *pDC)
{ 
	GetClientRect(&m_rectCtrl);
	CString show_str("");
	int start_x = m_rectCtrl.left;
	int start_y = m_rectCtrl.top;

	//Show m_LATD
	show_str.Format(_T("%5.2f"), m_TSPIDC.m_LATD);  
	DrawUavText(pDC, show_str, start_x + GPSPace::var_x_offset, start_y + 20, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str.Format(_T("%5.2f"), m_TSPIDC.m_LOTD);
	DrawUavText(pDC, show_str, start_x + GPSPace::var_x_offset, start_y + 35, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str.Format(_T("%5.2f"), m_TSPIDC.m_SPH);
	DrawUavText(pDC, show_str, start_x + GPSPace::var_x_offset, start_y + 50, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);
	
	show_str.Format(_T("%5.2f"), m_TSPIDC.m_PRH);
	DrawUavText(pDC, show_str, start_x + GPSPace::var_x_offset, start_y + 65, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

	show_str.Format(_T("%5.2f"), m_TSPIDC.m_RH);
	DrawUavText(pDC, show_str, start_x + GPSPace::var_x_offset, start_y + 80, UavViewPace::font_type, UavViewPace::font_size, UavViewPace::GREEN);

}



