#include "stdafx.h"
#include "DetectPinHole.h"

extern CParameterPool g_PP;
extern CResult g_RS;

CDetectPinHole::CDetectPinHole(void)
{
}

CDetectPinHole::~CDetectPinHole(void)
{
}

void CDetectPinHole::InitCamIndex( int Index )
{
	m_CamIndex = Index;   //几号相机
	if (Index>g_PP.m_TotalInitCamNum)
	{
		g_PP.m_TotalInitCamNum = Index;
	}
	m_TheBlackList = vector<ErrorRegion>(g_PP.m_MaxReturnNum+1);  //缺陷列表初始化
	m_Features = vector<Features>(g_PP.m_MaxReturnNum+1);

	strcpy_s(m_DefectName[OTHER],"其他");
	strcpy_s(m_DefectName[PINHOLE],"针孔");
	strcpy_s(m_DefectName[WELD],"焊缝");
	strcpy_s(m_DefectName[EDGE],"边缘");

	for (int i=0; i<TOTALTYPES; i++)
	{
		m_DefectOcc[i] = 0;
	}
}

int CDetectPinHole::DetectPinHole( vector<ErrorRegion> **DefectList ,int &ErrorCount)
{
	ErrorCount = 0;  //缺陷总数清零
	m_TheBlackList.empty();
	m_Features.empty();
	for (int i=0; i<TOTALTYPES; i++)
	{
		m_DefectOcc[i] = 0;
	}
	int r = 1;
	
	reduce_domain(g_PP.m_hOriginalImage[m_CamIndex], g_PP.m_hCheckRegion[m_CamIndex], &m_hImgReduced);
	area_center(g_PP.m_hCheckRegion[m_CamIndex], NULL, &m_ImageCenterRow, &m_ImageCenterCol);  //中心坐标

	threshold(m_hImgReduced, &m_hProductRegion, 0, g_PP.m_ProductGray);      //产品区域
	threshold(m_hImgReduced, &m_hWidthRegion, 0, g_PP.m_WidthGray);
	
	opening_rectangle1(m_hProductRegion, &m_hProcessRegion, 10, 100);
	closing_rectangle1(m_hProductRegion, &m_hProcessRegion, 1, 200);
	closing_rectangle1(m_hProcessRegion, &m_hProcessRegion, 500, 1);

	opening_rectangle1(m_hWidthRegion, &m_hWidthRegion, 1, 300);
	erosion_rectangle1(m_hProcessRegion, &m_hWidthRegion, 20, 1);
	if (CAM_POS_CENTER != g_PP.m_CamPos[m_CamIndex])
	{
		erosion_rectangle1(m_hProcessRegion, &m_hProcessRegion, 15, 1);
		Hlong m_moveCol = 0;
		if (CAM_POS_LEFT == g_PP.m_CamPos[m_CamIndex])
		{
			m_moveCol = 15;
		}
		else if (CAM_POS_RIGHT == g_PP.m_CamPos[m_CamIndex])
		{
			m_moveCol = -15;
		}
		move_region(m_hProcessRegion, &m_hRegionMoved, 0, m_moveCol);
		concat_obj(m_hProcessRegion, m_hRegionMoved, &m_hProcessRegion);
		union1(m_hProcessRegion, &m_hProcessRegion);
	}
	//opening_rectangle1(m_hProcessRegion, &m_hProcessRegion, 1, 200);
	fill_up(m_hProcessRegion, &m_hProcessRegion);
	connection(m_hProcessRegion, &m_hProcessRegion);

	fill_up(m_hWidthRegion, &m_hWidthRegion);
	connection(m_hWidthRegion, &m_hWidthRegion);

	if (CAM_POS_CENTER==g_PP.m_CamPos[m_CamIndex] || CAM_POS_SINGLE==g_PP.m_CamPos[m_CamIndex])
	{
		select_region_point(m_hProcessRegion,&m_hSelectedRegion,m_ImageCenterRow,m_ImageCenterCol);
		select_region_point(m_hWidthRegion,&m_hWidthRegion,m_ImageCenterRow,m_ImageCenterCol);
	}
	else if (CAM_POS_LEFT==g_PP.m_CamPos[m_CamIndex])
	{
		select_region_point(m_hProcessRegion,&m_hSelectedRegion,m_ImageCenterRow,m_ImageCenterCol*1.5);
		select_region_point(m_hWidthRegion,&m_hWidthRegion,m_ImageCenterRow,m_ImageCenterCol*1.5);
	}
	else if (CAM_POS_RIGHT==g_PP.m_CamPos[m_CamIndex])
	{
		select_region_point(m_hProcessRegion,&m_hSelectedRegion,m_ImageCenterRow,m_ImageCenterCol*0.5);
		select_region_point(m_hWidthRegion,&m_hWidthRegion,m_ImageCenterRow,m_ImageCenterCol*0.5);
	}
	Hlong ObjectAmount;
	count_obj(m_hSelectedRegion, &ObjectAmount);
	if (0 < ObjectAmount)
	{
		m_ifContinue = true;
	}
	else
	{
		HTuple hArea, hMaxArea;
		area_center(m_hProcessRegion, &hArea, NULL, NULL);
		tuple_max(hArea,&hMaxArea);
		if (hMaxArea[0].I() > 0)
		{
			select_shape(m_hProcessRegion, &m_hSelectedRegion, "area", "and", hMaxArea[0], hMaxArea[0]);
			select_shape(m_hWidthRegion, &m_hWidthRegion, "area", "and", hMaxArea[0], hMaxArea[0]);
			m_ifContinue = true;
		}
		else
		{
			m_ifContinue = false;
		}
		
	}

	//
	if (m_ifContinue)  //有效图片，继续检测
	{
		copy_obj(m_hSelectedRegion,&m_hProductRegion,1,1);
		smallest_rectangle1(m_hProductRegion,&m_ProdR1,&m_ProdC1,&m_ProdR2,&m_ProdC2);
		//计算宽度像素值
		smallest_rectangle1(m_hWidthRegion, &m_WidthR1, &m_WidthC1, &m_WidthR2, &m_WidthC2);
		g_RS.m_LastWidthPix = m_WidthC2-m_WidthC1+1;

		reduce_domain(g_PP.m_hOriginalImage[m_CamIndex],m_hProductRegion,&m_hImgReduced);
		threshold(m_hImgReduced, &m_hProcessRegion, g_PP.m_PinHoleGray, 255);
		closing_rectangle1(m_hProcessRegion, &m_hProcessRegion, 20, 1);
		Hlong pinholeArea;
		area_center(m_hProcessRegion, &pinholeArea, NULL, NULL);
		if (pinholeArea>0 && g_PP.m_IfRecord[PINHOLE])  //孔洞面积大于0，进行优先操作
		{
			connection(m_hProcessRegion,&m_hProcessRegion);
			select_shape(m_hProcessRegion,&m_hSelectedRegion,"area", "and", g_PP.m_PinHoleArea, AREA_MAX);
			//面积排序
			HTuple hArea, hSortIndex;
			area_center(m_hSelectedRegion, &hArea, NULL, NULL);
			tuple_sort_index(hArea, &hSortIndex);
			tuple_inverse(hSortIndex, &hSortIndex);
		
			count_obj(m_hSelectedRegion,&g_RS.m_DefectAmount[m_CamIndex]);
			for (int i=0; i<g_RS.m_DefectAmount[m_CamIndex] && i<g_PP.m_MaxReturnNum; i++)
			{
				Hobject hObjForAsses;
				Hlong Index;
				Index = hSortIndex[i].L();
				select_obj(m_hSelectedRegion,&hObjForAsses,Index+1);  //逐一选中区域进行分析
				
				CalculateFeatures(hObjForAsses,i);   //计算特征
				
				//根据特征分类
				int DefectType = 0;
				DefectType = ClassifyDefects(hObjForAsses,i);
				m_Features[i].retResults.Errortype = DefectType;
				strcpy_s(m_Features[i].retResults.strErrortype, m_DefectName[DefectType]);

			}
		}//if (pinholeArea>0) 孔洞面积大于0，进行优先操作
		else if (g_PP.m_IfCheckEdge && g_PP.m_IfRecord[EDGE])
		{
			Hobject hOpening;
			Hlong tempArea = 0;
			opening_rectangle1(m_hProductRegion, &hOpening, 1, 200);
			difference(m_hProductRegion,hOpening,&m_hTagRegion);
			area_center(m_hTagRegion,&tempArea,NULL,NULL);
			if (tempArea>=g_PP.m_EdgeArea)
			{
				//closing_rectangle1(m_hTagRegion,&m_hTagRegion,100,100);
				connection(m_hTagRegion,&m_hTagRegion);
				select_shape(m_hTagRegion,&m_hSelectedRegion,"area","and",g_PP.m_EdgeArea,AREA_MAX);
				select_shape(m_hSelectedRegion, &m_hSelectedRegion, "width", "and", g_PP.m_EdgeDepth,AREA_MAX);
				select_shape(m_hSelectedRegion, &m_hSelectedRegion, "height", "and", g_PP.m_EdgeWidth,AREA_MAX);
				//面积排序
				HTuple hArea, hSortIndex;
				area_center(m_hSelectedRegion, &hArea, NULL, NULL);

				if(hArea > 0)
				{
					tuple_sort_index(hArea, &hSortIndex);
					tuple_inverse(hSortIndex, &hSortIndex);
					if (hArea[hSortIndex[0].L()].I() >= g_PP.m_EdgeArea)
					{
						count_obj(m_hSelectedRegion,&g_RS.m_DefectAmount[m_CamIndex]);
					}
					else
					{
						g_RS.m_DefectAmount[m_CamIndex] = 0;
					}
					for (int i=0; i<g_RS.m_DefectAmount[m_CamIndex] && i<g_PP.m_MaxReturnNum; i++)
					{
						Hobject hObjForAsses;
						Hlong Index;
						Index = hSortIndex[i].L();
						select_obj(m_hSelectedRegion,&hObjForAsses,Index+1);  //逐一选中区域进行分析

						CalculateFeatures(hObjForAsses,i);   //计算特征

						//根据特征分类
						//int DefectType = 0;
						//DefectType = ClassifyDefects(hObjForAsses);
						m_Features[i].retResults.Errortype = EDGE;
						strcpy_s(m_Features[i].retResults.strErrortype, m_DefectName[EDGE]);

					}
				}
			}
		}
		CopyResults( ErrorCount );
		*DefectList = &m_TheBlackList;
	}//if (m_ifContinue)  //有效图片，继续检测


	return r;
}

void CDetectPinHole::CalculateFeatures( const Halcon::Hobject &InputRegion, long Index )
{
	//计算返回用的数据
	Hlong errC1, errC2, errR1, errR2;
	smallest_rectangle1(InputRegion, &errR1, &errC1, &errR2, &errC2);  //缺陷最小矩形
	m_Features[Index].regionWidthPix = errC2 - errC1 + 1;
	m_Features[Index].regionHeightPix = errR2 - errR1 +1;
	float errDiam;
	errDiam = max((errR2-errR1)*g_PP.m_Resolution_H,(errC2-errC1)*g_PP.m_Resolution_W[m_CamIndex]);  //取较大值作为直径
		if (errR1<=5)
		{
			errR1 = 1;
		}
		else
		{
			errR1-=5;
		}
		if (errR2>=(g_PP.m_ImageHeight-6))
		{
			errR2 = g_PP.m_ImageHeight-5;
		}
		else
		{
			errR2+=5;
		}

		if (errC1<=5)
		{
			errC1 = 1;
		}
		else
		{
			errC1-=5;
		}
		if (errC2>=(g_PP.m_ImageWidth[m_CamIndex]-6))
		{
			errC2 = g_PP.m_ImageWidth[m_CamIndex]-5;
		}
		else
		{
			errC2+=5;
		}

	Hlong errArea;
	double errCenterR, errCenterC;
	area_center(InputRegion, &errArea, &errCenterR, &errCenterC);    //缺陷面积及中心位置 
	//存于 m_Features.retResults
	m_Features[Index].errAreaPix = errArea;
	m_Features[Index].retResults.rect = CRect(errC1,errR1,errC2,errR2);
	m_Features[Index].retResults.ErrorArea = errArea*g_PP.m_Resolution_W[m_CamIndex]*g_PP.m_Resolution_H;
	m_Features[Index].retResults.Diameter = errDiam;
	if (g_PP.m_PinHoleArea > 0)
	{
		m_Features[Index].retResults.nLevel = (int)(errArea/g_PP.m_PinHoleArea);
	}
	else
	{
		m_Features[Index].retResults.nLevel = 0;
	}
	m_Features[Index].retResults.x = (int)(errCenterC-m_ProdC1);
	m_Features[Index].retResults.y = (int)errCenterR;

	//计算用于分类的数据
	Hlong imgC1, imgC2, imgR1, imgR2;
	imgR1 = (errR1-50)<0?0:(errR1-50);
	imgR2 = (errR2+50)>g_PP.m_ImageHeight?g_PP.m_ImageHeight:(errR2+50);
	imgC1 = (errC1-50)<0?0:(errC1-50);
	imgC2 = (errC2+50)>g_PP.m_ImageWidth[m_CamIndex]?g_PP.m_ImageWidth[m_CamIndex]:(errC2+50);
	m_Features[Index].sImgLeft = imgC1;
	m_Features[Index].sImgRight = imgC2;
	m_Features[Index].sImgTop = imgR1;
	m_Features[Index].sImgBotton = imgR2;
	m_Features[Index].sImageHeight = imgR2-imgR1;
	m_Features[Index].sImageWidth = imgC2-imgC1;

	Hobject imgRect;
	Hobject imgSmall;
	gen_rectangle1(&imgRect,imgR1,imgC1,imgR2,imgC2);
	reduce_domain(g_PP.m_hOriginalImage[m_CamIndex],imgRect,&imgSmall);
	Hobject threshArea;


	threshold(imgSmall,&threshArea,245,255);
	Hlong threshC1, threshC2, threshR1, threshR2;
	smallest_rectangle1(threshArea,&threshR1,&threshC1,&threshR2,&threshC2);
	m_Features[Index].errHeight = threshR2-threshR1+1;
	m_Features[Index].errWidth = threshC2-threshC1+1;

	if (errC1<50 && CAM_POS_LEFT==g_PP.m_CamPos[m_CamIndex])
	{
		m_Features[Index].ifNearEdge = true;
	}
	else if ((g_PP.m_ImageWidth[m_CamIndex]-errC2)<50 && CAM_POS_RIGHT==g_PP.m_CamPos[m_CamIndex])
	{
		m_Features[Index].ifNearEdge = true;
	}
	else if ((m_Features[Index].sImageHeight-m_Features[Index].errHeight)<=1 && m_Features[Index].sImageWidth!=m_Features[Index].errWidth)
	{
		m_Features[Index].ifNearEdge = true;
	}
	else
	{
		m_Features[Index].ifNearEdge = false;
	}
	
	
}

int CDetectPinHole::ClassifyDefects( const Halcon::Hobject &InputRegion, long Index )
{
	int retclass = OTHER;

	if (CAM_POS_CENTER == g_PP.m_CamPos[m_CamIndex])
	{
		retclass = PINHOLE;
	}
	else if (CAM_POS_LEFT==g_PP.m_CamPos[m_CamIndex] && (g_PP.m_ImageWidth[m_CamIndex]-m_Features[Index].retResults.x)<50)
	{
		retclass = PINHOLE;
	}
	else if (CAM_POS_RIGHT==g_PP.m_CamPos[m_CamIndex] && m_Features[Index].retResults.x<50)
	{
		retclass = PINHOLE;
	}
	else if (!m_Features[Index].ifNearEdge)
	{
		retclass = PINHOLE;
	}
	else if (m_Features[Index].ifNearEdge)
	{
		if (m_Features[Index].errAreaPix >= g_PP.m_EdgeArea)
		{
			if (m_Features[Index].errHeight >= g_PP.m_EdgeWidth)
			{
				if (m_Features[Index].errWidth >= g_PP.m_EdgeDepth)
				{
					retclass = EDGE;
				}
			}
		}
	}

	if (PINHOLE == retclass && m_Features[Index].retResults.nLevel >= g_PP.m_WeldArea_Min && m_Features[Index].errAreaPix <= g_PP.m_WeldArea_Max)
	{
		retclass = WELD;
	}

	if (m_Features[Index].regionWidthPix / m_Features[Index].regionHeightPix >=5)
	{
		retclass = OTHER;
	}

	return retclass;
}

void CDetectPinHole::CopyResults( int &ErrorCount )
{
	bool retAlarmFlag = false;
	for (int i=0; i<g_RS.m_DefectAmount[m_CamIndex] && i<g_PP.m_MaxReturnNum; i++)
	{
		int retErrType = m_Features[ErrorCount].retResults.Errortype;
		retAlarmFlag = (retAlarmFlag || g_PP.m_AlarmFlag[retErrType]);
		m_DefectOcc[retErrType]++;

		if(g_PP.m_IfRecord[retErrType])   //是否记录
		{
			m_TheBlackList[ErrorCount].nRegionType = m_Features[ErrorCount].retResults.nRegionType;
			m_TheBlackList[ErrorCount].ErrorArea = m_Features[ErrorCount].retResults.ErrorArea;
			m_TheBlackList[ErrorCount].Diameter = m_Features[ErrorCount].retResults.Diameter;
			m_TheBlackList[ErrorCount].Errortype = m_Features[ErrorCount].retResults.Errortype;
			strcpy_s(m_TheBlackList[ErrorCount].strErrortype, m_Features[ErrorCount].retResults.strErrortype);
			m_TheBlackList[ErrorCount].nLevel = m_Features[ErrorCount].retResults.nLevel;
			m_TheBlackList[ErrorCount].rect = m_Features[ErrorCount].retResults.rect;
			m_TheBlackList[ErrorCount].x = m_Features[ErrorCount].retResults.x;
			m_TheBlackList[ErrorCount++].y = m_Features[ErrorCount].retResults.y;
		}

	}
	g_RS.m_ImageAsses[m_CamIndex].AlarmFlag = retAlarmFlag;
	if (m_DefectOcc[PINHOLE]>0 && g_PP.m_AlarmFlag[PINHOLE])
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,m_DefectName[PINHOLE]);
	}
	else if (m_DefectOcc[WELD]>0 && g_PP.m_AlarmFlag[WELD])
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,m_DefectName[WELD]);
	}
	else if (m_DefectOcc[EDGE]>0 && g_PP.m_AlarmFlag[EDGE])
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,m_DefectName[EDGE]);
	}
	else if (m_DefectOcc[OTHER]>0 && g_PP.m_AlarmFlag[OTHER])
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,m_DefectName[OTHER]);
	}

}
