
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// UAV_3D_FCS.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


MessageBus g_Bus;				//��Ϣ����ȫ�ֱ���
std::atomic<int> g_TSPIPackNum;	//���ݰ�ȫ��ԭ�ӱ���



std::atomic<int> g_PID = -1;  //�ɻ���ţ�Ĭ��Ϊ��Ч�ı��-1
DWORD gStartTime = 0;
DWORD gCurTime = 0;
DOUBLE gTimeOffset = 0.0;
DOUBLE gPixel = 0;
INT g_CurID = 0;
BOOL gResetID = FALSE;//�ж��Ƿ��е��������


