#include "stdafx.h"
#include "MeasureWidth.h"

extern CParameterPool g_PP;
extern CResult g_RS;

CMeasureWidth::CMeasureWidth(void)
{
	InitWidthData();
}

CMeasureWidth::~CMeasureWidth(void)
{
}

void CMeasureWidth::InitWidthData()
{
	for (int i=0; i<CAM_NUM; i++)
	{
		for (int j=0; j<MAX_WIDTH_STORED; j++)
		{
			m_StoredImgWidth[i][j] = 0;
			m_StoredImgWidthF[i][j] = 0;
		}
	}
	for (int i=0; i<MAX_WIDTH_STORED; i++)
	{
		m_CalculatedWidth[i] = 0;
		m_CalculatedWidthF[i] = 0;
	}
	m_LastF_Width = 0;
}

void CMeasureWidth::MeasureWidth( int ImageIndex, int CamIndex )
{	
	IndexForStore = ImageIndex%g_PP.m_StoredNum;   //取余决定当前宽度存放于数组哪个位置
	m_StoredImgWidth[CamIndex][IndexForStore] = (int)g_RS.m_LastWidthPix;
	m_StoredImgWidthF[CamIndex][IndexForStore] = (float)g_RS.m_LastWidthPix*g_PP.m_Resolution_W[CamIndex];
	ifWidthExists = CheckWidthExists();
	if (ifWidthExists)
	{
		MaxIndex = GetMaxWidthIndex();
		g_RS.m_ImageAsses[CamIndex].Calc_Width = m_CalculatedWidthF[MaxIndex];
		g_RS.m_ImageAsses[CamIndex].Width = (int)g_RS.m_LastWidthPix;
		m_LastF_Width = m_CalculatedWidthF[MaxIndex];
	}
	else
	{
		g_RS.m_ImageAsses[CamIndex].Calc_Width = m_LastF_Width;
		g_RS.m_ImageAsses[CamIndex].Width = (int)g_RS.m_LastWidthPix;
	}
}

bool CMeasureWidth::CheckWidthExists()
{
	for (int i=0; i<g_PP.m_StoredNum; i++)
	{
		bool exists = true;
		for (int j=0; j<=g_PP.m_TotalInitCamNum; j++)
		{
			if (0 == m_StoredImgWidth[j][i])
			{
				exists = false;
			}
		}
		if (exists)
		{
			return true;
		}
	}
	return false;
}

int CMeasureWidth::GetMaxWidthIndex()
{
	int MaxIndex = 0;
	//calculate
	for (int i = 0; i < g_PP.m_StoredNum; i++)
	{
		m_CalculatedWidth[i] = 0;
		m_CalculatedWidthF[i] = 0;
		for (int j = 0; j <= g_PP.m_TotalInitCamNum; j++)
		{
			m_CalculatedWidth[i] = m_CalculatedWidth[i] + m_StoredImgWidth[j][i];
			m_CalculatedWidthF[i] = m_CalculatedWidthF[i] + m_StoredImgWidthF[j][i];
		}
		m_CalculatedWidthF[i] = m_CalculatedWidthF[i] + g_PP.m_Overlap_Width;
	}
	//max
	for (int i = 1; i < g_PP.m_StoredNum; i++)
	{
		if (m_CalculatedWidthF[MaxIndex] < m_CalculatedWidthF[i])
			MaxIndex = i;
	}
	return MaxIndex;
}