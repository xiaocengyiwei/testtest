// DlgImage.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgImage.h"


// CDlgImage 对话框

IMPLEMENT_DYNAMIC(CDlgImage, CDialog)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImage::IDD, pParent)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialog)
END_MESSAGE_MAP()


// CDlgImage 消息处理程序
