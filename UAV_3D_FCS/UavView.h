#pragma once

#include <cmath>

#include "afxwin.h"
#include "protocol/FCToPCProtocolConvertToRealData.h"
#include "MemoryDC.h"


namespace UavViewPace {
	const COLORREF DARK = RGB(0, 0, 0);
	const COLORREF WHITE = RGB(255, 255, 255);
	const COLORREF RED = RGB(255, 0, 0);
	const COLORREF GREEN = RGB(0, 255, 0);

	//�ı�������
	const CString font_type = _T("����");

	//�������������С
	const int font_size = 120;
};

class CUavView :
	public CWnd
{
public:
	CUavView();
	~CUavView();

protected:
	TSPIDC m_TSPIDC;			//���ݰ�

	//���ڴ�ſؼ�������δ�С�ı���
	CRect       m_rectCtrl;

	//�������ڻ��Ʊ���������DC
	CDC			m_dcPlate;

	//�ڻ������н�ͼ�λ��Ƶ���λͼ��
	CBitmap		m_bitmapPlate;

	//�ɵ�λ��ָ��
	CBitmap     *m_pbitmapOldPlate;

	//�Ƿ���Ҫ�ػ澲̬����
	bool m_reqRedrawStaticBgd = true; 
	
	//Ϊ���ƿؼ���׼��
	void DrawStaticPrepare(CDC* pDC);
	
	//���ƾ�̬����,���������д
	virtual void DrawStaticBackground(CDC *pDC) = 0;
	
	//���ƶ�̬����,���������д
	virtual void DrawDynamicBackground(CDC *pDC) = 0;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

public:
	//���¿ؼ�����
	void SetCurrentData(const TSPIDC& tspidc);

	//���ı�
	void DrawUavText(CDC* p_dc, const CString& p_show_text, int p_start_x, int p_start_y, CString p_font_type, int p_font_size, COLORREF p_color = UavViewPace::WHITE);

	//��Բ
	void DrawCricle(CDC* p_dc, POINT point_up_left, POINT point_low_right, COLORREF p_color = UavViewPace::WHITE, int p_line_width = 1, int p_line_type = PS_SOLID);
	 
};

