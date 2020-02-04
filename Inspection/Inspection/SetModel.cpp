// SetModel.cpp : implementation file
//

#include "stdafx.h"
#include "Inspection.h"
#include "SetModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSetModel* SetM;   //add by qq

#define SetStatus(Status,id)\
{\
	if(Status)\
{\
	CSetModel::GetDlgItem(id)->EnableWindow(TRUE);\
}\
	else\
{\
	CSetModel::GetDlgItem(id)->EnableWindow(FALSE);\
}\
};

/////////////////////////////////////////////////////////////////////////////
// CSetModel dialog


CSetModel::CSetModel(CWnd* pParent /*=NULL*/)
	: CDialog(CSetModel::IDD, pParent)
	, m_bRollChange(FALSE)
	, m_edgeOpenSize(0)
	, m_edgeCloseSize(0)
	, m_imgStored(50)
	, m_HorRes(0)
	, m_VerRes(0)
	, m_extraPix(0)
	, m_ifRecordWidth(FALSE)
	//, isCheckErrDistance(FALSE)
	//, m_errDistance(0)
	, m_ExtraWidth(0)
	, m_ProductWidth(0)
	, gray_background(0)
	, m_Gray_Product(0)
	, m_Width_Upbound(0)
	, m_Width_Downbound(0)
	, m_IfRecordWidthErr(FALSE)
	, m_Lock_PassWord(_T(""))
	, m_CameraPosition(-1)
	, m_ifDelayWidth(FALSE)
{
	//{{AFX_DATA_INIT(CSetModel)
	m_Gray = 0;
	m_Area = 0;
	m_Uploc = 0;		//��ƫ�� add by qq
	m_Leftloc = 0;		//��ƫ�� add by qq	
	m_Downloc = 0;  //��ƫ�� add by qq
	m_Rightloc = 0; //��ƫ�� add by qq
	m_bErrorArea = 1000;//�������add by qq
	
	m_bHeight = 6000;
	m_bWidth = 2048;
	m_bErrorNum = 0;
	
	//}}AFX_DATA_INIT

	m_bRollChange = TRUE;//add by qq
}


void CSetModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetModel)

	DDX_Text(pDX, IDC_EDIT1, m_Gray);
	DDV_MinMaxInt(pDX, m_Gray, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, m_Area);
	DDV_MinMaxInt(pDX, m_Area, 0, 10000);
	DDX_Text(pDX, IDC_ErrorNum, m_bErrorNum);		//add by qq

	DDX_Text(pDX, IDC_Up, m_Uploc);			//add by qq
	//	DDV_MinMaxInt(pDX, m_Uploc, 0, 6000);		//add by qq
	DDX_Text(pDX, IDC_Left, m_Leftloc);		//add by qq
	//	DDV_MinMaxInt(pDX, m_Leftloc, 0, 2048);	//add by qq
	DDX_Text(pDX, IDC_Down, m_Downloc);		//add by qq
	//	DDV_MinMaxInt(pDX, m_Downloc, 0, 6000);	//add by qq
	DDX_Text(pDX, IDC_Right, m_Rightloc);		//add by qq
	//	DDV_MinMaxInt(pDX, m_Rightloc, 0, 2048);	//add by qq
	DDX_Text(pDX, IDC_EDIT7, m_bErrorArea);		//add by qq
	DDV_MinMaxInt(pDX, m_bErrorArea, 0, 1000000);	//add by qq
	DDX_Text(pDX, IDC_pheight, m_bHeight);		//add by qq
	DDX_Text(pDX, IDC_pwidth, m_bWidth);		//add by qq





	DDX_Control(pDX, IDC_CHECK_ROLLCHANGE, m_ChkBtn_RollChange);//add by qq
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_ROLLCHANGE, m_bRollChange);
	DDX_Text(pDX, IDC_EDIT_OPEN_EDGE, m_edgeOpenSize);
	DDX_Text(pDX, IDC_EDIT_CLOSE_EDGE, m_edgeCloseSize);
	DDV_MinMaxInt(pDX, m_edgeCloseSize, 0, 999999);
	DDV_MinMaxInt(pDX, m_edgeOpenSize, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_IMG_STORED, m_imgStored);
	DDV_MinMaxInt(pDX, m_imgStored, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_HOR_RES, m_HorRes);
	DDV_MinMaxDouble(pDX, m_HorRes, 0.0, 9999.0);
	DDX_Text(pDX, IDC_EDIT_VER_RES, m_VerRes);
	DDV_MinMaxDouble(pDX, m_VerRes, 0.0, 9999.0);
	DDX_Text(pDX, IDC_EDIT_EXTR_PIX, m_extraPix);
	DDX_Check(pDX, IDC_CHECK_RECORD_WIDTH, m_ifRecordWidth);
	//DDX_Check(pDX, IDC_CHECK_ERRDISTANCE, isCheckErrDistance);
	//DDX_Text(pDX, IDC_ErrorDistance, m_errDistance);
	//DDV_MinMaxInt(pDX, m_errDistance, 0, 999999);
	DDX_Text(pDX, IDC_EDIT_EXTRA_WIDTH, m_ExtraWidth);
	DDX_Text(pDX, IDC_PRODUCT_WIDTH, m_ProductWidth);
	DDV_MinMaxFloat(pDX,m_ProductWidth, 0.0, 999999.0);
	DDX_Text(pDX, IDC_EDIT_ROI_Gray, gray_background);
	DDV_MinMaxInt(pDX, gray_background, 0, 255);
	DDX_Text(pDX, IDC_EDIT_ROI_Gray2, m_Gray_Product);
	DDV_MinMaxInt(pDX, m_Gray_Product, 0, 255);
	DDX_Text(pDX, IDC_EDIT_WIDTH_UPBOUND, m_Width_Upbound);
	DDX_Text(pDX, IDC_EDIT_WIDTH_DOWNBOUND, m_Width_Downbound);
	DDX_Check(pDX, IDC_CHECK_IFRECORD_WIDTHERR, m_IfRecordWidthErr);

	DDX_Text(pDX, IDC_EDIT_OPEN_EDGE2, m_Edge_Opening);
	DDV_MinMaxInt(pDX, m_Edge_Opening, 0, 9999);
	DDX_Text(pDX, IDC_EDIT_CLOSE_EDGE2, m_Edge_Closing);
	DDV_MinMaxInt(pDX, m_Edge_Closing, 0, 9999);
	DDX_Text(pDX, IDC_EDIT_EDGE_AREA, m_Edge_Area);
	DDV_MinMaxInt(pDX, m_Edge_Area, 0, 999999);
	DDX_Check(pDX, IDC_CHECK_EDGE, m_If_Check_Edge);
	DDX_Text(pDX, IDC_EDIT_EDGE_WHRATIO, m_Width_Height_Ratio);
	DDX_Text(pDX, IDC_EDIT_EDGE_WIDTH, m_edge_width);
	DDV_MinMaxInt(pDX, m_edge_width, 0, 9999);
	DDX_Text(pDX, IDC_EDIT_EDGE_HEIGHT, m_edge_height);
	DDV_MinMaxInt(pDX, m_edge_height, 0, 9999);
	DDX_Radio(pDX, IDC_RADIO_LEFT, m_CameraPosition);
	DDX_Check(pDX, IDC_CHECK_DELAY_WIDTH, m_ifDelayWidth);
}


BEGIN_MESSAGE_MAP(CSetModel, CDialog)
	//{{AFX_MSG_MAP(CSetModel)
	ON_BN_CLICKED(IDC_BUTTON1, OnDrawRegion)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_Up, &CSetModel::OnEnChangeUp)
	ON_EN_CHANGE(IDC_Left, &CSetModel::OnEnChangeLeft)
	ON_EN_CHANGE(IDC_Down, &CSetModel::OnEnChangeDown)
	ON_EN_CHANGE(IDC_Right, &CSetModel::OnEnChangeRight)


	ON_BN_CLICKED(IDC_BTN_PARA, &CSetModel::OnBnClickedBtnPara)
	//ON_BN_CLICKED(IDC_CHECK_ERRDISTANCE, &CSetModel::OnBnClickedCheckErrdistance)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ROI, &CSetModel::OnBnClickedButtonShowRoi)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ROI2, &CSetModel::OnBnClickedButtonShowRoi2)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &CSetModel::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDOK, &CSetModel::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_TEST_NEW, &CSetModel::OnBnClickedButtonTestNew)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetModel message handlers

BOOL CSetModel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_sWindowName);
	// TODO: Add extra initialization here
	CWnd *pWndShow = GetDlgItem(IDC_IMAGESHOW);
	CRect rcShow;

	pWndShow->GetClientRect(rcShow);
    set_check("~father");
	open_window(rcShow.top,rcShow.left,rcShow.Width(),rcShow.Height(),(long)pWndShow->GetSafeHwnd(),"visible","",&m_lWindowID);
	set_check("father");
    disp_image(m_hImage,m_lWindowID);
    set_draw(m_lWindowID,"margin");
	set_color(m_lWindowID,"green");
	disp_obj(m_hCheckRegion,m_lWindowID);
	//OnBnClickedBtnPara();

	ChangeStatus(m_Lock_Status);
	ChangeLockBtn();
	//add by qq
	if (m_bRollChange)
	{
		m_ChkBtn_RollChange.SetCheck(1);
	}
	else
	{
		m_ChkBtn_RollChange.SetCheck(0);
	}
	//end add
	
	SetM = this;  ///add by qq

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE


	
}

void CSetModel::OnDrawRegion() 
{
	// TODO: Add your control notification handler code here
	double Row1,Col1,Row2,Col2;
	draw_rectangle1(m_lWindowID,&Row1,&Col1,&Row2,&Col2);
	//draw_rectangle1(m_lWindowID,&m_Uploc,&m_Leftloc,&m_Downloc,&m_Rightloc); //add by qq
	//Row1<=0ʱ�������ϱ��ƶ����������ϱ�Ե��Row1>=heightʱ,�ƶ����±߿�
	//Col1<=0ʱ����������ƶ������������Ե��Col1>=widthʱ,�ƶ����ұ߿�
	//Row2������ڵ���Row1���������
	//Col2������ڵ���Col1, �������
	gen_rectangle1(&m_hCheckRegion,Row1,Col1,Row2,Col2); //ADD BY QQ
	m_Uploc = (int)Row1;
	m_Leftloc = (int)Col1;
	m_Downloc = m_bHeight - (int)Row2;
	m_Rightloc = m_bWidth - (int)Col2;
	UpdateData(false);
	disp_obj(m_hImage,m_lWindowID);
	disp_obj(m_hCheckRegion,m_lWindowID);
}

void CSetModel::OnEnChangeUp()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	//�����Ի����Զ��޸���ֵ
	char p[100];
	UpdateData(true); //���ı�������д�����������
	//��ƫ��������С�ڵ��ڣ��߶�-��ƫ������
	if(m_Uploc > m_bHeight - m_Downloc)
	{	
		sprintf_s(p,"���ڴ�ʱ��ƫ����Ϊ%d����ƫ������ֵӦ������%d(ͼ��߶�-��ƫ����), ������0��%d����",m_Downloc,m_bHeight - m_Downloc, m_bHeight - m_Downloc);
		MessageBox(p);
		m_Uploc = m_bHeight - m_Downloc;

	}
	if( m_Uploc > m_bHeight )
	{	
		sprintf_s(p,"��ƫ������ֵ�ѳ���ͼ��߶ȣ�%d, ������0��%d����",m_bHeight, m_bHeight);
		MessageBox(p);
		m_Uploc = m_bHeight;
	}
	UpdateData(false);//����ʱ�����е�ֵ�������ı�����
	gen_rectangle1(&m_hCheckRegion,m_Uploc,m_Leftloc,m_bHeight-m_Downloc,m_bWidth-m_Rightloc); //ADD BY QQ
	disp_obj(m_hImage,m_lWindowID);
	disp_obj(m_hCheckRegion,m_lWindowID);
	

}

void CSetModel::OnEnChangeLeft()
{
	char p[100];
	UpdateData(true);
	if(m_Leftloc > m_bWidth - m_Rightloc)
	{	
		sprintf_s(p,"���ڴ�ʱ��ƫ����Ϊ%d����ƫ������ֵӦ������%d(ͼ��߶�-��ƫ����), ������0��%d����",m_Rightloc,m_bWidth - m_Rightloc, m_bWidth - m_Rightloc);
		MessageBox(p);
		m_Leftloc = m_bWidth - m_Rightloc;

	}
	if( m_Leftloc > m_bWidth )
	{
		sprintf_s(p,"��ƫ������ֵ�ѳ���ͼ���ȣ�%d, ������0��%d����",m_bWidth, m_bWidth);
		MessageBox(p);
		m_Leftloc = m_bWidth;
	}
	UpdateData(false);
	gen_rectangle1(&m_hCheckRegion,m_Uploc,m_Leftloc,m_bHeight-m_Downloc,m_bWidth-m_Rightloc); //ADD BY QQ
	disp_obj(m_hImage,m_lWindowID);
	disp_obj(m_hCheckRegion,m_lWindowID);
}
void CSetModel::OnEnChangeDown()
{
	char p[100];
	UpdateData(true);
	if(m_Downloc > m_bHeight - m_Uploc)
	{	
		sprintf_s(p,"���ڴ�ʱ��ƫ����Ϊ%d����ƫ������ֵӦ������%d(ͼ��߶�-��ƫ����), ������0��%d����",m_Uploc,m_bHeight - m_Uploc, m_bHeight - m_Uploc);
		MessageBox(p);
		m_Downloc = m_bHeight - m_Uploc;

	}
	if( m_Downloc > m_bHeight )
	{
		sprintf_s(p,"��ƫ������ֵ�ѳ���ͼ��߶ȣ�%d, ������0��%d����",m_bHeight, m_bHeight);
		MessageBox(p);
		m_Downloc = m_bHeight;
	}
	UpdateData(false);
	gen_rectangle1(&m_hCheckRegion,m_Uploc,m_Leftloc,m_bHeight-m_Downloc,m_bWidth-m_Rightloc); //ADD BY QQ
	disp_obj(m_hImage,m_lWindowID);
	disp_obj(m_hCheckRegion,m_lWindowID);
}
void CSetModel::OnEnChangeRight()
{
	char p[100];
	UpdateData(true);
	if( m_Rightloc> m_bWidth - m_Leftloc)
	{	
		sprintf_s(p,"���ڴ�ʱ��ƫ����Ϊ%d����ƫ������ֵӦ������%d(ͼ��߶�-��ƫ����), ������0��%d����",m_Leftloc,m_bWidth - m_Leftloc, m_bWidth - m_Leftloc);
		MessageBox(p);
		m_Rightloc = m_bWidth - m_Leftloc;

	}
	if( m_Rightloc > m_bWidth )
	{	
		sprintf_s(p,"��ƫ������ֵ�ѳ���ͼ���ȣ�%d, ������0��%d����",m_bWidth, m_bWidth);
		MessageBox(p);
		m_Rightloc = m_bWidth;
	}
	UpdateData(false);
	gen_rectangle1(&m_hCheckRegion,m_Uploc,m_Leftloc,m_bHeight-m_Downloc,m_bWidth-m_Rightloc); //ADD BY QQ
	disp_obj(m_hImage,m_lWindowID);
	disp_obj(m_hCheckRegion,m_lWindowID);
}
void CSetModel::OnBnClickedBtnPara()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (str.IsEmpty())
	{
		GetDlgItemText(IDC_BTN_PARA,str);
	}
	if(str=="������������<<")
	{
		SetDlgItemText(IDC_BTN_PARA,_T("�߼���������>>"));
	}
	else
	{
		SetDlgItemText(IDC_BTN_PARA,_T("������������<<"));
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if(rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_STATIC_EDGE)->GetWindowRect(&rectSeparator);

		rectSmall.left=rectLarge.left;
		rectSmall.top=rectLarge.top;
		rectSmall.right=rectSeparator.left;
		rectSmall.bottom=rectLarge.bottom;
	}
	if(str=="������������<<")
	{
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
	str.Empty();
}

//void CSetModel::OnBnClickedCheckErrdistance()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	//SetStatus(isCheckErrDistance,IDC_ErrorDistance);
//}

void CSetModel::OnBnClickedButtonShowRoi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Hobject hThresholdRegion,hFillUpRegion, hReduceImg;
	HTuple CheckRegionArea, hRow1, hCol1;
	reduce_domain(m_hImage,m_hCheckRegion,&hReduceImg);					//��С������
	threshold(hReduceImg,&hThresholdRegion,0,gray_background);						//����ȫ�ַ�ֵ�ָ�ͼ��0:��С�Ҷ�ֵ��40�����Ҷ�ֵ
	closing_rectangle1(hThresholdRegion,&hThresholdRegion,5,100);
	opening_rectangle1(hThresholdRegion,&hThresholdRegion,1,100);
	connection(hThresholdRegion,&hThresholdRegion);
	shape_trans(hThresholdRegion,&hFillUpRegion,"rectangle1");
	area_center(m_hCheckRegion,&CheckRegionArea,&hRow1,&hCol1);			//���㱻�����������������
	select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1);	//���ܣ�ѡ����������������ڵ���������
	disp_obj(m_hImage,m_lWindowID);
	set_color(m_lWindowID,"green");
	disp_obj(hThresholdRegion,m_lWindowID);

	Hobject hImageMean1, hImageMean2;
	reduce_domain(m_hImage,hThresholdRegion,&hReduceImg);					//���ܣ���Сһ��ͼ�������
	mean_image(hReduceImg,&hImageMean1,3,5);
	mean_image(hReduceImg,&hImageMean2,3,100);
	dyn_threshold(hImageMean1,hImageMean2,&hThresholdRegion,m_Gray,"light");

	//threshold(hReduceImg,&hThresholdRegion,m_Gray,255);						//���ܣ�����ȫ����ֵ�ָ�ͼ��
	//closing_rectangle1(hThresholdRegion,&hThresholdRegion,20,20);
	connection(hThresholdRegion,&hThresholdRegion);							//���ܣ�����һ�����������ӵĲ���		
	select_shape(hThresholdRegion,&hThresholdRegion,"area","and",m_Area,70000);//  ���ܣ�����ͼ������ѡ������
	set_color(m_lWindowID,"red");
	disp_obj(hThresholdRegion,m_lWindowID);
}

void CSetModel::OnBnClickedButtonShowRoi2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Hobject hThresholdRegion,hFillUpRegion, hReduceImg;
	HTuple CheckRegionArea, hRow1, hCol1;
	reduce_domain(m_hImage,m_hCheckRegion,&hReduceImg);					//��С������
	threshold(hReduceImg,&hThresholdRegion,0,m_Gray_Product);						//����ȫ�ַ�ֵ�ָ�ͼ��0:��С�Ҷ�ֵ��40�����Ҷ�ֵ
	closing_rectangle1(hThresholdRegion,&hThresholdRegion,5,100);
	opening_rectangle1(hThresholdRegion,&hThresholdRegion,1,100);
	connection(hThresholdRegion,&hThresholdRegion);
	shape_trans(hThresholdRegion,&hFillUpRegion,"rectangle1");
	area_center(m_hCheckRegion,&CheckRegionArea,&hRow1,&hCol1);			//���㱻�����������������
	select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1);	//���ܣ�ѡ����������������ڵ���������
	disp_obj(m_hImage,m_lWindowID);
	set_color(m_lWindowID,"green");
	disp_obj(hThresholdRegion,m_lWindowID);

	Hobject hImageMean1, hImageMean2;
	reduce_domain(m_hImage,hThresholdRegion,&hReduceImg);					//���ܣ���Сһ��ͼ�������
	mean_image(hReduceImg,&hImageMean1,3,5);
	mean_image(hReduceImg,&hImageMean2,3,100);
	dyn_threshold(hImageMean1,hImageMean2,&hThresholdRegion,m_Gray,"light");

	//threshold(hReduceImg,&hThresholdRegion,m_Gray,255);						//���ܣ�����ȫ����ֵ�ָ�ͼ��
	//closing_rectangle1(hThresholdRegion,&hThresholdRegion,20,20);
	connection(hThresholdRegion,&hThresholdRegion);							//���ܣ�����һ�����������ӵĲ���		
	select_shape(hThresholdRegion,&hThresholdRegion,"area","and",m_Area,70000);//  ���ܣ�����ͼ������ѡ������
	set_color(m_lWindowID,"red");
	disp_obj(hThresholdRegion,m_lWindowID);
}


void CSetModel::OnBnClickedButtonLock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	CString str_Btn;
	GetDlgItemText(IDC_BUTTON_LOCK,str_Btn);
	GetDlgItemText(IDC_EDIT_UNLOCK,str);
	if(str_Btn == "����")
	{
		if (str == m_Lock_PassWord)
		{
			Reverse_Lock_Status();
			ChangeStatus(m_Lock_Status);	
			SetDlgItemText(IDC_BUTTON_LOCK,_T("����"));
		}
		else
		{
			AfxMessageBox("�������");
		}
	}
	else if(str_Btn == "����")
	{
		Reverse_Lock_Status();
		ChangeStatus(m_Lock_Status);
		SetDlgItemText(IDC_BUTTON_LOCK,_T("����"));
	}
}

void CSetModel::ChangeLockBtn()
{
	if(m_Lock_Status)
		SetDlgItemText(IDC_BUTTON_LOCK,_T("����"));
	else
		SetDlgItemText(IDC_BUTTON_LOCK,_T("����"));
}

void CSetModel::ChangeStatus(BOOL flag)
{
	SetStatus(flag,IDC_EDIT1);
	SetStatus(flag,IDC_EDIT2);
	SetStatus(flag,IDC_ErrorNum);
	SetStatus(flag,IDC_BUTTON_SHOW_ROI);
	SetStatus(flag,IDC_EDIT_ROI_Gray);
	SetStatus(flag,IDC_BUTTON_SHOW_ROI2);
	SetStatus(flag,IDC_EDIT_ROI_Gray2);
	SetStatus(flag,IDC_Up);
	SetStatus(flag,IDC_Left);
	SetStatus(flag,IDC_Down);
	SetStatus(flag,IDC_Right);

	SetStatus(flag,IDC_EDIT_OPEN_EDGE);
	SetStatus(flag,IDC_EDIT_CLOSE_EDGE);
	SetStatus(flag,IDC_EDIT_IMG_STORED);
	SetStatus(flag,IDC_EDIT_EXTRA_WIDTH);
	SetStatus(flag,IDC_CHECK_RECORD_WIDTH);
	//SetStatus(flag,IDC_CHECK_ERRDISTANCE);
	//SetStatus(flag,IDC_ErrorDistance);

	SetStatus(flag,IDC_EDIT_HOR_RES);
	SetStatus(flag,IDC_EDIT_VER_RES);

	SetStatus(flag,IDC_CHECK_EDGE);
	SetStatus(flag,IDC_EDIT_OPEN_EDGE2);
	SetStatus(flag,IDC_EDIT_CLOSE_EDGE2);
	SetStatus(flag,IDC_EDIT_EDGE_AREA);
	SetStatus(flag,IDC_EDIT_EDGE_WIDTH);
	SetStatus(flag,IDC_EDIT_EDGE_HEIGHT);
	SetStatus(flag,IDC_EDIT_EDGE_WHRATIO);
}

void CSetModel::Reverse_Lock_Status()
{
	if(1==m_Lock_Status)
		m_Lock_Status=FALSE;
	else if(0==m_Lock_Status)
		m_Lock_Status=TRUE;
}




void CSetModel::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CSetModel::OnBnClickedButtonTestNew()
{
	AfxMessageBox("abc");
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgParaSetting m_Dlg;
	m_Dlg.DoModal();
}
