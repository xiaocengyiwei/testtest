#pragma once


// CDlgPinhole �Ի���

class CDlgPinhole : public CDialog
{
	DECLARE_DYNAMIC(CDlgPinhole)

public:
	CDlgPinhole(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPinhole();

// �Ի�������
	enum { IDD = IDD_DLG_PINHOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
