#ifndef FILE_SQL_OPERATION_H
#define FILE_SQL_OPERATION_H

#include "../stdafx.h"


class SQLOperation
{
public:
	SQLOperation();
	~SQLOperation();

	//���Ӵ����ݿ�
	BOOL OpenDataBase(CString strConnection, 
							   CString strUserID, CString strPassword);
	//�Ͽ��ر����ݿ�
	BOOL CloseDataBase();

	//ִ�������
	BOOL Execute(const CString& strCommand);

	//��ѯ����
	BOOL Select(const CString& strCommand);

	//��������
	BOOL Update(const CString& table, const CString& col,
		const CString& data, const CString& key, const CString& keyValue);
    //ACCOUNT_INFOR m_AccountInfor;

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	_CommandPtr m_pCommand;
};
#endif