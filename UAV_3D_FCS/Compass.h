#pragma once
#include "UavView.h"
class CCompass :
	public CUavView
{
public:
	CCompass();
	~CCompass();

	//���ƾ�̬����
	virtual void DrawStaticBackground(CDC *pDC);
	//���ƶ�̬����
	virtual void DrawDynamicBackground(CDC *pDC);

};

