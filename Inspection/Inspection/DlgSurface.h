#pragma once

#include "HalconCpp.h"
using namespace Halcon;
// CDlgSurface 对话框

class CDlgSurface : public CDialog
{
	DECLARE_DYNAMIC(CDlgSurface)

public:
	CDlgSurface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSurface();

// 对话框数据
	enum { IDD = IDD_DLG_SURFACE };

protected:
	virtual BOOL OnInitDialog(); 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void InitComboBox();

public:
	CComboBox m_Combo_DynMode_1;
	CComboBox m_Combo_DynMode_2;
	CComboBox m_Combo_DynMode_3;
	CComboBox m_Combo_DynMode_4;

public:
	//画框测量
// 	int m_DrawRectWidth;
// 	int m_DrawRectHeight;
// 	int m_DrawRectArea;
// 	float m_DrawRectFArea;
// 	int m_DrawRectAvgGray;
// 	int m_DrawRectMaxGray;
// 	int m_DrawRectMinGray;

	Hobject m_hDrawRectangle;
	HTuple m_hRectR1, m_hRectR2, m_hRectC1, m_hRectC2;
	Hobject m_hTestThreshRegion;
	HTuple m_hRectArea;
	HTuple m_hRectAvgGray, m_hRectMaxGray, m_hRectMinGray;

	CSliderCtrl m_SliderTestThresh1;
	CSliderCtrl m_SliderTestThresh2;
	int m_TestThreshGray1;   //滑动条的灰度
	int m_TestThreshGray2;  

public:
	float m_RealMinArea;

public:
	void InitSliderTestThresh();
	void CalcTestRegion(Hobject hInputRegion);   //Calculate attributes of DrawRect
	void OnSliderTestGray1();   //slider test thresh
	void OnSliderTestGray2();
	void CalcRealMinArea();

public:
	afx_msg void OnCbnSelchangeComboSurfDynMode1();
	afx_msg void OnCbnSelchangeComboSurfDynMode2();
	afx_msg void OnCbnSelchangeComboSurfDynMode3();
	afx_msg void OnCbnSelchangeComboSurfDynMode4();
	afx_msg void OnBnClickedButtonDrawRect();
	afx_msg void OnBnClickedButtonTestThresh();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditSurfAreaMin();
};
