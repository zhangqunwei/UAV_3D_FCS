#pragma once

#include "MyToolTipCtrl.h"
#include "MirrorDlg.h"
#include "../MemoryDC.h"
#include"../resource.h"
class CTimeFormat
{
public:
	CTimeFormat(void);
	~CTimeFormat(void);
	static BOOL IsLeapYear(INT year);
	static DWORD YMDHMSToStartDay(SYSTEMTIME time);
	static DWORD YMDHMSToEndDay(SYSTEMTIME time);
	static DWORD YEndToYStart(INT year_start, INT year_end);
	static Time HMSAddHMS(Time t1, Time t2);
	static Time HMSSubHMS(Time t1, Time t2);
	static void YMDHMSToTime(Time &time, SYSTEMTIME start_time, SYSTEMTIME end_time);
	static DWORD YMDHMSToSecond(SYSTEMTIME start_time, SYSTEMTIME end_time);
	static DWORD HMSToSecond(DWORD hour, DWORD minute, DWORD second);
	static DWORD HMSToSecond(Time time);
	static void SecondToHMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD srcsecond);
	static void SecondToHMS(Time &time, DWORD src_second);

	static void MillSecondToHMSMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD &mill_second, DWORD src_mill_second);
	static void MillSecondToHMSMS(Time & time, DWORD src_mill_second);
	static void HMSMSToMillSecond(DWORD &mill_sercond, Time time);
	static void HMSMSToMillSecond(DWORD &mill_sercond, DWORD hour, DWORD minute, DWORD second, DWORD mill_second);
	static DWORD HMSMSToMillSecond(Time time);
	static DWORD HMSMSToMillSecond(DWORD hour, DWORD minute, DWORD second, DWORD mill_second);

	static DWORD HMSToSecond(DOUBLE hour, DOUBLE minute, DOUBLE second);
	static void SecondToHMS(DWORD &hour, DWORD &minute, DWORD &second, DOUBLE srcsecond);
	static void SecondToHMS(Time &time, DOUBLE srcsecond);
	static void MillSecondToHMSMS(DWORD &hour, DWORD &minute, DWORD &second, DWORD &mill_second, DOUBLE src_mill_second);
	static void MillSecondToHMSMS(Time & time, DOUBLE src_mill_second);
};


// COwnSliderCtrl

class COwnSliderCtrl : public CWnd
{
#define TIMER_THUMB_SHOW 0x0010
#define TIMER_THUMB_HIDE 0x0020
//������λ����ʽ
#define SLIDER 2000
	enum{
		HOVER,
		DRAG,
		LBUTTONDOWN,
		LBUTTONUP,
		RBUTTONDOWN,
		RBUTTONUP,
		CLICK,
		SELECTED,
		LEAVE
	};
//���򻮷�
	enum{
		AREA_BACK,
		AREA_CHANNEL,
		AREA_THUMB
	};
//������ʽ
	enum{
		TBS_VTOP = 0x0001,
		TBS_VCENTER = 0x0002,
		TBS_VBOTTOM = 0x0003,
		TBS_HLEFT = 0x0010,
		TBS_HCENTER = 0x0020,
		TBS_HRIGHT = 0x0030
	};
	DECLARE_DYNAMIC(COwnSliderCtrl)
//��ʾ����ʾ����ֵ
public:
	//�����ʽ
	enum{
		SIGN_TOP,
		SIGN_BOTTOM,
		SIGN_LEFT,
		SIGN_RIGHT
	};
	enum{
		TOOLTIP_TIME = 0x0010,
		TOOLTIP_VALUE = 0x0020
	};
	COwnSliderCtrl();
	virtual ~COwnSliderCtrl();
	//�����Ԫ�سߴ硢λ��
	VOID ResetAll();
	//����ͻ�����С
	VOID ResetClientRect();
	//����ͨ����С
	VOID ResetChannelRect();
	//���軬���С
	VOID ResetThumbRect();
	//����״̬
	INT m_ThumbState;
	//����״̬
	INT m_ChannelState;
	//��굱ǰ״̬
	INT m_MouseState;
	//������Сֵ
	DWORD m_MinValue;
	//�������ֵ
	DWORD m_MaxValue;
	//������������
	DWORD m_LineSize;
	//��ǰ���鴰��λ��
	DOUBLE m_CurPos;
	//����͸����
	INT m_Alpha;
	//����
	INT m_PageSize;
	//ͨ���������ֵ
	INT m_nChannelMax;
	//ͨ��������Сֵ
	INT m_nChannelMin;
	//����
	INT m_TickFeq;
	//����
	INT m_NumTick;
	//��ʾ����ʽ
	INT m_ToolStyle;
	//��ʾ�򴰿�
	CMyToolTipCtrl *m_ToolTipCtrl;
	//��ʾ��λ����ʽ
	INT m_TipSide;
	//��ʾ����ʱ����
	UINT m_uElapse;
	//�����ʽ
	INT m_SignAlign;
	//��ʽ
	DWORD m_Style;
	//���������ɫ
	COLORREF m_LeftColor;
	//�����ұ���ɫ
	COLORREF m_RightColor;
	//����δѡ�б���
	UINT m_uiThumbUnselected;
	//����������������
	UINT m_uiThumbHover;
	//����ѡ�б���
	UINT m_uiThumbSelected;
	//����뿪ͨ������
	UINT m_uiChannelLeave;
	//�������ͨ������
	UINT m_uiChannelHover;
	//�Ѳ��Ž���������
	UINT m_uiPlayed;
	//��ֹ������
	UINT m_uiBeyondArea;
	//�ؼ����屳��
	UINT m_uiBack;
	//������
	CWnd* m_Parent;
	//����ɴ�С
	CSize m_OldSize;
	//�������״
	HCURSOR m_OldCursor;
	//�����ƶ�����
	VOID MoveThumb(CPoint point);
	//�ж��������
	UINT JudgeArea(CPoint point);
	//��õ�ǰλ�õ�ʱ��
	DOUBLE GetPosTime(UINT curPos);
	//��ȡ��ǰ����λ�õ�ʱ��
	DOUBLE GetPixelTime(DOUBLE pixel);
	//�Ŵ�
	CMirrorDlg m_LargerMirror;
	//�Ƿ����Ŵ�
	BOOL m_bMirror;
	//�Ŵ󾵴���λ��
	CRect m_MirrorRect;
	//���֡��
	INT m_iMaxFrameSpeed;
	//��С֡��
	INT m_iMinFrameSpeed;
	//�ؼ���ʽʵ��
	VOID ImplementStyle(UINT style);
	//��̬�����������ؼ�
	bool Create(CWnd* pParent, const CRect &rc, CString text, DWORD id = 0,
		DWORD style = WS_VISIBLE | WS_CHILD);
	//���ͨ������ͻ���λ��
	VOID GetChannelRect(CRect &rect);
	//����ͨ���ͻ���λ��
	VOID SetChannelRect(CRect rect);
	//��û���ͻ���λ��
	VOID GetThumbRect(CRect &rect);
	//���û���ͻ���λ��
	VOID SetThumbRect(CRect rect);
	//���ò�����Ϣ
	VOID SetDisplayInfo(_DISPLAY_INFO DisplayInfo);
	//���ñ�Ƕ�����ʽ
	VOID SetSignAlign(INT AlignStyle);
	//��ʼ��������Ϣ
	VOID Init();
	//��ò����ٶ�
	DOUBLE GetSpeed();
	//��ò���֡�ٶ�
	INT GetFrameSpeed();
	//���ò���֡�ٶ�
	VOID SetFrameSpeed(INT frame);
	//���õ�λ֡�ٶ�
	//VOID SetSpeed(DOUBLE speed);
	//����ʱ����ֵ������Ϊ��λ
	VOID SetValue(DWORD value);
	//�����ٶ�
	VOID ResetSpeed();
	//����֡��
	VOID ResetFrameSpeed();
	//���ʱ������ֵ
	DOUBLE GetValue();
	//��ò���������
	DWORD GetLineSize( ) const;
	//���ò�����
	BOOL SetLineSize( DWORD nSize );
	//���ñ���߳ߴ�
	BOOL SetSignSize( CSize cSize );
	//����
	INT GetPageSize( ) const;
	//����
	INT SetPageSize( INT nSize );
	//����������ֵ
	DWORD GetRangeMax( ) const;
	//���������Сֵ
	DWORD GetRangeMin( ) const;
	//���ֵ����/����
	DOUBLE GetUnit();
	//����ֵ����/����
	BOOL SetUnit(DOUBLE unit);
	//����������ֵ����Сֵ
	VOID GetRange( DWORD& nMin, DWORD& nMax ) const;
	//�����������ֵ����Сֵ
	VOID SetRange( DWORD nMin, DWORD nMax, BOOL bRedraw = FALSE );
	//��ȡͨ���������ֵ����Сֵ
	VOID GetSelection( DWORD &nMin, DWORD &nMax ) const;
	VOID SetSelection( DWORD nMin, DWORD nMax );
	//����ͨ�����ڵ�ǰλ��
	DOUBLE GetPos( ) const;
	//ͨ������ʱ�̻�ȡλ��
	DOUBLE GetPosByTime(DWORD time);
	DOUBLE GetPosByTime(DOUBLE passedTime);
	VOID InsertIntoPointLists(POINT point, INT flag);
	//���ò���λ��
	VOID SetPos( DOUBLE nPos );
	//����
	UINT GetNumTics( ) const;
	//����
	DWORD* GetTicArray( ) const;
	//����
	INT GetTic( INT nTic ) const;
	//����
	INT GetTicPos( INT nTic ) const;
	//����
	BOOL SetTic( INT nTic );
	//����
	VOID SetTicFreq( INT nFreq );
	//����
	CWnd* GetBuddy( BOOL fLocation = TRUE ) const;
	//����
	CWnd* SetBuddy( CWnd* pWndBuddy, BOOL fLocation = TRUE );
	//��õ�ǰ�󶨵���ʾ��
	CMyToolTipCtrl* GetToolTips( ) const;
	//���ð���ʾ��
	VOID SetToolTips( CMyToolTipCtrl* pWndTip );
	//������ʾ��λ����ʽ
	INT SetTipSide( INT nLocation );
	//�����Ƿ����������
	VOID SetSign(BOOL bSign);
	//�����Ƿ����Ŵ�
	VOID SetMirror(BOOL bMirror);
	//���ñ��ͼƬ
	VOID SetSignBack(UINT utSignBack);
	//����͸��ֵ
	VOID SetAlpha(INT alpha);
	//���͸��ֵ
	INT	 GetAlpha();
	//������ʾ����ʽ
	VOID SetToolTipStyle(INT style);
	//��ȡ����λ�ö�Ӧ��ʱ��
	CString GetPosValue(UINT curPos);
	//��ʾ���ƶ�
	VOID ToolTipMove(CPoint point);

	VOID OnMyPaint(COLORREF left, COLORREF right, 
		UINT thumbUnselected, UINT thumbSelected);
	//��������Ϣ
	DISPLAY_INFO m_DisplayInfo;
	//����ǰ������ǵ�
	VOID AddCurPointToSign();
protected:
	//ͨ���ͻ���λ��
	CRect m_ChannelRect;
	//����ͻ���λ��
	CRect m_ThumbRect;
	//�ؼ��ͻ���λ��
	CRect m_ClientRect;
	//��ʾ��ͻ���λ��
	CRect m_ToolTipRect;
	//��ǳߴ�
	CSize m_SignSize;
	//����
	CPoint m_SignLine;
	//��¼���λ����Ϣ
	CStringArray m_saPointRecords;
	//��¼���
	vector<INT> m_PointStyle;
	vector<UINT> m_PointBack;
	vector<INT> m_PointFlag;

	//Ӳ�̴洢λ��
	CString m_strFileName;
	//����
	CString m_szClassName;
	//��Ǳ���
	UINT m_uiSignBack;
	//�Ƿ�������
	BOOL m_bSign;
	//ÿ��1����ǰ��������---��Ϊ1֡
	DOUBLE m_Speed;
	//ÿ���뼸֡
	INT m_iFrame;
	//ÿ���ز��ż�����
	DOUBLE m_Unit;
	//�ܹ�������
	DOUBLE m_Value;
	//�������
	VOID ClearBack(CMemoryDC *pDC);
	//����
	VOID MoveBorder();
	/************************���ƺ���************************/
	//���ƻ���
	VOID DrawThumb(CDC *pDC);
	//����ͨ��
	VOID DrawChannel(CDC *pDC);
	//���ƽ�ֹ��
	VOID DrawByeondRange(CDC *pDC);
	//�����Ѳ�����
	VOID DrawPlayed(CDC *pDC);
	//����ͨ������
	VOID DrawBack(CDC *memDC);
	//���Ʊ����
	VOID DrawSignLine(CDC *pDC, CPoint pos);
	//���Ʊ��
	VOID DrawSign(CDC *pDC);
	//���ƷŴ�
	VOID DrawLargerMirror(CDC *pDC, CPoint pos);
	/************************���ƺ���************************/
	DECLARE_MESSAGE_MAP()
public:
	VOID PostClickEvent();
	/***************************��Ϣ*************************/
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg VOID OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg VOID OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg VOID OnMouseMove(UINT nFlags, CPoint point);
	afx_msg VOID OnMouseHover(UINT nFlags, CPoint point);
	afx_msg VOID OnMouseLeave();
	afx_msg VOID OnPaint();
	afx_msg VOID OnDestroy();
	afx_msg VOID OnTimer(UINT_PTR nIDEvent);/*���齥������*/
	afx_msg VOID OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg VOID OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg VOID OnSize(UINT nType, INT cx, INT cy);
	afx_msg VOID OnRButtonUp(UINT nFlags, CPoint point);
	/****************��Ϣ*************************************/
};