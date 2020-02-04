#ifndef __HalconCheck_HEAD__
#define __HalconCheck_HEAD__
#include <afx.h>
#include "HalconCpp.h"
#include "HCPPdl_ConfigIni.h"
using namespace HalconCpp;
_declspec(dllexport) void InitGlobalOnce ();
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box);
// Chapter: File
// Short Description: Parse a filename into directory, base filename, and extension 
void parse_filename (HTuple hv_FileName, HTuple *hv_BaseName, HTuple *hv_Extension, 
	HTuple *hv_Directory);
void HCheck (HObject ho_Image, HObject *ho_PreprocessImage, HTuple hv_IndexSN, HTuple hv_ShowHide, 
	HTuple hv_WindowHandle, HTuple hv_MessageHandle, HTuple *hv_ResultInfo, HTuple *hv_WindowInfo, 
	HTupleVector/*{eTupleVector,Dim=2}*/ *hvec_FeatureVals);
void InitCheck (HTuple hv_TestName, HTuple hv_CameraIndex, HTuple hv_ImageW, HTuple hv_ImageH, 
	HTuple *hv_MessageInHandle);
void CloseCheck (HTuple hv_MessageInHandle);

void getmessage (HObject *ho_EmptyObjects, HTuple hv_MessageHandle, HTuple *hv_GenParamKeys, 
	HTupleVector/*{eTupleVector,Dim=1}*/ *hvec_GenParamTuples, HTuple *hv_GenParamType);
void get_message_tuple_romove (HTuple hv_MessageHandle, HTuple hv_Key, HTuple *hv_TupleData);


void GetResult (HTuple hv_Resultstrs, HTuple *hv_ResultName, HTuple *hv_Resultstrs2);
void loglog (HTuple hv_MessageInHandle, HTuple hv_NewCreate, HTuple hv_logtxt);
void SaveImageThread (HObject ho_Image, HTuple hv_Format, HTuple hv_fillcolor, HTuple hv_filename);
#endif