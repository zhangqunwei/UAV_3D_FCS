#include "stdafx.h"
#include "Compass.h"


CCompass::CCompass()
{
}


CCompass::~CCompass()
{
}



/*! @function
********************************************************************************
* ������   : DrawStaticBackground
* ����     : ����ָ����ľ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ��������
*******************************************************************************/
void CCompass::DrawStaticBackground(CDC *pDC)
{
	GetClientRect(&m_rectCtrl); 
	int start_x = m_rectCtrl.left;
	int start_y = m_rectCtrl.top;
	
	POINT start;
	start.x = m_rectCtrl.left;
	start.y = m_rectCtrl.top;
	POINT end;
	int r = 100;
	end.x = start.x + r;
	end.y = start.y + r;
	 
	DrawCricle(pDC, start, end);
}



/*! @function
********************************************************************************
* ������   : DrawDynamicBackground
* ����     : ����ָ����Ķ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ��������
			 ʹ��m_TSPIDC.m_TH��ΪΪ�������ݣ���Χ[0, 360)
			 ����˳ʱ��ƫ�������ĽǶ�
*******************************************************************************/
void CCompass::DrawDynamicBackground(CDC *pDC)
{
	//GetClientRect(&m_rectCtrl);
	//pDC->FillSolidRect(m_rectCtrl, RGB(0, 0, 0));
	//CPoint center,point;
	//center.x = m_rectCtrl.left + 50;
	//center.y = m_rectCtrl.top + 50;
	//point.x = center.x + sin(m_TSPIDC.m_TH) * 40;
	//point.y = center.y + cos(m_TSPIDC.m_TH) * 40;
	//CPen pen;
	//pen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	//pDC->SelectObject(pen);
	//pDC->MoveTo(center);
	//pDC->LineTo(point);

	//pen.DeleteObject();
}