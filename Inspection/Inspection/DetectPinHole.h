#pragma once

#include <vector>
#include "datatype.h"
#include "halconcpp.h"
#include "ParameterPool.h"
#include "Result.h"
using namespace std;
using namespace Halcon;


class CDetectPinHole
{
public:
	CDetectPinHole(void);
	~CDetectPinHole(void);

private:
	int m_CamIndex;
public:
	typedef struct{
		ErrorRegion retResults;  //返回的特征

		Hlong regionWidthPix, regionHeightPix;  //缺陷本身的宽高

		Hlong errAreaPix;
		Hlong sImgLeft, sImgRight, sImgTop, sImgBotton;  //生成的小图区域 
		bool ifInterWithEdge;   //是否跟边缘区域有交集
		bool ifNearEdge; //是否靠近边缘
		Hlong errHeight, errWidth;  //分割的大块边缘区域宽高
		Hlong sImageHeight, sImageWidth;   //小图区域宽高
	}Features;   //特征
	char m_DefectName[100][64];  //定义缺陷编号
public:
	Hobject m_hImgReduced;  //剪裁后的图像
	Hobject m_hProductRegion;   //产品区域
	Hobject m_hRegionMoved;   //移动的区域
	Hlong m_ProdC1, m_ProdC2, m_ProdR1, m_ProdR2;   //产品区域矩形
	Hlong m_WidthC1, m_WidthC2, m_WidthR1, m_WidthR2;  //测宽
	Hobject m_hSelectedRegion;   //选中的要分析的区域
	Hobject m_hProcessRegion;   //处理中的区域
	Hobject m_hWidthRegion;  //计算宽度用的区域
	Hobject m_hTagRegion;   //检测标签用的

public:
	bool m_ifContinue;   //确认是否检测到区域
	HTuple m_ImageCenterRow, m_ImageCenterCol;   //检测区域的中心坐标

public:
	vector<ErrorRegion> m_TheBlackList;   //缺陷列表
	vector<Features> m_Features;   //用于分类的特征向量

public:
	int m_DefectOcc[TOTALTYPES];

public:
	void InitCamIndex(int Index);
	int  DetectPinHole(vector<ErrorRegion> **DefectList, int &ErrorCount);
	int  ClassifyDefects(const Halcon::Hobject &InputRegion, long Index);
	void CalculateFeatures(const Halcon::Hobject &InputRegion, long Index);
	void CopyResults(int &ErrorCount);  //复制结果
};
