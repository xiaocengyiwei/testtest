// DlgScore.cpp : 实现文件
//

#include "stdafx.h"
#include "Inspection.h"
#include "DlgScore.h"
#include "ParameterPool.h"
#include "DlgParaSetting.h"
#include <math.h>

extern CParameterPool g_PP;
extern CDlgParaSetting* g_DlgSetting;
// CDlgScore 对话框

IMPLEMENT_DYNAMIC(CDlgScore, CDialog)

CDlgScore::CDlgScore(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScore::IDD, pParent)
{

}

CDlgScore::~CDlgScore()
{
}

void CDlgScore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_THRESH_DEEP,g_PP.m_Surf_Thresh_Deep);   //深缺陷
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_S,g_PP.m_Surf_DeepSizePixS);   //像素
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_M,g_PP.m_Surf_DeepSizePixM);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_L,g_PP.m_Surf_DeepSizePixL);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_S,g_PP.m_Surf_DeepSizeAreaS);   //面积
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_M,g_PP.m_Surf_DeepSizeAreaM);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_L,g_PP.m_Surf_DeepSizeAreaL);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_S,g_PP.m_Surf_DeepSizeDiamS);   //直径
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_M,g_PP.m_Surf_DeepSizeDiamM);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_L,g_PP.m_Surf_DeepSizeDiamL);
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_S,g_PP.m_Surf_DeepScoreS);     //评分
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_M,g_PP.m_Surf_DeepScoreM);
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_L,g_PP.m_Surf_DeepScoreL);

	DDX_Text(pDX,IDC_EDIT_THRESH_SHALLOW,g_PP.m_Surf_Thresh_Shallow);    //浅缺陷
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_S,g_PP.m_Surf_ShallowSizePixS);   //像素
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_M,g_PP.m_Surf_ShallowSizePixM);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_L,g_PP.m_Surf_ShallowSizePixL);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_S,g_PP.m_Surf_ShallowSizeAreaS);   //面积
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_M,g_PP.m_Surf_ShallowSizeAreaM);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_L,g_PP.m_Surf_ShallowSizeAreaL);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_S,g_PP.m_Surf_ShallowSizeDiamS);   //直径
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_M,g_PP.m_Surf_ShallowSizeDiamM);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_L,g_PP.m_Surf_ShallowSizeDiamL);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_S,g_PP.m_Surf_ShallowScoreS);     //评分
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_M,g_PP.m_Surf_ShallowScoreM);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_L,g_PP.m_Surf_ShallowScoreL);

	DDX_Text(pDX,IDC_EDIT_THRESH_DEEP2,g_PP.m_Surf_Thresh_Deep2);   //深缺陷  2
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_S2,g_PP.m_Surf_DeepSizePixS2);   //像素
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_M2,g_PP.m_Surf_DeepSizePixM2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_PIX_L2,g_PP.m_Surf_DeepSizePixL2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_S2,g_PP.m_Surf_DeepSizeAreaS2);   //面积
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_M2,g_PP.m_Surf_DeepSizeAreaM2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_AREA_L2,g_PP.m_Surf_DeepSizeAreaL2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_S2,g_PP.m_Surf_DeepSizeDiamS2);   //直径
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_M2,g_PP.m_Surf_DeepSizeDiamM2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SIZE_DIAM_L2,g_PP.m_Surf_DeepSizeDiamL2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_S2,g_PP.m_Surf_DeepScoreS2);     //评分
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_M2,g_PP.m_Surf_DeepScoreM2);
	DDX_Text(pDX,IDC_EDIT_DEEP_SCORE_L2,g_PP.m_Surf_DeepScoreL2);

	DDX_Text(pDX,IDC_EDIT_THRESH_SHALLOW2,g_PP.m_Surf_Thresh_Shallow2);    //浅缺陷  2
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_S2,g_PP.m_Surf_ShallowSizePixS2);   //像素
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_M2,g_PP.m_Surf_ShallowSizePixM2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_PIX_L2,g_PP.m_Surf_ShallowSizePixL2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_S2,g_PP.m_Surf_ShallowSizeAreaS2);   //面积
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_M2,g_PP.m_Surf_ShallowSizeAreaM2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_AREA_L2,g_PP.m_Surf_ShallowSizeAreaL2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_S2,g_PP.m_Surf_ShallowSizeDiamS2);   //直径
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_M2,g_PP.m_Surf_ShallowSizeDiamM2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SIZE_DIAM_L2,g_PP.m_Surf_ShallowSizeDiamL2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_S2,g_PP.m_Surf_ShallowScoreS2);     //评分
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_M2,g_PP.m_Surf_ShallowScoreM2);
	DDX_Text(pDX,IDC_EDIT_SHALLOW_SCORE_L2,g_PP.m_Surf_ShallowScoreL2);

	DDX_Text(pDX,IDC_EDIT_VERT_LINE_SCORE,g_PP.m_Surf_VertLineScore);
	DDX_Text(pDX,IDC_EDIT_HOR_LINE_SCORE,g_PP.m_Surf_HorLineScore);

	DDX_Text(pDX,IDC_EDIT_TOTAL_SCORE,g_PP.m_Surf_TotalScore);   //总分

	//缺陷密度
// 	DDX_Text(pDX,IDC_EDIT_DENSITY_WIDTH,g_PP.m_Surf_DensitySizeWidth);
// 	DDX_Text(pDX,IDC_EDIT_DENSITY_WIDTH_MM,g_PP.m_Surf_DensitySizeWidthMM);
// 	DDX_Text(pDX,IDC_EDIT_DENSITY_HEIGHT,g_PP.m_Surf_DensitySizeHeight);
// 	DDX_Text(pDX,IDC_EDIT_DENSITY_HEIGHT_MM,g_PP.m_Surf_DensitySizeHeightMM);
// 	DDX_Text(pDX,IDC_EDIT_DENSITY_COUNT,g_PP.m_Surf_DensityCount);

	//是否打标
	//DDX_Check(pDX,IDC_CHECK_DENSITY_TAG,g_PP.m_Surf_IfDensityTag);
	DDX_Check(pDX,IDC_CHECK_DEEP_S_TAG,g_PP.m_Surf_IfDeepSTag);
	DDX_Check(pDX,IDC_CHECK_DEEP_M_TAG,g_PP.m_Surf_IfDeepMTag);
	DDX_Check(pDX,IDC_CHECK_DEEP_L_TAG,g_PP.m_Surf_IfDeepLTag);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_S_TAG,g_PP.m_Surf_IfShallowSTag);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_M_TAG,g_PP.m_Surf_IfShallowMTag);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_L_TAG,g_PP.m_Surf_IfShallowLTag);

	DDX_Check(pDX,IDC_CHECK_DEEP_S_TAG2,g_PP.m_Surf_IfDeepSTag2);
	DDX_Check(pDX,IDC_CHECK_DEEP_M_TAG2,g_PP.m_Surf_IfDeepMTag2);
	DDX_Check(pDX,IDC_CHECK_DEEP_L_TAG2,g_PP.m_Surf_IfDeepLTag2);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_S_TAG2,g_PP.m_Surf_IfShallowSTag2);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_M_TAG2,g_PP.m_Surf_IfShallowMTag2);
	DDX_Check(pDX,IDC_CHECK_SHALLOW_L_TAG2,g_PP.m_Surf_IfShallowLTag2);

	DDX_Check(pDX,IDC_CHECK_VERT_LINE_TAG,g_PP.m_Surf_IfVertLineTag);
	DDX_Check(pDX,IDC_CHECK_HOR_LINE_TAG,g_PP.m_Surf_IfHorLineTag);

	//打标报警时长
	DDX_Text(pDX,IDC_EDIT_ALARMLENGTH,g_PP.m_Surf_AlarmLength);
	DDX_Text(pDX,IDC_EDIT_TAGLENGTH,g_PP.m_Surf_TagLength);

	//校准
	DDX_Text(pDX,IDC_EDIT_CALIB,g_PP.m_Surf_Calib);
	DDX_Text(pDX,IDC_EDIT_CALIB2,g_PP.m_Surf_Calib2);

	//是否保存缺陷
	DDX_Text(pDX,IDC_HANDVRATION,g_PP.m_fHorAndVorRatio);
	DDX_Text(pDX,IDC_MinWidthLineGray,g_PP.m_iMinWidthGray);
	DDX_Text(pDX,IDC_WidthLineMaxGray,g_PP.m_iMaxWidthGray);
	DDX_Check(pDX,IDC_IfRecordWidthLine,g_PP.m_iRecordWidthLine);
}


BEGIN_MESSAGE_MAP(CDlgScore, CDialog)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_S, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_M, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_L, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_S, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_M, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_L, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_S2, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_M2, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_DEEP_SIZE_PIX_L2, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_S2, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_M2, &CDlgScore::OnEnChangeEditDeepSizePix)
	ON_EN_CHANGE(IDC_EDIT_SHALLOW_SIZE_PIX_L2, &CDlgScore::OnEnChangeEditDeepSizePix)
// 	ON_EN_CHANGE(IDC_EDIT_DENSITY_WIDTH, &CDlgScore::OnEnChangeEditDeepSizePix)
// 	ON_EN_CHANGE(IDC_EDIT_DENSITY_HEIGHT, &CDlgScore::OnEnChangeEditDeepSizePix)
END_MESSAGE_MAP()

BOOL CDlgScore::OnInitDialog()
{
	CDialog::OnInitDialog();
	RefreshSize();
	UpdateData(false);
	GetDlgItem(IDC_EDIT_SHALLOW_SIZE_PIX_S2)->SetFocus();
	return FALSE;
}

void CDlgScore::RefreshSize()
{
	Pix2Area(g_PP.m_Surf_DeepSizePixS, g_PP.m_Surf_DeepSizeAreaS, g_PP.m_Surf_DeepSizeDiamS);
	Pix2Area(g_PP.m_Surf_DeepSizePixM, g_PP.m_Surf_DeepSizeAreaM, g_PP.m_Surf_DeepSizeDiamM);
	Pix2Area(g_PP.m_Surf_DeepSizePixL, g_PP.m_Surf_DeepSizeAreaL, g_PP.m_Surf_DeepSizeDiamL);
	Pix2Area(g_PP.m_Surf_ShallowSizePixS, g_PP.m_Surf_ShallowSizeAreaS, g_PP.m_Surf_ShallowSizeDiamS);
	Pix2Area(g_PP.m_Surf_ShallowSizePixM, g_PP.m_Surf_ShallowSizeAreaM, g_PP.m_Surf_ShallowSizeDiamM);
	Pix2Area(g_PP.m_Surf_ShallowSizePixL, g_PP.m_Surf_ShallowSizeAreaL, g_PP.m_Surf_ShallowSizeDiamL);

	Pix2Area(g_PP.m_Surf_DeepSizePixS2, g_PP.m_Surf_DeepSizeAreaS2, g_PP.m_Surf_DeepSizeDiamS2);
	Pix2Area(g_PP.m_Surf_DeepSizePixM2, g_PP.m_Surf_DeepSizeAreaM2, g_PP.m_Surf_DeepSizeDiamM2);
	Pix2Area(g_PP.m_Surf_DeepSizePixL2, g_PP.m_Surf_DeepSizeAreaL2, g_PP.m_Surf_DeepSizeDiamL2);
	Pix2Area(g_PP.m_Surf_ShallowSizePixS2, g_PP.m_Surf_ShallowSizeAreaS2, g_PP.m_Surf_ShallowSizeDiamS2);
	Pix2Area(g_PP.m_Surf_ShallowSizePixM2, g_PP.m_Surf_ShallowSizeAreaM2, g_PP.m_Surf_ShallowSizeDiamM2);
	Pix2Area(g_PP.m_Surf_ShallowSizePixL2, g_PP.m_Surf_ShallowSizeAreaL2, g_PP.m_Surf_ShallowSizeDiamL2);
// 
// 	Pix2MM(g_PP.m_Surf_DensitySizeWidth, g_PP.m_Resolution_W[0], g_PP.m_Surf_DensitySizeWidthMM);
// 	Pix2MM(g_PP.m_Surf_DensitySizeHeight, g_PP.m_Resolution_H, g_PP.m_Surf_DensitySizeHeightMM);
}

void CDlgScore::Pix2Area( int pix, float &area, float &diam )
{
	if (pix <= 0)
	{
		area = 0;
		diam = 0;
	}
	else
	{
		area = pix*g_PP.m_Resolution_H*g_PP.m_Resolution_W[g_DlgSetting->m_CurrSelectedCam];
		if (area <= 0)
		{
			area = 0;
			diam = 0;
		}
		else
		{
			diam = (sqrt(area/3.14159))*2;
			diam = diam*g_PP.m_Surf_Calib;
			area = area*g_PP.m_Surf_Calib2;
		}
	}
}
void CDlgScore::Pix2MM(int pix, float resolution, float &mm)
{
	mm = (float)pix*resolution;
}

// CDlgScore 消息处理程序

void CDlgScore::OnEnChangeEditDeepSizePix()
{
	UpdateData(true);
	RefreshSize();
	UpdateData(false);
}
