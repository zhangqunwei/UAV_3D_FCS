// ComboBoxNoWheel.cpp : ʵ���ļ�
//

#include "stdafx.h" 
#include "ComboBoxNoWheel.h"


// CComboBoxNoWheel

IMPLEMENT_DYNAMIC(CComboBoxNoWheel, CComboBox)

CComboBoxNoWheel::CComboBoxNoWheel()
{

}

CComboBoxNoWheel::~CComboBoxNoWheel()
{
}


BEGIN_MESSAGE_MAP(CComboBoxNoWheel, CComboBox)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// CComboBoxNoWheel ��Ϣ�������




BOOL CComboBoxNoWheel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CComboBox::OnMouseWheel(nFlags, zDelta, pt);
}
