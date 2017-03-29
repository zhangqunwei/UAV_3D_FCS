#include "stdafx.h"
#include"..\stdafx.h"
#include "ServerSQLOperation.h"


SQLOperation::SQLOperation()
{
}

SQLOperation::~SQLOperation()
{
}	

//�����ݿ��в�ѯ���� //////////////////////////////////// 
BOOL SQLOperation::Select(const CString& strCommand)
{
	HRESULT hr;
	_bstr_t bstrCommand(strCommand);
	//����Recordset����
	hr = m_pRecordSet.CreateInstance(TEXT("ADODB.Recordset"));
	m_pRecordSet->CursorLocation  =  adUseClient;	
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(TEXT("����Recordser����ʧ��"));
		return FALSE;
	}
	try
	{
		m_pRecordSet->Open(bstrCommand, m_pConnection.GetInterfacePtr(), 
			adOpenStatic, adLockOptimistic, adCmdText);
	}
	catch(_com_error err)
	{
		AfxMessageBox((LPCTSTR)err.Description());
		return FALSE;
	}
	//m_pRecordSet.Release();
	return  TRUE;
}
////////////////////////////////////////////////////////////////////

//ִ���ض���� ///////////////////////////////////////////////////
BOOL SQLOperation::Execute(const CString& strCommand)
{
	HRESULT hr;
	try
	{
		hr = m_pCommand.CreateInstance(TEXT("ADODB.Command"));
		if (!SUCCEEDED(hr))
		{
			AfxMessageBox(TEXT("�����ʧ��"));
			return FALSE;
		}
	}
	catch(_com_error err)
	{
		AfxMessageBox(err.Description());
		return FALSE;
	}

	m_pCommand->put_ActiveConnection(_variant_t((IDispatch*)m_pConnection, TRUE));
	m_pCommand->CommandText = _bstr_t(strCommand);
	try
	{
		m_pCommand->Execute(NULL, NULL, adCmdText);
	}
	catch(_com_error ce)
	{
		CString error;
		error.Format(TEXT("������ϢΪ:%s\r\n"), (LPCTSTR)ce.Description());
		AfxMessageBox(error);
		return FALSE;
	}
	//m_pCommand.Release();
	return TRUE;
}
/////////////////////////////////////////////////////////////////////

BOOL SQLOperation::Update(const CString& table, const CString& col, 
		const CString& data, const CString& key, const CString& keyValue)
{
	CString Command = TEXT("");
	Command = TEXT("UPDATE ") + table + TEXT(" SET ") + col + TEXT(" = ") + data + 
		TEXT(" WHERE ") + key + TEXT(" = ") + keyValue;
	Execute(Command);
	return TRUE;
}

BOOL SQLOperation::OpenDataBase(CString strConnection, 
							   CString strUserID, CString strPassword)
{
	if (m_pConnection && m_pConnection->GetState() == adStateOpen)
	{
		//AfxMessageBox(TEXT("���ݿ�������"));
		return TRUE;
	}
	HRESULT hr;
	hr = ::CoInitialize(NULL);	//��ʼ��COM

	if (!SUCCEEDED(hr))
	{
		return FALSE;
	}
	//����Connection����
	hr = m_pConnection.CreateInstance(TEXT("ADODB.Connection"));
	if (!SUCCEEDED(hr))
	{
		return FALSE;
	}
	_bstr_t bstrConnect(strConnection);
	_bstr_t bstrUserID(strUserID);
	_bstr_t bstrPassword(strPassword);

	try
	{
		//�������ݿ�
		hr = m_pConnection->Open(bstrConnect, bstrUserID, bstrPassword, adModeUnknown);	
		if (!SUCCEEDED(hr))
		{
			return FALSE;
		}
	}
	catch(_com_error err)
	{
		CString strError;                     
		strError.Format(TEXT("�������ݿ�ʧ����Ϣ!\r\n������Ϣ:%s"), (LPCTSTR)err.Description());  
		AfxMessageBox(strError);     
		return FALSE;
	}

	//��ʾ�û��������ݿ�ɹ�
	AfxMessageBox(TEXT("�������ݿ�ɹ�")); 
	return TRUE;
}

BOOL SQLOperation::CloseDataBase()
{
	if (m_pConnection == NULL)
	{
		return TRUE;
	}
	try
	{
		m_pConnection->Close();
		m_pConnection = NULL;
	}
	catch(_com_error err)
	{
		CString strError;                     
		strError.Format( err.Description() );  
		AfxMessageBox(strError);  
		TRACE("�ر����ݿⷢ������:%s\n", err.ErrorMessage());
		return FALSE;
	}
	return TRUE;
}