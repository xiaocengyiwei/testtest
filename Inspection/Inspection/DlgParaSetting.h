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
// CDlgParaSetting �Ի���


class CDlgParaSetting : public CDialog
{
	DECLARE_DYNAMIC(CDlgParaSetting)

public:
	CDlgParaSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParaSetting();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	int m_TotalCamNum;  //�������

public:
	void SetCamNum(int Num);

public:
	CStatusBar m_StatusBar;   //״̬��
	Hlong m_HandleShowImage;  //ͼ����ʾ���

public:
	Hobject m_hBackGroundImg[CAM_NUM];
	int m_CurrSelectedCam;  //��ǰѡ�е������ 
	CStatic m_Static_CamPara;
	int m_CamPos;  //���λ��
	CSliderCtrl m_SliderImgLeft;  //�����������߽�
	CSliderCtrl m_SliderImgRight; //�Ҳ�
	CString m_ImgLeft;   //��߽�
	CString m_ImgRight;  //�ұ߽�

	int m_SetMothod;
	
public:  //����ҳǩ��ʾ
	CTabControler m_TabControler;

	CRect m_Rect_Image;
	CTabCtrl m_Tab_Image;
	CDlgImage m_Dlg_Image;

	CRect m_Rect_Parameters;
	CTabCtrl m_Tab_Parameters;   //ҳǩ�ؼ�
	CDlgPinhole m_Dlg_Pinhole;   //���ҳǩ
	CDlgWidth m_Dlg_Width;       //���ҳǩ
	CDlgSurface m_Dlg_Surface;   //����ҳǩ
	CDlgScore m_Dlg_Score;       //����ȱ������ҳǩ


public:
	void InitStatusBar();

	void InitTabImage();
	void InitTabParameters();

	void OnSlideImgLeft();
	void OnSlideImgRight();
	void ChangeL_CheckR(int LeftOffset, int LeftMin, int LeftMax);  //��߽�䶯��������ؿؼ���ֵ��ͬʱ����ұ߽�
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
