#pragma once


// CDlgPinhole 对话框

class CDlgPinhole : public CDialog
{
	DECLARE_DYNAMIC(CDlgPinhole)

public:
	CDlgPinhole(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPinhole();

// 对话框数据
	enum { IDD = IDD_DLG_PINHOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
