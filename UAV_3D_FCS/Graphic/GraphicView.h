#pragma once

#include "Graphic.h" 
#include <mutex>
#include <vector>
#include "../ComboBoxNoWheel.h"
// CGraphicView �Ի���

//ʹ�ö�ý�嶨ʱ��Ҫ�õ��Ŀ��ͷ�ļ�
#pragma comment(lib, "Winmm.lib")
#include <Mmsystem.h> 
#include "afxcmn.h"
#include "afxwin.h"
#include "../resource.h"


#define UM_TIMER_GRAPHIC_PROC (WM_USER + 1)


namespace GraphicView
{
	//������̬
	const CString TSPI = _T("TSPI");

	//������1
	const CString ESD = _T("Engine");//_T("ESD");

	//������2
	const CString ESD2 = _T("Engine_2");//_T("ESD2");

	//�澯
	const CString AMD = _T("Warning");//_T("AMD");

	//Һ��
	const CString LOSD = _T("HYD_Oil");//_T("LOSD");
	
	//����
	const CString ASD = _T("AVS");

	//�ɿ�
	const CString AFCSD = _T("FCS");

	//ʵʱ���ģʽ
	const int MonitoringModel = 1;
	//�ط�ģʽ
	const int PlaybackModel = 0;

	//ֹͣ״̬
	const int stop_state = 1;
	//����״̬
	const int play_state = 0;

	//ͨ�ö�ʱʱ��ms
	const int Timer = 200;

	//�ط�ģʽģʽ��ʱʱ��ms
	const int PlaybackModelTimer = 50;

	//ʵʱ���ģʽ��ʱʱ��ms
	const int MonitoringModelTimer = 200;
}


class CGraphicView : public CDialogEx
{


	DECLARE_DYNAMIC(CGraphicView)

public:
	CGraphicView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGraphicView();

// �Ի�������
	enum { IDD = IDD_DIALOG_GRAPHIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP() 
	afx_msg LRESULT OnMyGriphicTimerProc(WPARAM wParam, LPARAM lParam);


public:
	typedef CString value_name;
	typedef Graphic::data_struct value_struct;

	typedef std::map<value_name, Graphic::data_scope_struct> data_scope_map;
	typedef std::pair<value_name, Graphic::data_scope_struct> data_scope_pair;

	//���õ����߿ؼ��ϵ��������ݶ���
	Graphic::Chart_Data_Queue m_ChartDataDeque;

	//���߿ؼ�
	CGraphic m_Graphic;

	virtual BOOL OnInitDialog();

private:
	//��Ϣͷ
	MessageHeader m_MessageHeader; 

	//���Ҫ���µ������Ƿ��õ�
	bool isDataArriva = false;

	std::mutex m_mutex;

	//��ʱ��ID
	UINT m_uTimerID = 0; 

	//�洢�������ݵ���������ݽṹ
	Graphic::Chart_Data m_rec_chart_data; 

	//�洢���ݷ�Χ�����ݽṹ
	data_scope_map m_data_scope;

	//��ǰ���ݵ���ʾģʽ
	int m_current_model;

	//������ߵ�ǰ��Ҫ�����ĸ����ݰ������ݣ������˹ر���Ϣ���ߵ�ȱ��
	CString m_data_pkg_flag;
	 
private:

	//��������
	void UpdateTSPIDC(const TSPIDC& p_tspidc); 

private:
	//��ʼ������Ҫ���µ����ݽṹ��
	void InitTSPIDCValueStruct(std::vector<CString>& p_param_vec, const TSPIDC& p_tspidc, value_struct& p_value_struct);
	 

private:
	//��ʼ�����ݵ�ṹ��
	void InitValueStruct(value_struct& p_value_struct, const value_name p_name, const Graphic::point_value_type& p_value);

private: 
	//���ݵ�ǰѡ������ݰ���ʼ�����ݷ�Χ
	void InitDataScope(); 

	//��ʼ��ÿ�����ݰ���Χ
	void InitTSPIDataScope(); 
	 

private:
	//������ȷ�Ķ�ʱ��
	void StartEventTimer();

	//�رվ�ȷ�Ķ�ʱ��
	void CloseEventTimer();

	//��ʼ����Ϣ����
	void StartMessageBus();

	//�ر���Ϣ����
	void CloseMessageBus();

private:
	//��ʼ�����ݰ���������
	void InitFormVector(std::vector<CString>& p_form_vec);
	//��ʼ�����ݰ�������������
	void InitFormParamVector();

	//�����ݰ���ӵ���Ͽ���
	void AddFormVecToComboForm(std::vector<CString>& m_form_param_vec);
	//�����ݰ��еı�����ӵ������б����
	void AddFormParamVecToComboFormParam(std::vector<CString>& p_form_param_vec); 

	//�������ݰ��б��
	void UpdataFormCombo();  
	//�������ݰ������б��
	void UpdataFormParamCombo(); 

private:
	//�������������ӱ�������
	void AddTSPIParamToParamVec();  
	 

private:
	//��������ͼ
	void UpdateGraphic();

	//����Y�᷶Χ�༭��
	void UpdateYScopeEdit();

	//���µ����ʱ���ֵ
	void UpdataArriveTimeAndValue(double p_cur_time, double p_cur_value);

	//���µ����ʱ���ֵ������
	void CGraphicView::UpdataArriveTimeAndValue(Graphic::time_struct arrive_time, double p_cur_value);

private:
	//�õ���С��Χ
	double GetMinScope(const CString p_current_select_param) { return (*m_data_scope.find(p_current_select_param)).second.min_scope; }

	//�õ����Χ
	double GetMaxScope(const CString p_current_select_param) { return (*m_data_scope.find(p_current_select_param)).second.max_scope; }

	//�õ���ǰ���ݵ�λ
	CString GetCurDataUnit(const CString p_current_select_param) { return (*m_data_scope.find(p_current_select_param)).second.data_unit; }


public:
	//��ʼ������ͼ
	void InitGraphic(); 

	//��ʼ��������ť
	void InitTwoBtn();

	//���õ�ǰ��ʾģʽ
	void SetCurentModel(const int p_model) { m_current_model = p_model; }

	//���õ�ǰ����ʱ��͵���ֵ�����ڻط���ͣʱ�����ƶ���Ϣ
	void SetCurrentTimeAndValue(double p_cur_time, double p_cur_value) { UpdataArriveTimeAndValue(p_cur_time, p_cur_value); }

	//�õ���ǰ����ͼ��������ʾģʽ
	int GetCurrentModel() { return m_current_model; }

	//���õ�ǰ��ʾ״̬
	void SetCurShowState(const int p_cur_state){ m_cur_state = p_cur_state; }
	 
private:
	// ������
	//CSliderCtrl m_SliderZoom;

	// ��ͣ��ť
	CButton m_BtnPause;

	// ���ڻط�ģʽ����min��max��Χ
	CButton m_BtnUpdataParam;

	// ���ݰ�ѡ���
	CComboBoxNoWheel m_SelectForm;

	// ���ݰ��о������ѡ���
	CComboBoxNoWheel m_SelectFormParam; 

	// Y�����Χ
	CEdit m_y_max_edit;

	// Y����С��Χ
	CEdit m_y_min_edit; 

	// ��ʾ����ʱ��ı༭��
	CEdit m_edit_arrive_time;

	// ��ʾ����ֵ�ı༭��
	CEdit m_edit_arrive_value;

	//�洢��ǰѡ������ݰ�������
	CString m_current_select_form;

	//�洢��ǰѡ������ݰ��еĲ���
	CString m_current_select_param;
	
	//�洢���ݰ����Ƶ���������
	std::vector<CString> m_form_vec;

	//�洢���ݰ��б������Ƶ���������
	std::vector<CString> m_form_param_vec; 

	//�洢���ݰ��о���������ͺͶ�Ӧֵ�Ľṹ�������
	std::map<value_name, value_struct> m_form_param_map;
	 
	//��ǰ���ݻطŵ�״̬��ֹͣ���Ǽ���
	int m_cur_state;
protected:
	//ʹ���˶��ֶ�ʱ������ʱ��ʹ�����ֻص�
	static void CALLBACK TimerCallBack(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
	{
		CGraphicView* pThis = (CGraphicView*)dwUser;
		pThis->OnMyTimerCallBack();
	}
public:
	void OnMyTimerCallBack();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPause(); 
	afx_msg void OnBnClickedUpdataParam();
	afx_msg void OnCbnSelchangeComboTable();
	afx_msg void OnCbnSelchangeComboTablePara();
	afx_msg void OnNMReleasedcaptureSliderZoom(NMHDR *pNMHDR, LRESULT *pResult);  
public: 
	afx_msg void OnStnClickedGraphic();
};
void _stdcall TimeGriphicProc(UINT uTimerID, UINT uMessage, DWORD dwUser, DWORD dw1, DWORD dw2);

 