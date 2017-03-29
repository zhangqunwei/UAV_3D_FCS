#include "stdafx.h"
#include "../stdafx.h"
#include "HUD.h"

CHUD::CHUD()
{
	m_dRadius = 130;	// Բ���뾶
	
}


CHUD::~CHUD()
{
}


/*! @function
********************************************************************************
* ������   : SetCurrentData
* ����     : ����HUD�������Ľӿڣ���������HUD�ؼ�������
* ����     : tspidc ��HUDViewControl�����������ݰ�
* ����ֵ   : void
* ����     : �µ��� �ϲ����մ�ѧ��Ϣ����ѧԺ�Զ�����ϵ
* ����     : 2017-03-04
*******************************************************************************/
void CHUD::SetCurrentData(const TSPIDC& tspidc)
{ 
	// ���ݸ��¸�ֵ
	// double m_ANGP = 0.0;            //������  27��28 ��Χ��(-180��,180��)
	// double m_ANGR = 0.0;            //�����  29��30 ��Χ��(-180��,180��)
	//double m_ANGPS = 0.0;                  //����������  31��32
	//double m_ANGRS = 0.0;                  //���������  33��34

	// ���յ�������Ϊ�Ƕ���
	m_TSPIDC.m_ANGP = tspidc.m_ANGP;
	m_TSPIDC.m_ANGPS = tspidc.m_ANGPS;
	m_TSPIDC.m_ANGR = tspidc.m_ANGR;
	m_TSPIDC.m_ANGRS = tspidc.m_ANGRS;
	//�ػ�
	Invalidate();
}



BEGIN_MESSAGE_MAP(CHUD, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


/*! @function
********************************************************************************
* ������   : OnPaint
* ����     : ��ͼ����
* ����     : void
* ����ֵ   : void 
* ��ע     : ���еĻ�ͼ������Ӧ���������������ɣ�ʹ��˫���漼��(MemoryDC.h)
			 ��ֹ��Ļ��˸,�Ȼ��ƾ�̬���֣��ٻ��ƶ�̬���֡�
*******************************************************************************/
void CHUD::OnPaint()
{
	CPaintDC dc(this);  

	//���Ի����о�̬�ı���ؼ��Ĵ�С���긳��m_rectCtrl
	GetClientRect(&m_rectCtrl);
	

	//memDCΪһ�����dc����CMemoryDC��Ĺ��캯���н�ʵ�ʵ�dc
	CMemoryDC memDC(&dc, &m_rectCtrl);

	if (m_reqRedrawStaticBgd)
	{ 
		//�ڻ������ڻ���HUD��̬ͼ��
		if ((m_dcPlate == nullptr) || (m_bitmapPlate.m_hObject == nullptr))
		{
			//����һ����ʵ��dcƥ��������豸������(m_dcHudPlate)
			m_dcPlate.CreateCompatibleDC(&dc);

			DrawStaticPrepare(&dc);
		}
		else
		{
			m_dcPlate.DeleteDC();
			//����һ����ʵ��dcƥ��������豸������(m_dcHudPlate)
			m_dcPlate.CreateCompatibleDC(&dc);
			m_bitmapPlate.DeleteObject();

			DrawStaticPrepare(&dc);
		}

		//��λͼm_bitmapHUDPlate����������dc(m_dcHUDPlate)����HUD��̬����
		DrawStaticBackground(&m_dcPlate);

		//ֻ��Ҫ����һ�ξ�̬����������ϳ����治��������ʾ��̬��������ȥ��������
		m_reqRedrawStaticBgd = false;
	}

	//��̬������Ҫ�ظ����ƣ�����ʵ�ֶ���Ч��
	DrawDynamicBackground(&memDC);	

	//���������ڻ�����ɵ�λͼһ���Կ�������ʾ������ʾ
	//ʹ�û����������ɫ�ϲ������⸲�Ƕ�̬����
	memDC.BitBlt(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), &m_dcPlate, 0, 0, SRCPAINT);

}


/*! @function
********************************************************************************
* ������   : DrawStaticPrepare
* ����     : ��ͼ����
* ����     : void
* ����ֵ   : void
* ��ע     : ���ƿؼ��ľ�̬����
*******************************************************************************/
void CHUD::DrawStaticPrepare(CDC* p_dc)
{ 
	//����һ����ʵ��dc��ʵ�ʾ��οؼ������໥���ݵ�λͼ
	m_bitmapPlate.CreateCompatibleBitmap(p_dc, m_rectCtrl.Width(), m_rectCtrl.Height());

	//����m_dcHUDPlate��λͼѡ��
	m_pbitmapOldPlate = m_dcPlate.SelectObject(&m_bitmapPlate); 

	//����һ����ɫ��Ϊ�ڴ���ʾ�豸�ı���ɫ
	m_dcPlate.FillSolidRect(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), RGB(0, 0, 0));
}

/*! @function
********************************************************************************
* ������   : DrawStaticBackground
* ����     : ����HUD�ľ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ��������
*******************************************************************************/
void CHUD::DrawStaticBackground(CDC *pDC)
{ 
	//!	�ڴ˴������ÿؼ�����ʾ�Ĵ�С��λ��
	// ��ȡ�������ĵ�
	m_CenterPoint = m_rectCtrl.CenterPoint();
	// ������ʾ�Ĵ�С
	m_dRadius = 105;
}

/*! @function
********************************************************************************
* ������   : DrawDynamicBackground
* ����     : ����HUD�Ķ�̬����
* ����     : pDC ��ͼָ��
* ����ֵ   : void
* ��ע     : ʹ��pDCָ��������
*******************************************************************************/
void CHUD::DrawDynamicBackground(CDC *pDC)
{
	//- [3/26/2017 ��Ⱥΰ]

	// ����ƽ�����������Ϊ��ɫ                 
	currentBrush.CreateSolidBrush(RGB(0, 0, 0));
	pDC->FillRect(&m_rectCtrl, &currentBrush);
	currentBrush.DeleteObject();
	// ���ƿ̶Ⱥ�Բ
	DrawTickCircle(pDC);
	// ������պʹ��
	DrawSkyGround(pDC);
	// ��������������
	DrawTriangle(pDC);
	// ���Ʒɻ�
	DrawAerofoil(pDC);
	// ��������ˮƽ��
	DrawCenterHorizontal(pDC);

}





////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//-[3/26/2017 ��Ⱥΰ] 

/**************************************************************************************
 * ������	��DrawTickCircle
 * ����		�����ƿ̶Ⱥ�Բ
 * ����		��pDC ��ͼָ��
 * ����ֵ   : void
 * ˵��  	�����Ƶ�ƽ�Ǻ���ǿ̶Ⱥ�Բ,�Ȼ��̶��ٻ�ԲЧ������
 * ����		����Ⱥΰ
 * ����		��[3/26/2017]
 **************************************************************************************/
inline void CHUD::DrawTickCircle(CDC *pDC)
{
	// ��Բ���ϵĿ̶�
	double dTickLength = 3.0 / 25.0*m_dRadius;	// �̶ȵĳ���
	double dCurrentAngle = 0.0;					// ÿ���̶�������Ӧ�ĽǶ�
	double dSinCurrentAngle = 0.0;				// ÿ���̶�������Ӧ�ĽǶȵ�����ֵ
	double dCosCurrentAngle = 0.0;				// ÿ���̶�������Ӧ�ĽǶȵ�����ֵ
	double powNegJ = 0.0;						// pow(-1, j)��ֵ
	CPoint ptTickStart;							// �̶ȵ����
	CPoint ptTickEnd;							// �̶ȵ��յ�

//- ON  ��̬�̶�
//- OFF ��̬�̶�
#if ON
	for (int i = 0; i < 16; i++)
	{
		// ���ÿ̶ȵ���ɫ
		switch (i)
		{
			// 0��̶ȱ�ʶ�������λ�ã���Ϊ��յ���ɫ
		case 0:
			currentPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			break;
			// +- 10�㣬+- 20��̶���Ϊ��ɫ
		case 1:
		case 2:
		case 14:
		case 15:
			currentPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			break;
			// 180��̶ȱ�ʶ�������λ�ã���Ϊ��ɫ������
		case 8:
			//!currentPen.CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			//!break;
			// +- 90��̶�Ϊ��ɫ
		case 5:
		case 11:
			currentPen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
			break;
			// �����Ƕȿ̶���Ϊ��ɫ
		default:
			currentPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			break;
		}
		// �̶ȼ����С����
		if (i < 3)			// �����ɫ
			dCurrentAngle = (i * 10 + m_TSPIDC.m_ANGR) * PI / 180;
		else if (i >= 14)	// �ұ���ɫ
			dCurrentAngle = (i * 10 - 160 + m_TSPIDC.m_ANGR) * PI / 180;
		else
			dCurrentAngle = ((i - 2) * 30 + m_TSPIDC.m_ANGR)* PI / 180;

		// ����̶������յ�����
		dSinCurrentAngle = sin(dCurrentAngle);
		dCosCurrentAngle = cos(dCurrentAngle);
		ptTickStart.x = (int)(m_CenterPoint.x - m_dRadius*dSinCurrentAngle);
		ptTickStart.y = (int)(m_CenterPoint.y - m_dRadius*dCosCurrentAngle);
		ptTickEnd.x = (int)(ptTickStart.x - dTickLength*dSinCurrentAngle);
		ptTickEnd.y = (int)(ptTickStart.y - dTickLength*dCosCurrentAngle);

		// ���̶�
		pDC->SelectObject(&currentPen);
		pDC->MoveTo(ptTickStart);
		pDC->LineTo(ptTickEnd);
		currentPen.DeleteObject();
	}
#else
	for (int j = 0; j < 2; j++)
	{
		powNegJ = pow(-1, j);
		for (int i = 0; i < 9; i++)
		{
			// ���ÿ̶ȵ���ɫ
			switch (i)
			{
				// 0����ɫ�̶�
			case 0:
				currentPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
				break;
				// 10�㣬20����ɫ�̶�
			case 1:
			case 2:
				currentPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
				break;
				//�����Ƕ�Ϊ��ɫ�̶�
			default:
				currentPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
				break;
			}
			// �̶ȼ����С����
			if (i < 4)
				dCurrentAngle = i * 10 * PI / 180;
			else
				dCurrentAngle = (i - 2) * 30 * PI / 180;
			// ����̶������յ�����
			dSinCurrentAngle = sin(dCurrentAngle);
			dCosCurrentAngle = cos(dCurrentAngle);
			ptTickStart.x = (int)(m_CenterPoint.x - powNegJ*m_dRadius*dSinCurrentAngle);
			ptTickStart.y = (int)(m_CenterPoint.y - m_dRadius*dCosCurrentAngle);
			ptTickEnd.x = (int)(ptTickStart.x - powNegJ*dTickLength*dSinCurrentAngle);
			ptTickEnd.y = (int)(ptTickStart.y - dTickLength*dCosCurrentAngle);
			// ���̶�
			pDC->SelectObject(&currentPen);
			pDC->MoveTo(ptTickStart);
			pDC->LineTo(ptTickEnd);
			currentPen.DeleteObject();
		}
	}
#endif
	// ��������Բ
	currentPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->SelectObject(&currentPen);
	CRect rectCenterArc(m_CenterPoint.x - 27.0 / 24.0*m_dRadius, m_CenterPoint.y - 27.0 / 24.0*m_dRadius,
		m_CenterPoint.x + 27.0 / 24.0*m_dRadius, m_CenterPoint.y + 27.0 / 24.0*m_dRadius);
	pDC->Arc(rectCenterArc,
		CPoint(m_CenterPoint.x + m_dRadius, m_CenterPoint.y),
		CPoint(m_CenterPoint.x + m_dRadius, m_CenterPoint.y));
	currentPen.DeleteObject();

	// ���ڲ�СԲ
	currentPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->SelectObject(&currentPen);
	rectCenterArc.DeflateRect(3.0 / 25.0*m_dRadius, 3.0 / 25.0*m_dRadius);
	pDC->Arc(rectCenterArc,
		CPoint(m_CenterPoint.x + m_dRadius, m_CenterPoint.y),
		CPoint(m_CenterPoint.x + m_dRadius, m_CenterPoint.y));
	currentPen.DeleteObject();
}

/**************************************************************************************
 * ������	��DrawSkyGround	
 * ����		��������պʹ��
 * ����		��pDC ��ͼָ��
 * ����ֵ   : void
 * ˵��  	�����ƶ�̬����պʹ��
 * ����		����Ⱥΰ
 * ����		��[3/26/2017]
 **************************************************************************************/
inline void CHUD::DrawSkyGround(CDC *pDC)
{
	// �ü����������Σ�����������Բ 
	CRgn rgn, rgnRect, inCircle; 
	// ������
	CRect rect((int)(m_CenterPoint.x - m_dRadius), (int)(m_CenterPoint.y - m_dRadius),
		(int)(m_CenterPoint.x + m_dRadius), (int)(m_CenterPoint.y + m_dRadius));
	// ѡ�������ξ��ο�
	rgnRect.CreateRectRgnIndirect(rect);
	// ѡ�������ξ��ο�����Բ
	inCircle.CreateEllipticRgnIndirect(rect);
	// �ü�������Բ����
	rgn.CreateRectRgn(0, 0, 0, 1);
	rgn.CombineRgn(&rgnRect, &inCircle, RGN_AND);
	pDC->SelectClipRgn(&rgn);

	// ������ɫ��ˢ�����������Բ
	currentBrush.CreateSolidBrush(RGB(0, 0, 255));
	pDC->SelectObject(&currentBrush);
	pDC->FillRgn(&rgn, &currentBrush);
	currentBrush.DeleteObject();

	// Ȼ���ó�ɫ��ˢ���Ƶ�ƽ�ǵĵ��沿��
	currentBrush.CreateSolidBrush(RGB(130, 80, 0));
	pDC->SelectObject(&currentBrush);

	CRgn rgnArc;		// �����Բ�βü���
	CPoint ptArcStart;	// �������Բ�����
	CPoint ptArcEnd;	// �������Բ���յ�

	// ���������Ƿ���
	ptArcStart.x = m_CenterPoint.x - m_dRadius*cos(m_TSPIDC.m_ANGR*PI / 180.0);
	ptArcStart.y = m_CenterPoint.y + m_dRadius*sin(m_TSPIDC.m_ANGR*PI / 180.0);
	// �����븩���Ƿ���
	ptArcStart.x = ptArcStart.x + m_TSPIDC.m_ANGP/30.0*m_dRadius*sin(m_TSPIDC.m_ANGR*PI / 180.0);
	ptArcStart.y = ptArcStart.y + m_TSPIDC.m_ANGP / 30.0*m_dRadius*cos(m_TSPIDC.m_ANGR*PI / 180.0);
	// �յ�������Ƿ���
	ptArcEnd.x = m_CenterPoint.x + m_dRadius*cos(m_TSPIDC.m_ANGR*PI / 180.0);
	ptArcEnd.y = m_CenterPoint.y - m_dRadius*sin(m_TSPIDC.m_ANGR*PI / 180.0);
	// �յ���븩���Ƿ���
	ptArcEnd.x = ptArcEnd.x + m_TSPIDC.m_ANGP / 30.0*m_dRadius*sin(m_TSPIDC.m_ANGR*PI / 180.0);
	ptArcEnd.y = ptArcEnd.y + m_TSPIDC.m_ANGP / 30.0*m_dRadius*cos(m_TSPIDC.m_ANGR*PI / 180.0);

	// Ϊ�ü�����һ��·����
	pDC->BeginPath();
	pDC->Arc(&rect, ptArcStart, ptArcEnd);
	// �ر�·����
	pDC->EndPath();
	// ��·��ת��Ϊ������������
	rgnArc.CreateFromPath(pDC);
	pDC->FillRgn(&rgnArc, &currentBrush);

	currentBrush.DeleteObject();
}

/**************************************************************************************
* ������	��DrawTriangle
* ����		����������������
* ����		��pDC ��ͼָ��
* ����ֵ   : void
* ˵��  	����ɫ������  ��ʶ�����Ϊ0�����ڵ�λ��
			  ��ɫ������  ��ʶ�ɻ������Ϸ�
* ����		����Ⱥΰ
* ����		��[3/26/2017]
**************************************************************************************/
inline void CHUD::DrawTriangle(CDC *pDC)
{
	/*****************************���ƶ�̬��ɫʵ��������***********************************/
	currentBrush.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(&currentBrush);
	ptTriangle[0].x = (int)(m_CenterPoint.x - 146.0 / 150.0*m_dRadius*sin(m_TSPIDC.m_ANGR*PI / 180));
	ptTriangle[0].y = (int)(m_CenterPoint.y - 146.0 / 150.0*m_dRadius*cos(m_TSPIDC.m_ANGR*PI / 180));
	ptTriangle[1].x = (int)(m_CenterPoint.x - (13 / 16.0*m_dRadius)*sin(m_TSPIDC.m_ANGR*PI / 180 - PI / 48.0));
	ptTriangle[1].y = (int)(m_CenterPoint.y - (13 / 16.0*m_dRadius)*cos(m_TSPIDC.m_ANGR*PI / 180 - PI / 48.0));
	ptTriangle[2].x = (int)(m_CenterPoint.x - (13 / 16.0*m_dRadius)*sin(m_TSPIDC.m_ANGR*PI / 180 + PI / 48.0));
	ptTriangle[2].y = (int)(m_CenterPoint.y - (13 / 16.0*m_dRadius)*cos(m_TSPIDC.m_ANGR*PI / 180 + PI / 48.0));
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(ptTriangle, 3);
	currentBrush.DeleteObject();

	/***************************���ƶ�����̬��ɫʵ��С������*******************************/
	currentBrush.CreateSolidBrush(RGB(0, 255, 0));
	currentPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pDC->SelectObject(&currentPen);
	pDC->SelectObject(&currentBrush);
	ptTriangle[0].x = (int)(m_CenterPoint.x);
	ptTriangle[0].y = (int)(m_CenterPoint.y - 146.0 / 150.0*m_dRadius);
	ptTriangle[1].x = (int)(m_CenterPoint.x - (13.0 / 16.0*m_dRadius)*sin(-PI / 48.0));
	ptTriangle[1].y = (int)(m_CenterPoint.y - (13.0 / 16.0*m_dRadius)*cos(-PI / 48.0));
	ptTriangle[2].x = (int)(m_CenterPoint.x - (13.0 / 16.0*m_dRadius)*sin(PI / 48.0));
	ptTriangle[2].y = (int)(m_CenterPoint.y - (13.0 / 16.0*m_dRadius)*cos(PI / 48.0));
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(ptTriangle, 3);
	currentPen.DeleteObject();
	currentBrush.DeleteObject();
}

/**************************************************************************************
 * ������	��DrawAerofoil	
 * ����		�����Ʒɻ�
 * ����		��pDC ��ͼָ��
 * ����ֵ   : void
 * ˵��  	�����ƾ�̬�ɻ�
 * ����		����Ⱥΰ
 * ����		��[3/26/2017]
 **************************************************************************************/
inline void CHUD::DrawAerofoil(CDC *pDC)
{
	// ���ɻ������ĵ�
	CRect rectCenterSpot(m_CenterPoint.x - 2, m_CenterPoint.y - 2, m_CenterPoint.x + 2, m_CenterPoint.y + 2);
	pDC->FillSolidRect(rectCenterSpot, RGB(0, 255, 0));
	// ���ɻ��Ļ���
	const int AerofoilLeng = 80;	// ����ĳ���
	const int AerofoilLengEx = 12;	// ����ֱ���ֵĳ���
	currentPen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	pDC->SelectObject(&currentPen);
	for (int i = 0; i < 2; i++)
	{
		int flage = pow(-1, i);
		// ��������������ת
		ptTriangle[0].x = m_CenterPoint.x - flage*AerofoilLeng;
		ptTriangle[0].y = m_CenterPoint.y;
		ptTriangle[1].x = m_CenterPoint.x - flage*AerofoilLeng*8.0 / 25.0;
		ptTriangle[1].y = m_CenterPoint.y;
		ptTriangle[2].x = ptTriangle[1].x;
		ptTriangle[2].y = ptTriangle[1].y + AerofoilLengEx;
		pDC->MoveTo(ptTriangle[0]);
		pDC->LineTo(ptTriangle[1]);
		pDC->LineTo(ptTriangle[2]);
	}
	currentPen.DeleteObject();
}

/**************************************************************************************
 * ������	��DrawCenterHorizontal	
 * ����		����������ˮƽ��
 * ����		��pDC ��ͼָ��
 * ����ֵ   : void
 * ˵��  	�����ƶ�̬ˮƽ��(��ʾ������)
 * ����		����Ⱥΰ
 * ����		��[3/26/2017]
 **************************************************************************************/
inline void CHUD::DrawCenterHorizontal(CDC *pDC)
{
	// �̶��Եĸ�������ֵ
	CString strNumAngP;		
	// ���û���
	currentPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(&currentPen);
	// ��������
	currentFont.CreateFont((int)(0.14 * m_dRadius), 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FF_ROMAN, _T("����"));
	pDC->GetTextMetrics(&tm);
	pDC->SelectObject(&currentFont);
	pDC->SetBkMode(TRANSPARENT);	// ���屳��ɫ͸�� 
	// ��������ˮƽ��
	for (int j = 0; j < 2; j++)
	{
		// �������߶���ʾ����
		int PNflag = pow(-1, j);

		CPoint ptscale[3]; // ���ֲ�ͬ���ȵ�ˮƽ�ߵ����������� 
		for (int i = 0; i <= 17; i++)
		{	//+ 0�㣬1�㣬2�㣬3�㣬4�㣬5�� ��������
			if (i < 5)
			{
				// ����ˮƽ������������
				ptscale[0].x = m_CenterPoint.x - 5.0 / 100.0*m_dRadius;
				ptscale[0].y = m_CenterPoint.y - 1.0 / 30.0*PNflag*i*m_dRadius+m_TSPIDC.m_ANGP/30.0*m_dRadius;
				//+ ��̶���
				if (0 == i)
				{
					pDC->SetTextColor(RGB(255, 0, 0));
					// ��ߵ�����
					pDC->TextOutW(ptscale[0].x - 15, ptscale[0].y - 6, _T("0"));
					// �ұߵ�����
					pDC->TextOutW(ptscale[0].x + 20.0 / 100.0*m_dRadius, ptscale[0].y - 6, _T("0"));
					// ����ˮƽ��
					pDC->MoveTo(m_CenterPoint.x - 10.0 / 100.0*m_dRadius, ptscale[0].y);
					pDC->LineTo(m_CenterPoint.x + 10.0 / 100.0*m_dRadius, ptscale[0].y);

				}
				// ����ˮƽ��
				pDC->MoveTo(ptscale[0].x, ptscale[0].y);
				pDC->LineTo(ptscale[0].x + 11.0 / 100.0*m_dRadius, ptscale[0].y);
			}
			//+ 5�㣬15�㣬25��... 85��  ��������
			if (0 != i % 2)
			{
				// ����ˮƽ������������
				ptscale[1].x = m_CenterPoint.x - 18.0 / 100.0*m_dRadius;
				ptscale[1].y = m_CenterPoint.y - 5.0 / 30.0*PNflag*i*m_dRadius + m_TSPIDC.m_ANGP / 30.0*m_dRadius;
				// ˮƽ�ߵ���ֵ
				strNumAngP.Format(L"%d", i * 5);
				pDC->SetTextColor(RGB(255, 255, 255));
				// ��ʾ��ߵ�����
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOutW(ptscale[1].x - 5, ptscale[1].y - 6, strNumAngP);
				// ��ʾ�ұߵ�����
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOutW(ptscale[1].x + 41.0 / 100.0*m_dRadius, ptscale[1].y - 6, strNumAngP);
				// ����ˮƽ��
				pDC->MoveTo(ptscale[1].x, ptscale[1].y);
				pDC->LineTo(m_CenterPoint.x + 18.0 / 100.0*m_dRadius, ptscale[1].y);
			}
			//+ 10�㣬20�㣬30��... 90��  ��������
			if ((i <= 9) && (i>0))
			{
				// ����ˮƽ������������
				ptscale[2].x = m_CenterPoint.x - 30.0 / 100.0*m_dRadius;
				ptscale[2].y = m_CenterPoint.y - 10.0 / 30.0*PNflag*i*m_dRadius + m_TSPIDC.m_ANGP / 30.0*m_dRadius;
				strNumAngP.Format(L"%d", i * 10);
				// ��ߵ�����
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOutW(ptscale[2].x - 5, ptscale[2].y - 6, strNumAngP);
				// �ұߵ�����
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOutW(ptscale[2].x + 65.0 / 100.0*m_dRadius, (int)ptscale[2].y - 6, strNumAngP);
				// ����ˮƽ��
				pDC->MoveTo(ptscale[2].x, ptscale[2].y);
				pDC->LineTo(m_CenterPoint.x + 30.0 / 100.0*m_dRadius, ptscale[2].y);
			}
		}
	}
	currentFont.DeleteObject();
	currentPen.DeleteObject();
}



