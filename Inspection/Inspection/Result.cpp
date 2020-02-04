#include "stdafx.h"
#include "Result.h"

CResult::CResult(void)
{
}

CResult::~CResult(void)
{
}

void CResult::InitResult()
{
	for (int i=0; i<CAM_NUM; i++)
	{
		m_DefectAmount[i] = 0;

		m_ImageAsses[i].AlarmFlag = false;
		m_ImageAsses[i].Calc_Width = 0.0;
		strcpy_s(m_ImageAsses[i].Comment,"检测正常");
		m_ImageAsses[i].Defection = 0;
		m_ImageAsses[i].Width = 0;
	}
	
}

void CResult::Clear( int Index )
{
	m_DefectAmount[Index] = 0;

	m_ImageAsses[Index].AlarmFlag = false;
	m_ImageAsses[Index].Calc_Width = 0.0;
	strcpy_s(m_ImageAsses[Index].Comment,"检测正常");
	m_ImageAsses[Index].Defection = 0;
	m_ImageAsses[Index].Width = 0;

	m_LastWidthPix = 0;
}