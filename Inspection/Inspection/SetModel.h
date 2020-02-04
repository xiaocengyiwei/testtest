#if !defined(AFX_SETMODEL_H__3D006B97_35F3_4D80_AA6C_85A62F84BEE4__INCLUDED_)
#define AFX_SETMODEL_H__3D006B97_35F3_4D80_AA6C_85A62F84BEE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetModel.h : header file
//
#include "DlgParaSetting.h"

#include "halconcpp.h"
#include "resource.h"
using namespace Halcon;
/////////////////////////////////////////////////////////////////////////////
// CSetModel dialog

class CSetModel : public CDialog
{
// Construction
public:
	CSetModel(CWnd* pParent = NULL);   // standard constructor
	
	//BOOL m_bRollChange;	//add by qq

// Dialog Data
	//{{AFX_DATA(CSetModel)
	enum { IDD = IDD_DIALOG2 };
	int		m_Gray;     //对比度
	int		m_Area;     //面积
	int		m_Uploc;	//上定位 add by qq
	int		m_Leftloc;	//左定位 add by qq	
	int		m_Downloc;  //下定位 add by qq
	int		m_Rightloc; //右定位 add by qq
	
	int		m_bHeight; //图像高度
	int		m_bWidth;  //图像宽度

	int		m_bErrorNum;            //最状缺陷个数
	
	CButton	m_ChkBtn_RollChange;//add by qq
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetModel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	Hobject m_hImage;
	Hobject m_hCheckRegion;
	CString m_sWindowName;

	CString str;
protected:
	
	long      m_lWindowID;

	// Generated message map functions
	//{{AFX_MSG(CSetModel)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawRegion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL	m_bRollChange;  //add by qq
	long 	m_bErrorArea;	//add by qq				
	int m_edgeOpenSize;
	int m_edgeCloseSize;
	int m_imgStored;
	float m_HorRes;
	float m_VerRes;
	int m_extraPix;
	BOOL m_ifRecordWidth;
	//BOOL isCheckErrDistance;
	//int m_errDistance;
	float m_ExtraWidth;
	int gray_background;
	int m_Gray_Product;
	float m_ProductWidth;
	float m_Width_Upbound;
	float m_Width_Downbound;
	BOOL m_IfRecordWidthErr;

	int m_Edge_Opening;
	int m_Edge_Closing;
	int m_Edge_Area;
	BOOL m_If_Check_Edge;

	double m_Width_Height_Ratio;
	int m_edge_width;
	int m_edge_height;

	CString m_Lock_PassWord;  //锁定
	BOOL m_Lock_Status;   //1锁定状态，0解锁状态

public:
	void ChangeStatus(BOOL flag);   //根据m_Lock_Status改变控件的enable
	void Reverse_Lock_Status();
	void ChangeLockBtn();
public:
	afx_msg void OnEnChangeUp();
	afx_msg void OnEnChangeLeft();
	afx_msg void OnEnChangeDown();
	afx_msg void OnEnChangeRight();
	afx_msg void OnBnClickedBtnPara();
	//afx_msg void OnBnClickedCheckErrdistance();
	afx_msg void OnBnClickedButtonShowRoi();
	afx_msg void OnBnClickedButtonShowRoi2();

	afx_msg void OnBnClickedButtonLock();
	int m_CameraPosition;
	BOOL m_ifDelayWidth;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonTestNew();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETMODEL_H__3D006B97_35F3_4D80_AA6C_85A62F84BEE4__INCLUDED_)
