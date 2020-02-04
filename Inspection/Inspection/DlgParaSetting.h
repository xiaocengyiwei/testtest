#pragma once
#include "resource.h"
#include "DlgImage.h"
#include "TabControler.h"
#include "DlgPinhole.h"
#include "DlgWidth.h"
#include "DlgSurface.h"
#include "DlgScore.h"
#include "ParameterPool.h"


#include "halconcpp.h"
#include "afxcmn.h"
using namespace Halcon;
// CDlgParaSetting 对话框


class CDlgParaSetting : public CDialog
{
	DECLARE_DYNAMIC(CDlgParaSetting)

public:
	CDlgParaSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParaSetting();

// 对话框数据
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	int m_TotalCamNum;  //相机总数

public:
	void SetCamNum(int Num);

public:
	CStatusBar m_StatusBar;   //状态栏
	Hlong m_HandleShowImage;  //图像显示句柄

public:
	Hobject m_hBackGroundImg[CAM_NUM];
	int m_CurrSelectedCam;  //当前选中的相机号 
	CStatic m_Static_CamPara;
	int m_CamPos;  //相机位置
	CSliderCtrl m_SliderImgLeft;  //滑动条，左侧边界
	CSliderCtrl m_SliderImgRight; //右侧
	CString m_ImgLeft;   //左边界
	CString m_ImgRight;  //右边界

	int m_SetMothod;
	
public:  //用于页签显示
	CTabControler m_TabControler;

	CRect m_Rect_Image;
	CTabCtrl m_Tab_Image;
	CDlgImage m_Dlg_Image;

	CRect m_Rect_Parameters;
	CTabCtrl m_Tab_Parameters;   //页签控件
	CDlgPinhole m_Dlg_Pinhole;   //针孔页签
	CDlgWidth m_Dlg_Width;       //宽度页签
	CDlgSurface m_Dlg_Surface;   //表面页签
	CDlgScore m_Dlg_Score;       //表面缺陷评分页签


public:
	void InitStatusBar();

	void InitTabImage();
	void InitTabParameters();

	void OnSlideImgLeft();
	void OnSlideImgRight();
	void ChangeL_CheckR(int LeftOffset, int LeftMin, int LeftMax);  //左边界变动，设置相关控件的值，同时检查右边界
	void ChangeR_CheckL(int RightOffset, int RightMin, int RightMax);

public:
	void ReduceTabRect(CRect* rect, int left, int right, int top, int bottom);
	void DispOneObject(Hobject hObj, const char *Colour);
	void RefreshImage();
	void DrawRectangle();
	void TestThresh();  //Thresh for light defect, result stored in DrawRectangle

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTabImage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabParameters(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioCamPos();

	afx_msg void OnBnClickedRadioSetPara();
		
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditImgLeft();
	afx_msg void OnBnClickedBtnLeftL();
	afx_msg void OnBnClickedBtnLeftR();
	afx_msg void OnEnChangeEditImgRight();
	afx_msg void OnBnClickedBtnRightL();
	afx_msg void OnBnClickedBtnRightR();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
