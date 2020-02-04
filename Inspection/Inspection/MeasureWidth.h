#pragma once
#include "datatype.h"
#include "halconcpp.h"
#include "ParameterPool.h"
#include "Result.h"

using namespace Halcon;
class CMeasureWidth
{
public:
	CMeasureWidth(void);
	~CMeasureWidth(void);

public:
	float m_LastF_Width;
	int m_StoredImgWidth[CAM_NUM][MAX_WIDTH_STORED];
	int m_CalculatedWidth[MAX_WIDTH_STORED];
	float m_StoredImgWidthF[CAM_NUM][MAX_WIDTH_STORED];
	float m_CalculatedWidthF[MAX_WIDTH_STORED];

public:
	void InitWidthData();

public:
	int IndexForStore;
	int MaxIndex;   //最大的一组宽度
	bool ifWidthExists;   //检查宽度数据是否缺失

public:
	void MeasureWidth(int ImageIndex, int CamIndex);
	bool CheckWidthExists();
	int GetMaxWidthIndex();
};
