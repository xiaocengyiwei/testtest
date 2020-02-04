// Inspection.h : Inspection DLL ����ͷ�ļ�
//

#ifndef AFX_INSPECTION_HEAD__
#define AFX_INSPECTION_HEAD__
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#include "afxmt.h"
#include "resource.h"		// ������
#include "HalconCpp.h"
using namespace HalconCpp;
#include "../../Profiler/Profiler/Profiler.h"
#include "../../SimVision_Include/datatype.h"

//H_TYPE_INT (1).
//H_TYPE_REAL (2).
//H_TYPE_STRING (4).
#define TYPE_INT		1;
#define TYPE_double		2;
#define TYPE_CStr		4;
#define TYPE_NULL		0;
typedef struct  htupval
{
	CString _s;
	int _i;
	double _d;
	int	_type;
};



// CInspectionApp
// �йش���ʵ�ֵ���Ϣ������� Inspection.cpp
//
#define DLL_InspectionEXT _declspec(dllexport) 

class DLL_InspectionEXT CCheckCenter
{
public:
	CCheckCenter();//Ĭ�Ϲ��캯��add by qq
	CCheckCenter(int nIndex);
	virtual ~CCheckCenter();
public:
	HTuple m_MessageHandle;//��Ϣ��� �ڲ�������Կ��ֵ
	//HTuple m_OutMessageHandle;//��Ϣ��� ��Ҫ���ڻ�ȡ���ֵ
	HTuple m_TestName;
	int m_CameraIndex;
	int m_ImageW;
	int m_ImageH;
	///��ʼ��
	bool CCheckCenter::Init (HTuple TestName,int CameraIndex,int ImageW,int ImageH);

	void CCheckCenter::Check (HObject ho_Image, HObject *ho_PreprocessImage,
		bool showhide,HTuple IndexSN,HTuple hv_WindowHandle,
		CString *ResultInfo, vector<vector<vector<htupval>>> *outvals);
	void CCheckCenter::Check (HObject ho_Image, HObject *ho_PreprocessImage,
		bool showhide,HTuple IndexSN,HTuple hv_WindowHandle,CString* ResultInfo,
		vector<ErrorRegion>* outErrorVector);
	void Close ();
	int HTupleToVector(HTuple HTupV,vector<htupval> *val);
	int HTupleVectorToVector( 
		HTupleVector/*{eTupleVector,Dim=1}*/ HTupV,vector<vector<htupval>> *val);
	int HTupleVectorToVector( 
		HTupleVector/*{eTupleVector,Dim=2}*/ HTupV,vector<vector<vector<htupval>>> *val);
	void Save_Image_Thread (HObject ho_Image, HTuple hv_Format, HTuple hv_fillcolor, HTuple hv_filename);

public:
	void CCheckCenter::getmessageHtupleromove (HTuple hv_MessageHandle, HTuple hv_Key, HTuple *hv_TupleData);
	HTuple CCheckCenter::getmessageHtupleromove ( HTuple hv_Key);
	CString CCheckCenter::getmessageCStringromove ( HTuple hv_Key);
	double CCheckCenter::getmessageDoubleromove ( HTuple hv_Key);
public:
	int CCheckCenter::getmessageIntromove ( HTuple hv_Key);
	HTuple CCheckCenter::getmessageHtuple( HTuple hv_Key);
	CString CCheckCenter::getmessageCString ( HTuple hv_Key);
	double CCheckCenter::getmessageDouble( HTuple hv_Key);
	int CCheckCenter::getmessageInt ( HTuple hv_Key);
	void CCheckCenter::DispMessage (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
		HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
	void CCheckCenter::DispMessage (HTuple hv_WindowHandle, HTuple hv_String, 
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
	void CCheckCenter::setmessageHtuple (HTuple hv_MessageHandle, HTuple hv_Key, HTuple hv_TupleData);
	void CCheckCenter::setmessageHtuple (HTuple hv_Key, HTuple hv_TupleData);
	void CCheckCenter::getmessageHtuple (HTuple hv_MessageHandle, HTuple hv_Key, HTuple *hv_TupleData);
	void CCheckCenter::getmessageHtuple (HTuple hv_Key, HTuple* hv_TupleData);
	void CCheckCenter::SaveImage(HObject Image,CString filename);

	BOOL IsPathExist(const CString &strPath);
	BOOL IsFileExist(const CString &strFileName);
	BOOL CreateMultiLevelPath(CString &strPath);
	void CCheckCenter::DispMessagebyImage (HTuple hv_WindowHandle, HTuple hv_String, 
		HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
	CString Get_Result (HTuple hv_Resultstrs,  HTuple *hv_Resultstrs2);
	void log_log (HTuple hv_logtxt,bool newcreate);

private:
	int PreprocessType;
	CProfiler m_Profiler;
	HANDLE m_pParamhMutex;//��������

public:
	bool Init(int width,int height);
	void ChangeCheckRegion(int leftoffset, int rightoffset, int camIndex);
	bool Setting_model(vector<char *>imagedata, int CamNum);
	bool Free();
	int ddddmax;

	CCriticalSection m_locksect;
	CRITICAL_SECTION m_sect;
	int m_MutexIndex;
	void lock();
	void unlock();
};
extern DLL_InspectionEXT  void Init_Global_Once ();
#endif