#if !defined(AFX_METER_H__D5802279_6502_4453_BE21_58604877AD39__INCLUDED_)
#define AFX_METER_H__D5802279_6502_4453_BE21_58604877AD39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Meter.h : header file
//

#ifndef ROUND
#define ROUND(x) (int)((x) + 0.5 - (double)((x) < 0))
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeter window

enum class ZMETERSTYLE
{
	N1,
	N2,
	T4,
	HYD1,
	HYD2,
	LW,
	RW
};

//�Ǳ����Խṹ��
struct MeterAttribute
{
	int StartAngleDeg;  //��ʼ�Ƕ�
	int EndAngleDeg;	//��ֹ�Ƕ�
	int Ticks;			//���̶̿�
	int SubTicks;		//С��̶�
	double MaxValue;	//���ֵ
	double MinValue;	//��Сֵ
	double CurrentValue;//��ǰֵ

	int ScaleDecimals;	//
	int ValueDecimals;	//��ֵ����
	COLORREF colorNeedle;//ָ�����ɫ
	CString strUnits;	//���̱�ʶ
	BOOL bColorTick;	//
	CString meterUnit;	//��ֵ��λ

	COLORREF colorTable[3];	//���̻���������ɫ
	int space_3[3];			//	

	ZMETERSTYLE meterStyle;		//��������
	double valueRange[4];		//valueRange[4]={X1,X2,X3,X4}
};


class CMeter : public CWnd
{
	// Construction
public:
	explicit CMeter(void);
	virtual ~CMeter();

	// Attributes
public:
	void SetMeterAttribute(const MeterAttribute &meterValue);

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeter)
protected:
	//}}AFX_VIRTUAL

	// Implementation
public:
	const double GetMaxValue(void) const;  //��ȡ�Ǳ����ֵ
	const double GetMinValue(void) const;  //��ȡ�Ǳ���Сֵ
	void SetAngleRange(int nStartAngleDeg, int nEndAngleDeg);
	void SetSubTicks(int nSubTicks);
	void SetTicks(int nTicks);
	void DrawValue(CDC *pDC);
	void SetColorTick(BOOL bColorTick = FALSE);
	void DrawNode(CDC *pDC);
	void SetValueDecimals(int nDecimals);	//��̬������ֵ����
	void SetUnits(CString &strUnits);  //�����Ǳ�����
	void SetScaleDecimals(int nDecimals);
	void SetRange(double dMin, double dMax);	//������ֵ�ķ�Χ
	void SetNeedleColor(COLORREF colorNeedle);	//����ָ�����ɫ
	void UpdateNeedle(double dValue);	//���õ�ǰֵ
	void UpdateCenterCircle(const BOOL tAFCSD9);


	void DrawNeedle(CDC *pDC);
	void ReconstructControl();
	void DrawMeterBackground(CDC *pDC, CRect &rect);

	void GetBaseLineLength(const CRect& rect);




	// Generated message map functions
private:
	int m_nTabNum;
	BOOL m_bColorTick;
	COLORREF m_colorNeedle;
	double m_dCurrentValue;
	BOOL m_N2IsWorking = FALSE;
	double m_dMaxValue;  //�Ǳ����ֵ
	double m_dMinValue;  //�Ǳ���Сֵ
	int m_nScaleDecimals;
	CString m_strUnits;
	int m_nValueDecimals;  //�Ǳ���ֵ�ľ���

	enum { TABNUM = 3 };   //ɫ�ʿ̶�����������������Ӽ���
	COLORREF m_colorTable[3];

	int m_space3[3];
	int m_TotalDots;

	ZMETERSTYLE m_meterStyle;		//��������
	double m_valueRange[4];

	int m_nStartAngleDeg;	// �Ǳ���Բ����ʼ�Ƕ�
	int m_nEndAngleDeg;		// �Ǳ���Բ����ֹ�Ƕ�
	int m_nTicks;			// �̶���
	int m_nSubTicks;		// �̶ֿ���


	double m_dLeftAngleRad;
	double m_dRightAngleRad;
	int    m_nCenterRadius;


	CRect m_rectCtrl;			// �ؼ�����
	CRect m_rectValue;			// ��ʾ��ֵ����
	CRgn m_rgnBoundary;

	CBitmap *m_pBitmapOldBackground;
	CBitmap m_bitmapBackground;
	CDC m_dcBackground;

	CPoint m_ptMeterCenter;		// �Ǳ�����

	enum { BOUNDARY_POINTS = 200 };
	CPoint m_pointBoundary[BOUNDARY_POINTS]; // �߽�㣬���ڻ��ƿ̶�

	CFont m_font;			// ��ʾ��������

	COLORREF m_colorWindow;		// ����ɫ
	COLORREF m_colorHighlight;
	COLORREF m_colorShadow;
	COLORREF m_colorButton;
	COLORREF m_colorText = RGB(0, 255, 0);		// ��ʾ�ı���ɫ
	int m_nRadiusFrame;			                // �Ǳ��̱߿�뾶

	CString m_meterUnit;
	//{{AFX_MSG(CMeter)
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METER_H__D5802279_6502_4453_BE21_58604877AD39__INCLUDED_)
