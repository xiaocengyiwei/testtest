// DlgPinhole.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgPinhole.h"
#include "ParameterPool.h"

extern CParameterPool g_PP;
// CDlgPinhole 对话框

IMPLEMENT_DYNAMIC(CDlgPinhole, CDialog)

CDlgPinhole::CDlgPinhole(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPinhole::IDD, pParent)
{

}

CDlgPinhole::~CDlgPinhole()
{
}

void CDlgPinhole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_PIN_AREA_PIX, g_PP.m_PinHoleArea);
	DDX_Text(pDX,IDC_EDIT_MAXNUM,g_PP.m_MaxReturnNum);
	DDX_Text(pDX,IDC_EDIT_PRODUCT_GRAY,g_PP.m_ProductGray);
	DDX_Text(pDX,IDC_EDIT_PINHOLE_GRAY,g_PP.m_PinHoleGray);
	DDX_Text(pDX,IDC_EDIT_WELD_AREA_PIX_MIN,g_PP.m_WeldArea_Min);
	DDX_Text(pDX,IDC_EDIT_WELD_AREA_PIX_MAX,g_PP.m_WeldArea_Max);
	DDX_Check(pDX,IDC_CHECK_EDGECRACK,g_PP.m_IfCheckEdge);
	DDX_Text(pDX,IDC_EDIT_EDGE_AREA_PIX,g_PP.m_EdgeArea);
	DDX_Text(pDX,IDC_EDIT_EDGE_WIDTH_PIX,g_PP.m_EdgeWidth);
	DDX_Text(pDX,IDC_EDIT_EDGE_DEPTH_PIX,g_PP.m_EdgeDepth);

	DDX_Check(pDX,IDC_CHECK_AF_PINHOLE,g_PP.m_AlarmFlag[PINHOLE]);
	DDX_Check(pDX,IDC_CHECK_AF_WELD,g_PP.m_AlarmFlag[WELD]);
	DDX_Check(pDX,IDC_CHECK_AF_EDGE,g_PP.m_AlarmFlag[EDGE]);
	DDX_Check(pDX,IDC_CHECK_AF_OTHER,g_PP.m_AlarmFlag[OTHER]);

	DDX_Check(pDX,IDC_CHECK_RECORD_PINHOLE,g_PP.m_IfRecord[PINHOLE]);
	DDX_Check(pDX,IDC_CHECK_RECORD_WELD,g_PP.m_IfRecord[WELD]);
	DDX_Check(pDX,IDC_CHECK_RECORD_EDGE,g_PP.m_IfRecord[EDGE]);
	DDX_Check(pDX,IDC_CHECK_RECORD_OTHER,g_PP.m_IfRecord[OTHER]);
}


BEGIN_MESSAGE_MAP(CDlgPinhole, CDialog)
END_MESSAGE_MAP()


// CDlgPinhole 消息处理程序
