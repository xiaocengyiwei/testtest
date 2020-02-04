// DlgEdge.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgWidth.h"

extern CParameterPool g_PP;
// CDlgEdge 对话框

IMPLEMENT_DYNAMIC(CDlgWidth, CDialog)

CDlgWidth::CDlgWidth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWidth::IDD, pParent)
{

}

CDlgWidth::~CDlgWidth()
{
}

void CDlgWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_WIDTH_GRAY,g_PP.m_WidthGray);
	DDX_Text(pDX,IDC_EDIT_STORED_NUM,g_PP.m_StoredNum);
	DDX_Text(pDX,IDC_EDIT_OVERLAP_WIDTH,g_PP.m_Overlap_Width);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W1,g_PP.m_Resolution_W[0]);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W2,g_PP.m_Resolution_W[1]);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W3,g_PP.m_Resolution_W[2]);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W4,g_PP.m_Resolution_W[3]);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W5,g_PP.m_Resolution_W[4]);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION_W6,g_PP.m_Resolution_W[5]);
}


BEGIN_MESSAGE_MAP(CDlgWidth, CDialog)
END_MESSAGE_MAP()


// CDlgEdge 消息处理程序
