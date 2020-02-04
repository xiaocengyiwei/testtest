#pragma once

#include "HalconCpp.h"
using namespace Halcon;
// CDlgImage 对话框

class CDlgImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgImage();

// 对话框数据
	enum { IDD = IDD_DLG_IMAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
