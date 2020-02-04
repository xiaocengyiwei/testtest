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
	Hlong m_DefectAmount[CAM_NUM];   //���������ȱ������
	Assesment m_ImageAsses[CAM_NUM];   //ͼ����Ϣ

	Hlong m_LastWidthPix;  //���һ���������Ŀ������ֵ
};
