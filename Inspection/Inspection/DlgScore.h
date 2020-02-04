#pragma once


// CDlgScore 对话框

class CDlgScore : public CDialog
{
	DECLARE_DYNAMIC(CDlgScore)

public:
	CDlgScore(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgScore();

// 对话框数据
	enum { IDD = IDD_DLG_SCORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void Pix2Area(int pix, float &area, float &diam);   //像素转面积和直径
	void Pix2MM(int pix, float resolution, float &mm);  //像素转实际
	void RefreshSize();   //根据像素尺寸计算实际面积，估算直径
	
public:
	afx_msg void OnEnChangeEditDeepSizePix();
};
