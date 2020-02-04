#include "stdafx.h"
#include "SurfaceCheck.h"

extern CParameterPool g_PP;
extern CResult g_RS;
extern CParameterPool gl_P[CAM_NUM];
//extern CParameterPool gl_PB[CAM_NUM];

void tuple_gen_sequence (Halcon::HTuple Start, Halcon::HTuple End, Halcon::HTuple Step, 
						 Halcon::HTuple *Sequence);

void tuple_gen_sequence (Halcon::HTuple Start, Halcon::HTuple End, Halcon::HTuple Step, 
						 Halcon::HTuple *Sequence)
{
	using namespace Halcon;
	(*Sequence) = (Start-Step)+(HTuple((((End-Start)/Step).Int())+1,Step).Cumul());
	return;
}

CSurfaceCheck::CSurfaceCheck(void)
{
}

CSurfaceCheck::~CSurfaceCheck(void)
{
	m_TheBlackList.clear();
	m_Features.clear();
}

void CSurfaceCheck::InitCamIndex( int Index )
{
	//for(int CAM_INDEX=0;CAM_INDEX<CAM_NUM;CAM_INDEX++)
	//{
		gl_P[Index].InitSettingPath();
		gl_P[Index].LoadAllPara(Index);
		//g_PP=gl_P[Index];

	//}
	
	m_CamIndex = Index;   //几号相机
	if (Index>gl_P[Index].m_TotalInitCamNum)
	{
		gl_P[Index].m_TotalInitCamNum = Index;
	}
	m_TheBlackList = vector<ErrorRegion>(gl_P[Index].m_MaxReturnNum+2);  //缺陷列表初始化
	m_Features = vector<Features>(gl_P[Index].m_MaxReturnNum+2);
	for (int i=0; i<TOTALTYPES; i++)
	{
		m_DefectOcc[i] = 0;
		m_DefectPower[i] = 0;
	}
	m_TotalPower = 0;
	strcpy_s(m_DefectName[OTHER],gl_P[m_CamIndex].GetErrString(OTHER));
	strcpy_s(m_DefectName[DEFECT],gl_P[m_CamIndex].GetErrString(DEFECT));
	strcpy_s(m_DefectName[DEEP_S],gl_P[m_CamIndex].GetErrString(DEEP_S));
	strcpy_s(m_DefectName[DEEP_M],gl_P[m_CamIndex].GetErrString(DEEP_M));
	strcpy_s(m_DefectName[DEEP_L],gl_P[m_CamIndex].GetErrString(DEEP_L));
	strcpy_s(m_DefectName[SHALLOW_S],gl_P[m_CamIndex].GetErrString(SHALLOW_S));
	strcpy_s(m_DefectName[SHALLOW_M],gl_P[m_CamIndex].GetErrString(SHALLOW_M));
	strcpy_s(m_DefectName[SHALLOW_L],gl_P[m_CamIndex].GetErrString(SHALLOW_L));
	strcpy_s(m_DefectName[DEEP_S2],gl_P[m_CamIndex].GetErrString(DEEP_S2));
	strcpy_s(m_DefectName[DEEP_M2],gl_P[m_CamIndex].GetErrString(DEEP_M2));
	strcpy_s(m_DefectName[DEEP_L2],gl_P[m_CamIndex].GetErrString(DEEP_L2));
	strcpy_s(m_DefectName[SHALLOW_S2],gl_P[m_CamIndex].GetErrString(SHALLOW_S2));
	strcpy_s(m_DefectName[SHALLOW_M2],gl_P[m_CamIndex].GetErrString(SHALLOW_M2));
	strcpy_s(m_DefectName[SHALLOW_L2],gl_P[m_CamIndex].GetErrString(SHALLOW_L2));
	strcpy_s(m_DefectName[VERT_LINE],gl_P[m_CamIndex].GetErrString(VERT_LINE));
	strcpy_s(m_DefectName[HOR_LINE],gl_P[m_CamIndex].GetErrString(HOR_LINE));

	m_DefectPower[DEFECT] = 0;
	m_DefectPower[DEEP_S] = gl_P[m_CamIndex].m_Surf_DeepScoreS;
	m_DefectPower[DEEP_M] = gl_P[m_CamIndex].m_Surf_DeepScoreM;
	m_DefectPower[DEEP_L] = gl_P[m_CamIndex].m_Surf_DeepScoreL;
	m_DefectPower[SHALLOW_S] = gl_P[m_CamIndex].m_Surf_ShallowScoreS;
	m_DefectPower[SHALLOW_M] = gl_P[m_CamIndex].m_Surf_ShallowScoreM;
	m_DefectPower[SHALLOW_L] = gl_P[m_CamIndex].m_Surf_ShallowScoreL;

	m_DefectPower[DEEP_S2] = gl_P[m_CamIndex].m_Surf_DeepScoreS2;
	m_DefectPower[DEEP_M2] = gl_P[m_CamIndex].m_Surf_DeepScoreM2;
	m_DefectPower[DEEP_L2] = gl_P[m_CamIndex].m_Surf_DeepScoreL2;
	m_DefectPower[SHALLOW_S2] = gl_P[m_CamIndex].m_Surf_ShallowScoreS2;
	m_DefectPower[SHALLOW_M2] = gl_P[m_CamIndex].m_Surf_ShallowScoreM2;
	m_DefectPower[SHALLOW_L2] = gl_P[m_CamIndex].m_Surf_ShallowScoreL2;

	m_DefectPower[VERT_LINE] = gl_P[m_CamIndex].m_Surf_VertLineScore;
	m_DefectPower[HOR_LINE] = gl_P[m_CamIndex].m_Surf_HorLineScore;
}

void CSurfaceCheck::CopyResults( int &ErrorCount )
{
	bool retAlarmFlag = false;
	m_TotalPower = 0;
	for (int i=0; i<g_RS.m_DefectAmount[m_CamIndex] && i<gl_P[m_CamIndex].m_MaxReturnNum; i++)
	{
		int retErrType = m_Features[i].retResults.Errortype;
		retAlarmFlag = (retAlarmFlag || gl_P[m_CamIndex].m_AlarmFlag[retErrType]);
		m_DefectOcc[retErrType]++;

		//if(g_PP.m_IfRecord[retErrType])   //是否记录
		if((retErrType!=DEFECT)&&(m_DefectPower[retErrType]>0))
		{
			m_TheBlackList[ErrorCount].nRegionType = m_Features[ErrorCount].retResults.nRegionType;
			m_TheBlackList[ErrorCount].ErrorArea = m_Features[ErrorCount].retResults.ErrorArea;
			m_TheBlackList[ErrorCount].Diameter = m_Features[ErrorCount].retResults.Diameter;
			m_TheBlackList[ErrorCount].Errortype = m_Features[ErrorCount].retResults.Errortype;
			m_TheBlackList[ErrorCount].ifTag = m_Features[ErrorCount].retResults.ifTag;
			m_TheBlackList[ErrorCount].tagLength = m_Features[ErrorCount].retResults.tagLength;
			strcpy_s(m_TheBlackList[ErrorCount].strErrortype, m_Features[ErrorCount].retResults.strErrortype);
			m_TheBlackList[ErrorCount].nLevel = m_Features[ErrorCount].retResults.nLevel;
			m_TheBlackList[ErrorCount].rect = m_Features[ErrorCount].retResults.rect;
			m_TheBlackList[ErrorCount].x = m_Features[ErrorCount].retResults.x;
			m_TheBlackList[ErrorCount++].y = m_Features[ErrorCount].retResults.y;
		}
		else{
			ErrorCount++;
		}
	}
	if ((m_DefectOcc[VERT_LINE]>0)&&(m_DefectPower[VERT_LINE]>0))
	{
		m_TheBlackList[ErrorCount].nRegionType = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.nRegionType;
		m_TheBlackList[ErrorCount].ErrorArea = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.ErrorArea;
		m_TheBlackList[ErrorCount].Diameter = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.Diameter;
		m_TheBlackList[ErrorCount].Errortype = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.Errortype;
		m_TheBlackList[ErrorCount].ifTag = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.ifTag;
		m_TheBlackList[ErrorCount].tagLength = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.tagLength;
		strcpy_s(m_TheBlackList[ErrorCount].strErrortype, m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.strErrortype);
		m_TheBlackList[ErrorCount].nLevel = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.nLevel;
		m_TheBlackList[ErrorCount].rect = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.rect;
		m_TheBlackList[ErrorCount].x = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.x;
		m_TheBlackList[ErrorCount++].y = m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.y;
	}
	if ((m_DefectOcc[HOR_LINE]>0)&&(m_DefectPower[HOR_LINE]>0))
	{
		m_TheBlackList[ErrorCount].nRegionType = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.nRegionType;
		m_TheBlackList[ErrorCount].ErrorArea = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.ErrorArea;
		m_TheBlackList[ErrorCount].Diameter = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.Diameter;
		m_TheBlackList[ErrorCount].Errortype = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.Errortype;
		m_TheBlackList[ErrorCount].ifTag = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.ifTag;
		m_TheBlackList[ErrorCount].tagLength = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.tagLength;
		strcpy_s(m_TheBlackList[ErrorCount].strErrortype, m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.strErrortype);
		m_TheBlackList[ErrorCount].nLevel = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.nLevel;
		m_TheBlackList[ErrorCount].rect = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.rect;
		m_TheBlackList[ErrorCount].x = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.x;
		m_TheBlackList[ErrorCount++].y = m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.y;
	}
	for (int i=0; i<TOTALTYPES; i++)
	{
		m_TotalPower+=m_DefectOcc[i] * m_DefectPower[i];
	}
	//TRACE("TotalPower=%d\n",m_TotalPower);
	if (m_TotalPower >= gl_P[m_CamIndex].m_Surf_TotalScore)
	{
		retAlarmFlag = true;
	}

	g_RS.m_ImageAsses[m_CamIndex].AlarmFlag = retAlarmFlag;
	g_RS.m_ImageAsses[m_CamIndex].AlarmLength = m_TotalPower*20;
	if (g_RS.m_ImageAsses[m_CamIndex].AlarmLength>gl_P[m_CamIndex].m_Surf_AlarmLength)
	{
		g_RS.m_ImageAsses[m_CamIndex].AlarmLength = gl_P[m_CamIndex].m_Surf_AlarmLength;
	}
	if (retAlarmFlag)
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,"缺陷");
	}
	else
	{
		strcpy_s(g_RS.m_ImageAsses[m_CamIndex].Comment,"检测正常");
	}
}

int CSurfaceCheck::SurfaceCheck( vector<ErrorRegion> **DefectList, int &ErrorCount )
{
	ErrorCount = 0;  //缺陷总数清零
	m_TheBlackList.empty();
	m_Features.empty();

	hAlreadySeg.Reset();
	hRegionLeft.Reset();
	hRegionReduced.Reset();
	m_hDynThreshRegion.Reset();
	m_hDynThreshRegion1.Reset();
	m_hDynThreshRegion2.Reset();
	m_hDynThreshRegion3.Reset();
	m_hDynThreshRegion4.Reset();

	for (int i=0; i<TOTALTYPES; i++)
	{
		m_DefectOcc[i] = 0;
	}
	int r = 1;
	//HTuple row1,column1,row2,column2;
	//smallest_rectangle1(g_PP.m_hCheckRegion[m_CamIndex],&row1,&column1,&row2,&column2);
	//int xx1=column1[0].I();
	//int xx2=column2[0].I();
	//TRACE("checkregion column1=%d, colomu2=%d \n",xx1,xx2);

	reduce_domain(gl_P[m_CamIndex].m_hOriginalImage[m_CamIndex], g_PP.m_hCheckRegion[m_CamIndex], &m_hImgReduced);
	area_center(g_PP.m_hCheckRegion[m_CamIndex], NULL, &m_ImageCenterRow, &m_ImageCenterCol);  //中心坐标
	/*将reduce后的图像进行阈值处理*/
	threshold(m_hImgReduced, &m_hProductRegion, gl_P[m_CamIndex].m_Surf_ProdGray_Low, gl_P[m_CamIndex].m_Surf_ProdGray_High);      //产品区域
	

	closing_rectangle1(m_hProductRegion,&m_hProductRegion,gl_P[m_CamIndex].m_Surf_CloseW,gl_P[m_CamIndex].m_Surf_CloseH);
	fill_up(m_hProductRegion, &m_hProductRegion);
	/*将切边去掉*/
	erosion_rectangle1(m_hProductRegion,&m_hProcessRegion,gl_P[m_CamIndex].m_Surf_EroseW,gl_P[m_CamIndex].m_Surf_EroseH);
	connection(m_hProcessRegion,&m_hProcessRegion);

	select_shape(m_hProcessRegion, &m_hSelectedRegion,"area","and",gl_P[m_CamIndex].m_Surf_ProdArea,AREA_MAX);
	Hlong ObjectAmount;
	count_obj(m_hSelectedRegion, &ObjectAmount);
	if (0 < ObjectAmount)
	{
		m_ifContinue = true;
		if (ObjectAmount > 1)
		{
			union1(m_hSelectedRegion, &m_hSelectedRegion);
		}
	}
	if (m_ifContinue)  //有效图片，继续检测
	{
		copy_obj(m_hSelectedRegion,&m_hProductRegion,1,1);

		smallest_rectangle1(m_hProductRegion,&m_ProdR1,&m_ProdC1,&m_ProdR2,&m_ProdC2);//求产品reducce之后进行一些列处理后的图像的宽度
		/*重新定位要检测的区域*/
		reduce_domain(gl_P[m_CamIndex].m_hOriginalImage[m_CamIndex], m_hProductRegion, &m_hImgReduced);
		
		g_RS.m_ImageAsses[m_CamIndex].Width = (int)(m_ProdC2-m_ProdC1);
		g_RS.m_ImageAsses[m_CamIndex].Height = (int)(m_ProdR2-m_ProdR1);
		reduce_domain(gl_P[m_CamIndex].m_hOriginalImage[m_CamIndex],m_hProductRegion,&m_hImgReduced);
		copy_obj(m_hProductRegion,&hRegionReduced,1,1);   //初始化剩余区域   
#pragma region 横竖条纹检测
		if ( ((m_ProdC2-m_ProdC1)>5) && ((m_ProdR2-m_ProdR1)>5) )//检测横竖条纹
		{
			HTuple HorProjection, VertProjection;
			HTuple projWidth, projHeight;
			HTuple sequenceWidth, sequenceHeight;
			Hobject histoWidth, histoHeight;
			Hobject hVertLine, hHorLine;
			gray_projections(m_hProductRegion,gl_P[m_CamIndex].m_hOriginalImage[m_CamIndex],"simple",&HorProjection,&VertProjection);
			tuple_length(VertProjection,&projWidth);
			tuple_length(HorProjection,&projHeight);
			//smallest_rectangle1(m_hProductRegion,&m_ProdR1,&m_ProdC1,&m_ProdR2,&m_ProdC2);
			tuple_gen_sequence(m_ProdC1,(projWidth+m_ProdC1)-1,1,&sequenceWidth);
			tuple_gen_sequence(m_ProdR1,(projHeight+m_ProdR1)-1,1,&sequenceHeight);
			gen_region_points(&histoWidth, projHeight-((VertProjection*projHeight)/255), sequenceWidth);
			gen_region_points(&histoHeight, sequenceHeight, projWidth-((HorProjection*projWidth)/255));
		
			if (gl_P[m_CamIndex].m_Surf_Stripe_W1>0 && gl_P[m_CamIndex].m_Surf_Stripe_W2>gl_P[m_CamIndex].m_Surf_Stripe_W1) //检测竖条纹
			{
				closing_circle(histoWidth,&histoWidth,gl_P[m_CamIndex].m_Surf_Stripe_Close_WC5);
				connection(histoWidth,&histoWidth);
				select_shape(histoWidth,&histoWidth,"width","and",gl_P[m_CamIndex].m_Surf_Stripe_W1,gl_P[m_CamIndex].m_Surf_Stripe_W2);
				union1(histoWidth,&histoWidth);
				Hlong tempArea;
				area_center(histoWidth,&tempArea,NULL,NULL);
				if (tempArea>0)
				{
					m_DefectOcc[VERT_LINE]++;
					Hlong R1,C1,R2,C2;
					smallest_rectangle1(histoWidth,&R1,&C1,&R2,&C2);
					R1 = m_ProdR1;
					R2 = m_ProdR2;
					gen_rectangle1(&hVertLine, R1, C1, R2, C2);
					GetRemainRegion(&hVertLine);
					//计算Feature
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].properDynThresh = WIDTH_STRIPE;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].regionWidthPix = C2-C1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].regionHeightPix = R2-R1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].errAreaPix = tempArea;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.rect = CRect(C1,R1,C2,R2);
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.ErrorArea = tempArea*g_PP.m_Resolution_W[m_CamIndex]*gl_P[m_CamIndex].m_Resolution_H;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.Diameter = (C2-C1)*g_PP.m_Resolution_W[m_CamIndex];
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.nLevel = 1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.x = (C2-C1)/2;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.y = (R2-R1)/2;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.tagLength = gl_P[m_CamIndex].m_Surf_TagLength;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfVertLineTag;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.Errortype = VERT_LINE;
					strcpy_s(m_Features[gl_P[m_CamIndex].m_MaxReturnNum].retResults.strErrortype,m_DefectName[VERT_LINE]);
				}
			} //if (g_PP.m_Surf_Stripe_W1>0 && g_PP.m_Surf_Stripe_W2>g_PP.m_Surf_Stripe_W1) //检测竖条纹
			if (gl_P[m_CamIndex].m_Surf_Stripe_H1>0 && gl_P[m_CamIndex].m_Surf_Stripe_H2>gl_P[m_CamIndex].m_Surf_Stripe_H1) //检测横条纹
			{
				closing_circle(histoHeight,&histoHeight,gl_P[m_CamIndex].m_Surf_Stripe_Close_HC5);
				connection(histoHeight,&histoHeight);
				select_shape(histoHeight,&histoHeight,"height","and",gl_P[m_CamIndex].m_Surf_Stripe_H1,gl_P[m_CamIndex].m_Surf_Stripe_H2);
				union1(histoHeight,&histoHeight);
				Hlong tempArea;
				area_center(histoHeight,&tempArea,NULL,NULL);
				if (tempArea>0)
				{
					m_DefectOcc[HOR_LINE]++;
					Hlong R1,C1,R2,C2;
					smallest_rectangle1(histoHeight,&R1,&C1,&R2,&C2);
					C1 = m_ProdC1;
					C2 = m_ProdC2;
					gen_rectangle1(&hHorLine, R1, C1, R2, C2);
					GetRemainRegion(&hHorLine);
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].properDynThresh = HEIGHT_STRIPE;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].regionWidthPix = C2-C1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].regionHeightPix = R2-R1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].errAreaPix = tempArea;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.rect = CRect(C1,R1,C2,R2);
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.ErrorArea = tempArea*g_PP.m_Resolution_W[m_CamIndex]*gl_P[m_CamIndex].m_Resolution_H;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.Diameter = (R2-R1)*gl_P[m_CamIndex].m_Resolution_H;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.nLevel = 1;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.x = (C2-C1)/2;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.y = (R2-R1)/2;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.tagLength = gl_P[m_CamIndex].m_Surf_TagLength;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfVertLineTag;
					m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.Errortype = HOR_LINE;
					strcpy_s(m_Features[gl_P[m_CamIndex].m_MaxReturnNum+1].retResults.strErrortype,m_DefectName[HOR_LINE]);
				}
			}//if (g_PP.m_Surf_Stripe_H1>0 && g_PP.m_Surf_Stripe_H2>g_PP.m_Surf_Stripe_H1) //检测横条纹
		}//if ( ((m_ProdC2-m_ProdC1)>5) && ((m_ProdR2-m_ProdR1)>5) )//检测横竖条纹
#pragma endregion 
#pragma  region  模式选择，dark，light
		if(TRUE)
		{
			switch(gl_P[m_CamIndex].m_Surf_DynMode_1)
			{
			case DYN_MODE_LIGHT:
				str_DynMode1.Format("light");
				break;
			case DYN_MODE_DARK:
				str_DynMode1.Format("dark");
				break;
			case DYN_MODE_NOTEQUAL:
				str_DynMode1.Format("not_equal");
				break;
			default:
				str_DynMode1.Format("not_equal");
				break;
			}
			switch(gl_P[m_CamIndex].m_Surf_DynMode_2)
			{
			case DYN_MODE_LIGHT:
				str_DynMode2.Format("light");
				break;
			case DYN_MODE_DARK:
				str_DynMode2.Format("dark");
				break;
			case DYN_MODE_NOTEQUAL:
				str_DynMode2.Format("not_equal");
				break;
			default:
				str_DynMode2.Format("not_equal");
				break;
			}
			switch(gl_P[m_CamIndex].m_Surf_DynMode_3)
			{
			case DYN_MODE_LIGHT:
				str_DynMode3.Format("light");
				break;
			case DYN_MODE_DARK:
				str_DynMode3.Format("dark");
				break;
			case DYN_MODE_NOTEQUAL:
				str_DynMode3.Format("not_equal");
				break;
			default:
				str_DynMode3.Format("not_equal");
				break;
			}
			switch(gl_P[m_CamIndex].m_Surf_DynMode_4)
			{
			case DYN_MODE_LIGHT:
				str_DynMode4.Format("light");
				break;
			case DYN_MODE_DARK:
				str_DynMode4.Format("dark");
				break;
			case DYN_MODE_NOTEQUAL:
				str_DynMode4.Format("not_equal");
				break;
			default:
				str_DynMode4.Format("not_equal");
				break;
			}
#pragma  endregion

			mean_image(m_hImgReduced,&m_hMean1,gl_P[m_CamIndex].m_Surf_MeanW1,gl_P[m_CamIndex].m_Surf_MeanH1);
			mean_image(m_hImgReduced,&m_hMean2,gl_P[m_CamIndex].m_Surf_MeanW2,gl_P[m_CamIndex].m_Surf_MeanH2);
			Hlong tempThreshArea;
			/////////////////////////////////////阈值1/////////////////////////////////////////////////
			//dyn_thresh 1
			dyn_threshold(m_hMean1, m_hMean2, &m_hDynThreshRegion1, gl_P[m_CamIndex].m_Surf_DynThresh1, str_DynMode1);
			fill_up(m_hDynThreshRegion1,&m_hDynThreshRegion1);
			area_center(m_hDynThreshRegion1,&tempThreshArea,NULL,NULL);
			if (tempThreshArea>0)
			{
				if (gl_P[m_CamIndex].m_Surf_Close_W1>0 && gl_P[m_CamIndex].m_Surf_Close_H1>0)
				{
					closing_rectangle1(m_hDynThreshRegion1,&m_hDynThreshRegion1,gl_P[m_CamIndex].m_Surf_Close_W1,gl_P[m_CamIndex].m_Surf_Close_H1);
				}
				connection(m_hDynThreshRegion1,&m_hDynThreshRegion1);
				select_shape(m_hDynThreshRegion1,&m_hDynThreshRegion1,"area","and",gl_P[m_CamIndex].m_Surf_DeepSizePixS,AREA_MAX);
				GetRemainRegion(&m_hDynThreshRegion1);/*求补集*/
			}

			////////////////////////////////////////////阈值2////////////////////////////////////////////////////////
			//dyn_thresh 2
			dyn_threshold(m_hMean1, m_hMean2, &m_hDynThreshRegion2, gl_P[m_CamIndex].m_Surf_DynThresh2, str_DynMode2);
			fill_up(m_hDynThreshRegion2,&m_hDynThreshRegion2);
			area_center(m_hDynThreshRegion2,&tempThreshArea,NULL,NULL);
			if (tempThreshArea>0)
			{
				if (gl_P[m_CamIndex].m_Surf_Close_W2>0 && gl_P[m_CamIndex].m_Surf_Close_H2>0)
				{
					closing_rectangle1(m_hDynThreshRegion2,&m_hDynThreshRegion2,gl_P[m_CamIndex].m_Surf_Close_W2,gl_P[m_CamIndex].m_Surf_Close_H2);
				}
				connection(m_hDynThreshRegion2,&m_hDynThreshRegion2);
				select_shape(m_hDynThreshRegion2,&m_hDynThreshRegion2,"area","and",gl_P[m_CamIndex].m_Surf_ShallowSizePixS,AREA_MAX);
				GetRemainRegion(&m_hDynThreshRegion2);
			}
			///////////////////////////////////////////////阈值3//////////////////////////////////////////////////
			//dyn_thresh3
			dyn_threshold(m_hMean1, m_hMean2, &m_hDynThreshRegion3, gl_P[m_CamIndex].m_Surf_DynThresh3, str_DynMode3);
			fill_up(m_hDynThreshRegion3,&m_hDynThreshRegion3);
			area_center(m_hDynThreshRegion3,&tempThreshArea,NULL,NULL);
			if (tempThreshArea>0)
			{
				if (gl_P[m_CamIndex].m_Surf_Close_1C3>0)
				{
					closing_circle(m_hDynThreshRegion3,&m_hDynThreshRegion3,gl_P[m_CamIndex].m_Surf_Close_1C3);
				}
				remove_noise_region(m_hDynThreshRegion3,&m_hDynThreshRegion3,"n_48");
				if (gl_P[m_CamIndex].m_Surf_Close_2C3>0)
				{
					closing_circle(m_hDynThreshRegion3,&m_hDynThreshRegion3,gl_P[m_CamIndex].m_Surf_Close_2C3);
				}
				connection(m_hDynThreshRegion3,&m_hDynThreshRegion3);
				select_shape(m_hDynThreshRegion3,&m_hDynThreshRegion3,"area","and",gl_P[m_CamIndex].m_Surf_DeepSizePixS2,AREA_MAX);
				GetRemainRegion(&m_hDynThreshRegion3);
			}
			/////////////////////////////////////////////阈值4////////////////////////////////////////////////////
			//dyn_thresh4
			dyn_threshold(m_hMean1,m_hMean2,&m_hDynThreshRegion4,gl_P[m_CamIndex].m_Surf_DynThresh4, str_DynMode4);
			fill_up(m_hDynThreshRegion4,&m_hDynThreshRegion4);
			area_center(m_hDynThreshRegion4,&tempThreshArea,NULL,NULL);
			if (tempThreshArea>0)
			{
				if (gl_P[m_CamIndex].m_Surf_Close_1C4>0)
				{
					closing_circle(m_hDynThreshRegion4,&m_hDynThreshRegion4,gl_P[m_CamIndex].m_Surf_Close_1C4);
				}
				remove_noise_region(m_hDynThreshRegion4,&m_hDynThreshRegion4,"n_48");
				if (gl_P[m_CamIndex].m_Surf_Close_2C4)
				{
					closing_circle(m_hDynThreshRegion4,&m_hDynThreshRegion4,gl_P[m_CamIndex].m_Surf_Close_2C4);
				}
				connection(m_hDynThreshRegion4,&m_hDynThreshRegion4);
				select_shape(m_hDynThreshRegion4,&m_hDynThreshRegion4,"area","and",gl_P[m_CamIndex].m_Surf_ShallowSizePixS2,AREA_MAX);
				GetRemainRegion(&m_hDynThreshRegion4);
			}

			connection(m_hDynThreshRegion,&m_hProcessRegion);
		} //if(TRUE)
		/*将检测出的区域联合到一起*/
 		union1(m_hDynThreshRegion1,&m_hDynThreshRegion1);
 		union1(m_hDynThreshRegion2,&m_hDynThreshRegion2);
		union1(m_hDynThreshRegion3,&m_hDynThreshRegion3);
		union1(m_hDynThreshRegion4,&m_hDynThreshRegion4);
	

		Hlong defectArea;
		area_center(m_hDynThreshRegion, &defectArea, NULL, NULL);
		if (defectArea>0)
		{
			HTuple temphArea, temphSortIndex;
			area_center(m_hProcessRegion, &temphArea, NULL, NULL);
			tuple_sort_index(temphArea, &temphSortIndex);
			tuple_inverse(temphSortIndex, &temphSortIndex);
			count_obj(m_hProcessRegion,&g_RS.m_DefectAmount[m_CamIndex]);
			/*根据最大记录缺陷的数量来分析检测结果*/
			for (int i=0; i<g_RS.m_DefectAmount[m_CamIndex] && i<gl_P[m_CamIndex].m_MaxReturnNum; i++)
			{
				Hobject hObjForAsses;
				Hlong Index;
				Index = temphSortIndex[i].L();
				select_obj(m_hProcessRegion,&hObjForAsses,Index+1);  //逐一选中区域进行分析

				CalculateFeatures(hObjForAsses,i);   //计算特征

				int DefectType = OTHER;
				DefectType = ClassifyDefects(hObjForAsses,i);
				m_Features[i].retResults.Errortype = DefectType;
				strcpy_s(m_Features[i].retResults.strErrortype, m_DefectName[DefectType]);
			}
		}  // if(defectArea>0)

		//

		CopyResults( ErrorCount );
		*DefectList = &m_TheBlackList;
	}// if(m_ifContinue)

	return 1;
}


void CSurfaceCheck::CalculateFeatures( const Halcon::Hobject &InputRegion, long Index )
{
	//计算返回用的数据
	m_Features[Index].retResults.ifTag = 0;
	m_Features[Index].ifCrowded = false;
	Hlong errC1, errC2, errR1, errR2;
	smallest_rectangle1(InputRegion, &errR1, &errC1, &errR2, &errC2);  //缺陷最小矩形
	
	Hlong imgC1, imgC2, imgR1, imgR2;   //局部小区域,这里要根据先前检测出的实际产品四周坐标来决定，而不是整个图像的四周坐标
	imgR1 = (errR1-50)<(m_ProdR1+5)?(m_ProdR1+5):(errR1-50);
	imgR2 = (errR2+50)>(m_ProdR2-5)?(m_ProdR2-5):(errR2+50);
	imgC1 = (errC1-50)<(m_ProdC1+5)?(m_ProdC1+5):(errC1-50);
	imgC2 = (errC2+50)>(m_ProdC2-5)?(m_ProdC2-5):(errC2+50);

	//判断小图是否完全在产品区域之内
	Hobject imgRect;
	Hobject imgSmall;
	Hobject regionDyn;
	Hlong subSet1, subSet2, subSet3, subSet4;
	//Hlong subSet;
	gen_rectangle1(&imgRect,imgR1,imgC1,imgR2,imgC2);
	reduce_domain(gl_P[m_CamIndex].m_hOriginalImage[m_CamIndex],imgRect,&imgSmall);   //生成小图
	if (TRUE)
	{
// 		hTempDisp.TempDispRegion(m_hDynThreshRegion1);
// 		hTempDisp.TempWindowClose();
// 		hTempDisp.TempDispRegion(m_hDynThreshRegion2);
// 		hTempDisp.TempWindowClose();

		test_subset_region(InputRegion, m_hDynThreshRegion1, &subSet1);
		test_subset_region(InputRegion, m_hDynThreshRegion2, &subSet2);
		test_subset_region(InputRegion, m_hDynThreshRegion3, &subSet3);
		test_subset_region(InputRegion, m_hDynThreshRegion4, &subSet4);
// 		test_subset_region(InputRegion, m_hDynThreshRegion, &subSet);
// 		test_subset_region(m_hDynThreshRegion1,m_hDynThreshRegion, &subSet);
// 		test_subset_region(m_hDynThreshRegion2,m_hDynThreshRegion, &subSet);
		if (subSet1 > 0)
		{
			m_Features[Index].properDynThresh = DEEP_REGION;
		}
		else if(subSet2>0)
		{
			m_Features[Index].properDynThresh = SHALLOW_REGION;
		}
		else if (subSet3>0)
		{
			m_Features[Index].properDynThresh = DEEP_REGION2;
		}
		else if (subSet4>0)
		{
			m_Features[Index].properDynThresh = SHALLOW_REGION2;
		}
	}


	//计算面积与方差
	Hlong regionArea;   //面积
	double regionMean, regionDeviation;   //均值与方差
	copy_obj(InputRegion, &regionDyn, 1, 1);
	area_center(regionDyn,&regionArea,NULL,NULL);
	intensity(regionDyn,imgSmall,&regionMean,&regionDeviation);
	
	smallest_rectangle1(regionDyn,&errR1, &errC1, &errR2, &errC2);
	m_Features[Index].regionWidthPix = errC2 - errC1 + 1;
	m_Features[Index].regionHeightPix = errR2 - errR1 +1;
	float errDiam;
	errDiam = max((errR2-errR1)*gl_P[m_CamIndex].m_Resolution_H,(errC2-errC1)*g_PP.m_Resolution_W[m_CamIndex]);  //取较大值作为直径
	
	Hlong errArea;
	double errCenterR, errCenterC;
	area_center(regionDyn, &errArea, &errCenterR, &errCenterC);    //缺陷面积及中心位置 
	//存于 m_Features.retResults
	m_Features[Index].errAreaPix = errArea;
	m_Features[Index].retResults.rect = CRect(errC1,errR1,errC2,errR2);
	m_Features[Index].retResults.ErrorArea = errArea*g_PP.m_Resolution_W[m_CamIndex]*gl_P[m_CamIndex].m_Resolution_H*gl_P[m_CamIndex].m_Surf_Calib2;
	m_Features[Index].retResults.Diameter = errDiam*gl_P[m_CamIndex].m_Surf_Calib;
	if (gl_P[m_CamIndex].m_Surf_Area_Min > 0)
	{
		m_Features[Index].retResults.nLevel = (int)(errArea/gl_P[m_CamIndex].m_Surf_Area_Min);
	}
	else
	{
		m_Features[Index].retResults.nLevel = 0;
	}
	m_Features[Index].retResults.x = (int)(errCenterC-m_ProdC1);
	m_Features[Index].retResults.y = (int)(errCenterR/*-m_ProdR1*/);

	m_Features[Index].retResults.tagLength = gl_P[m_CamIndex].m_Surf_TagLength;

	//是否是亮线
	Hobject threshArea;
	threshold(imgSmall,&threshArea,gl_P[m_CamIndex].m_iMinWidthGray,gl_P[m_CamIndex].m_iMaxWidthGray);
	connection(threshArea,&threshArea);
	Hlong threshC1, threshC2, threshR1, threshR2;
	smallest_rectangle1(threshArea,&threshR1,&threshC1,&threshR2,&threshC2);
	m_Features[Index].errHeight = threshR2-threshR1+1;//缺陷的宽
	m_Features[Index].errWidth = threshC2-threshC1+1;//缺陷的高

}

int CSurfaceCheck::ClassifyDefects( const Halcon::Hobject &InputRegion, long Index )
{
	int retClass = DEFECT;  //默认未分类缺陷  


	//判断横纵比

	{
		if (DEEP_REGION == m_Features[Index].properDynThresh)  //最终分割阈值 ≥ 深缺陷阈值
		{
			if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixL)  //面积 ≥ 大点
			{
				retClass = DEEP_L;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepLTag;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixM)  //面积 ≥ 中点
			{
				retClass = DEEP_M;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepMTag;

			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixS)  //面积 ≥ 小点
			{
				retClass = DEEP_S;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepSTag;
			}
		}
		else if (SHALLOW_REGION == m_Features[Index].properDynThresh)  //最终分割阈值 < 深缺陷阈值
		{
			if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixL)  //面积 ≥ 大点
			{
				retClass = SHALLOW_L;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowLTag;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixM)  //面积 ≥ 中点
			{
				retClass = SHALLOW_M;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowMTag;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixS)  //面积 ≥ 小点
			{
				retClass = SHALLOW_S;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowSTag;
			}
		}
		else if (DEEP_REGION2 == m_Features[Index].properDynThresh)  //最终分割阈值 ≥ 深缺陷阈值
		{
			if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixL2)  //面积 ≥ 大点
			{
				retClass = DEEP_L2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepLTag2;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixM2)  //面积 ≥ 中点
			{
				retClass = DEEP_M2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepMTag2;

			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_DeepSizePixS2)  //面积 ≥ 小点
			{
				retClass = DEEP_S2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfDeepSTag2;
			}
		}
		else if (SHALLOW_REGION2 == m_Features[Index].properDynThresh)  //最终分割阈值 < 深缺陷阈值
		{
			if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixL2)  //面积 ≥ 大点
			{
				retClass = SHALLOW_L2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowLTag2;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixM2)  //面积 ≥ 中点
			{
				retClass = SHALLOW_M2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowMTag2;
			}
			else if (m_Features[Index].errAreaPix >= gl_P[m_CamIndex].m_Surf_ShallowSizePixS2)  //面积 ≥ 小点
			{
				retClass = SHALLOW_S2;
				m_Features[Index].retResults.ifTag = gl_P[m_CamIndex].m_Surf_IfShallowSTag2;
			}
		}
	}
	if((float)m_Features[Index].errWidth/(float)m_Features[Index].errHeight >= gl_P[m_CamIndex].m_fHorAndVorRatio && gl_P[m_CamIndex].m_iRecordWidthLine)
	{
		retClass = DEFECT;
		return retClass;
	}
	return retClass;
}

bool CSurfaceCheck::CalculateCrowdness()
{
	bool isCrowded;
	isCrowded = false;
	int m_Total = g_RS.m_DefectAmount[m_CamIndex];
	int m_Count = 42;//g_PP.m_Surf_DensityCount;
	//按x坐标排序
	tuple_sort_index(hX,&hX_Sort);
	//计算Width密度
	for (int i=0; i<(m_Total-m_Count+1) && i<gl_P[m_CamIndex].m_MaxReturnNum; i++)
	{
		int i_test = i+m_Count-1;
		//while ((i_test<m_Total)&&((hX[hX_Sort[i_test].L()].L()-hX[hX_Sort[i].L()].L())<=g_PP.m_Surf_DensitySizeWidth))
		{
			i_test++;
		}
		if ((i_test-i)>=m_Count)
		{
			//说明i到i_test之间的x坐标距离满足条件，继续判断y坐标
			i_test--;
			Hobject hYRegion;
			Hobject hTempRegion;
			select_obj(m_hSelectedRegion,&hTempRegion,(hX_Sort[i].L()+1));
			copy_obj(hTempRegion,&hYRegion,1,1);
			for (int j=i+1; j<=i_test; j++)
			{
				select_obj(m_hSelectedRegion,&hTempRegion,(hX_Sort[j].L()+1));
				Hlong tempArea;
				double tempRow, tempCol;
				area_center(hTempRegion,&tempArea,&tempRow,&tempCol);
				concat_obj(hTempRegion,hYRegion,&hYRegion);
			}
			Hlong xCount;
			count_obj(hYRegion,&xCount);
			area_center(hYRegion,NULL,NULL,&hY);
			tuple_sort_index(hY,&hY_Sort);
			for (int k=0; k<(xCount-m_Count+1); k++)
			{
				int k_test = k+m_Count-1;
				//if ((k_test<m_Total)&&((hY[hY_Sort[k_test].L()].L()-hY[hY_Sort[k].L()].L())<=g_PP.m_Surf_DensitySizeHeight))
				{
					isCrowded = true;
					union1(hYRegion,&hYRegion);
					Hlong hY_R1,hY_R2,hY_C1,hY_C2;
					smallest_rectangle1(hYRegion,&hY_R1,&hY_C1,&hY_R2,&hY_C2);
					Hlong hY_Area;
					double hY_CenterC,hY_CenterR;
					area_center(hYRegion,&hY_Area,&hY_CenterR,&hY_CenterC);
					int tempIndex;
					tempIndex = m_Total<=gl_P[m_CamIndex].m_MaxReturnNum?m_Total:gl_P[m_CamIndex].m_MaxReturnNum;
					m_Features[tempIndex].retResults.ErrorArea = (float)hY_Area*gl_P[m_CamIndex].m_Resolution_H*g_PP.m_Resolution_W[m_CamIndex];
					m_Features[tempIndex].retResults.Diameter = (float)(hY_C2-hY_C1)*g_PP.m_Resolution_W[m_CamIndex];
					m_Features[tempIndex].retResults.Errortype = OVER_CROWDED;
					strcpy_s(m_Features[tempIndex].retResults.strErrortype,m_DefectName[OVER_CROWDED]);
					m_Features[tempIndex].retResults.nLevel = hY_Area;
					m_Features[tempIndex].retResults.rect = CRect(hY_C1,hY_R1,hY_C2,hY_R2);
					m_Features[tempIndex].retResults.x = (int)(hY_CenterC);
					m_Features[tempIndex].retResults.y = (int)hY_CenterR;

				}
			}

		}
	}
	return isCrowded; 
}

void CSurfaceCheck::GetRemainRegion( Hobject *hRegionInput )
{
	union1(*hRegionInput,hRegionInput);
	Hlong inputArea = 0;
	area_center(*hRegionInput,&inputArea,NULL,NULL);
	if(inputArea>0)
	{
		//1. 与剩余区域取交集
		intersection(hRegionReduced,*hRegionInput,hRegionInput);
		Hlong tempInputArea = 0;
		area_center(*hRegionInput,&tempInputArea,NULL,NULL);
		if(tempInputArea>0)
		{
			//2. 适当膨胀该区域
			Hobject hTempDilationRegion;
			dilation_rectangle1(*hRegionInput,&hTempDilationRegion,50,50);

			//3. 将膨胀后的区域添加进已分割区域
			Hlong tempAlreadySegArea = 0;
			area_center(hAlreadySeg,&tempAlreadySegArea,NULL,NULL);
			if (tempAlreadySegArea>0)
			{
				concat_obj(hTempDilationRegion,hAlreadySeg,&hAlreadySeg);
				union1(hAlreadySeg,&hAlreadySeg);
			}
			else
			{
				copy_obj(hTempDilationRegion,&hAlreadySeg,1,1);
			}
			//4. 更新剩余区域
			complement(hAlreadySeg,&hRegionLeft);
			//5. 更新RegionReduced
			Hlong tempRegionLeftArea = 0;
			area_center(hRegionLeft,&tempRegionLeftArea,NULL,NULL);
			if (tempRegionLeftArea>0)
			{
				intersection(m_hProductRegion,hRegionLeft,&hRegionReduced);
			}
			//6. 将InputRegion合并入m_hThresholdRegion
			Hlong tempDynThreshRegionArea = 0;
			area_center(m_hDynThreshRegion,&tempDynThreshRegionArea,NULL,NULL);
			if (tempDynThreshRegionArea>0)
			{
				concat_obj(*hRegionInput,m_hDynThreshRegion,&m_hDynThreshRegion);
			}
			else
			{
				copy_obj(*hRegionInput,&m_hDynThreshRegion,1,1);
			}
		}  //if(tempInputArea>0)
	}  //if(inputArea>0)
	connection(*hRegionInput,hRegionInput);
}