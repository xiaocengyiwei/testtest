// Inspection.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include <stdio.h>

#include "stdafx.h"
#include "Resource.h"

#include "HalconCheck.h"

#include "Inspection.h"
#include<iostream>
#include<string>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CCheckCenter::CCheckCenter()
{
	HRESULT hr = S_OK;
	if (!InitializeCriticalSectionAndSpinCount(&m_sect, 0))//�������ΪInitializeCriticalSection��Ϊ��Ч�ʣ�����һ����ת����
	{
		hr =  HRESULT_FROM_WIN32(GetLastError());
	}

	if (FAILED(hr))
	{
		AtlThrow(hr);
	}	

	
}
	
CCheckCenter::~CCheckCenter()
{
	::DeleteCriticalSection(&m_sect); 
}
void  CCheckCenter::lock()
{

	::EnterCriticalSection(&m_sect);
	//m_locksect.Lock();
}
void CCheckCenter::unlock()
{
	::LeaveCriticalSection(&m_sect);
	//m_locksect.Unlock();
}


bool CCheckCenter::Init (HTuple TestName,int CameraIndex,int ImageW,int ImageH)
{
	CString Tesssss=TestName[0].S();
		lock();
	
	m_TestName=TestName;
	m_CameraIndex=CameraIndex;
	m_ImageW=ImageW;
	m_ImageH=ImageH;
	try
	{
		InitCheck (TestName, CameraIndex, ImageW, ImageH, &m_MessageHandle);
	}
	catch(...)
	{
		unlock();
		return false;
	}
	unlock();
	return true;
}

int CCheckCenter::HTupleToVector( 
	HTuple HTupV,vector<htupval> *val)
{
	HTuple hv_Types;
	TupleTypeElem(HTupV, &hv_Types);
	int lsize=hv_Types.Length();
	for(int i=0;i<lsize;i++)
	{
		htupval lstupval;
		if (0 != (HTuple(hv_Types[i])==4))
		{
			lstupval._type=TYPE_CStr;
			lstupval._s=(CString)(HTupV[i].S());
			lstupval._i=atoi(lstupval._s);
			lstupval._d=atof(lstupval._s);
			//string
		}
		else if (0 != (HTuple(hv_Types[i])==1))
		{
			lstupval._type=TYPE_INT;
			lstupval._i=HTupV[i].I();
			lstupval._d=(double)HTupV[i].I();
			lstupval._s.Format("%d",HTupV[i].I());
			//int
		}
		else if (0 != (HTuple(hv_Types[i])==2))
		{
			lstupval._type=TYPE_double;
			lstupval._d=HTupV[i].D();
			lstupval._i=(int)HTupV[i].D();
			lstupval._s.Format("%f",HTupV[i].D());
		}
		else
		{
			//����
			lstupval._type=TYPE_NULL;
			lstupval._d=0;
			lstupval._i=0;
			lstupval._s="";
		}
		val->push_back(lstupval);
	}
	return lsize;
}
int CCheckCenter::HTupleVectorToVector( 
	HTupleVector/*{eTupleVector,Dim=1}*/ HTupV,vector<vector<htupval>> *val)
{
	vector<htupval> lsval;
	int lsize=HTupV.Length();
	for (int i=0;i<lsize;i++)
	{
		lsval.clear();
		HTupleToVector(HTupV[i].T(),&lsval);
		val->push_back(lsval);
	}
	return lsize;
}
int CCheckCenter::HTupleVectorToVector( 
	HTupleVector/*{eTupleVector,Dim=2}*/ HTupV,vector<vector<vector<htupval>>> *val)
{
	vector<vector<htupval>> lsval;
	int lsize=HTupV.Length();
	for (int i=0;i<lsize;i++)
	{
		lsval.clear();
		HTupleVectorToVector(HTupV[i],&lsval);
		val->push_back(lsval);
	}
	return lsize;
}
void CCheckCenter::Check (HObject ho_Image, HObject *ho_PreprocessImage,
	bool showhide,HTuple IndexSN,HTuple hv_WindowHandle,CString* ResultInfo,
	vector<ErrorRegion>* outErrorVector)
{
	lock();
	int t1=GetTickCount();

	*ResultInfo="OK";
	try
	{
		HTuple hv_ResultInfo,hv_WindowInfo;
		HTupleVector hvec_FeatureVals(2);
		HCheck ( ho_Image, ho_PreprocessImage, IndexSN, showhide, 
			hv_WindowHandle, m_MessageHandle, &hv_ResultInfo,&hv_WindowInfo, &hvec_FeatureVals);
		*ResultInfo=(CString)(hv_ResultInfo.S());
		t1=GetTickCount()-t1;
		if(ddddmax<t1)
			ddddmax=t1;
		(*outErrorVector).clear();
		for (int i=0;i<hvec_FeatureVals.Length();i++)
		{
			ErrorRegion lsErrorVector;
			for (int j=0;j<hvec_FeatureVals[i].Length();j++)
			{
				HTuple lstup=hvec_FeatureVals[i][j].T();
				try
				{

					if (lstup.Length()>1)
					{	
						CString lstupstr=lstup[0].S();
						if(lstupstr=="Features_retResults_ErrorArea")
						{
							lsErrorVector.ErrorArea=lstup[1].D();
						}
						if(lstupstr=="Features_errAreaPix")
						{
							lsErrorVector.ErrorAreaPix=lstup[1].I();
						}
						else if(lstupstr=="Features_retResults_Diameter")
						{
							lsErrorVector.Diameter=lstup[1].D();
						}
						else if(lstupstr=="Features_retResults_ifTag")
						{
							lsErrorVector.ifTag =lstup[1].I();
						}
						else if(lstupstr=="Features_retResults_strErrortype")
						{
							lsErrorVector.strErrortype=_T(lstup[1].S());
						}
						else if(lstupstr=="Features_retResults_rectvals")
						{
							//errC1,errR1,errC2,errR2
							lsErrorVector.rect.left=lstup[1].I();
							lsErrorVector.rect.top=lstup[2].I();
							lsErrorVector.rect.right=lstup[3].I();
							lsErrorVector.rect.bottom=lstup[4].I();
						}
						else if(lstupstr=="Features_retResults_x")
						{
							lsErrorVector.x=lstup[1].I();
						}
						else if(lstupstr=="Features_retResults_y")
						{
							lsErrorVector.y=lstup[1].I();
						}
						else if(lstupstr=="Features_retResults_Alarm")
						{
							lsErrorVector.ifAlarm=lstup[1].I();
						}else if(lstupstr=="Features_retResults_ErrortypeID")
						{
							lsErrorVector.ErrorTypeID=lstup[1].S();
						}
						else
						{
							vector<htupval> val;
							HTupleToVector(lstup, &val);
						}
					}
				}
				catch (...)
				{
				}
				

			}
			(*outErrorVector).push_back(lsErrorVector);
		}
	}
	catch (HalconCpp::HException &HDevExpDefaultException)
	{
		HTuple hv_Exception;
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		TupleString(hv_Exception,"#",&hv_Exception);
		CString lsstr="";
		for (int i=0;i<hv_Exception.Length();i++)
		{
			lsstr=lsstr+hv_Exception[i].S();
		}
		*ResultInfo="error";
		HTuple  hv_DirName, hv_Seconds, hv_lsfile;
		CString lsfilePath="";
		lsfilePath.Format("ErrorImage%d",m_CameraIndex+1);
		m_Profiler.CreateMultiLevelPath(lsfilePath);
		DWORD aaa=GetTickCount();
		CString lsfile="";
		lsfile.Format("%s\\%d.bmp",lsfilePath,aaa);
		SaveImageThread(ho_Image,"bmp",0,(HTuple)lsfile);
	}
	catch (...)
	{
		*ResultInfo="error";
		HTuple  hv_DirName, hv_Seconds, hv_lsfile;
		CString lsfilePath="";
		lsfilePath.Format("ErrorImage%d",m_CameraIndex+1);
		m_Profiler.CreateMultiLevelPath(lsfilePath);
		DWORD aaa=GetTickCount();
		CString lsfile="";
		lsfile.Format("%s\\%d.bmp",lsfilePath,aaa);
		SaveImageThread(ho_Image,"bmp",0,(HTuple)lsfile);
		//DispMessagebyImage(hv_WindowHandle,"��ⱨ��",0,0,"red","true");
	}

	unlock();
}

void CCheckCenter::Check (HObject ho_Image, HObject *ho_PreprocessImage,
	bool showhide,HTuple IndexSN,HTuple hv_WindowHandle,
	CString *ResultInfo, vector<vector<vector<htupval>>> *outvals)
{
	*ResultInfo="OK";
	try
	{
		HTuple hv_ResultInfo,hv_WindowInfo;
		HTupleVector hvec_FeatureVals(2);
		HCheck ( ho_Image, ho_PreprocessImage, IndexSN, showhide, 
			hv_WindowHandle, m_MessageHandle, &hv_ResultInfo,&hv_WindowInfo, &hvec_FeatureVals);
		HTupleVectorToVector(hvec_FeatureVals,outvals);
		(*ResultInfo)=(CString)hv_ResultInfo[0].S();
	}
	catch (...)
	{
		*ResultInfo="error";
		HTuple  hv_DirName, hv_Seconds, hv_lsfile;
		CString lsfilePath="";
		lsfilePath.Format("ErrorImage%d",m_CameraIndex);
		m_Profiler.CreateMultiLevelPath(lsfilePath);
		DWORD aaa=GetTickCount();
		CString lsfile="";
		lsfile.Format("%s\\%d.bmp",lsfilePath,aaa);
		SaveImageThread(ho_Image,"bmp",0,(HTuple)lsfile);

	}

	
}
void CCheckCenter::Close ()
{
	try
	{
		CloseCheck (m_MessageHandle);
	}
	catch (...)
	{

	}

}
void CCheckCenter::getmessageHtupleromove (HTuple hv_MessageHandle, HTuple hv_Key, HTuple *hv_TupleData)
{
	get_message_tuple_romove (hv_MessageHandle, hv_Key,hv_TupleData);
}
HTuple CCheckCenter::getmessageHtupleromove ( HTuple hv_Key)
{
	HTuple hv_TupleData;
	get_message_tuple_romove (m_MessageHandle, hv_Key,&hv_TupleData);
	//TupleString(hv_TupleData,"#",&hv_TupleData);

	return hv_TupleData;
}
CString CCheckCenter::getmessageCStringromove ( HTuple hv_Key)
{
	HTuple hv_TupleData="";
	try
	{
		
		get_message_tuple_romove (m_MessageHandle, hv_Key,&hv_TupleData);
		TupleString(hv_TupleData,"#",&hv_TupleData);
	}
	catch (...)
	{
	}
	
	if (hv_TupleData.TupleLength()==0)
		return "";
	else
		return (CString)(hv_TupleData[0].S());
}


double CCheckCenter::getmessageDoubleromove ( HTuple hv_Key)
{
	return atof(getmessageCStringromove (hv_Key));
}
int CCheckCenter::getmessageIntromove ( HTuple hv_Key)
{
	return atoi(getmessageCStringromove (hv_Key));
}


void CCheckCenter::setmessageHtuple (HTuple hv_MessageHandle, HTuple hv_Key, HTuple hv_TupleData)
{
	SetMessageTuple(hv_MessageHandle, hv_Key,hv_TupleData);
}
void CCheckCenter::setmessageHtuple (HTuple hv_Key, HTuple hv_TupleData)
{
	SetMessageTuple(m_MessageHandle, hv_Key,hv_TupleData);
}
void CCheckCenter::getmessageHtuple (HTuple hv_MessageHandle, HTuple hv_Key, HTuple *hv_TupleData)
{
	GetMessageTuple(hv_MessageHandle, hv_Key,hv_TupleData);
}
void CCheckCenter::getmessageHtuple (HTuple hv_Key, HTuple* hv_TupleData)
{
	GetMessageTuple(m_MessageHandle, hv_Key,hv_TupleData);
}
HTuple CCheckCenter::getmessageHtuple (HTuple hv_Key)
{
	HTuple hv_TupleData;
	GetMessageTuple(m_MessageHandle, hv_Key,&hv_TupleData);
	return hv_TupleData;
}

CString CCheckCenter::getmessageCString ( HTuple hv_Key)
{
	HTuple hv_TupleData;
	GetMessageTuple(m_MessageHandle, hv_Key,&hv_TupleData);
	TupleString(hv_TupleData,"#",&hv_TupleData);
	if (hv_TupleData.TupleLength()==0)
		return "";
	else
		return (CString)(hv_TupleData[0].S());
}
double CCheckCenter::getmessageDouble ( HTuple hv_Key)
{
	return atof(getmessageCString(hv_Key));

}
int CCheckCenter::getmessageInt ( HTuple hv_Key)
{
	return atoi(getmessageCString(hv_Key));
}
void CCheckCenter::DispMessagebyImage (HTuple hv_WindowHandle, HTuple hv_String, 
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)

{
	try
	{
		disp_message (hv_WindowHandle,  hv_String, "image", hv_Row, hv_Column, hv_Color, hv_Box);
	}
	catch (...)
	{

	}


}

void CCheckCenter::DispMessage (HTuple hv_WindowHandle, HTuple hv_String, 
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)

{
	try
	{
		disp_message (hv_WindowHandle,  hv_String, "window", hv_Row, hv_Column, hv_Color, hv_Box);
	}
	catch (...)
	{

	}


}
void CCheckCenter::DispMessage (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)

{
	try
	{
		disp_message (hv_WindowHandle,  hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color, hv_Box);
	}
	catch (...)
	{

	}


}
//�ж�·���Ƿ����
BOOL CCheckCenter::IsPathExist(const CString &strPath)
{
	WIN32_FIND_DATA fd; 
	HANDLE hFind = FindFirstFile(strPath, &fd); 
	if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{ 
		FindClose(hFind);
		return TRUE; 
	} 
	else
	{
		FindClose(hFind); 
		return FALSE;
	}
}
BOOL CCheckCenter::IsFileExist(const CString &strFileName)
{
	CFileFind searcher;

	if(searcher.FindFile(strFileName))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CCheckCenter::CreateMultiLevelPath(CString &strPath)
{
	strPath.Replace("/","\\");
	CString tmpPath = strPath;
	CList<CString,CString&> FolderStrList;
	int nStrLen = 0;

	for(;;)
	{
		nStrLen = tmpPath.GetLength();
		if(nStrLen <= 0)
		{
			break;//��ͷ���ļ���
		}		

		BOOL bPathExist = FALSE;//��·���Ƿ��Ѿ�����
		bPathExist = IsPathExist(tmpPath);
		if(bPathExist)//���·������
		{
			break;//���Ѵ��ڵ�·���½��ļ���
		}

		//���·��������		
		//ÿ�ν�����һ���ļ��������

		int nPos = 0;
		nPos = tmpPath.ReverseFind('\\');//�Ӻ���ǰȷ���ļ�����
		if(nPos == -1)//�ѵ����һ���ļ�����
		{
			nPos = 0;//����һ���ļ��������
		}

		//���ļ��������
		CString tmpStr = tmpPath.Right(nStrLen - nPos);
		FolderStrList.AddHead(tmpStr);
		tmpPath.Delete(nPos, nStrLen - nPos);		
	}	

	//�����ļ���������˳����
	while(FolderStrList.IsEmpty() == FALSE)
	{
		tmpPath += FolderStrList.RemoveHead();
		BOOL bRet = FALSE;
		bRet = CreateDirectory(tmpPath, NULL);
		if(bRet == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}
void CCheckCenter::SaveImage(HObject Image,CString filename)
{

	try
	{
		filename.Replace("/","\\");
		CString lsPath=	filename.Mid(0,filename.ReverseFind('\\'));
		CreateMultiLevelPath(lsPath);

		int dd=filename.ReverseFind('.');
		if (dd>0)
		{
			CString type=filename.Mid(dd+1,filename.GetLength()-dd-1);
			WriteImage(Image,(HTuple)type, 0,(HTuple)filename);
		}
		else
		{
			WriteImage(Image,"bmp", 0,(HTuple)filename);
		}
	}
	catch (...)
	{
	}

	
	
}
CString CCheckCenter::Get_Result (HTuple hv_Resultstrs,  HTuple *hv_Resultstrs2)
{
	HTuple hv_ResultName;
	GetResult (hv_Resultstrs, &hv_ResultName, hv_Resultstrs2);
	return (CString) hv_ResultName.S();
}
void CCheckCenter::log_log (HTuple hv_logtxt,bool newcreate)
{

	loglog (m_MessageHandle,newcreate,hv_logtxt);
}
void CCheckCenter::Save_Image_Thread (HObject ho_Image, HTuple hv_Format, HTuple hv_fillcolor, HTuple hv_filename)
{
	SaveImageThread (ho_Image, hv_Format, hv_fillcolor, hv_filename);
}

void Init_Global_Once ()
{
	InitGlobalOnce ();
}