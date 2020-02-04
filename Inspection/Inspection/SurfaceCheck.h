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
		ErrorRegion retResults;  //返回的特征

		int properDynThresh;   
		Hlong regionWidthPix, regionHeightPix;  //缺陷本身的宽高
		Hlong errAreaPix;   //像素面积
		Hlong sImgLeft, sImgRight, sImgTop, sImgBotton;  //生成的小图区域 
		bool ifInterWithEdge;   //是否跟边缘区域有交集
		bool ifNearEdge; //是否靠近边缘
		Hlong errHeight, errWidth;  //分割的大块边缘区域宽高
		Hlong sImageHeight, sImageWidth;   //小图区域宽高

		bool ifCrowded;  //是否密度过大
	}Features;   //特征

	char m_DefectName[100][64];  //定义缺陷编号

public:
	vector<ErrorRegion> m_TheBlackList;   //缺陷列表
	vector<Features> m_Features;   //用于分类的特征向量
	int m_DefectOcc[TOTALTYPES];
	int m_DefectPower[TOTALTYPES];   //缺陷权值
	int m_TotalPower;   //本张图片总权值
public:
	HTuple hX,hY;
	HTuple hX_Sort, hY_Sort;
	Hobject m_hImgReduced;  //剪裁后的图像
	Hobject m_hProductRegion;   //产品区域
	Hobject m_hProcessRegion;   //处理中的区域
	Hobject m_hSelectedRegion;   //选中的要分析的区域
	Hlong m_ProdC1, m_ProdC2, m_ProdR1, m_ProdR2;   //产品区域矩形
	Hobject m_hMean1, m_hMean2;   //2次均值滤波
	Hobject m_hDynThreshRegion2, m_hDynThreshRegion1;
	Hobject m_hDynThreshRegion3, m_hDynThreshRegion4;
	Hobject m_hDynThreshRegion;   //动态阈值
	CString str_DynMode1, str_DynMode2;   //阈值分割模式
	CString str_DynMode3, str_DynMode4;

public:
	Hobject hAlreadySeg, hRegionLeft, hRegionReduced;    //已经分割出缺陷的区域，剩下需要分割的区域
	void GetRemainRegion(Hobject *hRegionInput);  //把分割出的区域，Closing，Select_Shape之后，与剩余区域求交集，同时在剩余区域中减去该区域

public:
	bool m_ifContinue;   //确认是否检测到区域
	HTuple m_ImageCenterRow, m_ImageCenterCol;   //检测区域的中心坐标
public:
	void InitCamIndex(int Index);
	int  SurfaceCheck(vector<ErrorRegion> **DefectList, int &ErrorCount);
	int  ClassifyDefects(const Halcon::Hobject &InputRegion, long Index);
	void CalculateFeatures(const Halcon::Hobject &InputRegion, long Index);
	bool CalculateCrowdness();  //calculate density
	void CopyResults(int &ErrorCount);  //复制结果
public:
	CHTempDispRegion hTempDisp;
};
