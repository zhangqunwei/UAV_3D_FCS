// Graphic.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "../stdafx.h"
//#include "GraphicTest-1.h"
#include "Graphic.h"
#include "../resource.h"

#include <cmath>

CRITICAL_SECTION g_csA;

 

// CGraphic

IMPLEMENT_DYNAMIC(CGraphic, CWnd)

CGraphic::CGraphic() :
m_slider_zoom(0),
m_y_graduation_num(GraphicCoordinate::y_graduation_num),
m_y_graduation_offset(GraphicCoordinate::y_graduation_offset),
m_cur_model(Graphic::MonitoringModel),
m_cur_time(_T("00:00:00:000"))
{
	InitializeCriticalSection(&g_csA);
	 
	double start_x_scale = 0.05;
 
	//0.05 -> 0.93 - GraphicCoordinate::y_graduation_length_scale = 0.92
	for (int i = 0; i < Graphic::Deque_Point_Num; i++)
	{
		start_x_scale += GraphicCoordinate::x_offset;// = 0.0174
		m_x_scale_vec.push_back(start_x_scale);
	}
}

CGraphic::~CGraphic()
{
	DeleteCriticalSection(&g_csA);
}


BEGIN_MESSAGE_MAP(CGraphic, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CGraphic ��Ϣ�������

//void CGraphic::ReconstructControl()
//{
//	  Invalidate();
//}



void CGraphic::OnPaint()
{ 
	CPaintDC dc(this);  

	//����������͵Ļ���
	CPen PenForDraw(PS_SOLID, 1, RGB(0, 232, 255));

	//���Ի����о�̬�ı���ؼ��Ĵ�С���긳��m_rectCtrl	
	GetClientRect(&m_rectCtrl);

	//memDCΪһ�����dc����CMemoryDC��Ĺ��캯���н�ʵ�ʵ�dc
	CMemoryDC memDC(&dc, &m_rectCtrl);

	//����Ҫ��ʱ��Ż��Ʊ������֣�����ֻ��������
	if (m_requiresRedraw)
	{
		if ((m_dcPlate == nullptr) || (m_bitmapPlate.m_hObject == nullptr))
		{
			m_dcPlate.CreateCompatibleDC(&dc);

			DrawStaticInOnPaint(&dc);
		}
		else
		{
			m_dcPlate.DeleteDC();
			m_dcPlate.CreateCompatibleDC(&dc);
			m_bitmapPlate.DeleteObject();

			DrawStaticInOnPaint(&dc);
		}

		m_requiresRedraw = false;
	}

	//���ڴ��л��õ�ͼ��ֱ�ӿ�������Ļָ��������
	memDC->BitBlt(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), &m_dcPlate, 0, 0, SRCCOPY);

	//��������
	DrawDynamicCurve(&memDC, m_ChartDataDeque);
}




/*********************************************************
������   :	DrawStaticInOnPaint
����     :	������OnPaint�л��ƾ�̬�ı��ĳ�ʼ���;������
����     :	[IN]	: p_dc DCָ��
			[OUT]	: ��
����ֵ   : ��
��ע     :  
ʱ��     : 2016/8/10 �µ���
**********************************************************/
void CGraphic::DrawStaticInOnPaint(CDC* p_dc)
{ 
	m_bitmapPlate.DeleteObject();
	//����һ���ڴ��е�ͼ�� 
	m_bitmapPlate.CreateCompatibleBitmap(p_dc, m_rectCtrl.Width(), m_rectCtrl.Height());

	//ָ���ڴ���ʾ�豸���ڴ��е�ͼ���ϻ�ͼ
	m_pbitmapOldPlate = m_dcPlate.SelectObject(&m_bitmapPlate);

	//����һ����ɫ��Ϊ�ڴ���ʾ�豸�ı���ɫ
	m_dcPlate.FillSolidRect(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), RGB(1, 4, 1));

	//����������
	//DrawStaticAxis(&m_dcPlate, _T("/s"), _T("/") + m_cur_y_unit);
	DrawStaticAxis(&m_dcPlate, _T("/s"), m_cur_y_unit);

	//����Y��Ķ�̬�̶�ֵ
	DrawDynamicYScale(&m_dcPlate, m_y_min, m_y_max);
}


 

/*********************************************************
������   : DrawStaticAxis
����     : ��������ϵ�еľ�̬Ԫ��
����     :	[IN]	:	CDCָ��
					:	X�ᵥλ
					:	Y�ᵥλ
			[OUT]	: ��
����ֵ   : ��
��ע     :  ��������X��Y��ĵ�λ
ʱ��     : 2016/8/17 �µ���
**********************************************************/
void CGraphic::DrawStaticAxis(CDC* CDC, const CString p_x_unit, const CString p_y_unit)
{
	using namespace GraphicCoordinate;

	//��ÿؼ�����
	GetClientRect(&m_rectCtrl); 

	//ѡ��������ĺ�ɫ����
	CPen PenForDrawAxis(PS_SOLID, 1, GraphicColor::WHITE);
	CDC->SelectObject(PenForDrawAxis);

	//�õ�ԭ������
	POINT ordinary_point = GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale);
 
	//�õ�x���յ�����
	POINT x_end_point = GetRealPoint(m_rectCtrl, x_scale_of_x_end, y_scale_of_x_end);

	//�õ�y���յ�����
	POINT y_end_point = GetRealPoint(m_rectCtrl, x_scale_of_y_end, y_scale_of_y_end);


	//����X��
	DrawLine(CDC, ordinary_point, x_end_point);

	//���Ƶ�ǰʱ��
	DrawGraphicText(CDC, m_cur_time, ordinary_point.x - 35, ordinary_point.y + 8, font_type, coordinate_cur_time_font_size);

	//�������Y��
	DrawLine(CDC, ordinary_point, y_end_point);

	//�����Ҳ�Y��
	DrawLine(CDC, GetRealPoint(m_rectCtrl, right_y_start_x_scale, right_y_start_y_scale), GetRealPoint(m_rectCtrl, right_y_end_x_scale, right_y_end_y_scale));

	//����X���ͷ
	DrawLine(CDC, x_end_point, GetRealPoint(m_rectCtrl, x_arrow_end_x_scale, x_arrow_start_y_scale_top));
	DrawLine(CDC, x_end_point, GetRealPoint(m_rectCtrl, x_arrow_end_x_scale, x_arrow_start_y_scale_bot));

	//����X�ᵥλ
	DrawGraphicText(CDC, p_x_unit, x_end_point.x + 5, x_end_point.y - 7, font_type, x_unit_font_size);

	//�������Y���ͷ
	DrawLine(CDC, y_end_point, GetRealPoint(m_rectCtrl, y_arrow_end_x_scale_left, y_arrow_end_y_scale));
	DrawLine(CDC, y_end_point, GetRealPoint(m_rectCtrl, y_arrow_end_x_scale_right, y_arrow_end_y_scale));
	 
	//����Y�ᵥλ
	//DrawGraphicText(CDC, p_y_unit, y_end_point.x - 40, y_end_point.y, font_type, y_unit_font_size);


	CString min_str("");
	CString max_str("");
	min_str.Format(_T("%.2f"), m_value_min);
	max_str.Format(_T("%.2f"), m_value_max);
	
	//DrawGraphicText(CDC, m_cur_data_name + _T("[") + min_str + _T(",") + max_str + _T("]"), y_end_point.x + 10, y_end_point.y, font_type, y_data_name_font_size, GraphicColor::RED);
	//_T("[") + min_str + _T(",") + max_str + _T("]")
	//���Ƶ�ǰ�������Ƽ����ݵ�λ
	//DrawGraphicText(CDC, m_cur_data_name, y_end_point.x + 10, y_end_point.y, font_type, y_data_name_font_size, GraphicColor::WHITE);
	DrawGraphicText(CDC, m_cur_data_name + _T("(") + p_y_unit + _T(")"), y_end_point.x + 10, y_end_point.y, font_type, y_data_name_font_size, GraphicColor::WHITE);

	//���Ƶ�ǰ���ݷ�Χ
	DrawGraphicText(CDC, _T("Value[") + min_str + _T(",") + max_str + _T("]"), y_end_point.x + 650, y_end_point.y, font_type, y_data_name_font_size, GraphicColor::RED);





	POINT start_point;
	POINT end_point;
	CString show_str("");

	//����X��10���̶���
	for (int i = 0; i < x_graduation_num; i++)
	{
		start_point = GetRealPoint(m_rectCtrl,
			x_graduation_offset * i + ordinary_x_scale,
			ordinary_y_scale);

		end_point = GetRealPoint(m_rectCtrl,
			x_graduation_offset * i + ordinary_x_scale,
			ordinary_y_scale - x_graduation_length_scale);

		DrawLine(CDC, start_point, end_point);  

		//���ƺ�����ʱ��̶ȣ����1s
		if (0 == i)
		{
			continue;
		}
		 
		show_str.Format(_T("%d.%d"), i, 0); 
		//show_str.Format(_T("%.1f"), i);
		//����x���ı�������ڿ̶�����10������5�����壬��С��120
		DrawGraphicText(CDC, show_str, start_point.x - 10, start_point.y + 5, font_type, 120);
		 
	} 

	//��������Y��Ŀ̶���
	//for (int i = 0; i < y_graduation_num + 1; i++)
	//for (int i = 0; i < m_y_graduation_num + 1; i++)
	//for (int i = 0; i < m_y_graduation_num; i++)
	{
		//2 * y_graduation_offsetΪ��һ���̶���(����������)��y����������Ϸ���λ�ñ���
		//0.9 - (0.046 * 15 + 0.046 * 2) = 0.118
// 		DrawLine(CDC,
// 			GetRealPoint(m_rectCtrl, ordinary_x_scale, -y_graduation_offset * i + ordinary_y_scale - 2 * y_graduation_offset),
// 			GetRealPoint(m_rectCtrl, ordinary_x_scale + y_graduation_length_scale, -y_graduation_offset * i + ordinary_y_scale - 2 * y_graduation_offset));
// 
// 		 
// 		DrawLine(CDC,
// 			GetRealPoint(m_rectCtrl, right_y_end_x_scale, -y_graduation_offset * i + ordinary_y_scale - 2 * y_graduation_offset),
// 			GetRealPoint(m_rectCtrl, right_y_end_x_scale - y_graduation_length_scale, -y_graduation_offset * i + ordinary_y_scale - 2 * y_graduation_offset));

// 		DrawLine(CDC,
// 			GetRealPoint(m_rectCtrl, ordinary_x_scale, -m_y_graduation_offset * i + ordinary_y_scale - m_y_graduation_offset),
// 			GetRealPoint(m_rectCtrl, ordinary_x_scale + y_graduation_length_scale, -m_y_graduation_offset * i + ordinary_y_scale - m_y_graduation_offset));
// 
// 
// 		DrawLine(CDC,
// 			GetRealPoint(m_rectCtrl, right_y_end_x_scale, -m_y_graduation_offset * i + ordinary_y_scale - m_y_graduation_offset),
// 			GetRealPoint(m_rectCtrl, right_y_end_x_scale - y_graduation_length_scale, -m_y_graduation_offset * i + ordinary_y_scale - m_y_graduation_offset));
// 		 
	}

	//�����Ϸ�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - y_graduation_offset * (y_graduation_num) - first_y_graduation_offset - red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - y_graduation_offset * (y_graduation_num) - first_y_graduation_offset - red_line_y_offset / 2), GraphicColor::RED);
	//�����Ϸ��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - y_graduation_offset * (y_graduation_num) - first_y_graduation_offset + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - y_graduation_offset * (y_graduation_num) - first_y_graduation_offset + red_line_y_offset), GraphicColor::RED);

	//�����Ϸ�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num) - m_y_graduation_offset - red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset - red_line_y_offset / 2), GraphicColor::RED);
	//�����Ϸ��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num) - m_y_graduation_offset + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset + red_line_y_offset), GraphicColor::RED);

	 
	//�����Ϸ�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num) - m_y_graduation_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset), GraphicColor::RED);
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, y_scale_of_y_end + (m_y_graduation_offset * temp_red_line_scale) - red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, y_scale_of_y_end + (m_y_graduation_offset * temp_red_line_scale) - red_line_y_offset / 2), GraphicColor::RED);
	//�����Ϸ��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset + red_line_y_offset), GraphicColor::RED);
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, y_scale_of_y_end + (m_y_graduation_offset * temp_red_line_scale) + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, y_scale_of_y_end + (m_y_graduation_offset * temp_red_line_scale) + red_line_y_offset), GraphicColor::RED);






	/////////////////////////////////�·�/////////////////////////////////////////




	//�����·��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - 2 * y_graduation_offset - red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - 2 * y_graduation_offset - red_line_y_offset), GraphicColor::RED);
	//�����·�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - 2 * y_graduation_offset + red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - 2 * y_graduation_offset + red_line_y_offset / 2), GraphicColor::RED);
	


	//�����·��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset - red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset - red_line_y_offset), GraphicColor::RED);
	//�����·�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset + red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset + red_line_y_offset / 2), GraphicColor::RED);



	//�����·��ڲ����
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - (m_y_graduation_offset * temp_red_line_scale) - red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - (m_y_graduation_offset * temp_red_line_scale) - red_line_y_offset), GraphicColor::RED);
	//�����·�������
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset), GraphicColor::RED);
	//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - (m_y_graduation_offset * temp_red_line_scale) + red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - (m_y_graduation_offset * temp_red_line_scale) + red_line_y_offset / 2), GraphicColor::RED);

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
ʱ��     : 2016/8/8 �µ���
**********************************************************/
void CGraphic::DrawGraphicText(CDC* p_dc, const CString& p_show_text, int p_start_x, int p_start_y, CString p_font_type, int p_font_size, COLORREF p_color)
{

	CFont currentFont;  	

	currentFont.CreatePointFont(p_font_size, p_font_type, nullptr);

	CFont* pOldFont = p_dc->SelectObject(&currentFont);
 

	p_dc->SetTextColor(p_color); 

	//�����ı�
	p_dc->TextOut(p_start_x, p_start_y, p_show_text);

	p_dc->SelectObject(pOldFont);
}




/********************************************************************
������   :	DrawDynamicCurve
����     :	����̬������
����     :	[IN] :	MemDC �ڴ�DCָ��
					Pen ���ʵ�����
					DisplayData Ҫ��ʾ���������ݶ�������
			[OUT]	: ��
����ֵ   : ��
��ע     : �������ݷ�Χ�ĵ�ҲҪ��ʾ�ɺ�ɫ����������ʾ�ڸ澯��λ��
ʱ��     : 2016/8/18 �µ���
*********************************************************************/
void CGraphic::DrawDynamicCurve(CMemoryDC* MemDC, Graphic::Chart_Data_Queue &DisplayData)
{
	using namespace GraphicCoordinate;
	//�����ٽ���
	EnterCriticalSection(&g_csA);
 
	//���µ�ǰһ���������ݶ����е�����ʱ��Ӧ��֤�����е����궼�Ѿ�ȷ��
	if (DisplayData.size() >= 2)
	{
		POINT temp_start_point;
		POINT temp_end_point;

		POINT temp_cricle_start_point;
		POINT temp_cricle_end_point;

		for (int PointIndex = 1; PointIndex != DisplayData.size(); PointIndex++)
		{
			//��ʼ���������-������Χ
			temp_start_point.x = DisplayData[PointIndex - 1].first.xPos;
			temp_start_point.y = DisplayData[PointIndex - 1].first.yPos; 

			//��ʼ���յ�����-������Χ
			temp_end_point.x = DisplayData[PointIndex].first.xPos;
			temp_end_point.y = DisplayData[PointIndex].first.yPos;
			
			
			//ǰһ��������ݳ���Y��Max��Χ��ʾ��Y������λ��
			if (DisplayData[PointIndex - 1].second.base_data.arrive_value >  m_y_max)
			{ 
				//����y����--�ڲ����
				//temp_start_point.y = (ordinary_y_scale - ((m_value_max - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) + red_line_y_offset) * m_rectCtrl.Height();

				//����y����--������
				//temp_start_point.y = (ordinary_y_scale - ((m_value_max - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) - red_line_y_offset / 2) * m_rectCtrl.Height();

				temp_start_point.y = (ordinary_y_scale - y_graduation_offset * (GraphicCoordinate::y_graduation_num - 1)) * m_rectCtrl.Height();

				//ʹ������ܹ���׽������Y��max��Χ�ĵ�
				DisplayData[PointIndex - 1].first.yPos = temp_start_point.y;
 			}

			//��һ��������ݳ���Y��Max��Χ��ʾ��Y������λ��
			if (DisplayData[PointIndex].second.base_data.arrive_value > m_y_max)
			{ 
				//����y����--�ڲ����
				//temp_end_point.y = (ordinary_y_scale - ((m_value_max - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) + red_line_y_offset) * m_rectCtrl.Height();

				//����y����--������
				//temp_end_point.y = (ordinary_y_scale - ((m_value_max - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) - red_line_y_offset / 2) * m_rectCtrl.Height();

				temp_end_point.y = (ordinary_y_scale - y_graduation_offset * (GraphicCoordinate::y_graduation_num - 1)) * m_rectCtrl.Height();

				//ʹ������ܹ���׽������Y��max��Χ�ĵ�
				DisplayData[PointIndex].first.yPos = temp_end_point.y;

			}


			//ǰһ��������ݵ���Y��min��Χ��ʾ��Y������λ��
			if (DisplayData[PointIndex - 1].second.base_data.arrive_value < m_y_min)
			{
				//����y����-�ڲ����  
				//temp_start_point.y = (ordinary_y_scale - ((m_value_min - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) - red_line_y_offset) * m_rectCtrl.Height();

				//����y����-������
				//temp_start_point.y = (ordinary_y_scale - ((m_value_min - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) + red_line_y_offset / 2) * m_rectCtrl.Height();

				temp_start_point.y = ordinary_y_scale * m_rectCtrl.Height();

				//ʹ������ܹ���׽��С��Y��min��Χ�ĵ�
				DisplayData[PointIndex - 1].first.yPos = temp_start_point.y;
			} 

			//��һ��������ݵ���Y��min��Χ��ʾ��Y������λ��
			if (DisplayData[PointIndex].second.base_data.arrive_value < m_y_min)
			{ 
				//����y����-�ڲ���� 
				//temp_end_point.y = (ordinary_y_scale - ((m_value_min - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) - red_line_y_offset) * m_rectCtrl.Height();

				//����y����-������
				//temp_end_point.y = (ordinary_y_scale - ((m_value_min - m_y_min) / (m_y_max - m_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset)) + red_line_y_offset / 2) * m_rectCtrl.Height();

				temp_end_point.y = ordinary_y_scale * m_rectCtrl.Height();

				//ʹ������ܹ���׽��С��Y��min��Χ�ĵ�
				DisplayData[PointIndex].first.yPos = temp_end_point.y;

			}
			
			
			//��һ����ɫ���ߣ�Ĭ��Ϊ��ɫ
			DrawLine(MemDC, temp_start_point, temp_end_point); 


			//��ָ����ɫ���
			temp_cricle_start_point.x = temp_start_point.x - point_radius;
			temp_cricle_start_point.y = temp_start_point.y - point_radius;

			temp_cricle_end_point.x = temp_start_point.x + point_radius;
			temp_cricle_end_point.y = temp_start_point.y + point_radius;

			
			if (GraphicColor::GREEN == DisplayData[PointIndex - 1].second.attributes.color)
			{  
				DrawCricle(MemDC, temp_cricle_start_point, temp_cricle_end_point, GraphicColor::GREEN);
			}
			else
			{
				DrawCricle(MemDC, temp_cricle_start_point, temp_cricle_end_point, GraphicColor::RED);
			}
			


			//��ָ����ɫ�յ�
			temp_cricle_start_point.x = temp_end_point.x - GraphicCoordinate::point_radius;
			temp_cricle_start_point.y = temp_end_point.y - GraphicCoordinate::point_radius;

			temp_cricle_end_point.x = temp_end_point.x + GraphicCoordinate::point_radius;
			temp_cricle_end_point.y = temp_end_point.y + GraphicCoordinate::point_radius;

			
			if (GraphicColor::GREEN == DisplayData[PointIndex].second.attributes.color)
			{
				DrawCricle(MemDC, temp_cricle_start_point, temp_cricle_end_point, GraphicColor::GREEN);
			}
			else
			{
				DrawCricle(MemDC, temp_cricle_start_point, temp_cricle_end_point, GraphicColor::RED);
			} 
			
 		}  
	}

	//�뿪�ٽ���
	LeaveCriticalSection(&g_csA); 

}
 

void CGraphic::SetCurrentData_One_Package(Graphic::Chart_Data& chart_data)
{  
	//����յ���һ��û�г�ʼ�������ݵ��ֱ�ӷ���
	if (!chart_data.second.attributes.hasInit)
	{
		return;
	} 


	//�����ǰ���߶����Ѿ�װ����Graphic::Deque_Point_Num������
	if (m_ChartDataDeque.size() >= Graphic::Deque_Point_Num)
	{
		 
		m_ChartDataDeque.pop_front(); 
		//���������ݶ��к������µ�һ���µ���������
		m_ChartDataDeque.push_back(chart_data);   
	}
	else
	{  
		m_ChartDataDeque.push_back(chart_data); 
	}  

	//ÿ�θ��¶���������߶�����ÿ��Ԫ�ص�λ��
	AdjustQueuePoint();

	//200ms�ػ�һ������
	ReconstructControl();
}



void CGraphic::SetCurrentData_One_Deque(const Graphic::Chart_Data_Queue& chart_data_deque)
{
	//�����µ�һ�����ݣ�Ӧ����Ҫ�������жϴ���
	m_ChartDataDeque = chart_data_deque;

	//�ػ�����
	ReconstructControl();

}


/*********************************************************
������   : GetRealPoint
����     : ���ݶԻ����С����Ӧ�����������ȡʵ�ʵ�����λ��
����     :	[IN]	:	rect	�ܵĳ��ȺͿ��
						x_scale	x��ı���
						y_scale	y��ı��� 
			[OUT]	: ��
����ֵ   :	ת�����ʵ�������
��ע     :  
ʱ��     : 2016/8/7 �µ���
**********************************************************/
inline POINT CGraphic::GetRealPoint(CRect rect, double x_scale, double y_scale)
{ 
	POINT temp;
	temp.x = x_scale * rect.Width();
	temp.y = y_scale * rect.Height();
	return temp; 
}



/*******************************************************************
������   : DrawLine
����     : ���ߺ���
����     :	[IN]	:	p_dc	DCָ��
						p_start	��ʼ������
						p_end	��ֹ������
						p_color	�ߵ���ɫ��Ĭ��Ϊ��ɫ
						p_line_type		�ߵ����ͣ� Ĭ��Ϊʵ��
						p_line_width	�ߵĿ�ȣ� Ĭ��Ϊ1
			[OUT]	: ��
����ֵ   : ��
��ע     :  
ʱ��     : 2016/8/7 �µ���
*******************************************************************/
void CGraphic::DrawLine(CDC* p_dc, POINT p_start, POINT p_end, COLORREF p_color, int p_line_type, int p_line_width)
{
	//��Ϊ����ֵ
	if (!p_dc || !p_dc->GetSafeHdc())
	{
		return;
	}

	//ѡ�񻭱�
	CPen pen(p_line_type, p_line_width, p_color);
	CPen* p_OldPen = p_dc->SelectObject(&pen);

	//��ʼ����
	p_dc->MoveTo(p_start);
	p_dc->LineTo(p_end);

	//�ָ�֮ǰ�Ļ���
	p_dc->SelectObject(p_OldPen);
}



void CGraphic::DrawPoint(CDC* p_dc, POINT point, COLORREF p_color, int p_line_width, int p_line_type)
{
	//��Ϊ����ֵ
	if (!p_dc || !p_dc->GetSafeHdc())
	{
		return;
	}

	//ѡ�񻭱�
	CPen pen(p_line_type, p_line_width, p_color);

	CPen* p_OldPen = p_dc->SelectObject(&pen);

	p_dc->SetPixel(point, p_color);

	//�ָ�֮ǰ�Ļ���
	p_dc->SelectObject(p_OldPen);
}


void CGraphic::DrawCricle(CDC* p_dc, POINT point_up_left, POINT point_low_right, COLORREF p_color, int p_line_width, int p_line_type)
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
	CBrush brush(p_color);
	CBrush* p_OldBrush = p_dc->SelectObject(&brush);

	//��Բ
	p_dc->Ellipse(CRect(point_up_left, point_low_right));

	//�ָ�֮ǰ�Ļ���
	p_dc->SelectObject(p_OldPen);
	p_dc->SelectObject(p_OldBrush);
}


void CGraphic::AddCoordinatePointForChartData(Graphic::Chart_Data& chart_data)
{
	//��ÿؼ�����
	GetClientRect(&m_rectCtrl);  
	//��ȡ�����ֵ
	//double arrive_value = chart_data.second.base_data.arrive_value; 


	//��ȡ�������ݵ�x����������ȵ�����������ұ�
	static int index = m_x_scale_vec.size() - 1;
	double arrive_x_scale = 0.0;
	if (index >= 0)
	{
		 arrive_x_scale = m_x_scale_vec.at(index--);
	}  


	//��ȡ�������ݵ�y���������   
	double arrive_y_scale = GetArriveYScale(chart_data);

	//�õ�ʵ�ʵ�����
 	POINT arrive_point = GetRealPoint(m_rectCtrl, arrive_x_scale, arrive_y_scale);
 	 
 	//����ʵ�����굽���������ݰ���
 	chart_data.first.xPos = arrive_point.x;
 	chart_data.first.yPos = arrive_point.y;
}




/************************************************************************************************************
������   :	DrawDynamicYScale
����     :	����̬Y��̶�
����     :	[IN]	: dcָ��
					: y����Сֵ
					: y�����ֵ
			[OUT]	: ��
����ֵ   : ��
��ע     : Y��̶ȱ���(0.9 - 0.05) / 23���ֲ��䣬�̶�����25���ֲ��䣬��24 - 1 = 23���̶ȼ�����̶�ֵ����ͨ�������仯
ʱ��     : 2016/8/18 �µ���
*************************************************************************************************************/
void CGraphic::DrawDynamicYScale(CDC* p_dc, const double p_y_min, const double p_y_max)
{
	using namespace GraphicCoordinate;

	//��ÿؼ�����
	GetClientRect(&m_rectCtrl);

	//���ݿ̶�ֵ������ÿ���̶ȼ������Ĵ�С
	double temp_scale = (p_y_max - p_y_min) / (GraphicCoordinate::y_graduation_num - 1);

	CString show_str("0.0");
	POINT left_y_point;
	POINT right_y_point;
	 
	double temp_y_scale = 0.0;

	//��������Y���24���̶���
	for (int i = 0; i < GraphicCoordinate::y_graduation_num; i++)
	{
		//����ÿ���̶��ߵ�Y������
		temp_y_scale = ordinary_y_scale - y_graduation_offset * i;// -y_graduation_offset;


		//����߿̶���
		DrawLine(p_dc,
			GetRealPoint(m_rectCtrl, ordinary_x_scale, temp_y_scale),
			GetRealPoint(m_rectCtrl, ordinary_x_scale + y_graduation_length_scale, temp_y_scale));

		//���ұ߿̶���
		DrawLine(p_dc,
			GetRealPoint(m_rectCtrl, right_y_end_x_scale, temp_y_scale),
			GetRealPoint(m_rectCtrl, right_y_end_x_scale - y_graduation_length_scale, temp_y_scale));



		//��߿̶�ֵ������
// 		left_y_point = GetRealPoint(m_rectCtrl,
// 			ordinary_x_scale - 0.02,
// 			ordinary_y_scale - y_graduation_offset * i - 0.03);

		left_y_point = GetRealPoint(m_rectCtrl,
			ordinary_x_scale,
			temp_y_scale);



		//�ұ߿̶�ֵ������
// 		right_y_point = GetRealPoint(m_rectCtrl,
// 			x_scale_of_x_end,
// 			ordinary_y_scale - y_graduation_offset * i - 0.03); 

		right_y_point = GetRealPoint(m_rectCtrl,
			x_scale_of_x_end,
			temp_y_scale);


		//������̶�ֵ
		show_str.Format(_T("%5.2f"), p_y_min + i * temp_scale); 

		//�����Y��̶�ֵ
		//DrawGraphicText(p_dc, show_str, left_y_point.x - 24, left_y_point.y + 5, font_type, y_scale_font_size, GraphicColor::WHITE);
		DrawGraphicText(p_dc, show_str, left_y_point.x - 42, left_y_point.y - 5, font_type, y_scale_font_size, GraphicColor::WHITE);

		if (0 == i)
		{
			//�ұ�0�̶Ȳ����ˣ��ᵲסx��ͷ�͵�λ
			continue;
		}
		//���ұ�Y��̶�ֵ
		//DrawGraphicText(p_dc, show_str, right_y_point.x - 13, right_y_point.y + 5, font_type, y_scale_font_size, GraphicColor::WHITE);
		DrawGraphicText(p_dc, show_str, right_y_point.x - 13, right_y_point.y - 5, font_type, y_scale_font_size, GraphicColor::WHITE);


	}





	//�����Ϸ������ߣ����ߵ�Y�������Ӧ����Max��Ӧ�ķ�ΧY���������ȡMaxY�����
	double top_red_line_scale = ordinary_y_scale - ((m_value_max - p_y_min) / (p_y_max - p_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset));
	//�����Ϸ�������
	//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, top_red_line_scale - red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, top_red_line_scale - red_line_y_offset / 2), GraphicColor::RED);
	//�����Ϸ��ڲ����
	//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, top_red_line_scale + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, top_red_line_scale + red_line_y_offset), GraphicColor::RED);
	
	//ֻ��һ������Max����
	DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, top_red_line_scale), GetRealPoint(m_rectCtrl, right_y_end_x_scale, top_red_line_scale), GraphicColor::RED);

	//�����·������ߣ����ߵ�Y�������Ӧ����Min��Ӧ�ķ�ΧY���������ȡMinY�����
	double bot_red_line_scale = ordinary_y_scale - ((m_value_min - p_y_min) / (p_y_max - p_y_min)) * (ordinary_y_scale - (y_scale_of_y_end_top_line + y_graduation_offset));
	//�����·��ڲ����
	//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, bot_red_line - red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, bot_red_line - red_line_y_offset), GraphicColor::RED);
	//�����·�������
	//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, bot_red_line + red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, bot_red_line + red_line_y_offset / 2), GraphicColor::RED);
	
	//ֻ��һ������Min����
	DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, bot_red_line_scale), GetRealPoint(m_rectCtrl, right_y_end_x_scale, bot_red_line_scale), GraphicColor::RED);


}








 






// 
// void CGraphic::DrawDynamicYScale(CDC* p_dc, const double p_y_min, const double p_y_max)
// {
// 	using namespace GraphicCoordinate;
// 
// 	//��ÿؼ�����
// 	GetClientRect(&m_rectCtrl); 
// 
// 	 
//	//double temp_scale = (p_y_max - p_y_min) / GraphicCoordinate::y_graduation_num;
//	double temp_scale = (p_y_max - p_y_min) / m_y_graduation_num;
// 	//double temp_scale = (p_max - p_min) / m_y_graduation_num;
// 	
// 	CString show_str("0.0");
// 	POINT left_y_point;
// 	POINT right_y_point;
// 	COLORREF draw_color;
// 
// 	//��������Y��̶�        16
////  	for (int i = 0; i < GraphicCoordinate::y_graduation_num + 1; i += 2)
////  	//for (int i = 0; i < m_y_graduation_num + 1; i += 2)
////  	{
////  		
////  		//if ((GraphicCoordinate::y_graduation_num - 1) == i) i++;
////  		 
////  		//����̶�ֵ����
////  // 		left_y_point = GetRealPoint(m_rectCtrl,
////  // 			ordinary_x_scale - 0.02,
////  // 			ordinary_y_scale - y_graduation_offset * i - 2 * y_graduation_offset - 0.03);
////  // 
////  // 		right_y_point = GetRealPoint(m_rectCtrl,
////  // 			x_scale_of_x_end,
////  // 			ordinary_y_scale - y_graduation_offset * i - 2 * y_graduation_offset - 0.03);
////  
////   
////  		left_y_point = GetRealPoint(m_rectCtrl,
////  			ordinary_x_scale - 0.02,
////  			ordinary_y_scale - y_graduation_offset * i - first_y_graduation_offset - 0.03);
////  
////  		right_y_point = GetRealPoint(m_rectCtrl,
////  			x_scale_of_x_end,
////  			ordinary_y_scale - y_graduation_offset * i - first_y_graduation_offset - 0.03);
////  	
////  		 
////  
////  		//������̶�ֵ
////  		show_str.Format(_T("%5.2f"), p_y_min + i * temp_scale); 
////  
////  
////  		//min��max���ɺ�ɫ
////  		if ((0 == i) || ((GraphicCoordinate::y_graduation_num) == i))
////  		//if ((0 == i) || ((m_y_graduation_num) == i))
////  			draw_color = GraphicColor::RED;
////  		else 
////  			draw_color = GraphicColor::WHITE; 
////  
////  
////  		//�����Y��̶�ֵ
////  		DrawGraphicText(p_dc, show_str, left_y_point.x - 24, left_y_point.y + 5,font_type, y_scale_font_size, draw_color);
////  
////  		//���ұ�Y��̶�ֵ
////  		DrawGraphicText(p_dc, show_str, right_y_point.x - 11, right_y_point.y + 5,font_type, y_scale_font_size, draw_color);
////  		 
////  		//��֤max�̶�ֵ���Ի���������14 + 2 = 16 ������16��max�̶Ȳ��ử��
////  		//if ((GraphicCoordinate::y_graduation_num - 2) == i)
////  		//	i++;
////  		//else 
////  		//	i += 2; 
////  	} 
//
//
//	//m_y_graduation_num = (p_y_max - p_y_min)
//
//	//Ĭ�Ϻ���λ��
//	double bot_red_line_y_scale = ordinary_y_scale - m_y_graduation_offset;
//	double top_red_line_y_scale = ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset;
//
//
//	//ordinary_y_scale -m_y_graduation_offset * i +  - m_y_graduation_offset
//
//	double y_offset = 0.0;
//	//Y�᷶Χ�����ݷ�Χ�󣬿̶ȱ�࣬�̶ȱ�����С,����������bot_red_line_scale���top_red_line_scale��С
//	if ((p_y_max - p_y_min) / (m_value_max - m_value_min) > 1)
//	{
//		y_offset = y_graduation_offset - ((((p_y_max - p_y_min) - (m_value_max - m_value_min))/ (m_value_max - m_value_min))) * 0.1;// < 0.046
//		bot_red_line_y_scale += ((((p_y_max - p_y_min) - (m_value_max - m_value_min)) / (m_value_max - m_value_min)));
//		top_red_line_y_scale -= ((((p_y_max - p_y_min) - (m_value_max - m_value_min)) / (m_value_max - m_value_min)));
//	} 
//	//Y�᷶Χ�����ݷ�ΧС���̶ȱ��٣��̶ȱ�����󣬺���������bot_red_line_scale��С��top_red_line_scale���
//	else if ((p_y_max - p_y_min) / (m_value_max - m_value_min) < 1)
//	{
//		//y_offset = y_graduation_offset + (((m_value_max - m_value_min) - (p_y_max - p_y_min)) / (p_y_max - p_y_min)) * 0.1;// < 0.046
//		y_offset = y_graduation_offset - (((m_value_max - m_value_min) - (p_y_max - p_y_min)) / (p_y_max - p_y_min)) * 0.1;// < 0.046
//
//		bot_red_line_y_scale += (((m_value_max - m_value_min) - (p_y_max - p_y_min)) / (p_y_max - p_y_min));
//		top_red_line_y_scale -= (((m_value_max - m_value_min) - (p_y_max - p_y_min)) / (p_y_max - p_y_min));
//
//	}
//	//���Ĭ�Ͽ̶ȱ���0.046
//	else
//	{
//		y_offset = y_graduation_offset;
//	}
//	 
//	SetCurrentYGraduationOffset(y_offset);
//
//	double temp_y_graduation_num = ((GraphicCoordinate::ordinary_y_scale - GraphicCoordinate::y_scale_of_y_end) / y_offset);//Ĭ��19���̶�
//
//	SetCurrentYGraduationNum(temp_y_graduation_num);
//
//	
//	double temp_y_scale = 0.0;
//
//	//��������Y���16���̶���
//	for (int i = 0; i < m_y_graduation_num - 2; i++) 
//	{ 
//		temp_y_scale = -m_y_graduation_offset * i + ordinary_y_scale - m_y_graduation_offset;
//		DrawLine(p_dc,
//			GetRealPoint(m_rectCtrl, ordinary_x_scale, temp_y_scale),
//			GetRealPoint(m_rectCtrl, ordinary_x_scale + y_graduation_length_scale, temp_y_scale));
//				 
//				 
//		DrawLine(p_dc,
//			GetRealPoint(m_rectCtrl, right_y_end_x_scale, temp_y_scale),
//			GetRealPoint(m_rectCtrl, right_y_end_x_scale - y_graduation_length_scale, temp_y_scale));
//		   
//
//
//
//		left_y_point = GetRealPoint(m_rectCtrl,
//		  	ordinary_x_scale - 0.02,
//			ordinary_y_scale - m_y_graduation_offset * i - m_y_graduation_offset - 0.03);
//		  
//		right_y_point = GetRealPoint(m_rectCtrl,
//		  	x_scale_of_x_end,
//			ordinary_y_scale - m_y_graduation_offset * i - m_y_graduation_offset - 0.03);
//		  	
//		  		 
//		  
//		//������̶�ֵ
//		show_str.Format(_T("%5.2f"), p_y_min + i * temp_scale); 
//		  
//		  
//		//min��max���ɺ�ɫ
//		//if ((0 == i) || ((GraphicCoordinate::y_graduation_num) == i))
//		//if ((0 == i) || ((m_y_graduation_num) == i))
//		//  	draw_color = GraphicColor::RED;
//		//else 
//		  	draw_color = GraphicColor::WHITE; 
//		  
//		//�����Y��̶�ֵ
//		DrawGraphicText(p_dc, show_str, left_y_point.x - 24, left_y_point.y + 5, font_type, y_scale_font_size, draw_color);
//		  
//		//���ұ�Y��̶�ֵ
//		DrawGraphicText(p_dc, show_str, right_y_point.x - 11, right_y_point.y + 5, font_type, y_scale_font_size, draw_color);
//		 
//
//
//
//
//		//�ж��������澯��ɫ��
//		if (temp_y_scale == top_red_line_y_scale)
//		{
//			//�����Ϸ�������
//			//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, top_red_line_y_scale - red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, top_red_line_y_scale - red_line_y_offset / 2), GraphicColor::RED);
//			//�����Ϸ��ڲ����
//			//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset + red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset * (m_y_graduation_num)-m_y_graduation_offset + red_line_y_offset), GraphicColor::RED);
//			 
//		}
//
//		//�ж��������澯��ɫ��
//		if (temp_y_scale == bot_red_line_y_scale)
//		{
//
//			//�����·��ڲ����
//			//DrawLine(p_dc, GetRealPoint(m_rectCtrl, ordinary_x_scale, bot_red_line_y_scale - red_line_y_offset), GetRealPoint(m_rectCtrl, right_y_end_x_scale, bot_red_line_y_scale - red_line_y_offset), GraphicColor::RED);
//			//�����·�������
//			//DrawLine(CDC, GetRealPoint(m_rectCtrl, ordinary_x_scale, ordinary_y_scale - m_y_graduation_offset + red_line_y_offset / 2), GetRealPoint(m_rectCtrl, right_y_end_x_scale, ordinary_y_scale - m_y_graduation_offset + red_line_y_offset / 2), GraphicColor::RED);
//
//
//		}
//
//	}
// 
// 	 
// }

/*
void CGraphic::DrawDynamicYScale(CDC* p_dc, const double p_y_min, const double p_y_max)
{
	using namespace GraphicCoordinate;

	//��ÿؼ�����
	GetClientRect(&m_rectCtrl); 
	 
	double temp_scale = (p_y_max - p_y_min) / m_y_graduation_num;
	 

	CString show_str("0.0");
	POINT left_y_point;
	POINT right_y_point;
	COLORREF draw_color;

	//��������Y��̶� 
	for (int i = 0; i < m_y_graduation_num; i += 2)
	{ 

		left_y_point = GetRealPoint(m_rectCtrl,
			ordinary_x_scale - 0.02,
			ordinary_y_scale - m_y_graduation_offset * i - m_y_graduation_offset - 0.03);

		right_y_point = GetRealPoint(m_rectCtrl,
			x_scale_of_x_end,
			ordinary_y_scale - m_y_graduation_offset * i - m_y_graduation_offset - 0.03);


		double show_value = p_y_min + i * temp_scale;


		//������̶�ֵ
		show_str.Format(_T("%5.2f"), show_value);


		if (m_value_min == show_value || m_value_max == show_value)
		{
			draw_color = GraphicColor::RED;
		}
		else
		{
			draw_color = GraphicColor::WHITE;
		}


		//y��min��max���ɺ�ɫ
		//if ((0 == i) || ((GraphicCoordinate::y_graduation_num) == i))
// 		if ((0 == i) || ((m_y_graduation_num) == i))
// 			draw_color = GraphicColor::RED;
// 		else
// 			draw_color = GraphicColor::WHITE;


		//���ݷ�Χmin��max���ɺ�ɫ
		 

		//�����Y��̶�ֵ
		DrawGraphicText(p_dc, show_str, left_y_point.x - 20, left_y_point.y + 5,font_type, y_scale_font_size, draw_color);

		//���ұ�Y��̶�ֵ
		DrawGraphicText(p_dc, show_str, right_y_point.x - 5, right_y_point.y + 5,font_type, y_scale_font_size, draw_color);
 
	} 



}

*/

/*******************************************************************************
������   :	AdjustQueuePoint
����     :	���µ���������Ԫ�ص�����
����     :	[IN]	: ��
			[OUT]	: ��
����ֵ   : ��
��ע     : �ڶ���δ������ʱ���ܹ����е������޸���ǰ50���㲻�ܵ���Y���������
ʱ��     : 2016/8/18 �µ���
*******************************************************************************/
void CGraphic::AdjustQueuePoint()
{
	//��ÿؼ�����
	GetClientRect(&m_rectCtrl);
	POINT temp_adjust_point;
	//x����ͨ��m_x_scale_vec.at(index)ȡ��
	double arrive_y_scale(0.0);
	double arrive_x_scale(0.0);
	//��ǰ�������ݶ��д�С
	auto queue_size = m_ChartDataDeque.size();

	//������ʱ���е���
	if (queue_size >= Graphic::Deque_Point_Num)
	{  
		for (int index = 0; index != queue_size; index++)
		{
			//˫�˶������������ʱ���ٶȲ��Ǻܿ죬��������ʱ�����洢index����ֵ����ֹ�����ظ�ʹ��m_ChartDataDeque[index]����Ч�ʵ���
			auto& temp_queue_point = m_ChartDataDeque[index];

			//��ȡÿ�����ݵ�x���������   
			arrive_x_scale = m_x_scale_vec.at(index);

			//��ȡÿ�����ݵ�y���������
			arrive_y_scale = GetArriveYScale(temp_queue_point); 

			//�õ�ʵ�ʵ�����
			temp_adjust_point = GetRealPoint(m_rectCtrl, arrive_x_scale, arrive_y_scale);

			//��ֵ����
			temp_queue_point.first.xPos = temp_adjust_point.x;
			temp_queue_point.first.yPos = temp_adjust_point.y;
		}
	}
	else 
	{ 
		//�ó����һ��Ԫ�ص�
		auto& temp_queue_point = m_ChartDataDeque.back();

		//��ȡ���ݵ�x���������    
		arrive_x_scale = GraphicCoordinate::right_y_start_x_scale - GraphicCoordinate::y_graduation_length_scale;

		//��ȡ���ݵ�y���������   
		arrive_y_scale = GetArriveYScale(temp_queue_point);

		//�õ�ʵ�ʵ�����
		temp_adjust_point = GetRealPoint(m_rectCtrl, arrive_x_scale, arrive_y_scale);

		//��ֵ����
		temp_queue_point.first.xPos = temp_adjust_point.x;
		temp_queue_point.first.yPos = temp_adjust_point.y;


		//����ǰ���ÿ��Ԫ�ص�xPos������ǰ�ƶ�������֮��ļ�����
		for (int index = 0; index < queue_size - 1; index++)
		{
			//0 ... 46 47 48 49 end(50)
			//queue_size = 3                                      m_x_scale_vec.size() = 50 - 3 = 47 + index = 47 48 49
			m_ChartDataDeque[index].first.xPos = m_x_scale_vec.at(m_x_scale_vec.size() - queue_size + index) * m_rectCtrl.Width();

			//���µ��������е����ݵ��Y����,�������ǳ��Ը߶ȣ�GetArriveYScale���ر���
			m_ChartDataDeque[index].first.yPos = GetArriveYScale(m_ChartDataDeque[index]) * m_rectCtrl.Height();
		}
 
		//for (int index = 0; index != queue_size - 1; index++)
		//{  
		//��ǰ���Ԫ�ص��xPos��ǰ�ƶ�0.0174(������������֮��ı���)������,����ʹ�ã����ǵ�һ��λ����Ҫ���� 
		//	m_ChartDataDeque[index].first.xPos -= m_rectCtrl.Width() * 0.0174;  
		//}
		 
	}
}





 

/*******************************************************************************
������   :	GetArriveXScale
����     :	�õ��������ݵ��y�������
����     :	[IN]	: ��
			[OUT]	: arrive_data �������ݵ������
����ֵ   :	����arrive_dataʵ�ʵ�y�ı���
��ע     :	 
			 
ʱ��     :	2016/8/14 �µ���
********************************************************************************/
inline double CGraphic::GetArriveYScale(Graphic::Chart_Data& arrive_data)
{
// 	double temp = (GraphicCoordinate::ordinary_y_scale - GraphicCoordinate::y_graduation_offset) - (GraphicCoordinate::y_graduation_offset * GraphicCoordinate::y_graduation_num);
// 	return ((arrive_data.second.base_data.arrive_value - arrive_data.second.attributes.max) / (arrive_data.second.attributes.min - arrive_data.second.attributes.max)) * GraphicCoordinate::y_graduation_offset * GraphicCoordinate::y_graduation_num + temp;


// 	double temp = (GraphicCoordinate::ordinary_y_scale - m_y_graduation_offset) - (m_y_graduation_offset * m_y_graduation_num);
// 	return ((arrive_data.second.base_data.arrive_value - arrive_data.second.attributes.max) / (arrive_data.second.attributes.min - arrive_data.second.attributes.max)) * m_y_graduation_offset * m_y_graduation_num + temp;

// 	double temp = GraphicCoordinate::ordinary_y_scale - (m_y_graduation_offset * (m_y_graduation_num - 1));
// 	return ((arrive_data.second.base_data.arrive_value - arrive_data.second.attributes.max) / (arrive_data.second.attributes.min - arrive_data.second.attributes.max)) * m_y_graduation_offset * (m_y_graduation_num - 1) + temp;

	double temp = GraphicCoordinate::ordinary_y_scale - (m_y_graduation_offset * (m_y_graduation_num - 1));
	return ((arrive_data.second.base_data.arrive_value - m_y_max) / (m_y_min - m_y_max)) * m_y_graduation_offset * (m_y_graduation_num - 1) + temp;

}


BOOL CGraphic::PreTranslateMessage(MSG* pMsg)
{

	// TODO:  �ڴ����ר�ô����/����û���

	CString temp_text("");

	//��ʱȥ��
	//GetParent()->GetDlgItem(IDC_BTN_PAUSE)->GetWindowText(temp_text);

	//�ط�ģʽ���ҵ�ǰ��ͣ�ſ�����Ӧ����ƶ���Ϣ
	//if ((m_hWnd == pMsg->hwnd) && (pMsg->message == WM_MOUSEMOVE) && (Graphic::PlaybackModel == m_cur_model) && (_T("Resume") == m_cur_btn_pause_text))
	if ((m_hWnd == pMsg->hwnd) && (pMsg->message == WM_MOUSEMOVE) && (Graphic::PlaybackModel == m_cur_model) && (_T("Resume") == temp_text))
	{
		OnMouseMove(MK_MBUTTON, pMsg->pt);
		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}


void CGraphic::OnMouseMove(UINT nFlags, CPoint point)
{
	//CRect rect_ctr;
	//GetClientRect(&rect_ctr);

	CRect rect_ctr;
	//��ȡPicture�ؼ������Ļ���Ͻǵ����꣬�洢��rect_ctr��
	this->GetWindowRect(&rect_ctr);

	//ScreenToClient(rect_ctr);

	point.x -= rect_ctr.left;
	point.y -= rect_ctr.top;

	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ 
	for (int index = 0; index != m_ChartDataDeque.size(); index++)
	{
		if (((point.x > m_ChartDataDeque[index].first.xPos - GraphicCoordinate::point_radius) && (point.x < m_ChartDataDeque[index].first.xPos + GraphicCoordinate::point_radius))
			&& ((point.y > m_ChartDataDeque[index].first.yPos - GraphicCoordinate::point_radius) && (point.y < m_ChartDataDeque[index].first.yPos + GraphicCoordinate::point_radius)))
		{
			//MessageBox(_T("OK!"));

			CString temp_text("");

			//temp_text.Format(_T("%.2f"), m_ChartDataDeque[index].second.base_data.arrive_time);
			
			auto arrive_time = m_ChartDataDeque[index].second.base_data.arrive_time;
			temp_text.Format(_T("%2u:%2u:%2u:%3u"), arrive_time.hour, arrive_time.min, arrive_time.sec, arrive_time.ms);
			
			//��ʱȥ��
			//GetParent()->GetDlgItem(IDC_EDIT_ARRIVE_TIME)->SetWindowText(temp_text);


			temp_text.Format(_T("%.2f"), m_ChartDataDeque[index].second.base_data.arrive_value);
			
			//��ʱȥ��
			//GetParent()->GetDlgItem(IDC_EDIT_ARRIVE_VALUE)->SetWindowText(temp_text);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}


/*********************************************************
������   :	GetArriveXScale
����     :	�õ��������ݵ��x�������
����     :	[IN]	: ��
[OUT]	: arrive_data �������ݵ������
����ֵ   :	����arrive_data��ʵ��x����
��ע     :	�˺���Ŀǰ��ʹ��
ʱ��     :	2016/8/10 �µ���
**********************************************************/
inline double CGraphic::GetArriveXScale(Graphic::Chart_Data& arrive_data)
{
	// 	static int index = m_x_scale_vec.size() - 1;
	// 	double arrive_x_scale = 0.0;
	// 	if (index >= 0)
	// 	{
	// 		return arrive_x_scale = m_x_scale_vec.at(index--);
	// 	}  

	//֮ǰ������xPosλ����ǰ�ƶ�


	//���������������0.92
	return 0.93 - GraphicCoordinate::y_graduation_length_scale;
}
 