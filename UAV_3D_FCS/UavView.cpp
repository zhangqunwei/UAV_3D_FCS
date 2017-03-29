#include "stdafx.h"
#include "UavView.h"


CUavView::CUavView()
{
	memset(&m_TSPIDC, 0, sizeof(m_TSPIDC));
}


CUavView::~CUavView()
{
}


BEGIN_MESSAGE_MAP(CUavView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CUavView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

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
	DrawDynamicBackground(&m_dcPlate);

	//���������ڻ�����ɵ�λͼһ���Կ�������ʾ������ʾ
	memDC.BitBlt(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), &m_dcPlate, 0, 0, SRCCOPY);

	
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
void CUavView::SetCurrentData(const TSPIDC& tspidc)
{
	//���ݸ��¸�ֵ
	m_TSPIDC = tspidc;
	//�ػ�
	Invalidate();
}



/*! @function
********************************************************************************
* ������   : DrawStaticPrepare
* ����     : ��ͼ����
* ����     : void
* ����ֵ   : void
* ��ע     : ���ƿؼ��ľ�̬����
*******************************************************************************/
void CUavView::DrawStaticPrepare(CDC* pDC)
{
	//����һ����ʵ��dc��ʵ�ʾ��οؼ������໥���ݵ�λͼ
	m_bitmapPlate.CreateCompatibleBitmap(pDC, m_rectCtrl.Width(), m_rectCtrl.Height());

	//����m_dcHUDPlate��λͼѡ��
	m_pbitmapOldPlate = m_dcPlate.SelectObject(&m_bitmapPlate);

	//����һ����ɫ��Ϊ�ڴ���ʾ�豸�ı���ɫ
	m_dcPlate.FillSolidRect(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), RGB(0, 0, 0));
}

 

/*********************************************************
������   :	DrawGraphicText
����     :	���������ı�����
����     :	[IN] :	p_dc CDCָ��
			p_show_text Ҫ��ʾ���ı�����
			p_start_x ��ʼ����
			p_start_y ��������
			p_font_type ��ʾ������
			p_font_size ��ʾ�������С
			p_color ��ʾ����ɫ��Ĭ��Ϊ��ɫ
			[OUT] :	��
			����ֵ   : ��
��ע     :
ʱ��     : 2017/3/6 �µ���
**********************************************************/
void CUavView::DrawUavText(CDC* p_dc, const CString& p_show_text, int p_start_x, int p_start_y, CString p_font_type, int p_font_size, COLORREF p_color)
{

	CFont currentFont;

	currentFont.CreatePointFont(p_font_size, p_font_type, nullptr);

	CFont* pOldFont = p_dc->SelectObject(&currentFont);

	p_dc->SetTextColor(p_color);

	//�����ı�
	p_dc->TextOut(p_start_x, p_start_y, p_show_text);

	p_dc->SelectObject(pOldFont);
}


/*********************************************************
������   :	DrawGraphicText
����     :	���������ı�����
����     :	[IN] :	p_dc CDCָ��
			point_up_left ���������Ͻ�����
			point_low_right ���������½�����
			p_color ��ʾ����ɫ
			p_line_width �߿�
			p_line_type ������
[OUT] :	��
����ֵ   : ��
��ע     :
ʱ��     : 2017/3/9 �µ���
**********************************************************/
void CUavView::DrawCricle(CDC* p_dc, POINT point_up_left, POINT point_low_right, COLORREF p_color, int p_line_width, int p_line_type)
{
	//��Ϊ����ֵ
	if (!p_dc || !p_dc->GetSafeHdc())
	{
		return;
	}

	//ѡ�񻭱�
	CPen pen(p_line_type, p_line_width, p_color);

	CPen* p_OldPen = p_dc->SelectObject(&pen);

	//ѡ��ָ����ɫ�Ļ�ˢ
	//CBrush brush(p_color);
	
	CBrush* pBrush = CBrush::FromHandle(static_cast<HBRUSH>(GetStockObject(NULL_BRUSH)));
	CBrush* p_OldBrush = p_dc->SelectObject(pBrush);
	//��Բ
	p_dc->Ellipse(CRect(point_up_left, point_low_right));
	//p_dc->Ellipse(point_up_left.x, point_up_left.y, point_low_right.x, point_low_right.y);

	//�ָ�֮ǰ�Ļ���
	p_dc->SelectObject(p_OldPen);
	p_dc->SelectObject(p_OldBrush);
}