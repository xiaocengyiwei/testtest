#pragma once
#include "ParameterPool.h"

// CDlgEdge 对话框

class CDlgWidth : public CDialog
{
	DECLARE_DYNAMIC(CDlgWidth)

public:
	CDlgWidth(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWidth();

// 对话框数据
	enum { IDD = IDD_DLG_WIDTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
