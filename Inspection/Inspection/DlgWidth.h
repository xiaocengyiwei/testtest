#pragma once
#include "ParameterPool.h"

// CDlgEdge �Ի���

class CDlgWidth : public CDialog
{
	DECLARE_DYNAMIC(CDlgWidth)

public:
	CDlgWidth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWidth();

// �Ի�������
	enum { IDD = IDD_DLG_WIDTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
