#pragma once

#include <vector>
#include "datatype.h"
#include "halconcpp.h"
#include "ParameterPool.h"
#include "Result.h"
#include "HTempDispRegion.h"
using namespace std;
using namespace Halcon;



class CSurfaceCheck
{
public:
	CSurfaceCheck(void);
	~CSurfaceCheck(void);

private:
	int m_CamIndex;
public:
	typedef struct{
		ErrorRegion retResults;  //���ص�����

		int properDynThresh;   
		Hlong regionWidthPix, regionHeightPix;  //ȱ�ݱ���Ŀ��
		Hlong errAreaPix;   //�������
		Hlong sImgLeft, sImgRight, sImgTop, sImgBotton;  //���ɵ�Сͼ���� 
		bool ifInterWithEdge;   //�Ƿ����Ե�����н���
		bool ifNearEdge; //�Ƿ񿿽���Ե
		Hlong errHeight, errWidth;  //�ָ�Ĵ���Ե������
		Hlong sImageHeight, sImageWidth;   //Сͼ������

		bool ifCrowded;  //�Ƿ��ܶȹ���
	}Features;   //����

	char m_DefectName[100][64];  //����ȱ�ݱ��

public:
	vector<ErrorRegion> m_TheBlackList;   //ȱ���б�
	vector<Features> m_Features;   //���ڷ������������
	int m_DefectOcc[TOTALTYPES];
	int m_DefectPower[TOTALTYPES];   //ȱ��Ȩֵ
	int m_TotalPower;   //����ͼƬ��Ȩֵ
public:
	HTuple hX,hY;
	HTuple hX_Sort, hY_Sort;
	Hobject m_hImgReduced;  //���ú��ͼ��
	Hobject m_hProductRegion;   //��Ʒ����
	Hobject m_hProcessRegion;   //�����е�����
	Hobject m_hSelectedRegion;   //ѡ�е�Ҫ����������
	Hlong m_ProdC1, m_ProdC2, m_ProdR1, m_ProdR2;   //��Ʒ�������
	Hobject m_hMean1, m_hMean2;   //2�ξ�ֵ�˲�
	Hobject m_hDynThreshRegion2, m_hDynThreshRegion1;
	Hobject m_hDynThreshRegion3, m_hDynThreshRegion4;
	Hobject m_hDynThreshRegion;   //��̬��ֵ
	CString str_DynMode1, str_DynMode2;   //��ֵ�ָ�ģʽ
	CString str_DynMode3, str_DynMode4;

public:
	Hobject hAlreadySeg, hRegionLeft, hRegionReduced;    //�Ѿ��ָ��ȱ�ݵ�����ʣ����Ҫ�ָ������
	void GetRemainRegion(Hobject *hRegionInput);  //�ѷָ��������Closing��Select_Shape֮����ʣ�������󽻼���ͬʱ��ʣ�������м�ȥ������

public:
	bool m_ifContinue;   //ȷ���Ƿ��⵽����
	HTuple m_ImageCenterRow, m_ImageCenterCol;   //����������������
public:
	void InitCamIndex(int Index);
	int  SurfaceCheck(vector<ErrorRegion> **DefectList, int &ErrorCount);
	int  ClassifyDefects(const Halcon::Hobject &InputRegion, long Index);
	void CalculateFeatures(const Halcon::Hobject &InputRegion, long Index);
	bool CalculateCrowdness();  //calculate density
	void CopyResults(int &ErrorCount);  //���ƽ��
public:
	CHTempDispRegion hTempDisp;
};
