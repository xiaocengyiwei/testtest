#if !defined(CHECKPARA)
#define CHECKPARA

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector"
//#include "StdAfx.h"

using namespace std;
/*
typedef struct{
	int  nRegionType; //检测区域类型
	//增加
	char strRegionType[64];  //检测类型字符串，返回值为“左面”或“右面”
	// end fo 增加
	RECT rect;		 // 错误区域外界矩形坐标
	int  Errortype;  // 错误类型
	//增加：
	char strErrortype[64];  //错误类型字符串，返回值为“暗斑”，“干料”等缺陷中文名称
	// end of 增加
	int ErrorContrast; //缺陷对比度
	float  ErrorArea;  // 错误面积
	float Diameter;
	char Descript[256];  //字符串描述 
	int  nLevel;	 // 错误程度
	int x;          //缺陷水平方向坐标
	int y;          //缺陷垂直方向坐标
	float fFeature[20];
	BOOL ifTag;  //是否打标
	int tagLength;  //打标持续行数
}ErrorRegion;		// 错误区域
*/
typedef struct{
	int Defection;   //缺陷加权密度
	bool AlarmFlag;    //是否报警
	int AlarmLength;   //报警持续时间
	int Width;      //图像宽度像素
	int Height;    //图像高度像素
	char Comment[128];   //报警说明
	float Calc_Width;   //计算的图像宽度（毫米）
}Assesment;

typedef struct{
	long ErrArea;
	double  CenterGrayVal;
}ErrClassifier;

#endif