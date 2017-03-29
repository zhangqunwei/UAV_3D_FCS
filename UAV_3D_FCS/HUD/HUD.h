#pragma once
#include "afxwin.h"


#include "../protocol/FCToPCProtocolConvertToRealData.h"

#include <cmath>
#include "../MemoryDC.h"

//- [3/26/2017 ��Ⱥΰ]
# define PI		(3.1415926)
# define ON		1
# define OFF	0

class CHUD :
	public CWnd
{
public:
	CHUD();
	~CHUD();

private:
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

//- [3/26/2017 ��Ⱥΰ]
//-	��ʾ����ʾ�Ĵ�С��λ�ÿ���DrawStaticBackground(CDC *pDC)������ͨ��Բ���뾶�Ϳؼ����ĵ��������
//-       ������ʾ�Ĳ��ֶ���Բ���뾶�Ϳؼ����ĵ�Ϊ�ο����л���
private:  
	// Բ���뾶
	double m_dRadius;
	// �ؼ������ĵ�
	CPoint m_CenterPoint;	
	// �����ε�������
	CPoint ptTriangle[3];
	// ��ͼ��ˢ
	CBrush currentBrush;
	// ��ͼ����
	CPen currentPen;
	// ����
	CFont currentFont;
	TEXTMETRIC tm;

public:
	//���¿ؼ�����
	void SetCurrentData(const TSPIDC& tspidc);
	//Ϊ���ƿؼ���׼��
	void DrawStaticPrepare(CDC* p_dc);
	//���ƾ�̬����
	void DrawStaticBackground(CDC *pDC);
	//���ƶ�̬����
	void DrawDynamicBackground(CDC *pDC);
	
//- [3/26/2017 ��Ⱥΰ]
public:
	// ���ƿ̶Ⱥ�Բ
	void DrawTickCircle(CDC *pDC);
	// ������պʹ��
	void DrawSkyGround(CDC *pDC);
	// ���Ʒɻ�
	void DrawAerofoil(CDC *pDC);
	// ��������ˮƽ��
	void DrawCenterHorizontal(CDC *pDC);
	// ��������������
	void DrawTriangle(CDC *pDC);


	DECLARE_MESSAGE_MAP()
	//���ƿؼ�
	afx_msg void OnPaint();	
};

