#include "stdafx.h"
#include "TabControler.h"
#include "DlgParaSetting.h"

extern CDlgParaSetting* g_DlgSetting;

CTabControler::CTabControler(void)
{
}

CTabControler::~CTabControler(void)
{
}

void CTabControler::Hide_All_Image()
{
	//隐藏相机拍摄到的图像标签
	g_DlgSetting->m_Dlg_Image.SetWindowPos(NULL,g_DlgSetting->m_Rect_Image.left,g_DlgSetting->m_Rect_Image.top,g_DlgSetting->m_Rect_Image.Width(),g_DlgSetting->m_Rect_Image.Height(),SWP_HIDEWINDOW);

}

void CTabControler::Show_Image_Tab( int index )
{
	//显示图像
	Hide_All_Image();
	switch(index)
	{
	case 0:
		g_DlgSetting->m_Dlg_Image.SetWindowPos(NULL,g_DlgSetting->m_Rect_Image.left,g_DlgSetting->m_Rect_Image.top,g_DlgSetting->m_Rect_Image.Width(),g_DlgSetting->m_Rect_Image.Height(),SWP_SHOWWINDOW);
		break;
	//case 1:
	//	break;
	default:
		g_DlgSetting->m_Dlg_Image.SetWindowPos(NULL,g_DlgSetting->m_Rect_Image.left,g_DlgSetting->m_Rect_Image.top,g_DlgSetting->m_Rect_Image.Width(),g_DlgSetting->m_Rect_Image.Height(),SWP_SHOWWINDOW);
	}
}

void CTabControler::Hide_All_Parameters()
{
	//隐藏所有参数页签
	g_DlgSetting->m_Dlg_Pinhole.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_HIDEWINDOW);
	g_DlgSetting->m_Dlg_Width.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_HIDEWINDOW);
	g_DlgSetting->m_Dlg_Surface.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_HIDEWINDOW);
	g_DlgSetting->m_Dlg_Score.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_HIDEWINDOW);
}

void CTabControler::Show_Parameters_Tab( int index )
{
	Hide_All_Parameters();
	switch(index)
	{
	case 2:
		g_DlgSetting->m_Dlg_Pinhole.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_SHOWWINDOW);
		break;
	case 3:
		g_DlgSetting->m_Dlg_Width.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_SHOWWINDOW);
		break;
	case 0:
		g_DlgSetting->m_Dlg_Surface.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_SHOWWINDOW);
		break;
	case 1:
		g_DlgSetting->m_Dlg_Score.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_SHOWWINDOW);
		break;
	default:
		g_DlgSetting->m_Dlg_Surface.SetWindowPos(NULL,g_DlgSetting->m_Rect_Parameters.left,g_DlgSetting->m_Rect_Parameters.top,g_DlgSetting->m_Rect_Parameters.Width(),g_DlgSetting->m_Rect_Parameters.Height(),SWP_SHOWWINDOW);
	}
}