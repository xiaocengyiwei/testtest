#pragma once


// CDlgScore �Ի���

class CDlgScore : public CDialog
{
	DECLARE_DYNAMIC(CDlgScore)

public:
	CDlgScore(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgScore();

// �Ի�������
	enum { IDD = IDD_DLG_SCORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void Pix2Area(int pix, float &area, float &diam);   //����ת�����ֱ��
	void Pix2MM(int pix, float resolution, float &mm);  //����תʵ��
	void RefreshSize();   //�������سߴ����ʵ�����������ֱ��
	
public:
	afx_msg void OnEnChangeEditDeepSizePix();
};
