#pragma once

#include "HalconCpp.h"
using namespace Halcon;
// CDlgImage �Ի���

class CDlgImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImage();

// �Ի�������
	enum { IDD = IDD_DLG_IMAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
