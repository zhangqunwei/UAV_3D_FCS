#include"stdafx.h"
#include "..\stdafx.h"
#include "CMyGridCtrl.h"
/***********************************************************************
* Copyright (c) 2014���ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
* All rights reserved.
* 
* �ļ����ƣ�CHUD.cpp
* ժ    Ҫ������Ŀ��Ϊһ�����MFC�����Ʊ��ؼ�
* 
* ��ǰ�汾��1.0
* ��    �ߣ�֣����
* ������ڣ�2015��1��26��
*
* NOTE    : δ����Ȩ�벻Ҫ��Ϊ��ҵ��;�����������Ҫ��Ϊ��ҵ
            ��;������ϵ����
***********************************************************************/
//FUNCTIONS //////////////////////////////////////////////

//���캯�� //////////////////////////////////////////////////
CMyGridCtrl::CMyGridCtrl()
{
}
/////////////////////////////////////////////////////////

//�������� ////////////////////////////////////////////////
CMyGridCtrl::~CMyGridCtrl()
{
}
/////////////////////////////////////////////////////////

//����ĳһ�б���ɫ ////////////////////////////////////////////
void CMyGridCtrl::SetColumnColor(int nCol, COLORREF clr)
{
}
///////////////////////////////////////////////////////////

//����ĳһ�б���ɫ ///////////////////////////////////////////
void CMyGridCtrl::SetRowColor(int nRow, COLORREF  clr)
{}
//////////////////////////////////////////////////////////////

//����ͼƬ�б� ///////////////////////////////////////////
void CMyGridCtrl::LoadImageList(int nImageId,int nSize)
{}
//////////////////////////////////////////////////////////////

//����ĳ����Ԫ��ΪComboBox ///////////////////////////////////////////
void CMyGridCtrl::SetCellCombo(int nRow, int nCol,  
		CStringArray& items)
{}
//////////////////////////////////////////////////////////////

//����ĳ����Ԫ��ΪComboBox ///////////////////////////////////////////
void CMyGridCtrl::SetCellCheck(int nRow, int nCol, 
		bool isCheck)
{
	CGridCellBase *pCell = this->GetCell(nRow, nCol);
	if (pCell != NULL && pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
	{
		//����checkBox��״̬	
		((CGridCellCheck*)pCell)->SetCheck(isCheck);
	}
}
//////////////////////////////////////////////////////////////
void CMyGridCtrl::SetCellRadio(int nRow, int nCol,
	bool isRadios)
{
	CGridCellBase *pCell = this->GetCell(nRow, nCol);
	if (pCell != NULL && pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
	{
		//����checkBox��״̬	
		((CGridCellCheck*)pCell)->SetRadio(isRadios);
	}
}