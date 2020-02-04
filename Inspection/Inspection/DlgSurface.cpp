// DlgSurface.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgSurface.h"
#include "ParameterPool.h"
#include "DlgParaSetting.h"


extern CDlgParaSetting* g_DlgSetting;
extern CParameterPool g_PP;

// CDlgSurface 对话框

IMPLEMENT_DYNAMIC(CDlgSurface, CDialog)

CDlgSurface::CDlgSurface(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSurface::IDD, pParent)
{
// 	m_DrawRectWidth = 0;
// 	m_DrawRectHeight = 0;
// 	m_DrawRectArea = 0;
// 	m_DrawRectFArea = 0;
// 	m_DrawRectAvgGray = 0;
// 	m_DrawRectMaxGray = 0;
// 	m_DrawRectMinGray = 0;
}

CDlgSurface::~CDlgSurface()
{
}

void CDlgSurface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_SURF_BACKGRAY,g_PP.m_Surf_ProdGray_Low);
	DDX_Text(pDX,IDC_EDIT_SURF_PRODUCTGRAY,g_PP.m_Surf_ProdGray_High);
	DDX_Text(pDX,IDC_EDIT_SURF_PRODUCTAREA,g_PP.m_Surf_ProdArea);

	DDX_Text(pDX,IDC_EDIT_SURF_MEAN_W1,g_PP.m_Surf_MeanW1);
	DDX_Text(pDX,IDC_EDIT_SURF_MEAN_H1,g_PP.m_Surf_MeanH1);
	DDX_Text(pDX,IDC_EDIT_SURF_MEAN_W2,g_PP.m_Surf_MeanW2);
	DDX_Text(pDX,IDC_EDIT_SURF_MEAN_H2,g_PP.m_Surf_MeanH2);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_W,g_PP.m_Surf_CloseW);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_H,g_PP.m_Surf_CloseH);
	DDX_Text(pDX,IDC_EDIT_SURF_EROSE_W,g_PP.m_Surf_EroseW);
	DDX_Text(pDX,IDC_EDIT_SURF_EROSE_H,g_PP.m_Surf_EroseH);

	DDX_Text(pDX,IDC_EDIT_SURF_DYN_THRESH1,g_PP.m_Surf_DynThresh1);
	DDX_Text(pDX,IDC_EDIT_SURF_DYN_THRESH2,g_PP.m_Surf_DynThresh2);
	DDX_Control(pDX,IDC_COMBO_SURF_DYN_MODE1,m_Combo_DynMode_1);
	DDX_Control(pDX,IDC_COMBO_SURF_DYN_MODE2,m_Combo_DynMode_2);
	DDX_Text(pDX,IDC_EDIT_SURF_AREA_MIN,g_PP.m_Surf_Area_Min);
	DDX_Text(pDX,IDC_EDIT_SURF_AREA_MIN_MM, m_RealMinArea);

	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_W1,g_PP.m_Surf_Close_W1);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_H1,g_PP.m_Surf_Close_H1);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_W2,g_PP.m_Surf_Close_W2);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_H2,g_PP.m_Surf_Close_H2);

	DDX_Text(pDX,IDC_EDIT_SURF_DYN_THRESH3,g_PP.m_Surf_DynThresh3);
	DDX_Text(pDX,IDC_EDIT_SURF_DYN_THRESH4,g_PP.m_Surf_DynThresh4);
	DDX_Control(pDX,IDC_COMBO_SURF_DYN_MODE3,m_Combo_DynMode_3);
	DDX_Control(pDX,IDC_COMBO_SURF_DYN_MODE4,m_Combo_DynMode_4);

	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_1C3,g_PP.m_Surf_Close_1C3);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_2C3,g_PP.m_Surf_Close_2C3);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_1C4,g_PP.m_Surf_Close_1C4);
	DDX_Text(pDX,IDC_EDIT_SURF_CLOSE_2C4,g_PP.m_Surf_Close_2C4);

	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_CLOSE_WC5,g_PP.m_Surf_Stripe_Close_WC5);
	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_CLOSE_HC5,g_PP.m_Surf_Stripe_Close_HC5);
	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_W,g_PP.m_Surf_Stripe_W1);
	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_W2,g_PP.m_Surf_Stripe_W2);
	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_H,g_PP.m_Surf_Stripe_H1);
	DDX_Text(pDX,IDC_EDIT_SURF_STRIPE_H2,g_PP.m_Surf_Stripe_H2);


	//DDX_Check(pDX,IDC_CHECK_SURF_FAST_MODE,g_PP.m_Surf_IfFastCheck);
	//DDX_Text(pDX,IDC_EDIT_SURF_ERRGRAY1,g_PP.m_Surf_ErrGray1);
	//DDX_Text(pDX,IDC_EDIT_SURF_ERRGRAY2,g_PP.m_Surf_ErrGray2);

	//Draw Rectangle
// 	DDX_Text(pDX,IDC_EDIT_DRAW_WIDTH, m_DrawRectWidth);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_HEIGHT, m_DrawRectHeight);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_AREA, m_DrawRectArea);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_F_AREA, m_DrawRectFArea);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_AVG_GRAY, m_DrawRectAvgGray);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_MAX_GRAY, m_DrawRectMaxGray);
// 	DDX_Text(pDX,IDC_EDIT_DRAW_MIN_GRAY, m_DrawRectMinGray);

	//Test Thresh
	DDX_Control(pDX,IDC_SLIDER_TEST_GRAY1, m_SliderTestThresh1);
	DDX_Control(pDX,IDC_SLIDER_TEST_GRAY2, m_SliderTestThresh2);
	DDX_Text(pDX,IDC_EDIT_TEST_GRAY1, m_TestThreshGray1);
	DDX_Text(pDX,IDC_EDIT_TEST_GRAY2, m_TestThreshGray2);
}


BEGIN_MESSAGE_MAP(CDlgSurface, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SURF_DYN_MODE1, &CDlgSurface::OnCbnSelchangeComboSurfDynMode1)
	ON_CBN_SELCHANGE(IDC_COMBO_SURF_DYN_MODE2, &CDlgSurface::OnCbnSelchangeComboSurfDynMode2)
	ON_CBN_SELCHANGE(IDC_COMBO_SURF_DYN_MODE3, &CDlgSurface::OnCbnSelchangeComboSurfDynMode3)
	ON_CBN_SELCHANGE(IDC_COMBO_SURF_DYN_MODE4, &CDlgSurface::OnCbnSelchangeComboSurfDynMode4)
	//ON_BN_CLICKED(IDC_BUTTON_DRAW_RECT, &CDlgSurface::OnBnClickedButtonDrawRect)
	//ON_BN_CLICKED(IDC_BUTTON_TEST_THRESH, &CDlgSurface::OnBnClickedButtonTestThresh)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_SURF_AREA_MIN, &CDlgSurface::OnEnChangeEditSurfAreaMin)
END_MESSAGE_MAP()

BOOL CDlgSurface::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitComboBox();
	InitSliderTestThresh();
	copy_obj(g_PP.m_hCheckRegion[g_DlgSetting->m_CurrSelectedCam], &m_hDrawRectangle, 1, 1);
	CalcRealMinArea();
	UpdateData(false);
	return TRUE;
}

void CDlgSurface::InitComboBox()
{
	m_Combo_DynMode_1.InsertString(DYN_MODE_LIGHT,"Light");
	m_Combo_DynMode_1.InsertString(DYN_MODE_DARK,"Dark");  //not_equal
	m_Combo_DynMode_1.InsertString(DYN_MODE_NOTEQUAL,"Not_equal");
	m_Combo_DynMode_1.InsertString(DYN_MODE_DIRECE,"Direct");
	m_Combo_DynMode_1.SetCurSel(g_PP.m_Surf_DynMode_1);

	m_Combo_DynMode_2.InsertString(DYN_MODE_LIGHT,"Light");
	m_Combo_DynMode_2.InsertString(DYN_MODE_DARK,"Dark");  //not_equal
	m_Combo_DynMode_2.InsertString(DYN_MODE_NOTEQUAL,"Not_equal");
	m_Combo_DynMode_2.InsertString(DYN_MODE_DIRECE,"Direct");
	m_Combo_DynMode_2.SetCurSel(g_PP.m_Surf_DynMode_2);

	m_Combo_DynMode_3.InsertString(DYN_MODE_LIGHT,"Light");
	m_Combo_DynMode_3.InsertString(DYN_MODE_DARK,"Dark");  //not_equal
	m_Combo_DynMode_3.InsertString(DYN_MODE_NOTEQUAL,"Not_equal");
	m_Combo_DynMode_3.InsertString(DYN_MODE_DIRECE,"Direct");
	m_Combo_DynMode_3.SetCurSel(g_PP.m_Surf_DynMode_3);

	m_Combo_DynMode_4.InsertString(DYN_MODE_LIGHT,"Light");
	m_Combo_DynMode_4.InsertString(DYN_MODE_DARK,"Dark");  //not_equal
	m_Combo_DynMode_4.InsertString(DYN_MODE_NOTEQUAL,"Not_equal");
	m_Combo_DynMode_4.InsertString(DYN_MODE_DIRECE,"Direct");
	m_Combo_DynMode_4.SetCurSel(g_PP.m_Surf_DynMode_4);
}

void CDlgSurface::InitSliderTestThresh()
{
	m_SliderTestThresh1.SetRange(1,254);
	m_SliderTestThresh2.SetRange(2,255);
	m_SliderTestThresh1.SetPos(g_PP.m_Surf_ProdGray_Low);
	m_SliderTestThresh2.SetPos(g_PP.m_Surf_ProdGray_High);
	m_TestThreshGray1 = m_SliderTestThresh1.GetPos();
	m_TestThreshGray2 = m_SliderTestThresh2.GetPos();
}
// CDlgSurface 消息处理程序

void CDlgSurface::OnCbnSelchangeComboSurfDynMode1()
{
	UpdateData(TRUE);
	g_PP.m_Surf_DynMode_1 = m_Combo_DynMode_1.GetCurSel();
}
void CDlgSurface::OnCbnSelchangeComboSurfDynMode2()
{
	UpdateData(TRUE);
	g_PP.m_Surf_DynMode_2 = m_Combo_DynMode_2.GetCurSel();
}
void CDlgSurface::OnCbnSelchangeComboSurfDynMode3()
{
	UpdateData(TRUE);
	g_PP.m_Surf_DynMode_3 = m_Combo_DynMode_3.GetCurSel();
}
void CDlgSurface::OnCbnSelchangeComboSurfDynMode4()
{
	UpdateData(TRUE);
	g_PP.m_Surf_DynMode_4 = m_Combo_DynMode_4.GetCurSel();
}
void CDlgSurface::OnBnClickedButtonDrawRect()
{
	g_DlgSetting->DrawRectangle();
	CalcTestRegion(m_hDrawRectangle);
}

void CDlgSurface::CalcTestRegion(Hobject hInputRegion)
{
// 	HTuple tempArea;
// 	area_center(hInputRegion, &tempArea, NULL, NULL);
// 	m_DrawRectArea = tempArea[0].I();
// 	if (m_DrawRectArea > 0)
// 	{
// 		smallest_rectangle1(hInputRegion, &m_hRectR1, &m_hRectC1, &m_hRectR2, &m_hRectC2);
// 		m_DrawRectWidth = m_hRectC2[0].I() - m_hRectC1[0].I();
// 		m_DrawRectHeight = m_hRectR2[0].I() - m_hRectR1[0].I();
// 
// 		m_DrawRectFArea = (float)m_DrawRectArea * g_PP.m_Resolution_H * g_PP.m_Resolution_W[g_DlgSetting->m_CurrSelectedCam];
// 		min_max_gray(hInputRegion,g_PP.m_hOriginalImage[g_DlgSetting->m_CurrSelectedCam], NULL, &m_hRectMinGray, &m_hRectMaxGray, NULL);
// 		intensity(hInputRegion,g_PP.m_hOriginalImage[g_DlgSetting->m_CurrSelectedCam],&m_hRectAvgGray, NULL);
// 		m_DrawRectAvgGray = m_hRectAvgGray[0].I();
// 		m_DrawRectMinGray = m_hRectMinGray[0].I();
// 		m_DrawRectMaxGray = m_hRectMaxGray[0].I();
// 		UpdateData(false);
// 	}
}

void CDlgSurface::OnBnClickedButtonTestThresh()
{
	UpdateData(true);
	g_DlgSetting->TestThresh();
	CalcTestRegion(m_hTestThreshRegion);
}

void CDlgSurface::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CWnd *pSliderTestThresh1 = this->GetDlgItem(IDC_SLIDER_TEST_GRAY1);
	CWnd *pSliderTestThresh2 = this->GetDlgItem(IDC_SLIDER_TEST_GRAY2);
	if (pSliderTestThresh1 == (CSliderCtrl*)pScrollBar)
	{
		OnSliderTestGray1();
	}
	if (pSliderTestThresh2 == (CSliderCtrl*)pScrollBar)
	{
		OnSliderTestGray2();
	}
	UpdateData(false);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgSurface::OnSliderTestGray1()
{
	m_TestThreshGray1 = m_SliderTestThresh1.GetPos();
	if ((m_TestThreshGray2-m_TestThreshGray1)<1)
	{
		m_TestThreshGray2 = m_TestThreshGray1 + 1;
		m_SliderTestThresh2.SetPos(m_TestThreshGray2);
	}
	UpdateData(false);
	OnBnClickedButtonTestThresh();
}

void CDlgSurface::OnSliderTestGray2()
{
	m_TestThreshGray2 = m_SliderTestThresh2.GetPos();
	if ((m_TestThreshGray2-m_TestThreshGray1)<1)
	{
		m_TestThreshGray1 = m_TestThreshGray2 - 1;
		m_SliderTestThresh1.SetPos(m_TestThreshGray1);
	}
	UpdateData(false);
	OnBnClickedButtonTestThresh();
}
void CDlgSurface::OnEnChangeEditSurfAreaMin()
{
	UpdateData(true);
	CalcRealMinArea();
	UpdateData(false);
}

void CDlgSurface::CalcRealMinArea()
{
	m_RealMinArea = (float)g_PP.m_Surf_Area_Min*g_PP.m_Resolution_H*g_PP.m_Resolution_W[0];
}