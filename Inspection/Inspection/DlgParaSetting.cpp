// DlgParaSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgParaSetting.h"
#include "Log.h"

extern CString strbefore;
extern CString strchanged;
extern CString g_user;
CString comparebefore;
CString compareafter;
CDlgParaSetting* g_DlgSetting;

extern CParameterPool g_PP;

extern CParameterPool gl_P[CAM_NUM];

extern CParameterPool gl_PB[CAM_NUM];
extern CParameterPool gl_PC[CAM_NUM];
extern CParameterPool g_PPC;
// CDlgParaSetting 对话框

IMPLEMENT_DYNAMIC(CDlgParaSetting, CDialog)

CDlgParaSetting::CDlgParaSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParaSetting::IDD, pParent)
{
	m_CamPos = -1;

}

CDlgParaSetting::~CDlgParaSetting()
{
}

void CDlgParaSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TAB_IMAGE,m_Tab_Image);
	DDX_Control(pDX,IDC_TAB_PARAMETERS,m_Tab_Parameters);
	DDX_Control(pDX,IDC_STATIC_CAMPARA,m_Static_CamPara);
	DDX_Radio(pDX,IDC_RADIO_SINGLE,m_CamPos);
	DDX_Radio(pDX,IDC_SETPARA1,m_SetMothod);
	DDX_Control(pDX, IDC_SLIDER_IMGLEFT, m_SliderImgLeft);
	DDX_Control(pDX, IDC_SLIDER_IMGRIGHT, m_SliderImgRight);
	DDX_Text(pDX,IDC_EDIT_IMGLEFT, m_ImgLeft);
	DDX_Text(pDX,IDC_EDIT_IMGRIGHT, m_ImgRight);
}


BEGIN_MESSAGE_MAP(CDlgParaSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgParaSetting::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_IMAGE, &CDlgParaSetting::OnTcnSelchangeTabImage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PARAMETERS, &CDlgParaSetting::OnTcnSelchangeTabParameters)
	ON_BN_CLICKED(IDC_RADIO_SINGLE, &CDlgParaSetting::OnBnClickedRadioCamPos)
	ON_BN_CLICKED(IDC_RADIO_LEFT, &CDlgParaSetting::OnBnClickedRadioCamPos)
	ON_BN_CLICKED(IDC_RADIO_CENTER, &CDlgParaSetting::OnBnClickedRadioCamPos)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, &CDlgParaSetting::OnBnClickedRadioCamPos)

	ON_BN_CLICKED(IDC_SETPARA1, &CDlgParaSetting::OnBnClickedRadioSetPara)
	ON_BN_CLICKED(IDC_SETPARA2, &CDlgParaSetting::OnBnClickedRadioSetPara)

	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_IMGLEFT, &CDlgParaSetting::OnEnChangeEditImgLeft)
	ON_BN_CLICKED(IDC_BTN_LEFT_L, &CDlgParaSetting::OnBnClickedBtnLeftL)
	ON_BN_CLICKED(IDC_BTN_LEFT_R, &CDlgParaSetting::OnBnClickedBtnLeftR)
	ON_EN_CHANGE(IDC_EDIT_IMGRIGHT, &CDlgParaSetting::OnEnChangeEditImgRight)
	ON_BN_CLICKED(IDC_BTN_RIGHT_L, &CDlgParaSetting::OnBnClickedBtnRightL)
	ON_BN_CLICKED(IDC_BTN_RIGHT_R, &CDlgParaSetting::OnBnClickedBtnRightR)
	ON_BN_CLICKED(IDCANCEL, &CDlgParaSetting::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CDlgParaSetting::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_DlgSetting = this;
	m_CurrSelectedCam = DEFAULT_CAM_SELECTED;

	InitStatusBar();
	InitTabImage();  //初始化相机图像显示页签
	InitTabParameters();  //初始化参数区
	
	CWnd *pWndShow = m_Dlg_Image.GetDlgItem(IDC_CAMIMAGE);
	CRect rectShow;
	pWndShow->GetClientRect(rectShow);
	open_window(rectShow.top,rectShow.left,rectShow.Width(),rectShow.Height(),(long)pWndShow->GetSafeHwnd(),"visible","",&m_HandleShowImage);
	//disp_image(g_PP.m_hOriginalImage[DEFAULT_CAM_SELECTED],m_HandleShowImage);
	set_draw(m_HandleShowImage,"margin");
	for (int i=0; i<m_TotalCamNum; i++)
	{
		copy_image(g_PP.m_hOriginalImage[i],&m_hBackGroundImg[i]);
	}
	
	DispOneObject(g_PP.m_hCheckRegion[m_CurrSelectedCam],"green");
	SetTimer(0,100,NULL);	//实时显示对应边界mm数
	UpdateData(false);
	return TRUE;
	
}

void CDlgParaSetting::InitStatusBar()
{
	CString str;
	static UINT status_id[]=
	{ 
		//-------设置N个小格
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};
	UINT nid = 0;
	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(status_id,sizeof(status_id)/sizeof(UINT));
	
	m_StatusBar.SetPaneInfo(0,nid,SBPS_STRETCH,50);
	str.Format("高度: %d    宽度: %d    ",g_PP.m_ImageWidth[m_CurrSelectedCam],g_PP.m_ImageHeight);
	m_StatusBar.SetPaneText(0,str);
	
	m_StatusBar.SetPaneInfo(1,nid,SBPS_STRETCH,100);
	str.Format("横向分辨率: %.2f    纵向分辨率: %.2f", g_PP.m_Resolution_W[m_CurrSelectedCam], g_PP.m_Resolution_H);
	m_StatusBar.SetPaneText(1,str);

	m_StatusBar.SetPaneInfo(2,nid,SBPS_STRETCH,150);
	m_StatusBar.SetPaneText(2," ");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}

void CDlgParaSetting::ReduceTabRect( CRect* rect, int left, int right, int top, int bottom )
{
	rect->left+=left;
	rect->right+=right;
	rect->top+=top;
	rect->bottom+=bottom;
}

void CDlgParaSetting::DispOneObject(Hobject hObj, const char *Colour)
{
	set_color(m_HandleShowImage,Colour);
	disp_obj(m_hBackGroundImg[m_CurrSelectedCam],m_HandleShowImage);
	disp_obj(hObj,m_HandleShowImage);
}

void CDlgParaSetting::RefreshImage()
{
	disp_obj(g_PP.m_hOriginalImage[m_CurrSelectedCam], m_HandleShowImage);
}

void CDlgParaSetting::DrawRectangle()
{
	RefreshImage();
	draw_rectangle1(m_HandleShowImage, &m_Dlg_Surface.m_hRectR1, &m_Dlg_Surface.m_hRectC1,&m_Dlg_Surface.m_hRectR2, &m_Dlg_Surface.m_hRectC2);
	gen_rectangle1(&m_Dlg_Surface.m_hDrawRectangle, m_Dlg_Surface.m_hRectR1, m_Dlg_Surface.m_hRectC1,m_Dlg_Surface.m_hRectR2, m_Dlg_Surface.m_hRectC2);
	DispOneObject(m_Dlg_Surface.m_hDrawRectangle,"green");
}

void CDlgParaSetting::TestThresh()
{
	Hobject reduceDomain;
	copy_obj(g_PP.m_hCheckRegion[m_CurrSelectedCam],&m_Dlg_Surface.m_hDrawRectangle,1,1);
	reduce_domain(g_PP.m_hOriginalImage[m_CurrSelectedCam], m_Dlg_Surface.m_hDrawRectangle, &reduceDomain);
	threshold(reduceDomain, &m_Dlg_Surface.m_hTestThreshRegion, m_Dlg_Surface.m_TestThreshGray1, m_Dlg_Surface.m_TestThreshGray2);
	DispOneObject(m_Dlg_Surface.m_hTestThreshRegion,"green");
}

void CDlgParaSetting::InitTabImage()
{
	m_Tab_Image.GetClientRect(&m_Rect_Image);
	ReduceTabRect(&m_Rect_Image,1,-1,25,-1);
	//m_Tab_Image.InsertItem(0,_T("1号相机"));
	//m_Tab_Image.InsertItem(1,_T("2号相机"));
	for (int i=0; i<m_TotalCamNum; i++)
	{
		CString str;
		str.Format("%d号相机",i+1);
		m_Tab_Image.InsertItem(i,str);
	}
	m_Dlg_Image.Create(IDD_DLG_IMAGE1,&m_Tab_Image);
	m_TabControler.Show_Image_Tab(DEFAULT_CAM_SELECTED);

	m_Static_CamPara.SetWindowText("1号相机");
	m_CamPos = g_PP.m_CamPos[DEFAULT_CAM_SELECTED];
	m_SetMothod = g_PP.m_SetParaMothod;
	//初始化左区域滑动条
	m_SliderImgLeft.SetRange(1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);  
	m_SliderImgLeft.SetPos(g_PP.m_ImgLeftOffset[DEFAULT_CAM_SELECTED]);
	m_ImgLeft.Format("%d",m_SliderImgLeft.GetPos());
	//初始化右区域滑动条
	m_SliderImgRight.SetRange(2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	m_SliderImgRight.SetPos(g_PP.m_ImgRightOffset[DEFAULT_CAM_SELECTED]);
	m_ImgRight.Format("%d",m_SliderImgRight.GetPos());
}

void CDlgParaSetting::InitTabParameters()
{
	m_Tab_Parameters.GetClientRect(&m_Rect_Parameters);
	ReduceTabRect(&m_Rect_Parameters,1,-1,25,-1);
	m_Tab_Parameters.InsertItem(0,_T("表面检测"));
	m_Tab_Parameters.InsertItem(1,_T("缺陷评分"));
	//m_Tab_Parameters.InsertItem(2,_T("孔洞参数"));
	//m_Tab_Parameters.InsertItem(3,_T("测宽"));
	m_Dlg_Pinhole.Create(IDD_DLG_PINHOLE,&m_Tab_Parameters);
	m_Dlg_Width.Create(IDD_DLG_WIDTH,&m_Tab_Parameters);
	m_Dlg_Surface.Create(IDD_DLG_SURFACE,&m_Tab_Parameters);
	m_Dlg_Score.Create(IDD_DLG_SCORE,&m_Tab_Parameters);
	m_TabControler.Show_Parameters_Tab(DEFAULT_CAM_SELECTED);
}

// CDlgParaSetting 消息处理程序

void CDlgParaSetting::OnTcnSelchangeTabImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 选择不同的相机时，切换图像，更新参数
	//g_PP.LoadCameraPara(m_CurrSelectedCam);
	g_PP.SaveCameraPara(m_CurrSelectedCam);
	*pResult = 0;
	m_Dlg_Surface.UpdateData(true);
	m_Dlg_Score.UpdateData(true);
	
	
	for(int samemodel=0;samemodel<CAM_NUM;samemodel++)
	{
		gl_P[samemodel].m_SetParaMothod=g_PP.m_SetParaMothod;
	}
	//g_PP.m_SetParaMothod=gl_P[m_CurrSelectedCam].m_SetParaMothod;
	
	if(1==g_PP.m_SetParaMothod)
	{
		for(int thesamepara=m_CurrSelectedCam;thesamepara<CAM_NUM;thesamepara++)
		{
			
			gl_P[thesamepara]=g_PP;
		}
		m_CurrSelectedCam = m_Tab_Image.GetCurSel();
		//g_PP.LoadAllPara(m_CurrSelectedCam);
		//gl_P[m_CurrSelectedCam].LoadAllPara(m_CurrSelectedCam);
		g_PP = gl_P[m_CurrSelectedCam];
	}
	else /*if(0==g_PP.m_SetParaMothod)*/
	{
		//g_PP.SaveCameraPara(m_CurrSelectedCam);
		//g_PP.SaveAllPara(m_CurrSelectedCam);
	
		gl_P[m_CurrSelectedCam]=g_PP;
		//gl_P[m_CurrSelectedCam].SaveAllPara(m_CurrSelectedCam);
		//g_PP.SaveCameraPara(m_CurrSelectedCam);
		m_CurrSelectedCam = m_Tab_Image.GetCurSel();
		//g_PP.LoadAllPara(m_CurrSelectedCam);
		//gl_P[m_CurrSelectedCam].LoadAllPara(m_CurrSelectedCam);
		g_PP = gl_P[m_CurrSelectedCam];
	}
	//切换图像
	g_PP.LoadCameraPara(m_CurrSelectedCam);


	//g_PP.SaveCameraPara(m_CurrSelectedCam);

	//切换参数
	CString str;
	str.Format("%d号相机",m_CurrSelectedCam+1);
	m_Static_CamPara.SetWindowText(str);
	//g_PP.LoadCameraPara(m_CurrSelectedCam);  //这句可以不要，在Init的时候LoadAll即可
	m_CamPos = g_PP.m_CamPos[m_CurrSelectedCam];
	
    //设置左右区域
	m_ImgLeft.Format("%d",g_PP.m_ImgLeftOffset[m_CurrSelectedCam]);
	m_ImgRight.Format("%d",g_PP.m_ImgRightOffset[m_CurrSelectedCam]);
	m_SliderImgLeft.SetPos(g_PP.m_ImgLeftOffset[m_CurrSelectedCam]);
	m_SliderImgRight.SetPos(g_PP.m_ImgRightOffset[m_CurrSelectedCam]);
	
	set_part(m_HandleShowImage,1,1,g_PP.m_ImageHeight,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	m_SliderImgLeft.SetRange(1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);
	m_SliderImgRight.SetRange(2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	gen_rectangle1(&g_PP.m_hCheckRegion[m_CurrSelectedCam],0,g_PP.m_ImgLeftOffset[m_CurrSelectedCam]-1,g_PP.m_ImageHeight-1,g_PP.m_ImgRightOffset[m_CurrSelectedCam]);


	DispOneObject(g_PP.m_hCheckRegion[m_CurrSelectedCam],"green");
	

	UpdateData(false);
	m_Dlg_Surface.UpdateData(false);
	m_Dlg_Score.UpdateData(false);
}

void CDlgParaSetting::OnTcnSelchangeTabParameters(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 切换不同的参数
	*pResult = 0;
	m_TabControler.Show_Parameters_Tab(m_Tab_Parameters.GetCurSel());
}

void CDlgParaSetting::OnBnClickedRadioCamPos()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	g_PP.m_CamPos[m_CurrSelectedCam] = m_CamPos;
}

void CDlgParaSetting::OnBnClickedRadioSetPara()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	g_PP.m_SetParaMothod = m_SetMothod;
	//UpdateData(false);
	

}


void CDlgParaSetting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CWnd *pSliderImgLeft = this->GetDlgItem(IDC_SLIDER_IMGLEFT);
	CWnd *pSliderImgRight = this->GetDlgItem(IDC_SLIDER_IMGRIGHT);
	if (pSliderImgLeft == (CSliderCtrl*)pScrollBar)
	{
		OnSlideImgLeft();
	}
	if (pSliderImgRight == (CSliderCtrl*)pScrollBar)
	{
		OnSlideImgRight();
	}

	UpdateData(false);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgParaSetting::ChangeL_CheckR(int LeftOffset, int LeftMin, int LeftMax)
{
	if (LeftOffset < LeftMin)
	{
		LeftOffset = LeftMin;
	}
	if (LeftOffset > LeftMax)
	{
		LeftOffset = LeftMax;
	}
	m_SliderImgLeft.SetPos(LeftOffset);
	g_PP.m_ImgLeftOffset[m_CurrSelectedCam] = LeftOffset;
	m_ImgLeft.Format("%d",LeftOffset);
	//Check Right
	if (LeftOffset >= g_PP.m_ImgRightOffset[m_CurrSelectedCam])
	{
		m_SliderImgRight.SetPos(LeftOffset+1);
		g_PP.m_ImgRightOffset[m_CurrSelectedCam] = LeftOffset+1;
		m_ImgRight.Format("%d",LeftOffset+1);
	}
	gen_rectangle1(&g_PP.m_hCheckRegion[m_CurrSelectedCam],0,g_PP.m_ImgLeftOffset[m_CurrSelectedCam]-1,g_PP.m_ImageHeight-1,g_PP.m_ImgRightOffset[m_CurrSelectedCam]);
	DispOneObject(g_PP.m_hCheckRegion[m_CurrSelectedCam],"green");
	//disp_obj(g_PP.m_hCheckRegion[m_CurrSelectedCam],m_HandleShowImage);
}
void CDlgParaSetting::ChangeR_CheckL(int RightOffset, int RightMin, int RightMax)
{
	if (RightOffset < RightMin)
	{
		RightOffset = RightMin;
	}
	if (RightOffset > RightMax)
	{
		RightOffset = RightMax;
	}
	m_SliderImgRight.SetPos(RightOffset);
	g_PP.m_ImgRightOffset[m_CurrSelectedCam] = RightOffset;
	m_ImgRight.Format("%d",RightOffset);
	//Check Left
	if (RightOffset <= g_PP.m_ImgLeftOffset[m_CurrSelectedCam])
	{
		m_SliderImgLeft.SetPos(RightOffset-1);
		g_PP.m_ImgLeftOffset[m_CurrSelectedCam] = RightOffset-1;
		m_ImgLeft.Format("%d",RightOffset-1);
	}
	gen_rectangle1(&g_PP.m_hCheckRegion[m_CurrSelectedCam],0,g_PP.m_ImgLeftOffset[m_CurrSelectedCam]-1,g_PP.m_ImageHeight-1,g_PP.m_ImgRightOffset[m_CurrSelectedCam]);
	DispOneObject(g_PP.m_hCheckRegion[m_CurrSelectedCam],"green");
	//disp_obj(g_PP.m_hCheckRegion[m_CurrSelectedCam],m_HandleShowImage);
}

void CDlgParaSetting::OnSlideImgLeft()
{
	ChangeL_CheckR(m_SliderImgLeft.GetPos(),1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);
}
void CDlgParaSetting::OnSlideImgRight()
{
	ChangeR_CheckL(m_SliderImgRight.GetPos(),2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
}

void CDlgParaSetting::OnBnClickedBtnLeftL()  //左减一
{
	int leftoffset = atoi(m_ImgLeft);
	leftoffset--;
	ChangeL_CheckR(leftoffset,1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);
	UpdateData(false);
}
void CDlgParaSetting::OnBnClickedBtnRightL()  //右减一
{
	int rightoffset = atoi(m_ImgRight);
	rightoffset--;
	ChangeR_CheckL(rightoffset,2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	UpdateData(false);
}


void CDlgParaSetting::OnBnClickedBtnLeftR()  //左加一
{
	int leftoffset = atoi(m_ImgLeft);
	leftoffset++;
	ChangeL_CheckR(leftoffset,1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);
	UpdateData(false);
}
void CDlgParaSetting::OnBnClickedBtnRightR()  //右加一
{
	int rightoffset = atoi(m_ImgRight);
	rightoffset++;
	ChangeR_CheckL(rightoffset,2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	UpdateData(false);
}

void CDlgParaSetting::OnEnChangeEditImgLeft()
{
	UpdateData(true);
	int leftoffset = atoi(m_ImgLeft);
	ChangeL_CheckR(leftoffset,1,g_PP.m_ImageWidth[m_CurrSelectedCam]-1);
	UpdateData(false);
}
void CDlgParaSetting::OnEnChangeEditImgRight()
{
	UpdateData(true);
	int rightoffset = atoi(m_ImgRight);
	ChangeR_CheckL(rightoffset,2,g_PP.m_ImageWidth[m_CurrSelectedCam]);
	UpdateData(false);
}

void CDlgParaSetting::OnBnClickedOk()
{
	//comparebefore="";
	comparebefore=g_PPC.ClearLoadToStrB();
	compareafter=g_PPC.ClearLoadToStrC();
	// TODO: 在此添加控件通知处理程序代码
	for(int CAM_INDEX=0;CAM_INDEX<CAM_NUM;CAM_INDEX++)
	{
		gl_PB[CAM_INDEX].InitSettingPath();
		gl_PB[CAM_INDEX].LoadCheckPara(CAM_INDEX);
		comparebefore=gl_PB[CAM_INDEX].LoadToStrB();
		// gl_P[CAM_INDEX].LoadCameraPara(CAM_INDEX);
	}
//	g_PP.LoadToStr();

	m_Dlg_Pinhole.UpdateData(true);
	m_Dlg_Width.UpdateData(true);
	m_Dlg_Surface.UpdateData(true);
	m_Dlg_Score.UpdateData(true);
	UpdateData(true);
	m_CurrSelectedCam = m_Tab_Image.GetCurSel();
	g_PP.SaveCameraPara(m_CurrSelectedCam);
	for(int samemodel=0;samemodel<CAM_NUM;samemodel++)
	{
		gl_P[samemodel].m_SetParaMothod=g_PP.m_SetParaMothod;
	}

	// for(int allsave=0;allsave<CAM_NUM;allsave++)
	//{
	//	
	//	gl_P[allsave].m_SetParaMothod=g_PP.m_SetParaMothod;
	// }
	if(0==g_PP.m_SetParaMothod)
	{
		gl_P[m_CurrSelectedCam]=g_PP;
		for(int thesamepara=0;thesamepara<CAM_NUM;thesamepara++)
		{
			gl_P[thesamepara].SaveAllPara(thesamepara);
		}
	}

		else if(1==g_PP.m_SetParaMothod)
		{
			for(int thesamepara=0;thesamepara<m_CurrSelectedCam;thesamepara++)
			{
				gl_P[thesamepara].SaveAllPara(thesamepara);
			}
			for(int thesamepara=m_CurrSelectedCam;thesamepara<CAM_NUM;thesamepara++)
			{
				gl_P[thesamepara]=g_PP;

				gl_P[thesamepara].SaveAllPara(thesamepara);

			}
		}
		
		
	
		
	   UpdateData(false);
	   m_Dlg_Surface.UpdateData(false);
	   m_Dlg_Score.UpdateData(false);
	MessageBox("参数已修改成功！");	
	//compareafter="";
	for(int CAM_INDEX=0;CAM_INDEX<CAM_NUM;CAM_INDEX++)
	{
		gl_PC[CAM_INDEX].InitSettingPath();
		gl_PC[CAM_INDEX].LoadCheckPara(CAM_INDEX);
		compareafter=gl_PC[CAM_INDEX].LoadToStrC();
		// gl_P[CAM_INDEX].LoadCameraPara(CAM_INDEX);
	}
	const size_t newsize = 100;
	char nstring[newsize];
	strcpy_s(nstring,g_user);
	if (comparebefore!=compareafter)
	{
		INITLOG("log\\");
		LogDebug1("%s", "用户修改参数并保存");
	}
	else
		{
		INITLOG("log\\");
		LogDebug1("%s", "用户未修改参数");
		}
	
}

void CDlgParaSetting::SetCamNum( int Num )
{
	m_TotalCamNum = Num;
}

void CDlgParaSetting::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//g_PP.m_SetParaMothod=0;
	//g_PP.SaveSetModel();
	INITLOG("log\\");
	LogDebug1("%s", "退出参数设置");
	CDialog::OnCancel();
}


void CDlgParaSetting::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	float fTemp1,fTemp2;
	switch(nIDEvent)
	{
	case 0:
		fTemp1=GetDlgItemInt(IDC_EDIT_IMGLEFT);
		//fTemp1=fTemp1*(g_PP.m_Resolution_W);
		str.Format("%.1f",fTemp1);
		SetDlgItemText(IDC_EDIT_RealMM,str);
			
		/*fTemp2=GetDlgItemInt(IDC_EDIT_IMGRIGHT);
		fTemp2=fTemp2*(g_PP.m_Resolution_W);
		str.Format("%.1f",fTemp2);
		SetDlgItemText(IDC_EDIT_RealMM2,str);*/
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
