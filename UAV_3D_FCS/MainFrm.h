
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "Tools/MySplitterWnd.h"
#include "OSG/OSGViewControl.h"
#include "Connection/ConnectionViewControl.h"
#include "FlightControl/FlightSysViewControl.h"
#include "PlayBack/PlayBackViewControl.h"
#include "HUD/HUDViewControl.h"
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

private:
	//���ܴ��ڷ�Ϊ����һ��
	CMySplitterWnd m_SplitterWnd;   

	CMySplitterWnd m_SplitterWnd1;


	//�������һ�зֳ�һ������
	//CMySplitterWnd m_SplitterWndBottom;
	//�������һ�зֳ�һ������
	//CMySplitterWnd m_SplitterWndTop;



// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual void ActivateFrame(int nCmdShow = -1);
	afx_msg LRESULT OnShowMainWindow(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


