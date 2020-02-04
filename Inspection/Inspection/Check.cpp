// Check.cpp: implementation of the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Shlwapi.h"  //����
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



//��������������С
const long MAX_COMMAND_SIZE = 10000;
//��ȡMAC������
char szFetCmd[] = "ipconfig /all";
//����MAC��ַ��ǰ����Ϣ
const string str4Search = "Physical Address. . . . . . . . . : ";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheck::CCheck()
{
	m_bChangeLap = TRUE;  //add by qq
	//��ʼ������
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
	gen_image1_extern(&m_himage, "byte", m_lWidth, m_lHeight, (long)imagedata,NULL);//�Ӵ��洢��������ص�һ��ָ�봴��һ��ͼ��,imagedataΪ����ָ�룬ClearProc
	
	mirror_image(m_himage,&m_himage,"row");//����һ��ͼ��
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
	//WritePrivateProfileString("���",str2,str,strFileName);
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
  //����ͼ��
  CString strFileName,str;
  CString commonFileName;
  strFileName.Format("%s\\ModelImage-%d.bmp",m_strModelDir,m_lComeraIndex);
  write_image(m_himage,"bmp",0,strFileName);
  //��������
  strFileName.Format("%s\\CheckRegion-%d.region",m_strModelDir,m_lComeraIndex);
  write_region(m_hCheckRegion,strFileName);
  //���������
  strFileName.Format("%s\\checkpara-%d.ini",m_strModelDir,m_lComeraIndex);
  commonFileName.Format("%s\\checkpara-all.ini",m_strModelDir);
  str.Format("%d", m_Gray);
  WritePrivateProfileString("����������Ϣ", "�Աȶ�", str, strFileName);
  str.Format("%d", m_area);
  WritePrivateProfileString("����������Ϣ", "������", str, strFileName);
  str.Format("%d", m_ErrorNum);
  WritePrivateProfileString("����������Ϣ", "ȱ�ݸ���", str, strFileName);
  //add by qq
  str.Format("%d", m_uploc);
  WritePrivateProfileString("����������Ϣ", "�϶�λ", str, strFileName);
  str.Format("%d", m_leftloc);
  WritePrivateProfileString("����������Ϣ", "��λ", str, strFileName);
  str.Format("%d", m_downloc);
  WritePrivateProfileString("����������Ϣ", "�¶�λ", str, strFileName);
  str.Format("%d", m_rightloc);
  WritePrivateProfileString("����������Ϣ", "�Ҷ�λ", str, strFileName);
  str.Format("%ld", m_berrorarea);
  WritePrivateProfileString("����������Ϣ", "�������", str, strFileName);

  str.Format("%d", m_bheight);
  WritePrivateProfileString("����������Ϣ", "ͼ��߶�", str, strFileName);
  str.Format("%d", m_bwidth);
  WritePrivateProfileString("����������Ϣ", "ͼ����", str, strFileName);

  str.Format("%d", m_CameraPosition);
  WritePrivateProfileString("����������Ϣ", "���λ��", str, strFileName);

  str.Format("%d", m_edgeOpenSize);
  WritePrivateProfileString("����������Ϣ", "����ë��", str, strFileName);
  str.Format("%d", m_edgeCloseSize);
  WritePrivateProfileString("����������Ϣ", "�ȱ��", str, strFileName);
  str.Format("%d", m_imgStored);
  WritePrivateProfileString("����������Ϣ", "Ԥ������", str, strFileName);
  str.Format("%d", m_extraPix);
  WritePrivateProfileString("����������Ϣ", "�ص�����", str, commonFileName);
  str.Format("%.2f", m_ExtraWidth);
  WritePrivateProfileString("����������Ϣ", "�ص����", str, commonFileName);
  str.Format("%d", m_ifRecordWidth);
  WritePrivateProfileString("����������Ϣ", "��¼���", str, strFileName);
 /* str.Format("%d", m_isCheckErrDistance);
  WritePrivateProfileString("����������Ϣ", "ȱ�ݼ�����", str, strFileName);*/
  /*str.Format("%d", m_ErrorDistance);
  WritePrivateProfileString("����������Ϣ", "ȱ�ݼ��", str, strFileName);*/
  str.Format("%f", m_HorRes);
  WritePrivateProfileString("����������Ϣ", "����ֱ���", str, strFileName);
  str.Format("%f", m_VerRes);
  WritePrivateProfileString("����������Ϣ", "����ֱ���", str, strFileName);
  str.Format("%d", gray_background);
  WritePrivateProfileString("����������Ϣ", "������򱳾�", str, strFileName);
  str.Format("%d", m_Gray_Product);
  WritePrivateProfileString("����������Ϣ", "��ʵ�����Ҷ�", str, strFileName);
  str.Format("%f", m_ProductWidth);
  WritePrivateProfileString("����������Ϣ", "��Ʒ��ƿ��", str, commonFileName);
  str.Format("%d", m_fake_width);
  WritePrivateProfileString("����������Ϣ", "����", str, strFileName);

  str.Format("%d", m_If_Check_Edge);
  WritePrivateProfileString("����������Ϣ", "�Ƿ������", str, strFileName);
  str.Format("%d", m_Edge_Opening);
  WritePrivateProfileString("����������Ϣ", "���ѿ������߶�", str, strFileName);
  str.Format("%d", m_Edge_Closing);
  WritePrivateProfileString("����������Ϣ", "���ѱղ����߶�", str, strFileName);
  str.Format("%d", m_Edge_Area);
  WritePrivateProfileString("����������Ϣ", "�������", str, strFileName);

  str.Format("%d", m_edge_width);
  WritePrivateProfileString("����������Ϣ", "����Width", str, strFileName);
  str.Format("%d", m_edge_height);
  WritePrivateProfileString("����������Ϣ", "����Height", str, strFileName);
  str.Format("%.2f",width_height_ratio);
  WritePrivateProfileString("����������Ϣ", "���ѿ�߱�", str, strFileName);

  str.Format("%d", m_ifDelayWidth);
  WritePrivateProfileString("����������Ϣ", "�Ƿ��ӳٿ��", str, commonFileName);
  str.Format("%d", m_IfRecordWidthErr);
  WritePrivateProfileString("����������Ϣ", "�Ƿ��¼���ȱ��", str, commonFileName);
  str.Format("%f", m_Width_Upbound);
  WritePrivateProfileString("����������Ϣ", "�������", str, commonFileName);
  str.Format("%f", m_Width_Downbound);
  WritePrivateProfileString("����������Ϣ", "�������", str, commonFileName);

  str.Format("%s", m_Lock_PassWord);
  WritePrivateProfileString("��������", "��������", str, commonFileName);
  str.Format("%d", m_Lock_Status);
  WritePrivateProfileString("��������", "����״̬", str, commonFileName);

  str.Format("%d", m_DebugMode);
  WritePrivateProfileString("���Բ���", "����ͼƬ", str, commonFileName);
  //end add		

//add by qq
  if (SetM->m_bRollChange)
  {
	  WritePrivateProfileString("����������Ϣ","��⺸��","1",strFileName);
  }
  else
  {
	  WritePrivateProfileString("����������Ϣ","��⺸��","0",strFileName);
  }
//end add 
}

// ��õ�ǰ��ִ���ļ�·��
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
	if (isEsit == TRUE) //���2ʱ��isEsit=1
	{
		read_image(&m_himage,strFileName);
	}
		
	//��ȡ����
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
		GetPrivateProfileInt("����������Ϣ", "�Աȶ�", 128, fileName);
	m_area = 
		GetPrivateProfileInt("����������Ϣ", "������", 10000, fileName);	
	//add by qq
	m_uploc = 
		GetPrivateProfileInt("����������Ϣ", "�϶�λ", 0, fileName);
	m_leftloc = 
		GetPrivateProfileInt("����������Ϣ", "��λ", 0, fileName);
	m_downloc = 
		GetPrivateProfileInt("����������Ϣ", "�¶�λ", 6000, fileName);
	m_rightloc = 
		GetPrivateProfileInt("����������Ϣ", "�Ҷ�λ", 2048, fileName);
	m_berrorarea =
		GetPrivateProfileInt("����������Ϣ", "�������", 1000, fileName);
	//end add

	m_bheight =
		GetPrivateProfileInt("����������Ϣ", "ͼ��߶�", 6000, fileName);
	m_bwidth =
		GetPrivateProfileInt("����������Ϣ", "ͼ����", 2048, fileName);

	m_CameraPosition =
		GetPrivateProfileInt("����������Ϣ", "���λ��", -1, fileName);
	//add by qq
	m_bChangeLap =
		GetPrivateProfileInt("����������Ϣ", "��⺸��", 0, fileName);
	//end add
	m_ErrorNum = 
		GetPrivateProfileInt("����������Ϣ", "ȱ�ݸ���", 5, fileName);	
	m_ErosionSize = 
		GetPrivateProfileInt("����������Ϣ", "�����߶�", 10, fileName);

	GetPrivateProfileString("����������Ϣ", "����ֱ���", NULL, pBuff,nMaxLen, fileName);
	m_HorRes = (float)atof(pBuff);
	GetPrivateProfileString("����������Ϣ", "����ֱ���", NULL, pBuff,nMaxLen, fileName);
	m_VerRes = (float)atof(pBuff);
	gray_background =
		GetPrivateProfileInt("����������Ϣ", "������򱳾�", 20, fileName);
	m_Gray_Product =
		GetPrivateProfileInt("����������Ϣ", "��ʵ�����Ҷ�", 10, fileName);
	m_edgeOpenSize =
		GetPrivateProfileInt("����������Ϣ", "����ë��", 50, fileName);
	m_edgeCloseSize = 
		GetPrivateProfileInt("����������Ϣ", "�ȱ��", 200, fileName);
	m_imgStored = 
		GetPrivateProfileInt("����������Ϣ", "Ԥ������", 50, fileName);
	m_ifRecordWidth =
		GetPrivateProfileInt("����������Ϣ", "��¼���", 1, fileName);
	/*m_isCheckErrDistance =
		GetPrivateProfileInt("����������Ϣ", "ȱ�ݼ�����", 1, fileName);*/
	/*m_ErrorDistance =
		GetPrivateProfileInt("����������Ϣ", "ȱ�ݼ��", 150, fileName);*/
	m_extraPix = 
		GetPrivateProfileInt("����������Ϣ", "�ص�����", 0, commonFileName);
	GetPrivateProfileString("����������Ϣ", "�ص����", NULL, pBuff, nMaxLen, commonFileName);
	m_ExtraWidth = (float)atof(pBuff);
	GetPrivateProfileString("����������Ϣ", "��Ʒ��ƿ��", NULL, pBuff, nMaxLen, commonFileName);
	m_ProductWidth = (float)atof(pBuff);
	m_fake_width =
		GetPrivateProfileInt("����������Ϣ","����", 0, fileName);

	GetPrivateProfileString("����������Ϣ", "���ѿ�߱�", NULL, pBuff, nMaxLen, fileName);
	width_height_ratio = (double)atof(pBuff);
	m_If_Check_Edge =
		GetPrivateProfileInt("����������Ϣ", "�Ƿ������", 1, fileName);
	m_Edge_Opening =
		GetPrivateProfileInt("����������Ϣ", "���ѿ������߶�", 1, fileName);
	m_Edge_Closing =
		GetPrivateProfileInt("����������Ϣ", "���ѱղ����߶�", 1, fileName);
	m_Edge_Area =
		GetPrivateProfileInt("����������Ϣ", "�������", 1, fileName);
	m_edge_width =
		GetPrivateProfileInt("����������Ϣ", "����Width", 1, fileName);
	m_edge_height =
		GetPrivateProfileInt("����������Ϣ", "����Height", 1, fileName);

	m_ifDelayWidth = 
		GetPrivateProfileInt("����������Ϣ", "�Ƿ��ӳٿ��", 1, commonFileName);
	m_IfRecordWidthErr =
		GetPrivateProfileInt("����������Ϣ", "�Ƿ��¼���ȱ��", 1, commonFileName);
	GetPrivateProfileString("����������Ϣ", "�������", NULL, pBuff, nMaxLen, commonFileName);
	m_Width_Upbound = (float)atof(pBuff);
	GetPrivateProfileString("����������Ϣ", "�������", NULL, pBuff, nMaxLen, commonFileName);
	m_Width_Downbound = (float)atof(pBuff);

	GetPrivateProfileString("��������", "��������", NULL, pBuff, nMaxLen, commonFileName);
	m_Lock_PassWord.Format("%s",pBuff);
	m_Lock_Status =
		GetPrivateProfileInt("��������", "����״̬",1, commonFileName);

	m_DebugMode =
		GetPrivateProfileInt("���Բ���", "����ͼƬ",0, commonFileName);
}

bool CCheck::GetMacByCmd(char *lpszMac)
{
  //��ʼ������MAC��ַ������
    memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret;
	SECURITY_ATTRIBUTES sa; 
    HANDLE hReadPipe,hWritePipe;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE; 
				
//�����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if(!bret)
	{
		return FALSE;
	}
	//���������д�����Ϣ
	STARTUPINFO si; 
	//���ؽ�����Ϣ
    PROCESS_INFORMATION pi;
    si.cb = sizeof(STARTUPINFO); 
    GetStartupInfo(&si); 
    si.hStdError = hWritePipe; 
    si.hStdOutput = hWritePipe; 
    si.wShowWindow = SW_HIDE; //���������д���
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//������ȡ�����н���
	bret = CreateProcess (NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, 
		NULL, &si, &pi ); 
		
	char szBuffer[MAX_COMMAND_SIZE+1]; //�������������������
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
			//�ر����еľ��
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
			//��ȡMAC��ַ��
			strBuffer = strBuffer.substr(ipos+str4Search.length());
			ipos = strBuffer.find("\n");
			strBuffer = strBuffer.substr(0, ipos);
		}
	}
	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());
	//ȥ���м�ġ�00-50-EB-0F-27-82���м��'-'�õ�0050EB0F2782
	int j = 0;
	for(int i=0; i<strlen(szBuffer); i++)
	{
		if(szBuffer[i] != '-')
		{
			lpszMac[j] = szBuffer[i];
			j++;
		}
	}
	//�ر����еľ��
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
	//��ȡMAC
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
	WritePrivateProfileString("����������Ϣ", "ͼ��߶�", str, strFileName);
	str.Format("%d", width);
	WritePrivateProfileString("����������Ϣ", "ͼ����", str, strFileName);
	m_lWidth = width;
	m_lHeight = height;
	
    readmodel();
	g_ErrorRegion = vector<ErrorRegion>(m_ErrorNum+1);

	return true;
}

int CCheck::classify(const Halcon::Hobject &RegionForClassify)
{
	int retVal = 0;
	long objarea;//Ŀ����������
	double CenterRow,CenterCol;
	//double GrayMean, Deviation;
	long roiRow1, roiCol1, roiRow2, roiCol2;
	long regRow1, regCol1, regRow2, regCol2;
	long imgRow1, imgCol1, imgRow2, imgCol2;
	Hobject imgRectangle, imgForRegion;
	//double errRadius;
	double wh_ratio;
	bool isNearEdge = false;
	bool isNearLeft;  //��Ч���򿿽����Ϊtrue�������ұ�Ϊfalse
	bool isCenter;   //�ж�region�Ƿ��ڸְ��м䣬���Ǻ����һ������
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
	smallest_rectangle1(hReduceImg, &roiRow1, &roiCol1, &roiRow2, &roiCol2); //��Ե.
	if (roiCol1 < (m_lWidth-roiCol2))  //�ж���Ч������������߻����ұ�
		isNearLeft = true;
	else
		isNearLeft = false;
	smallest_rectangle1(RegionForClassify,&regRow1,&regCol1,&regRow2,&regCol2); //����������С����
	//����Сͼ
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
	wh_ratio = (double)(regCol2-regCol1)/(regRow2-regRow1);   //����� = ���/�߶�
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

	//m_CameraPosition:  0:��� 1:�м� 2:�ұ� 3:�������

	if(regCol1<50 && 0==m_CameraPosition)
		isNearEdge = true;
	if((m_lWidth-regCol2)<50 && 2==m_CameraPosition)
		isNearEdge = true;

	if(inter_with_tag>=1)  //��Ե.
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
	if(1 == retVal && objarea > m_berrorarea)  //����
		retVal = 2;
	return retVal;	
}
int CCheck::Check(const char *imagedata, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount)
{
	timeBegin = clock();
	bool isGangBan = false;
	g_ErrorRegion.empty();
	strcpy_s(err_name[0],"����");
	strcpy_s(err_name[1],"���");
	strcpy_s(err_name[2],"����");
	strcpy_s(err_name[3],"��Ե");
	strcpy_s(err_name[4],"��ȹ�խ");
	strcpy_s(err_name[5],"��ȹ���");

	int flag;
	flag=1;

	m_imgCount = imgCount;
	ErrorCount = 0;
	
	if (m_bIsCheckRegion == false)  //��ͬ�㣺���3��m_bIsCheckRegionΪfalse
	{
		//		return 0;
	}
    SetImageData(imagedata);
   
	Hobject hThresholdRegion;
    HTuple  hRow1,hCol1,CheckRegionArea;
	Hobject hImageMean1,hImageMean2;									//
	
	Hobject hTempStoredRegion;//���ڼ���Ե���걨��
	Hobject hTempOpening;
	Hobject hTempClosing;
	Hobject hTempComplement;
	Hobject hTagRegion;

	Hobject hProductRegion;
	
	//Hobject hRegionForWeld, hRegionForWeldComplment, hFillUpForWeld, hWeld;
	
		reduce_domain(m_himage,m_hCheckRegion,&hReduceImg);					//��С������
		threshold(hReduceImg,&hThresholdRegion,0,gray_background);	//��������					//����ȫ�ַ�ֵ�ָ�ͼ��0:��С�Ҷ�ֵ��40�����Ҷ�ֵ
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

		area_center(m_hCheckRegion,&CheckRegionArea,&hRow1,&hCol1);			//���㱻�����������������
		if(1 == m_lComeraIndex || 3 == m_lComeraIndex)
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1);	//���ܣ�ѡ����������������ڵ���������
			select_region_point(hFillUpRegion2,&hProductRegion,hRow1,hCol1);
		}
		else if (0 == m_lComeraIndex)    //��ߵ��������Ҫ���ұ�һЩ
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1*1.5);
			select_region_point(hFillUpRegion2, &hProductRegion,hRow1,hCol1*1.5);
		}
		else if (2 == m_lComeraIndex)    //�ұߵ��������Ҫ�����һЩ
		{
			select_region_point(hFillUpRegion,&hThresholdRegion,hRow1,hCol1/2);
			select_region_point(hFillUpRegion2,&hProductRegion,hRow1,hCol1/2);
		}
		copy_obj(hProductRegion,&hTempStoredRegion,1,1);
		//copy_obj(hThresholdRegion,&hTempStoredRegion,1,1);

		HTuple Rec2Row,Rec2Col, Rec2Row2, Rec2Col2; //Rec2Ra,Rec2Rb,Rec2Phi;
	//	HTuple ZhenKongArea;
		long objnumber;  //Ŀ������
	//	area_center(hZhenkongRegion,&ZhenKongArea,NULL,NULL);
		count_obj(hThresholdRegion,&objnumber);								// ���ܣ�ͳ��һ��Ԫ���еĶ��󡣲�ͬ�㣺���3��ȥǰobjnumberû��ֵ��������objnumber=0����������ǽ�ȥǰobjnumberû��ֵ��������objnumber=1; 

	
		if (objnumber > 0)
		{
			isGangBan = true;
		}
		else
		{
			HTuple  hArea;
			HTuple  hMaxArea;
			area_center(hFillUpRegion,&hArea,&hRow1,&hCol1);				//���㱻hFillUpRegion��������������
			tuple_max(hArea,&hMaxArea);									//  ���ܣ�����һ��Ԫ������Ԫ�ء�
		 
			//if (CheckRegionArea[0].D() < hMaxArea[0].D()*3)
			//{
				select_shape(hFillUpRegion,&hThresholdRegion,"area","and",hMaxArea[0],hMaxArea[0]);//  ���ܣ�����ͼ������ѡ������
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

		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,600,1);   //����׵��ָ��ĺ���
		//opening_rectangle1(hThresholdRegion,&hThresholdRegion,5,200);     //��ֹ��Ե���ó浼�������
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,300,1);       //��ֹ��ס����챻������������ͼ��
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,1,40);			//���ܣ��ر�һ�����νṹ������һ������
		//���ٱ�Ե��
		//erosion_rectangle1(hThresholdRegion,&hThresholdRegion,m_ErosionSize,1);	//���ܣ���ʴһ�����νṹ������һ������
		//������ȱ�ݵ�x����
		smallest_rectangle1(hThresholdRegion,&Rec2Row,&Rec2Col,&Rec2Row2,&Rec2Col2);		// ���ܣ�ƽ����������İ�Χĳ����ľ��Ρ�
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,200,1);
		closing_rectangle1(hThresholdRegion,&hThresholdRegion,1,200);
		Hobject hThreshRect;
		gen_rectangle1(&hThreshRect,Rec2Row,Rec2Col,Rec2Row2,Rec2Col2);
		reduce_domain(m_himage,hThreshRect,&hReduceImg);					//���ܣ���Сһ��ͼ�������
		
		//�̶���ֵ����
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
		
		intersection(hRegionLeft, hThresholdRegion, &hThresholdRegion);   //�Ѷ�̬�ָ�������ʣ��δ�ָ������
		//threshold(hReduceImg,&hThresholdRegion,m_Gray,255);						//���ܣ�����ȫ����ֵ�ָ�ͼ��
		//closing_rectangle1(hThresholdRegion,&hThresholdRegion,20,20);
		connection(hThresholdRegion,&hThresholdRegion);							//���ܣ�����һ�����������ӵĲ���		
		select_shape(hThresholdRegion,&hThresholdRegion,"area","and",m_area,70000);//  ���ܣ�����ͼ������ѡ������
	
		if (hWeldArea>0)
			concat_obj(hThresholdRegion, hWeldThresh, &hThresholdRegion);  //��֮ǰ�̶���ֵ�ָ������ӽ�ȥ

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

		//�����Ȳ�������ļ�
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
			fprintf(fp,"�����%d\tͼ���ź�%d\tʵ����%d\nR1=%d\tC1=%d\tR2=%d\tC2=%d\n",m_lComeraIndex,m_imgCount,currWidth,temRow1,temCol1,temRow2,temCol2);
			fclose(fp);
		}

		int store_index = imgCount % m_imgStored;
		img_stored_width[m_lComeraIndex][store_index] = currWidth;  //����ͼ���ȣ����ص�λ
		img_stored_f_width[m_lComeraIndex][store_index] = currWidth*m_HorRes;  //����ͼ���ȣ����׵�λ
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
		
		//���������
        HTuple hArea,tupleIndex;
		area_center(hThresholdRegion,&hArea,NULL,NULL);	 //���㱻��������������
		tuple_sort_index(hArea,&tupleIndex);			 //���ܣ���Ԫ���Ԫ�ط��ಢ���ط���Ԫ���Ŀ¼��
		tuple_inverse(tupleIndex,&tupleIndex);			 //���ܣ���һ��Ԫ�鷴�ã���ת����
        
		long nCount;
		long nRow1, nCol1, nRow2, nCol2;
		count_obj(hThresholdRegion,&nCount);			// ���ܣ�ͳ��һ��Ԫ���еĶ��󡣲�ͬ�㣺���3������nCount=0����������ǳ�����nCount=3;

		
		RECT rect;
		long objarea;//Ŀ����������
		double CenterRow,CenterCol;

		//****************************************************//
		CString pComment;
		int density = 0;
		int Pinhole_Occ = 0;
		int Weld_Occ = 0;
		int Edge_Occ = 0;
		for (int i=0; i<nCount && i<m_ErrorNum; i++) //���� density
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
		
			else	plus_density = 0; //δ֪ȱ������
			density = density + plus_density; 
		}// ���� density
		imgAsses->Defection = density;
		if (0 < Pinhole_Occ)
			pComment.Format("���%d��",Pinhole_Occ);
		//else if (0 < Edge_Occ)
		//	pComment.Format("��Ե��ƽ");
		else if (0 < Weld_Occ)
			pComment.Format("����");
		else 
			pComment.Format("�������");

		if (density >= 1) // ������ʶ
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
			if (imgAsses->Calc_Width > m_Width_Upbound || imgAsses->Calc_Width < m_Width_Downbound)  //�����ȴ������޻���С������
			{
				m_IfWidth_Overbound = TRUE;
				if(imgAsses->AlarmFlag == false)
				{
					if(imgAsses->Calc_Width > m_Width_Upbound)
						strcpy_s(imgAsses->Comment, "��ȹ���");
					if(imgAsses->Calc_Width < m_Width_Downbound)
						strcpy_s(imgAsses->Comment, "��ȹ�խ");
				}
					
				imgAsses->AlarmFlag = true;
			}
		}
		//�����ٽ������ȱ��
		//int distance;	//ȱ�ݾ���
		//long errorLoc[500][2];	//ȱ������
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
			index = tupleIndex[i].L();//D��ʲô����
			select_obj(hThresholdRegion,&hselectobj,index+1);				//���ܣ���һ��Ŀ��Ԫ����ѡ��Ŀ�ꡣ
			
			area_center(hselectobj,&objarea,&CenterRow,&CenterCol);			//������������������
			smallest_rectangle1(hselectobj, &nRow1, &nCol1, &nRow2, &nCol2);// ���ܣ�ƽ����������İ�Χĳ����ľ��Ρ�

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
					//��Ŵ��������
					g_ErrorRegion[ErrorCount].nRegionType = 0;  
					g_ErrorRegion[ErrorCount].ErrorArea = objarea*m_HorRes*m_VerRes;
					g_ErrorRegion[ErrorCount].Diameter = (nCol2-nCol1)*m_HorRes;
					//g_ErrorRegion[ErrorCount].ErrorArea = 99.99;
					//g_ErrorRegion[ErrorCount].Diameter = 99.99;

					g_ErrorRegion[ErrorCount].Errortype = err_class;    //1��ʾ��ף�2��ʾ����
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

		if (m_IfRecordWidthErr && m_IfWidth_Overbound && width_Exists)  //��¼���ȱ��
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