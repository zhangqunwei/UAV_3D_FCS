#include "stdafx.h"
/////////////////////////////////////////////////////////////////////////
/// ����Դ�ļ��м���ͼƬ
/// @param [in] pImage ͼƬָ��
/// @param [in] nResID ��Դ��
/// @param [in] lpTyp ��Դ����
//////////////////////////////////////////////////////////////////////////
static bool LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID,
	IN CString lpTyp)
{
	if (pImage == NULL) return false;

	pImage->Destroy();

	// ������Դ
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) return false;

	// ������Դ
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);

	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);

		GlobalFree(hNew);
	}

	// �ͷ���Դ
	::FreeResource(hImgData);

	return true;
}