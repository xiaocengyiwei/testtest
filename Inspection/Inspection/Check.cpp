// Check.cpp: implementation of the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shlwapi.h"  //加密
#include "Check.h"
#include "SetModel.h"		//add by qq
#include "Inspection.h"		//add by qq
#include <time.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern CSetModel* SetM;   //add by qq



//命令行输出缓冲大小
const long MAX_COMMAND_SIZE = 10000;
//获取MAC命令行
char szFetCmd[] = "ipconfig /all";
//网卡MAC地址的前导信息
const string str4Search = "Physical Address. . . . . . . . . : ";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheck::CCheck()
{
	m_bChangeLap = TRUE;  //add by qq
	//初始化数组
}

CCheck::~CCheck()
{
	if(!g_ErrorRegion.empty())
	{
		g_ErrorRegion.clear();
	}
}

void CCheck::SetImageData(const char *imagedata)
{	 
	gen_image1_extern(&m_himage, "byte", m_lWidth, m_lHeight, (long)imagedata,NULL);//从带存储管理的像素的一个指针创建一个图像,imagedata为像素指针，ClearProc
	
	mirror_image(m_himage,&m_himage,"row");//镜像一个图像
}


void CCheck::writeWidth()
{
	CString strFileName,str;
	str.Format("%d",currWidth);
	FILE *fp;
	//errno_t err;
	if (0 == m_imgCount)
	{
		//for (int i = 0; i < CAMERA_NUM; i++)
		{
			strFileName.Format("%s\\outputWidth-%d.txt",m_strModelDir,m_lComeraIndex);
			if (0 == _access(strFileName,0))
			{
				CFile mFile;
				mFile.Remove(strFileName);
			}
		}	
	}
	strFileName.Format("%s\\outputWidth-%d.txt",m_strModelDir,m_lComeraIndex);
	//err = fopen_s(&fp,strFileName,"ab");
	fp = fopen(strFileName,"ab");
	fprintf(fp,"%d\t%d\n",m_imgCount,currWidth);
	fclose(fp);
	//WritePrivateProfileString("宽度",str2,str,strFileName);
}

void CCheck::writeTime()
{
	CString strFileName,str;
	str.Format("%d",timeConsume);
	FILE *fp;
	//errno_t err;
	if (0 == m_imgCount)
	{
		//for (int i = 0; i < CAMERA_NUM; i++)
		{
			strFileName.Format("%s\\outputTime-%d.txt",m_strModelDir,m_lComeraIndex);
			if (0 == _access(strFileName,0))
			{
				CFile mFile;
				mFile.Remove(strFileName);
			}
		}	
	}
	strFileName.Format("%s\\outputTime-%d.txt",m_strModelDir,m_lComeraIndex);
	fp = fopen(strFileName,"ab");
	//err = fopen_s(&fp, strFileName, "ab");
	fprintf(fp,"%d\t%d\n",m_imgCount,timeConsume);
	fclose(fp);
}

void CCheck::writemodel()
{
  //保存图像
  CString strFileName,str;
  CString commonFileName;
  strFileName.Format("%s\\ModelImage-%d.bmp",m_strModelDir,m_lComeraIndex);
  write_image(m_himage,"bmp",0,strFileName);
  //保存区域
  strFileName.Format("%s\\CheckRegion-%d.region",m_strModelDir,m_lComeraIndex);
  write_region(m_hCheckRegion,strFileName);
  //保存检测参数
  strFileName.Format("%s\\checkpara-%d.ini",m_strModelDir,m_lComeraIndex);
  commonFileName.Format("%s\\checkpara-all.ini",m_strModelDir);
  str.Format("%d", m_Gray);
  WritePrivateProfileString("精度设置信息", "对比度", str, strFileName);
  str.Format("%d", m_area);
  WritePrivateProfileString("精度设置信息", "针孔面积", str, strFileName);
  str.Format("%d", m_ErrorNum);
  WritePrivateProfileString("精度设置信息", "缺陷个数", str, strFileName);
  //add by qq
  str.Format("%d", m_uploc);
  WritePrivateProfileString("精度设置信息", "上定位", str, strFileName);
  str.Format("%d", m_leftloc);
  WritePrivateProfileString("精度设置信息", "左定位", str, strFileName);
  str.Format("%d", m_downloc);
  WritePrivateProfileString("精度设置信息", "下定位", str, strFileName);
  str.Format("%d", m_rightloc);
  WritePrivateProfileString("精度设置信息", "右定位", str, strFileName);
  str.Format("%ld", m_berrorarea);
  WritePrivateProfileString("精度设置信息", "焊缝面积", str, strFileName);

  str.Format("%d", m_bheight);
  WritePrivateProfileString("精度设置信息", "图像高度", str, strFileName);
  str.Format("%d", m_bwidth);
  WritePrivateProfileString("精度设置信息", "图像宽度", str, strFileName);

  str.Format("%d", m_CameraPosition);
  WritePrivateProfileString("精度设置信息", "相机位置", str, strFileName);

  str.Format("%d", m_edgeOpenSize);
  WritePrivateProfileString("精度设置信息", "消除毛刺", str, strFileName);
  str.Format("%d", m_edgeCloseSize);
  WritePrivateProfileString("精度设置信息", "填补缺口", str, strFileName);
  str.Format("%d", m_imgStored);
  WritePrivateProfileString("精度设置信息", "预存张数", str, strFileName);
  str.Format("%d", m_extraPix);
  WritePrivateProfileString("精度设置信息", "重叠像素", str, commonFileName);
  str.Format("%.2f", m_ExtraWidth);
  WritePrivateProfileString("精度设置信息", "重叠宽度", str, commonFileName);
  str.Format("%d", m_ifRecordWidth);
  WritePrivateProfileString("精度设置信息", "记录宽度", str, strFileName);
 /* str.Format("%d", m_isCheckErrDistance);
  WritePrivateProfileString("精度设置信息", "缺陷间距控制", str, strFileName);*/
  /*str.Format("%d", m_ErrorDistance);
  WritePrivateProfileString("精度设置信息", "缺陷间距", str, strFileName);*/
  str.Format("%f", m_HorRes);
  WritePrivateProfileString("精度设置信息", "横向分辨率", str, strFileName);
  str.Format("%f", m_VerRes);
  WritePrivateProfileString("精度设置信息", "纵向分辨率", str, strFileName);
  str.Format("%d", gray_background);
  WritePrivateProfileString("精度设置信息", "检测区域背景", str, strFileName);
  str.Format("%d", m_Gray_Product);
  WritePrivateProfileString("精度设置信息", "真实背景灰度", str, strFileName);
  str.Format("%f", m_ProductWidth);
  WritePrivateProfileString("精度设置信息", "产品设计宽度", str, commonFileName);
  str.Format("%d", m_fake_width);
  WritePrivateProfileString("精度设置信息", "吸附", str, strFileName);

  str.Format("%d", m_If_Check_Edge);
  WritePrivateProfileString("精度设置信息", "是否检测边裂", str, strFileName);
  str.Format("%d", m_Edge_Opening);
  WritePrivateProfileString("精度设置信息", "边裂开操作尺度", str, strFileName);
  str.Format("%d", m_Edge_Closing);
  WritePrivateProfileString("精度设置信息", "边裂闭操作尺度", str, strFileName);
  str.Format("%d", m_Edge_Area);
  WritePrivateProfileString("精度设置信息", "边裂面积", str, strFileName);

  str.Format("%d", m_edge_width);
  WritePrivateProfileString("精度设置信息", "边裂Width", str, strFileName);
  str.Format("%d", m_edge_height);
  WritePrivateProfileString("精度设置信息", "边裂Height", str, strFileName);
  str.Format("%.2f",width_height_ratio);
  WritePrivateProfileString("精度设置信息", "边裂宽高比", str, strFileName);

  str.Format("%d", m_ifDelayWidth);
  WritePrivateProfileString("精度设置信息", "是否延迟宽度", str, commonFileName);
  str.Format("%d", m_IfRecordWidthErr);
  WritePrivateProfileString("精度设置信息", "是否记录宽度缺陷", str, commonFileName);
  str.Format("%f", m_Width_Upbound);
  WritePrivateProfileString("精度设置信息", "宽度上限", str, commonFileName);
  str.Format("%f", m_Width_Downbound);
  WritePrivateProfileString("精度设置信息", "宽度下限", str, commonFileName);

  str.Format("%s", m_Lock_PassWord);
  WritePrivateProfileString("密码设置", "解锁密码", str, commonFileName);
  str.Format("%d", m_Lock_Status);
  WritePrivateProfileString("密码设置", "锁定状态", str, commonFileName);

  str.Format("%d", m_DebugMode);
  WritePrivateProfileString("测试参数", "弹出图片", str, commonFileName);
  //end add		

//add by qq
  if (SetM->m_bRollChange)
  {
	  WritePrivateProfileString("精度设置信息","检测焊缝","1",strFileName);
  }
  else
  {
	  WritePrivateProfileString("精度设置信息","检测焊缝","0",strFileName);
  }
//end add 
}

// 获得当前可执行文件路径
bool CCheck::GetCurrentAppPath(char **path)
{
	char str[MAX_PATH], drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
				
	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	strcpy_s(sCurrentPath,drive);
	*path = sCurrentPath;
	
	return true;
}

void CCheck::readmodel()
{
	CString strFileName;
	long isEsit;
	strFileName.Format("%s\\ModelImage-%d.bmp",m_strModelDir,m_lComeraIndex);

	file_exists(strFileName,&isEsit);
	if (isEsit == TRUE) //相机2时，isEsit=1
	{
		read_image(&m_himage,strFileName);
	}
		
	//读取区域
	strFileName.Format("%s\\CheckRegion-%d.region",m_strModelDir,m_lComeraIndex);
	file_exists(strFileName,&isEsit);
	if (isEsit == TRUE)
	{
		read_region(&m_hCheckRegion,strFileName);
		m_bIsCheckRegion = true;
	}
		
	CString fileName;
	CString commonFileName;
	int nMaxLen = 256;
	char* pBuff = new char[nMaxLen];
	fileName.Format("%s\\checkpara-%d.ini",m_strModelDir,m_lComeraIndex);
	commonFileName.Format("%s\\checkpara-all.ini",m_strModelDir);
	m_Gray = 
		GetPrivateProfileInt("精度设置信息", "对比度", 128, fileName);
	m_area = 
		GetPrivateProfileInt("精度设置信息", "针孔面积", 10000, fileName);	
	//add by qq
	m_uploc = 
		GetPrivateProfileInt("精度设置信息", "上定位", 0, fileName);
	m_leftloc = 
		GetPrivateProfileInt("精度设置信息", "左定位", 0, fileName);
	m_downloc = 
		GetPrivateProfileInt("精度设置信息", "下定位", 6000, fileName);
	m_rightloc = 
		GetPrivateProfileInt("精度设置信息", "右定位", 2048, fileName);
	m_berrorarea =
		GetPrivateProfileInt("精度设置信息", "焊缝面积", 1000, fileName);
	//end add

	m_bheight =
		GetPrivateProfileInt("精度设置信息", "图像高度", 6000, fileName);
	m_bwidth =
		GetPrivateProfileInt("精度设置信息", "图像宽度", 2048, fileName);

	m_CameraPosition =
		GetPrivateProfileInt("精度设置信息", "相机位置", -1, fileName);
	//add by qq
	m_bChangeLap =
		GetPrivateProfileInt("精度设置信息", "检测焊缝", 0, fileName);
	//end add
	m_ErrorNum = 
		GetPrivateProfileInt("精度设置信息", "缺陷个数", 5, fileName);	
	m_ErosionSize = 
		GetPrivateProfileInt("精度设置信息", "收缩尺度", 10, fileName);

	GetPrivateProfileString("精度设置信息", "横向分辨率", NULL, pBuff,nMaxLen, fileName);
	m_HorRes = (float)atof(pBuff);
	GetPrivateProfileString("精度设置信息", "纵向分辨率", NULL, pBuff,nMaxLen, fileName);
	m_VerRes = (float)atof(pBuff);
	gray_background =
		GetPrivateProfileInt("精度设置信息", "检测区域背景", 20, fileName);
	m_Gray_Product =
		GetPrivateProfileInt("精度设置信息", "真实背景灰度", 10, fileName);
	m_edgeOpenSize =
		GetPrivateProfileInt("精度设置信息", "消除毛刺", 50, fileName);
	m_edgeCloseSize = 
		GetPrivateProfileInt("精度设置信息", "填补缺口", 200, fileName);
	m_imgStored = 
		GetPrivateProfileInt("精度设置信息", "预存张数", 50, fileName);
	m_ifRecordWidth =
		GetPrivateProfileInt("精度设置信息", "记录宽度", 1, fileName);
	/*m_isCheckErrDistance =
		GetPrivateProfileInt("精度设置信息", "缺陷间距控制", 1, fileName);*/
	/*m_ErrorDistance =
		GetPrivateProfileInt("精度设置信息", "缺陷间距", 150, fileName);*/
	m_extraPix = 
		GetPrivateProfileInt("精度设置信息", "重叠像素", 0, commonFileName);
	GetPrivateProfileString("精度设置信息", "重叠宽度", NULL, pBuff, nMaxLen, commonFileName);
	m_ExtraWidth = (float)atof(pBuff);
	GetPrivateProfileString("精度设置信息", "产品设计宽度", NULL, pBuff, nMaxLen, commonFileName);
	m_ProductWidth = (float)atof(pBuff);
	m_fake_width =
		GetPrivateProfileInt("精度设置信息","吸附", 0, fileName);

	GetPrivateProfileString("精度设置信息", "边裂宽高比", NULL, pBuff, nMaxLen, fileName);
	width_height_ratio = (double)atof(pBuff);
	m_If_Check_Edge =
		GetPrivateProfileInt("精度设置信息", "是否检测边裂", 1, fileName);
	m_Edge_Opening =
		GetPrivateProfileInt("精度设置信息", "边裂开操作尺度", 1, fileName);
	m_Edge_Closing =
		GetPrivateProfileInt("精度设置信息", "边裂闭操作尺度", 1, fileName);
	m_Edge_Area =
		GetPrivateProfileInt("精度设置信息", "边裂面积", 1, fileName);
	m_edge_width =
		GetPrivateProfileInt("精度设置信息", "边裂Width", 1, fileName);
	m_edge_height =
		GetPrivateProfileInt("精度设置信息", "边裂Height", 1, fileName);

	m_ifDelayWidth = 
		GetPrivateProfileInt("精度设置信息", "是否延迟宽度", 1, commonFileName);
	m_IfRecordWidthErr =
		GetPrivateProfileInt("精度设置信息", "是否记录宽度缺陷", 1, commonFileName);
	GetPrivateProfileString("精度设置信息", "宽度上限", NULL, pBuff, nMaxLen, commonFileName);
	m_Width_Upbound = (float)atof(pBuff);
	GetPrivateProfileString("精度设置信息", "宽度下限", NULL, pBuff, nMaxLen, commonFileName);
	m_Width_Downbound = (float)atof(pBuff);

	GetPrivateProfileString("密码设置", "解锁密码", NULL, pBuff, nMaxLen, commonFileName);
	m_Lock_PassWord.Format("%s",pBuff);
	m_Lock_Status =
		GetPrivateProfileInt("密码设置", "锁定状态",1, commonFileName);

	m_DebugMode =
		GetPrivateProfileInt("测试参数", "弹出图片",0, commonFileName);
}

bool CCheck::GetMacByCmd(char *lpszMac)
{
  //初始化返回MAC地址缓冲区
    memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa; 
    HANDLE hReadPipe,hWritePipe;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE; 
				
//创建管道
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if(!bret)
	{
		return FALSE;
	}
	//控制命令行窗口信息
	STARTUPINFO si; 
	//返回进程信息
    PROCESS_INFORMATION pi;
    si.cb = sizeof(STARTUPINFO); 
    GetStartupInfo(&si); 
    si.hStdError = hWritePipe; 
    si.hStdOutput = hWritePipe; 
    si.wShowWindow = SW_HIDE; //隐藏命令行窗口
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//创建获取命令行进程
	bret = CreateProcess (NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, 
		NULL, &si, &pi ); 
		
	char szBuffer[MAX_COMMAND_SIZE+1]; //放置命令行输出缓冲区
	string strBuffer;
	if (bret) 
	{ 
		WaitForSingleObject (pi.hProcess, INFINITE); 
		unsigned long count;
		CloseHandle(hWritePipe);
		memset(szBuffer, 0x00, sizeof(szBuffer));
		bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
		if(!bret)
		{
			//关闭所有的句柄
			CloseHandle(hWritePipe);
			CloseHandle(pi.hProcess); 
			CloseHandle(pi.hThread); 
			CloseHandle(hReadPipe);
			return FALSE;
		}
		else
		{
    		strBuffer = szBuffer;
			long ipos;
			ipos = strBuffer.find(str4Search);
			//提取MAC地址串
			strBuffer = strBuffer.substr(ipos+str4Search.length());
			ipos = strBuffer.find("\n");
			strBuffer = strBuffer.substr(0, ipos);
		}
	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//去掉中间的“00-50-EB-0F-27-82”中间的'-'得到0050EB0F2782
	int j = 0;
	for(int i=0; i<strlen(szBuffer); i++)
	{
		if(szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//关闭所有的句柄
	//    CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread); 
	CloseHandle(hReadPipe);
	
	return true;
}

bool CCheck::Init(int nIndex,int width,int height)
{
	m_lComeraIndex = nIndex;

	if(nIndex>TotalCameraNum)
		TotalCameraNum = nIndex;

	CString str, strFileName;
	char lpszMac[128];
	memset(lpszMac, 0x00, sizeof(lpszMac));
	//获取MAC
	GetMacByCmd(lpszMac);
	
    char StrMac[] = "00190F014CCF";
	int nRet = StrCmpN(lpszMac,StrMac,12);
    if (nRet !=0)
    {
//		return false;
    }
	
	char* dir = NULL;
	GetCurrentAppPath(&dir);
    g_Path.Format("%s", dir);
	
	m_strModelDir.Format("%sModel",g_Path);
	CreateDirectory(m_strModelDir, NULL);
	strFileName.Format("%s\\checkpara-%d.ini",m_strModelDir,m_lComeraIndex);
	m_bIsCheckRegion = false;
	str.Format("%d", height);
	WritePrivateProfileString("精度设置信息", "图像高度", str, strFileName);
	str.Format("%d", width);
	WritePrivateProfileString("精度设置信息", "图像宽度", str, strFileName);
	m_lWidth = width;
	m_lHeight = height;
	
    readmodel();
	g_ErrorRegion = vector<ErrorRegion>(m_ErrorNum+1);

	return true;
}

int CCheck::classify(const Halcon::Hobject &RegionForClassify)
{
	int retVal = 0;
	long objarea;//目标区域的面积
	double CenterRow,CenterCol;
	//double GrayMean, Deviation;
	long roiRow1, roiCol1, roiRow2, roiCol2;
	long regRow1, regCol1, regRow2, regCol2;
	long imgRow1, imgCol1, imgRow2, imgCol2;
	Hobject imgRectangle, imgForRegion;
	//double errRadius;
	double wh_ratio;
	bool isNearEdge = false;
	bool isNearLeft;  //有效区域靠近左边为true，靠近右边为false
	bool isCenter;   //判断region是否在钢板中间，这是焊缝的一个特征
	long inter_with_tag = 0;
	long inter_with_edge = 0;
	long temp_area1 = 0;
	long temp_area2 = 0;
	
	area_center(hTagRegion,&temp_area1,NULL,NULL);
	if(temp_area1>0)
		test_subset_region(RegionForClassify,hTagRegion,&inter_with_tag);
	area_center(hEdgeRegion,&temp_area2,NULL,NULL);
	if(temp_area2>0)
		test_subset_region(RegionForClassify,hEdgeRegion,&inter_with_edge);
	//area_center(RegionForClassify,&objarea,NULL,NULL);
	smallest_rectangle1(hReduceImg, &roiRow1, &roiCol1, &roiRow2, &roiCol2); //边缘.
	if (roiCol1 < (m_lWidth-roiCol2))  //判断有效区域是贴着左边还是右边
		isNearLeft = true;
	else
		isNearLeft = false;
	smallest_rectangle1(RegionForClassify,&regRow1,&regCol1,&regRow2,&regCol2); //分类区域最小矩形
	//生成小图
	imgRow1 = (regRow1-50)<0?0:(regRow1-50);
	imgRow2 = (regRow2+50)>m_lHeight?m_lHeight:(regRow2+50);
	imgCol1 = (regCol1-50)<0?0:(regCol1-50);
	imgCol2 = (regCol2+50)>m_lWidth?m_lWidth:(regCol2+50);
	gen_rectangle1(&imgRectangle,imgRow1,imgCol1,imgRow2,imgCol2);
	reduce_domain(m_himage,imgRectangle,&imgForRegion);
	int thresh_for_edge;
	Hobject test_for_edge;
	long test_edge_area;
	long edge_top,edge_botton;
	long edge_left,edge_right;
	long imgHeight,regionHeight;
	long imgWidth, regionWidth;
	long thresh_edge_area;
	//double minGray, maxGray, rangeGray;
	//min_max_gray(RegionForClassify,imgForRegion,0,&minGray,&maxGray,&rangeGray);
	area_center(imgRectangle,&thresh_edge_area,NULL,NULL);
	thresh_for_edge = 245;
	threshold(imgForRegion,&test_for_edge,thresh_for_edge,255);
	smallest_rectangle1(test_for_edge,&edge_top,&edge_left,&edge_botton,&edge_right);
	imgHeight = imgRow2 - imgRow1;
	imgWidth = imgCol2 - imgCol1;
	regionHeight = edge_botton - edge_top;
	regionWidth = edge_right - edge_left;
	area_center(test_for_edge,&test_edge_area,NULL,NULL);
	long regHeight, regWidth;
	regHeight = regRow2-regRow1+1;
	regWidth = regCol2-regCol1+1;
	wh_ratio = (double)(regCol2-regCol1)/(regRow2-regRow1);   //长宽比 = 宽度/高度
	//intensity(RegionForClassify,hReduceImg, &GrayMean, &Deviation);
	//circularity(RegionForClassify, &Circularity);
	area_center(RegionForClassify, &objarea, &CenterRow, &CenterCol);
	//errRadius = sqrt((double)objarea/3.14);
	thresh_edge_area = thresh_edge_area/3;
	if (isNearLeft)
	{
		if (CenterCol < (roiCol2/2))
			isCenter = true;
		else
			isCenter = false;
	}
	else
	{
		if(CenterCol > (m_lWidth-(roiCol2-roiCol1)/2))
			isCenter = true;
		else
			isCenter = false;
	}

	//m_CameraPosition:  0:左边 1:中间 2:右边 3:单个相机

	if(regCol1<50 && 0==m_CameraPosition)
		isNearEdge = true;
	if((m_lWidth-regCol2)<50 && 2==m_CameraPosition)
		isNearEdge = true;

	if(inter_with_tag>=1)  //边缘.
		isNearEdge = true; 
	if(inter_with_edge>=1)
		isNearEdge = true;
	if(((imgHeight-regionHeight<=1) && imgWidth!=regionWidth) || test_edge_area>=thresh_edge_area)
		isNearEdge = true;
	if(1==m_CameraPosition)
		retVal = 1;
	else if(0==m_CameraPosition && (m_lWidth-regCol2)<50)
		retVal = 1;
	else if(2==m_CameraPosition && regCol1<50)
		retVal = 1;
	else if (!isNearEdge)// && (rangeGray>=m_Gray))
		retVal = 1;
	else if (isNearEdge && objarea>m_Edge_Area && regWidth > m_edge_width && regHeight >m_edge_height) //|| wh_ratio>=width_height_ratio))
		retVal = 3;
	if(1 == retVal && objarea > m_berrorarea)  //焊缝
		retVal = 2;
	return retVal;	
}
int CCheck::Check(const char *imagedata, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount)
{
	timeBegin = clock();
	bool isGangBan = false;
	g_ErrorRegion.empty();
	strcpy_s(err_name[0],"其他");
	strcpy_s(err_name[1],"针孔");
	strcpy_s(err_name[2],"焊缝");
	strcpy_s(err_name[3],"边缘");
	strcpy_s(err_name[4],"宽度过窄");
	strcpy_s(err_name[5],"宽度过宽");

	int flag;
	flag=1;

	m_imgCount = imgCount;
	ErrorCount = 0;
	
	if (m_bIsCheckRegion == false)  //不同点：相机3的m_bIsCheckRegion为false
	{
		//		return 0;
	}
    SetImageData(imagedata);
   
	Hobject hThresholdRegion;
    HTuple  hRow1,hCol1,CheckRegionArea;
	Hobject hImageMean1,hImageMean2;									//
	
	Hobject hTempStoredRegion;//用于检测边缘贴标报警
	Hobject hTempOpening;
	Hobject hTempClosing;
	Hobject hTempComplement;
	Hobject hTagRegion;

	Hobject hProductRegion;
	
	//Hobject hRegionForWeld, hRegionForWeldComplment, hFillUpForWeld, hWeld;
	
		reduce_domain(m_himage,m_hCheckRegion,&hReduceImg);					//缩小定义域
		threshold(hReduceImg,&hThresholdRegion,0,gray_background);	//检测针孔用					//利用全局阀值分割图像。0:最小灰度值，40：最大灰度值
		threshold(hReduceImg,&hProductRegion,0,m_Gray_Product);    //150
		
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,1,100);
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,200,1);
		opening_rectangle1(hThresholdRegion,&hThresholdRegion,1,100);
		
		closing_rectangle1(hProductRegion,&hProductRegion,1,100);
		opening_rectangle1(hProductRegion,&hProductRegion,1,100);
		
		connection(hThresholdRegion,&hThresholdRegion);
		connection(hProductRegion,&hProductRegion);

		Hobject hFillUpRegion, hFillUpRegion2;
		//fill_up(hThresholdRegion,&hFillUpRegion);
		fill_up(hThresholdRegion,&hFillUpRegion);
		fill_up(hProductRegion,&hFillUpRegion2);

		area_center(m_hCheckRegion,&CheckRegionArea,&hRow1,&hCol1);			//计算被检测区域的面积和重心
		if(1 == m_lComeraIndex || 3 == m_lComeraIndex)
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1);	//功能：选择包括给定像素在内的所有区域。
			select_region_point(hFillUpRegion2,&hProductRegion,hRow1,hCol1);
		}
		else if (0 == m_lComeraIndex)    //左边的相机区域要靠右边一些
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1*1.5);
			select_region_point(hFillUpRegion2, &hProductRegion,hRow1,hCol1*1.5);
		}
		else if (2 == m_lComeraIndex)    //右边的相机区域要靠左边一些
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1/2);
			select_region_point(hFillUpRegion2,&hProductRegion,hRow1,hCol1/2);
		}
		copy_obj(hProductRegion,&hTempStoredRegion,1,1);
		//copy_obj(hThresholdRegion,&hTempStoredRegion,1,1);

		HTuple Rec2Row,Rec2Col, Rec2Row2, Rec2Col2; //Rec2Ra,Rec2Rb,Rec2Phi;
	//	HTuple ZhenKongArea;
		long objnumber;  //目标数量
	//	area_center(hZhenkongRegion,&ZhenKongArea,NULL,NULL);
		count_obj(hThresholdRegion,&objnumber);								// 功能：统计一个元组中的对象。不同点：相机3进去前objnumber没有值，出来后objnumber=0，其他相机是进去前objnumber没有值，出来后objnumber=1; 

	
		if (objnumber > 0)
		{
			isGangBan = true;
		}
		else
		{
			HTuple  hArea;
			HTuple  hMaxArea;
			area_center(hFillUpRegion,&hArea,&hRow1,&hCol1);				//计算被hFillUpRegion区域的面积和重心
			tuple_max(hArea,&hMaxArea);									//  功能：返回一个元组的最大元素。
		 
			//if (CheckRegionArea[0].D() < hMaxArea[0].D()*3)
			//{
				select_shape(hFillUpRegion,&hThresholdRegion,"area","and",hMaxArea[0],hMaxArea[0]);//  功能：根据图形特征选择区域。
				isGangBan = true;
				long area = 0;
				area_center(hThresholdRegion,&area, NULL, NULL);
				if(0 == area)
					isGangBan = false;
			//}
		}

		if (isGangBan)
		{
		imgAsses->AlarmFlag = true;

		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,600,1);   //填补被白道分隔的焊缝
		//opening_rectangle1(hThresholdRegion,&hThresholdRegion,5,200);     //防止边缘、蚊虫导致误报针孔
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,300,1);       //防止针孔、焊缝被分在上下两张图中
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,1,40);			//功能：关闭一个矩形结构基础的一个区域
		//减少边缘误报
		//erosion_rectangle1(hThresholdRegion,&hThresholdRegion,m_ErosionSize,1);	//功能：腐蚀一个矩形结构基础的一个区域。
		//用于求缺陷的x坐标
		smallest_rectangle1(hThresholdRegion,&Rec2Row,&Rec2Col,&Rec2Row2,&Rec2Col2);		// 功能：平行于坐标轴的包围某区域的矩形。
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,200,1);
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,1,200);
		Hobject hThreshRect;
		gen_rectangle1(&hThreshRect,Rec2Row,Rec2Col,Rec2Row2,Rec2Col2);
		reduce_domain(m_himage,hThreshRect,&hReduceImg);					//功能：缩小一个图像的区域。
		
		//固定阈值检测大洞
		Hobject hWeldThresh, hCopyWeldThresh;
		Hobject hRegionLeft, hComplement;
		long hWeldArea=0;
		copy_obj(hReduceImg, &hRegionLeft,1,1);     //
		threshold(hReduceImg,&hCopyWeldThresh,60,255);
		area_center(hCopyWeldThresh,&hWeldArea,NULL,NULL);
		if (hWeldArea>0)
		{
			connection(hCopyWeldThresh,&hWeldThresh);
			dilation_circle(hCopyWeldThresh,&hCopyWeldThresh,30);
			complement(hCopyWeldThresh,&hComplement);
			intersection(hComplement,hRegionLeft,&hRegionLeft);
		}
		
		//****************//
		
		mean_image(hReduceImg,&hImageMean1,3,3);
		mean_image(hReduceImg,&hImageMean2,3,101);
		dyn_threshold(hImageMean1,hImageMean2,&hThresholdRegion,m_Gray,"light");
		
		intersection(hRegionLeft, hThresholdRegion, &hThresholdRegion);   //把动态分割的区域跟剩下未分割的区域
		//threshold(hReduceImg,&hThresholdRegion,m_Gray,255);						//功能：利用全局阈值分割图像。
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,20,20);
		connection(hThresholdRegion,&hThresholdRegion);							//功能：计算一个区域相连接的部分		
		select_shape(hThresholdRegion,&hThresholdRegion,"area","and",m_area,70000);//  功能：根据图形特征选择区域。
	
		if (hWeldArea>0)
			concat_obj(hThresholdRegion, hWeldThresh, &hThresholdRegion);  //把之前固定阈值分割的区域加进去

		if (m_If_Check_Edge)
		{
			Hobject hClosingRegion;
			long tempArea = 0;
			closing_rectangle1(hTempStoredRegion,&hClosingRegion,1,m_Edge_Closing);
			difference(hClosingRegion,hTempStoredRegion,&hEdgeRegion);
			area_center(hEdgeRegion,&tempArea,NULL,NULL);
			if(tempArea>=1)
			{
				connection(hEdgeRegion,&hEdgeRegion);
				select_shape(hEdgeRegion,&hEdgeRegion,"area","and",m_Edge_Area,9999999);
				concat_obj(hThresholdRegion,hEdgeRegion,&hThresholdRegion);
				union1(hEdgeRegion,&hEdgeRegion);
			}
			//opening_rectangle1(hThresholdRegion,&hThresholdRegion,1,m_Edge_Opening);
			opening_rectangle1(hTempStoredRegion,&hTempOpening,1,m_Edge_Opening);
			difference(hTempStoredRegion,hTempOpening,&hTagRegion);
			area_center(hTagRegion,&tempArea,NULL,NULL);
			if (tempArea>=1)
			{
				connection(hTagRegion,&hTagRegion);
				select_shape(hTagRegion,&hTagRegion,"area","and",m_Edge_Area,9999999);
				concat_obj(hThresholdRegion,hTagRegion,&hThresholdRegion);
				union1(hTagRegion,&hTagRegion);
			}
			
		}

		//计算宽度并输出至文件
		long temRow1, temRow2, temCol1, temCol2;
		//threshold(hReduceImg,&hTempStoredRegion,0,40);
		copy_obj(hTempStoredRegion, &hTempClosing,1,1);
		if(0 != m_edgeOpenSize)
		{
			opening_rectangle1(hTempStoredRegion, &hTempClosing, 1, m_edgeOpenSize);
			if(0 != m_edgeCloseSize)
				closing_rectangle1(hTempClosing, &hTempClosing, 1, m_edgeCloseSize);
		}
		smallest_rectangle1(hTempClosing, &temRow1, &temCol1, &temRow2, &temCol2);
		currWidth = temCol2 - temCol1;
		if (currWidth==0)
		{
			smallest_rectangle1(hProductRegion,&temRow1, &temCol1, &temRow2, &temCol2);
			currWidth = temCol2 - temCol1;
		}
		//))))))))))//
		if (0==currWidth && TRUE == m_ifRecordWidth)
		{
			CString strFileName,str;
			str.Format("%d",currWidth);
			FILE *fp;
			//errno_t err;
			strFileName.Format("%s\\widtherror.txt",m_strModelDir);
			fp = fopen(strFileName,"ab");
			//err = fopen_s(&fp, strFileName,"ab");
			fprintf(fp,"相机号%d\t图像张号%d\t实测宽度%d\nR1=%d\tC1=%d\tR2=%d\tC2=%d\n",m_lComeraIndex,m_imgCount,currWidth,temRow1,temCol1,temRow2,temCol2);
			fclose(fp);
		}

		int store_index = imgCount % m_imgStored;
		img_stored_width[m_lComeraIndex][store_index] = currWidth;  //单张图像宽度，像素单位
		img_stored_f_width[m_lComeraIndex][store_index] = currWidth*m_HorRes;  //单张图像宽度，毫米单位
		int max_index;
		bool width_Exists;
		width_Exists = widthExists();
		if (m_ifDelayWidth)
		{
			if(width_Exists)
			{
				max_index = getMaxIndex();
				//imgAsses->Width = calculated_width_stored[max_index];     
				imgAsses->Calc_Width = calculated_f_width_stored[max_index];
				imgAsses->Width = currWidth;
				last_f_width = imgAsses->Calc_Width;
			}
			else
			{
				imgAsses->Calc_Width = last_f_width;
				imgAsses->Width = currWidth;
			}

		}
		else
		{
			max_index = getMaxIndex();
			//imgAsses->Width = calculated_width_stored[max_index];     
			imgAsses->Calc_Width = calculated_f_width_stored[max_index];
			imgAsses->Width = currWidth;
			//imgAsses->Width = imgCount;
		}
		
		if (TRUE == m_ifRecordWidth)
		{
			writeWidth();
		}
		
		//按面积排序
        HTuple hArea,tupleIndex;
		area_center(hThresholdRegion,&hArea,NULL,NULL);	 //计算被区域的面积和重心
		tuple_sort_index(hArea,&tupleIndex);			 //功能：将元组的元素分类并返回分类元组的目录。
		tuple_inverse(tupleIndex,&tupleIndex);			 //功能：将一个元组反置（反转）。
        
		long nCount;
		long nRow1, nCol1, nRow2, nCol2;
		count_obj(hThresholdRegion,&nCount);			// 功能：统计一个元组中的对象。不同点：相机3出来后nCount=0，其他相机是出来后nCount=3;

		
		RECT rect;
		long objarea;//目标区域的面积
		double CenterRow,CenterCol;

		//****************************************************//
		CString pComment;
		int density = 0;
		int Pinhole_Occ = 0;
		int Weld_Occ = 0;
		int Edge_Occ = 0;
		for (int i=0; i<nCount && i<m_ErrorNum; i++) //计算 density
		{
			Hobject hselectobj;
			long    index;
			index = tupleIndex[i].L();//
			select_obj(hThresholdRegion,&hselectobj,index+1);
			area_center(hselectobj,&objarea,&CenterRow,&CenterCol);
			//ErrAssesInfo.ErrArea = objarea;
			int plus_density = 0;
			int err_class = 0;
			err_class = classify(hselectobj);
			if (2 == err_class)
			{
				Weld_Occ++;
			}
			else if(1==err_class)
			{
				plus_density = 1;
				Pinhole_Occ++;
			}
			else if (3 == err_class)
			{
				plus_density = 0;
				Edge_Occ++;
			}
		
			else	plus_density = 0; //未知缺陷类型
			density = density + plus_density; 
		}// 计算 density
		imgAsses->Defection = density;
		if (0 < Pinhole_Occ)
			pComment.Format("针孔%d个",Pinhole_Occ);
		//else if (0 < Edge_Occ)
		//	pComment.Format("边缘不平");
		else if (0 < Weld_Occ)
			pComment.Format("焊缝");
		else 
			pComment.Format("检测正常");

		if (density >= 1) // 报警标识
		{
			imgAsses->AlarmFlag = true;
			strcpy_s(imgAsses->Comment, pComment);
		}
		else
		{
			imgAsses->AlarmFlag = false;
			strcpy_s(imgAsses->Comment, pComment);
		}		

		if(m_IfRecordWidthErr)
		{
			m_IfWidth_Overbound = FALSE;
			if (imgAsses->Calc_Width > m_Width_Upbound || imgAsses->Calc_Width < m_Width_Downbound)  //如果宽度大于上限或者小于下限
			{
				m_IfWidth_Overbound = TRUE;
				if(imgAsses->AlarmFlag == false)
				{
					if(imgAsses->Calc_Width > m_Width_Upbound)
						strcpy_s(imgAsses->Comment, "宽度过宽");
					if(imgAsses->Calc_Width < m_Width_Downbound)
						strcpy_s(imgAsses->Comment, "宽度过窄");
				}
					
				imgAsses->AlarmFlag = true;
			}
		}
		//跳过临近区域的缺陷
		//int distance;	//缺陷距离
		//long errorLoc[500][2];	//缺陷坐标
		//bool isRetErr=true;
		//distance=m_ErrorDistance;
		//m_errLocCount = 0;
		//for(int i=0;i<500;i++)
		//	for(int j=0;j<2;j++)
		//		errorLoc[i][j]=0;

		for (int i =0; i < nCount && i < m_ErrorNum; i++)
		{
			Hobject hselectobj;
			long    index;
			index = tupleIndex[i].L();//D是什么函数
			select_obj(hThresholdRegion,&hselectobj,index+1);				//功能：从一个目标元组中选择目标。
			
			area_center(hselectobj,&objarea,&CenterRow,&CenterCol);			//计算区域的面积和重心
			smallest_rectangle1(hselectobj, &nRow1, &nCol1, &nRow2, &nCol2);// 功能：平行于坐标轴的包围某区域的矩形。

			int err_class;
			err_class = classify(hselectobj);
			if (nRow1 == nRow2)
			{
				if (nRow1 == m_lHeight)
				{
					nRow1 = m_lHeight -1;
				}
				else
				{
					nRow2 = nRow1+1;
				}
			}
			if (nCol1 == nCol2)
			{
				if (nCol1 == m_lWidth)
				{
					nCol1 = m_lWidth -1;
				}
				else
				{
					nCol2 = nCol1+1;
				}
			}
			/*if(TRUE == m_isCheckErrDistance)
			{
				for(int j=0;j<m_errLocCount;j++)
				{
					long temp1=abs(errorLoc[j][0]-(long)CenterRow);
					long temp2=abs(errorLoc[j][1]-(long)CenterCol);
					long temp1s=temp1*temp1;
					long temp2s=temp2*temp2;
					long dist=(long)sqrt((double)(temp1s+temp2s));
					if(dist<=distance)
						isRetErr=false;
				}
			}*/
			//if(isRetErr)
			{
				if((1==err_class) || (2==err_class) ||((3==err_class)&&m_If_Check_Edge))
				{
					rect = CRect(nCol1, nRow1, nCol2+1, nRow2+1);
					//存放错误的链表
					g_ErrorRegion[ErrorCount].nRegionType = 0;  
					g_ErrorRegion[ErrorCount].ErrorArea = objarea*m_HorRes*m_VerRes;
					g_ErrorRegion[ErrorCount].Diameter = (nCol2-nCol1)*m_HorRes;
					//g_ErrorRegion[ErrorCount].ErrorArea = 99.99;
					//g_ErrorRegion[ErrorCount].Diameter = 99.99;

					g_ErrorRegion[ErrorCount].Errortype = err_class;    //1表示针孔，2表示焊缝
					strcpy_s(g_ErrorRegion[ErrorCount].strErrortype,err_name[err_class]);
					g_ErrorRegion[ErrorCount].nLevel = (int)(objarea/m_area);
					g_ErrorRegion[ErrorCount].rect = rect;
					g_ErrorRegion[ErrorCount].x = CenterCol - Rec2Col[0].D();
					//	g_ErrorRegion[ErrorCount].x = 0;
					g_ErrorRegion[ErrorCount++].y = CenterRow;	
					//g_ErrorRegion[ErrorCount++].y = CenterRow;
				}	

			}
			//isRetErr = true;
	
		}  //for (int i =0; i < nCount && i < m_ErrorNum; i++)

		if (m_IfRecordWidthErr && m_IfWidth_Overbound && width_Exists)  //记录宽度缺陷
		{
			rect = CRect(temCol1, temRow1, temCol2+1, temRow2+1);
			g_ErrorRegion[ErrorCount].nRegionType = 0;
			g_ErrorRegion[ErrorCount].ErrorArea = imgAsses->Calc_Width - m_ProductWidth;
			g_ErrorRegion[ErrorCount].Diameter = imgAsses->Width;
			if(imgAsses->Calc_Width < m_Width_Downbound)
				g_ErrorRegion[ErrorCount].Errortype = 4;
			else if(imgAsses->Calc_Width > m_Width_Upbound)
				g_ErrorRegion[ErrorCount].Errortype = 5;
			strcpy_s(g_ErrorRegion[ErrorCount].strErrortype, err_name[4]);
			g_ErrorRegion[ErrorCount].rect = rect;
			g_ErrorRegion[ErrorCount].x = (int)(temCol2/2);
			g_ErrorRegion[ErrorCount++].y = (int)(temRow2/2);
		}
		} //if(isGangBan)

	*ErrorVector = &g_ErrorRegion;
	timeEnd = clock();
	timeConsume = timeEnd - timeBegin;
	writeTime();
	return 1;
}

int  CCheck::getMaxIndex()
{
	//add up
	for (int i = 0; i < m_imgStored; i++)
	{
		calculated_width_stored[i] = 0;
		calculated_f_width_stored[i] = 0;
		for (int j = 0; j < CAMERA_NUM; j++)
		{
			calculated_width_stored[i] = calculated_width_stored[i] + img_stored_width[j][i];
			calculated_f_width_stored[i] = calculated_f_width_stored[i] + img_stored_f_width[j][i];
		}
		calculated_width_stored[i] = calculated_width_stored[i] + m_extraPix;
		calculated_f_width_stored[i] = calculated_f_width_stored[i] + m_ExtraWidth;
	}
	//get max
	int maxIndex = 0;
	for (int i = 1; i < m_imgStored; i++)
	{
		if (calculated_width_stored[maxIndex] < calculated_width_stored[i])
			maxIndex = i;
	}
	return maxIndex;
}

bool CCheck::widthExists()
{
	for (int i = 0; i < m_imgStored; i++)
	{
		bool flag = true;  
		for (int j = 0; j <= TotalCameraNum; j++)
		{
			if(0 == img_stored_width[j][i])
				flag = false;
		}
		if(flag)
			return true;
	}
	return false;
}


bool CCheck::Free()
{
	return true;
}

void CCheck::showImage(Hobject &hImgInput)
{
	/*HWindow wnd1("");
	wnd1.OpenWindow(0,0,800,800,0);
	wnd1.Display(hImgInput);
	wnd1.Click();*/
}