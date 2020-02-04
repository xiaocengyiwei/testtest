// Check.h: interface for the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECK_H__47032A48_1EA6_4275_93C5_3BA551ABF5E5__INCLUDED_)
#define AFX_CHECK_H__47032A48_1EA6_4275_93C5_3BA551ABF5E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <string>
#include "DataType.h"

#include "halconcpp.h"

using namespace std;
using namespace Halcon;

#define  CAMERA_NUM  6
#define  MAX_STORED_NUM 2000
static int img_stored_width[CAMERA_NUM][MAX_STORED_NUM];
static int calculated_width_stored[MAX_STORED_NUM];
static float img_stored_f_width[CAMERA_NUM][MAX_STORED_NUM];
static float calculated_f_width_stored[MAX_STORED_NUM];
static float last_f_width;	//��һ�ο��
static int TotalCameraNum;  //��ʼ�����������

class CCheck  
{
public:
	CCheck();
	virtual ~CCheck();

	void SetImageData(const char *imagedata);
	void readmodel();
	void writemodel();
	void writeWidth();
	void writeTime();
	int  getMaxIndex();

	BOOL m_ifDelayWidth;  //�Ƿ����ÿ�ȼ�����
	bool widthExists();  //�ж��Ƿ����ٴ���һ����ȷ�Ŀ������
	int  currWidth;

private:
	
	bool GetCurrentAppPath(char **path);
	bool GetMacByCmd(char *lpszMac);

public:
	bool Init(int nIndex,int width,int height);
	int  Check(const char *imagedata, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount);
	//bool Setting_model(char *imagedata);
	int  classify(const Halcon::Hobject &RegionForClassify);
	bool Free();
	void showImage(Hobject &hImgInput);

private:
	int			m_lComeraIndex;
	int			m_lWidth;
	int			m_lHeight;
	CString		g_Path;
	char		sCurrentPath[MAX_PATH];// ���Ӧ�ó���·��
	CString		m_strModelDir;
	bool		m_bIsCheckRegion;      //�Ƿ�����˼������

	int			m_ErosionSize;         //�����߶�

public:
	clock_t timeBegin, timeEnd, timeConsume; // ���ʱ��
	Hobject hReduceImg;
	Hobject m_himage;
	Hobject m_hCheckRegion;
	Hobject hTagRegion;
	Hobject hEdgeRegion;

	Hobject hReturnRegion;

	int     gray_background;  //
	int		m_Gray_Product;   //��ʵ�߽�
	
	int     m_Gray;
	int     m_area;	
	int		m_ErrorNum;            //��״ȱ�ݸ���

	int		m_uploc;    //add by qq
	int     m_leftloc;	//add by qq
	int		m_downloc;	//add by qq
	int		m_rightloc;	//add by qq

	int     m_bheight;
	int     m_bwidth;
		
	int		m_CameraPosition;  //���λ��  0=��� 1=�м� 2=�ұ�

	BOOL    m_bChangeLap; //add by qq
	long    m_berrorarea; //add by qq

	int		m_imgCount;
public:
	int		m_edgeOpenSize;
	int		m_edgeCloseSize;
	int		m_imgStored;
	BOOL	m_ifRecordWidth;

	//BOOL    m_isCheckErrDistance;
	//int     m_ErrorDistance;
	//int     m_errLocCount;

	int		m_extraPix;
	float   m_ExtraWidth;
	float   m_HorRes;
	float   m_VerRes;

	int     m_fake_width;

	char    err_name[100][64];

	float   m_ProductWidth;
	float	m_Width_Upbound;
	float	m_Width_Downbound;
	BOOL	m_IfRecordWidthErr;
	BOOL	m_IfWidth_Overbound;

	int m_Edge_Opening;
	int m_Edge_Closing;
	int m_Edge_Area;
	BOOL m_If_Check_Edge;

	double width_height_ratio;
	int m_edge_width;
	int m_edge_height;

	CString m_Lock_PassWord;  //����
	BOOL m_Lock_Status;   //1����״̬��0����״̬

	BOOL m_DebugMode;    //����ģʽ

	vector<ErrorRegion> g_ErrorRegion;  //��Ŵ��������
};

#endif // !defined(AFX_CHECK_H__47032A48_1EA6_4275_93C5_3BA551ABF5E5__INCLUDED_)
