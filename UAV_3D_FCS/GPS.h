#pragma once
#include "afxwin.h" 

#include "UavView.h"

namespace GPSPace {
	const int title_x_offset = 40;
	const int x_offset = 5;
	const int var_x_offset = 40;
};


class CGPS :
	public CUavView
{
public:
	CGPS();
	~CGPS();  
public: 
	
	//���ƾ�̬����
	virtual void DrawStaticBackground(CDC *pDC);
	//���ƶ�̬����
	virtual void DrawDynamicBackground(CDC *pDC);

private:
	
};




