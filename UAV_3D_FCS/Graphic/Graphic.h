#pragma once




#include <deque>
#include <queue>

#include "../MemoryDC.h" 
#include "../stdafx.h"

#define  UM_TIMER_GRAPHIC_PROC  (WM_USER + 1)


// CGraphic

namespace Graphic {

	//������һ��Ҫ��ʾ�ĵ�����:50����
	const int Deque_Point_Num = 50;

	//��ͨ��ı��
	const int Ordinary_Point = 1;

	//Բ��ı��
	const int Circle_Point = 2;

	//�����ε�ı��
	const int Triangle_Point = 3;

	//����ֵ����
	typedef int point_coord_inate;

	//��Ҫ��ʾ��ʵ������ֵ����
	typedef double point_value_type;

	//�����֮��ļ����������
	typedef double point_interval_type;

	//��ǰ������ͣ�1Ϊ��ͨ�㣬2ΪԲ�㣬3Ϊ�����ε�
	typedef int point_type;

	//�����ɫ����
	typedef COLORREF point_color;

	//ʱ����Ϣ�ṹ��
	typedef struct
	{
		int hour;
		int min;
		int sec;
		int ms;
	}time_struct;

	//������Ϣ�ṹ��
	typedef struct
	{
		point_coord_inate xPos;
		point_coord_inate yPos;
	}point_struct;

	//���ݷ�Χ�ṹ��
	typedef struct
	{
		double min_scope;
		double max_scope;
		//�������ݵ�λ
		CString data_unit;
	}data_scope_struct;

	//���л������ݽṹ�壬����ʱ�䣬ֵ2����Ϣ
	typedef struct
	{
		//��ǰʱ����Ϣ
		time_struct arrive_time; 
		//double arrive_time;

		//��ǰ�����ֵ
		point_value_type arrive_value;
	}base_data_struct;

	//�����е�����ͽṹ�壬Բ�ε㣬�����ε㣬��ͨ��
	// 	typedef struct
	// 	{
	// 		//Բ�ε�
	// 		bool isCricle;
	// 		//�����ε�
	// 		bool isTriangle;
	// 		//��ͨ��
	// 		bool isOrdinary;
	// 	}point_type;

	//����������Խṹ�� 
	typedef struct
	{
		//��ǰ�������
		point_type type;
		//�����֮��ļ������
		point_interval_type interval_length;
		//�����ɫ
		point_color color;

		//���ݷ�Χ��Сֵ
		double min;
		//���ݷ�Χ���ֵ
		double max;

		//�Ƿ��Ѿ���ʼ������������
		bool hasInit;

	}point_attributes;


	//�������������ṹ��
	typedef struct
	{
		//�������
		base_data_struct base_data;
		//�������
		point_attributes attributes;
	}data_struct;

	//Chart_DataΪ���߶����д洢�Ļ�����������
	typedef std::pair<Graphic::point_struct, Graphic::data_struct> Chart_Data;

	//Chart_Data_QueueΪ�������ݶ��У��������
	//typedef std::queue<Graphic::Chart_Data> Chart_Data_Queue;


	//Chart_Data_QueueΪ�������ݶ��У�˫�˶���
	typedef std::deque<Graphic::Chart_Data> Chart_Data_Queue;


	//ʵʱ���ģʽ
	const int MonitoringModel = 1;
	//�ط�ģʽ
	const int PlaybackModel = 0;

}

namespace GraphicColor {
	const COLORREF DARK = RGB(0, 0, 0);
	const COLORREF WHITE = RGB(255, 255, 255);
	const COLORREF RED = RGB(255, 0, 0);
	const COLORREF GREEN = RGB(0, 255, 0);
}

namespace GraphicCoordinate {
	//��ʼ�����x��y�ı���
	const double ordinary_x_scale = 0.05;
	const double ordinary_y_scale = 0.90;

	//x���������ı���
	const double x_scale_of_x_end = 0.95 + 0.02;
	const double y_scale_of_x_end = 0.90;

	//y���������ı��� 
	const double x_scale_of_y_end = 0.05;
	const double y_scale_of_y_end = 0.05 - 0.02; 
	const double y_scale_of_y_end_top_line = 0.05;

	//x, y��Ŀ̶�����
	const int x_graduation_num = 11;
	//Y��̶����ܹ��仯
	const int y_graduation_num = 24;// 16;


	//x��y��̶�֮���ƫ����
	const double x_graduation_offset = 0.09;
	//Y��ƫ�����ܹ��仯 (0.9 - 0.05) / 23 = 0.037
	const double y_graduation_offset = 0.0354;//0.0354 = (ordinary_y_scale - 0.05) / y_graduation_num;//0.046;

	//y���һ���̶��ߵ������y������ı���
	const double first_y_graduation_offset = y_graduation_offset;

	//x, y��̶��ߵĳ��ȱ���
	const double x_graduation_length_scale = 0.03;
	const double y_graduation_length_scale = 0.01;

	

	//�Ҳ�y����ʼ��x��y����
	const double right_y_start_x_scale = 0.93 + 0.02;
	const double right_y_start_y_scale = 0.9;

	//�Ҳ�y�������x��y����
	const double right_y_end_x_scale = 0.93 + 0.02;
	const double right_y_end_y_scale = 0.05 - 0.02;

	//X���ͷ��x��y����
	const double x_arrow_end_x_scale = 0.935 + 0.02;
	const double x_arrow_start_y_scale_top = 0.89;
	const double x_arrow_start_y_scale_bot = 0.91;
		   
	//���Y���ͷ��x��y����
	const double y_arrow_end_y_scale = 0.08 - 0.02;
	const double y_arrow_end_x_scale_left = 0.045;
	const double y_arrow_end_x_scale_right = 0.055;

	//��ɫ���������һ���̶ȵ�y��ƫ��
	const double red_line_y_offset = 0.005; 

	//�����ϻ��ĵ�Ĵ�С
	//const int point_size = 100;

	//x��ÿ�������ݵ�֮���x�������
	const double x_offset = (right_y_start_x_scale - 0.01 - ordinary_x_scale) / Graphic::Deque_Point_Num;

	//���ݵ�İ뾶
	const int point_radius = 2;

	//���ڻ�����������Y��̶�ʱʹ�õĵ��ڱ���
	const double adjust_y_graduation_scale = 0.1; 

	//����ʹ�õ�ֵ
	const double temp_red_line_scale = 2;

	
////////////////////////////////����������С//////////////////////////////////////////

	//y��̶������С
	const int y_scale_font_size = 70;

	//Y�ᵥλ�������С
	const int y_unit_font_size = 120;

	//X�ᵥλ�������С
	const int x_unit_font_size = 120;

	//����ϵ���ı�������
	const CString font_type = _T("����");

	//Y���������������С
	const int y_data_name_font_size = 120;

	//����ϵ��ǰ��ʾ��ʱ�� 
	const int coordinate_cur_time_font_size = 100;
}





class CGraphic : public CWnd
{
	DECLARE_DYNAMIC(CGraphic)

public:
	CGraphic();
	virtual ~CGraphic();

private: 

	//���ڴ�ſؼ�������δ�С�ı���
	CRect       m_rectCtrl;				

	//�������ڻ��Ʊ���������DC
	CDC			m_dcPlate;					

	//�ڻ������н�ͼ�λ��Ƶ���λͼ��
	CBitmap		m_bitmapPlate;	

	//�ɵ�λ��ָ��
	CBitmap     *m_pbitmapOldPlate; 

	//�洢��ǰ���ʱ��Ľṹ��
	Graphic::time_struct m_time_struct; 

	//�洢��ǰ�������Ľṹ��
	Graphic::point_struct m_point_struct; 

	//�洢x���ı�������
	std::vector<double> m_x_scale_vec;
private:
	bool m_requiresRedraw = true;

	//��������ֵ
	int m_slider_zoom;

	//�������ı���
	double m_slider_scale;

	//y���������̶�
	double m_y_max;

	//y��������С�̶�
	double m_y_min;

	//��ǰ������ʾ��ֵ��Χ����Сֵ
	double m_value_min;

	//��ǰ������ʾ��ֵ��Χ�����ֵ
	double m_value_max; 

	//Y��̶�����
	int m_y_graduation_num;

	//Y��̶ȼ������
	double m_y_graduation_offset;

	//��ǰ������ʾģʽ
	int m_cur_model;

	//��ǰY�����ݵ�λ
	CString m_cur_y_unit;

	//��ǰ������ʾ�����ݵ�����
	CString m_cur_data_name;

	//��ǰ�������½�����ʱ��
	CString m_cur_time;

	//��ǰ�Ƿ���ͣ���ı�
	//CString m_cur_btn_pause_text;
private:
	//����ͼ�������ݽṹ 
	Graphic::Chart_Data_Queue m_ChartDataDeque;

public:
	//�ؼ��ػ�
	void ReconstructControl() { Invalidate(); }

	//�������ݽӿ�1��ÿ�ν���һ�����ݰ�(һ����)������
	void SetCurrentData_One_Package(Graphic::Chart_Data& chart_data);

	//�������ݽӿ�2��ÿ�δ���һ�����е�����-��ʱ����
	void SetCurrentData_One_Deque(const Graphic::Chart_Data_Queue& chart_data_deque);

public:
	//���ڳ�ʼ����ն���������
	void CleanQueueData() { m_ChartDataDeque.clear(); } 

	//�õ���ǰ�������ݶ�����p_index���ĵ������
	Graphic::Chart_Data GetIndexPoint(const int p_index) { return m_ChartDataDeque[p_index]; } 

	//�õ���ǰ���д�С
	int GetCurrentQueueSize() { return m_ChartDataDeque.size(); }

public:
	//����y��min��max�̶�ֵ
	void SetYMinAndMaxScale(const double p_y_min, const double p_y_max) {m_y_min = p_y_min; m_y_max = p_y_max;}

	//����y��min��max�̶�ֵ
	void SetYValueMinAndMax(const double p_value_min, const double p_value_max) {m_value_max = p_value_max; m_value_min = p_value_min;}

	//�������ߵ�ǰ��y��̶�����
	void SetCurrentYGraduationNum(const int p_y_graduation_num) { m_y_graduation_num = p_y_graduation_num; }

	//�������ߵ�ǰ��ʾ���ݵ�ģʽ
	void SetCurModel(const int p_model) { m_cur_model = p_model; }

	//���õ�ǰY��̶ȵļ������
	void SetCurrentYGraduationOffset(const double p_y_graduation_offset) { m_y_graduation_offset = p_y_graduation_offset; }

	//���õ�ǰY�����ݵ�λ
	void SetYDataUnit(const CString p_cur_unit) { m_cur_y_unit = p_cur_unit; } 

	//���û������Ĵ�С
	void SetSliderZoom(const int p_slider_pos) { m_slider_zoom = p_slider_pos; } 

	//���õ�ǰ��ʾ����������
	void SetCurDataName(const CString p_data_name) { m_cur_data_name = p_data_name; }

	//���õ�ǰ����ʱ��,����ʱ�䲻Ϊ0���ж�
	void SetCurTime(const CString p_cur_time) { if (_T("00:00:00:000") == p_cur_time){ return; } m_cur_time = p_cur_time; }

	//�ṩ����Ҫ�ػ汳���߼����ֵĽӿ�
	void ReDraw() { m_requiresRedraw = true; Invalidate(); };
	
	//�õ���ͣ��ť�ı�
	//void SetCurBtnPauseText(const CString p_cur_btn_pause_text) { m_cur_btn_pause_text = p_cur_btn_pause_text; }
private:
	//�������߾�̬����
	void DrawStaticBackground(CDC * dc);	

	//����̬������
	void DrawStaticAxis(CDC* CDC, const CString p_x_unit, const CString p_y_unit);
 	 
	//����̬����
	void DrawDynamicCurve(CMemoryDC* MemDC, Graphic::Chart_Data_Queue &DisplayData);

	//���ݶԻ����С����Ӧ�����������ȡʵ�ʵ�����λ��
	inline POINT GetRealPoint(CRect rect, double x_scale, double y_scale);  

	//��ֱ��
	void DrawLine(CDC* p_dc, POINT p_start, POINT p_end, COLORREF p_color = GraphicColor::WHITE, int p_line_type = PS_SOLID, int p_line_width = 1);

	//����
	void DrawPoint(CDC* p_dc, POINT point, COLORREF p_color = GraphicColor::WHITE, int p_line_width = 1, int p_line_type = PS_SOLID);

	//��Բ
	void DrawCricle(CDC* p_dc, POINT point_up_left, POINT point_low_right, COLORREF p_color = GraphicColor::WHITE, int p_line_width = 1, int p_line_type = PS_SOLID);

	//���ı�
	void DrawGraphicText(CDC* p_dc, const CString& p_show_text, int p_start_x, int p_start_y, CString p_font_type, int p_font_size, COLORREF p_color = GraphicColor::WHITE);
	
	//���ݵ�ǰѡ���Y��ķ�Χ��̬����Y����Ŀ̶�
	void DrawDynamicYScale(CDC* p_dc, const double p_y_min, const double p_y_max);

	//������OnPaint�л��ƾ�̬������
	void DrawStaticInOnPaint(CDC* p_dc); 

private: 
	//Ϊm_ChartDataDeque�е����ݵ��������
	void AddCoordinatePointForChartData(Graphic::Chart_Data& chart_data);

	//���㵽�����ݵ��x�������
	inline double GetArriveXScale(Graphic::Chart_Data& arrive_data);

	//���㵽�����ݵ��y�������
	inline double GetArriveYScale(Graphic::Chart_Data& arrive_data);


public:

	//���µ���������Ԫ�ص�����
	void AdjustQueuePoint();


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


