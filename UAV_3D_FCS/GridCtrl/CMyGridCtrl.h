//HEAD FILES/////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "GridCtrl.h"
#include "NewCellTypes\GridCellCheck.h"
///////////////////////////////////////////////////////////////

//CLASS /////////////////////////////////////////////////////
//�̳�GridCtrl�࣬ʵ���Զ���GridCtrl
class CMyGridCtrl:public CGridCtrl
{
public:
	CMyGridCtrl();
	~CMyGridCtrl();

	void SetColumnColor(int nCol, COLORREF clr);	//����ĳһ�еı�����ɫ
	void SetRowColor(int nRow, COLORREF  clr);		//����ĳһ�еı�����ɫ
	void LoadImageList(int nImageId,int nSize);		//����ͼƬ�б�
	void SetCellCombo(int nRow, int nCol,  
		CStringArray& items);						//����ĳ����Ԫ��ΪComboBox
	void SetCellCheck(int nRow, int nCol, 
		bool isCheck);								//����ĳ����Ԫ��ΪCheckBox
	void SetCellRadio(int nRow, int nCol,
		bool isRadios);
};
/////////////////////////////////////////////////////////////
