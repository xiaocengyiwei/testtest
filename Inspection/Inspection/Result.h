#pragma once

#include "ParameterPool.h"
#include "datatype.h"

class CResult
{
public:
	CResult(void);
	~CResult(void);

public:
	void InitResult();
	void Clear(int Index);

public:
	Hlong m_DefectAmount[CAM_NUM];   //各相机检测的缺陷总数
	Assesment m_ImageAsses[CAM_NUM];   //图像信息

	Hlong m_LastWidthPix;  //最近一次相机测出的宽度像素值
};
