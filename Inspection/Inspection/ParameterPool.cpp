#include "stdafx.h"
#include "ParameterPool.h"


extern CString strbefore;
extern CString strchanged;
//extern int BeforePara;
//extern int ChangedPara;
CParameterPool::CParameterPool(void)
{
	m_TotalInitCamNum = 0;
}

CParameterPool::~CParameterPool(void)
{
}

void CParameterPool::ZeroArrays()
{
	for (int i = 0; i < CAM_NUM; i++)
	{
		m_CamPos[i] = 0;
	}
}

void CParameterPool::Convert2Himage(const char *Image, int CamIndex)
{
	gen_image1_extern(&m_hOriginalImage[CamIndex], "byte", m_ImageWidth[CamIndex], m_ImageHeight, (long)Image,NULL);
	mirror_image(m_hOriginalImage[CamIndex],&m_hOriginalImage[CamIndex],"row");
}

void CParameterPool::GenCheckRegion()
{
	for (int i=0; i<CAM_NUM; i++)
	{
		gen_rectangle1(&m_hCheckRegion[i],0,m_ImgLeftOffset[i]-1,m_ImageHeight-1,m_ImgRightOffset[i]);
	}
}

void CParameterPool::GetCurrPath( char **path )
{
	char str[MAX_PATH], drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	strcpy_s(m_CurrPath,drive);
	*path = m_CurrPath;
}

void CParameterPool::InitSettingPath()
{
	char* dir = NULL;
	GetCurrPath(&dir);
	m_SettingDirPath.Format("%sSetting",dir);
	m_CameraParaPath.Format("%s\\Camera.ini",m_SettingDirPath);
	m_CheckParaPath[0].Format("%s\\ParametersNum1.ini",m_SettingDirPath);
	m_SurfaceParaPath[0].Format("%s\\SurfaceNum1.ini",m_SettingDirPath);
	m_CheckParaPath[1].Format("%s\\ParametersNum2.ini",m_SettingDirPath);
	m_SurfaceParaPath[1].Format("%s\\SurfaceNum2.ini",m_SettingDirPath);
	m_CheckParaPath[2].Format("%s\\ParametersNum3.ini",m_SettingDirPath);
	m_SurfaceParaPath[2].Format("%s\\SurfaceNum3.ini",m_SettingDirPath);
	m_CheckParaPath[3].Format("%s\\ParametersNum4.ini",m_SettingDirPath);
	m_SurfaceParaPath[3].Format("%s\\SurfaceNum4.ini",m_SettingDirPath);
	m_SystemParaPath.Format("%s\\SystemConfiguration\\system.ini",dir);
	m_ParaSetModel.Format("%s\\SetParaModel.ini",m_SettingDirPath);
}

void CParameterPool::ReadIntKey( int &data, CString strApp, CString strKey, CString filePath )
{
	data = GetPrivateProfileInt(strApp, strKey, 0, filePath);
}

void CParameterPool::ReadFloatKey(float &data, CString strApp, CString strKey, CString filePath)
{
	char* pBuff = new char[MAX_LEN];
	GetPrivateProfileString(strApp, strKey, NULL, pBuff, MAX_LEN, filePath);
	data = (float)atof(pBuff);
}

void CParameterPool::WriteIntKey( int data, CString strApp, CString strKey, CString filePath )
{
	CString strData;
	strData.Format("%d", data);
	WritePrivateProfileString(strApp, strKey, strData, filePath);
}

void CParameterPool::WriteFloatKey( float data, CString strApp, CString strKey, CString filePath )
{
	CString strData;
	strData.Format("%.6f", data);
	WritePrivateProfileString(strApp, strKey, strData, filePath);
}

void CParameterPool::LoadCameraPara( int Index )  //������� ��ȡ
{
	if (Index==2)
	{
		int asd=23;
	}
	CString strKeyName;
	strKeyName.Format("%d�����", Index+1);
	ReadIntKey(m_ImgLeftOffset[Index], "��߽�", strKeyName, m_CameraParaPath);
	ReadIntKey(m_ImgRightOffset[Index], "�ұ߽�", strKeyName, m_CameraParaPath);
	gen_rectangle1(&m_hCheckRegion[Index],0,m_ImgLeftOffset[Index]-1,m_ImageHeight-1,m_ImgRightOffset[Index]);
	ReadIntKey(m_CamPos[Index], "���λ��", strKeyName, m_CameraParaPath);
	ReadFloatKey(m_Resolution_W[Index], "����ֱ���", strKeyName, m_CameraParaPath);
	
}


void CParameterPool::SaveCameraPara( int Index )  //�������  ����
{
	CString strKeyName;
	strKeyName.Format("%d�����", Index+1);
	WriteIntKey(m_CamPos[Index], "���λ��", strKeyName, m_CameraParaPath);
	WriteIntKey(m_ImgLeftOffset[Index], "��߽�", strKeyName, m_CameraParaPath);
	WriteIntKey(m_ImgRightOffset[Index], "�ұ߽�", strKeyName, m_CameraParaPath);
	WriteFloatKey(m_Resolution_W[Index], "����ֱ���", strKeyName, m_CameraParaPath);

	//////////////////////////////////////////д��system.ini�ļ�  �����20180530
	CString strLKeyName,strRKeyName;
	strLKeyName.Format("���%d��߽�", Index+1);
	strRKeyName.Format("���%d�ұ߽�", Index+1);
	CString cfileName = "SystemConfiguration\\system.ini";
	CString cstr;
	
///////////////////////////////////////////////////////////////////////////////

	//CString cfileName = "SystemConfiguration\\system.ini";
	//CString cstr;
	//cstr.Format("%d",m_ImgLeftOffset[Index]);  	WritePrivateProfileString("CameraImageParameters","���1��߽�",cstr,cfileName);
	//cstr.Format("%d",m_ImgRightOffset[Index]);  	WritePrivateProfileString("CameraImageParameters","���1�ұ߽�",cstr,cfileName);
	//WriteIntKey(m_SetParaMothod,"�����趨ģʽ","ģʽ ",m_ParaSetModel);
	/*CString strData;
	strData.Format("%d", m_CamPos[Index]);				WritePrivateProfileString("���λ��", strKeyName, strData, m_CameraParaPath);
	strData.Format("%d", m_ImgLeftOffset[Index]);		WritePrivateProfileString("��߽�", strKeyName, strData, m_CameraParaPath);
	strData.Format("%d", m_ImgRightOffset[Index]);		WritePrivateProfileString("�ұ߽�", strKeyName, strData, m_CameraParaPath);*/

}
void CParameterPool::LoadSetModel()
{
	ReadIntKey(m_SetParaMothod,"�����趨ģʽ","ģʽ ",m_ParaSetModel);
}

void CParameterPool::SaveSetModel()
{
	WriteIntKey(m_SetParaMothod,"�����趨ģʽ","ģʽ ",m_ParaSetModel);
}

void CParameterPool::LoadCheckPara(int Index)   //������ ��ȡ
{
	char* pBuff = new char[MAX_LEN];
	//GetPrivateProfileString("�ֱ���", "����", NULL, pBuff, MAX_LEN, m_CheckParaPath);

	//m_Resolution_W = ReadFloatKey("�ֱ���", "����", m_CheckParaPath);
	ReadFloatKey(m_Resolution_H, "�ֱ���", "����", m_CheckParaPath[Index]);
	//[��������]
	ReadIntKey(m_PinHoleArea, "��������", "�׶��������", m_CheckParaPath[Index]);
	ReadIntKey(m_MaxReturnNum, "��������", "���ż�¼����", m_CheckParaPath[Index]);
	ReadIntKey(m_ProductGray, "��������", "��Ʒ�Ҷ�", m_CheckParaPath[Index]);
	ReadIntKey(m_PinHoleGray, "��������","�׶��Ҷ�",m_CheckParaPath[Index]);
	ReadIntKey(m_WeldArea_Min, "��������", "�������MIN", m_CheckParaPath[Index]);
	ReadIntKey(m_WeldArea_Max, "��������", "�������MAX",m_CheckParaPath[Index]);
	//[��Ե���]
	ReadIntKey(m_IfCheckEdge, "��Ե���", "�Ƿ����Ե", m_CheckParaPath[Index]);
	ReadIntKey(m_EdgeArea, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	ReadIntKey(m_EdgeWidth, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	ReadIntKey(m_EdgeDepth, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	//[ȱ�ݱ���]
	ReadIntKey(m_AlarmFlag[PINHOLE], "ȱ�ݱ���", "���",m_CheckParaPath[Index]);
	ReadIntKey(m_AlarmFlag[WELD], "ȱ�ݱ���", "����", m_CheckParaPath[Index]);
	ReadIntKey(m_AlarmFlag[EDGE], "ȱ�ݱ���", "��Ե",m_CheckParaPath[Index]);
	ReadIntKey(m_AlarmFlag[OTHER], "ȱ�ݱ���", "����",m_CheckParaPath[Index]);
	//[��¼ȱ��]
	ReadIntKey(m_IfRecord[PINHOLE], "��¼ȱ��", "���", m_CheckParaPath[Index]);
	ReadIntKey(m_IfRecord[WELD], "��¼ȱ��", "����", m_CheckParaPath[Index]);
	ReadIntKey(m_IfRecord[EDGE], "��¼ȱ��", "��Ե",m_CheckParaPath[Index]);
	ReadIntKey(m_IfRecord[OTHER], "��¼ȱ��", "����",m_CheckParaPath[Index]);
	//[���]
	ReadIntKey(m_WidthGray,"���","���Ҷ�",m_CheckParaPath[Index]);
	ReadIntKey(m_StoredNum,"���","��������",m_CheckParaPath[Index]);
	ReadFloatKey(m_Overlap_Width,"���","�ص����(mm)",m_CheckParaPath[Index]);

	//*********������********//
	//[��������]
	ReadIntKey(m_Surf_ProdGray_Low,"��������","��Ʒ�Ҷ�>",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ProdGray_High,"��������","��Ʒ�Ҷ�<",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ProdArea,"��������","��Ʒ���>",m_SurfaceParaPath[Index]);
	//[ȱ��ʶ��]
	
	ReadIntKey(m_Surf_MeanW1,"ȱ��ʶ��","MeanW1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_MeanH1,"ȱ��ʶ��","MeanH1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_MeanW2,"ȱ��ʶ��","MeanW2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_MeanH2,"ȱ��ʶ��","MeanH2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_CloseW,"ȱ��ʶ��","CloseW",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_CloseH,"ȱ��ʶ��","CloseH",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_EroseW,"ȱ��ʶ��","EroseW",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_EroseH,"ȱ��ʶ��","EroseH",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_DynThresh1,"ȱ��ʶ��","DynThresh1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DynMode_1,"ȱ��ʶ��","DynMode1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_W1,"ȱ��ʶ��","CloseW1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_H1,"ȱ��ʶ��","CloseH1",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_DynThresh2,"ȱ��ʶ��","DynThresh2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DynMode_2,"ȱ��ʶ��","DynMode2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_W2,"ȱ��ʶ��","CloseW2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_H2,"ȱ��ʶ��","CloseH2",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_DynThresh3,"ȱ��ʶ��","DynThresh3",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DynMode_3,"ȱ��ʶ��","DynMode3",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_1C3,"ȱ��ʶ��","Close1C3",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_2C3,"ȱ��ʶ��","Close2C3",m_SurfaceParaPath[Index]);
	
	ReadIntKey(m_Surf_DynThresh4,"ȱ��ʶ��","DynThresh4",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DynMode_4,"ȱ��ʶ��","DynMode4",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_1C4,"ȱ��ʶ��","Close1C4",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Close_2C4,"ȱ��ʶ��","Close2C4",m_SurfaceParaPath[Index]);


	ReadIntKey(m_Surf_Stripe_Close_WC5,"ȱ��ʶ��","Close_WC5",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Stripe_Close_HC5,"ȱ��ʶ��","Close_HC5",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Stripe_W1,"ȱ��ʶ��","Stripe_W1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Stripe_W2,"ȱ��ʶ��","Stripe_W2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Stripe_H1,"ȱ��ʶ��","Stripe_H1",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Stripe_H2,"ȱ��ʶ��","Stripe_H2",m_SurfaceParaPath[Index]);

	//[����ģʽ]
	//ReadIntKey(m_Surf_IfFastCheck,"����ģʽ","ʹ�ÿ���ģʽ",m_SurfaceParaPath);
	//ReadIntKey(m_Surf_ErrGray1,"����ģʽ","ȱ�ݻҶ�>",m_SurfaceParaPath);
	//ReadIntKey(m_Surf_ErrGray2,"����ģʽ","ȱ�ݻҶ�<",m_SurfaceParaPath);
	//[ȱ�ݳߴ�]
	ReadIntKey(m_Surf_Area_Min,"ȱ�ݳߴ�","��С���",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_Thresh_Deep,"ȱ�ݳߴ�","��ȱ����ֵ",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixS,"ȱ�ݳߴ�","��С����",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixM,"ȱ�ݳߴ�","��������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixL,"ȱ�ݳߴ�","�������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Thresh_Shallow,"ȱ�ݳߴ�","ǳȱ����ֵ",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixS,"ȱ�ݳߴ�","ǳС����",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixM,"ȱ�ݳߴ�","ǳ������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixL,"ȱ�ݳߴ�","ǳ������",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_Thresh_Deep2,"ȱ�ݳߴ�","��ȱ����ֵ2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixS2,"ȱ�ݳߴ�","��С����2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixM2,"ȱ�ݳߴ�","��������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepSizePixL2,"ȱ�ݳߴ�","�������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_Thresh_Shallow2,"ȱ�ݳߴ�","ǳȱ����ֵ2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixS2,"ȱ�ݳߴ�","ǳС����2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixM2,"ȱ�ݳߴ�","ǳ������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowSizePixL2,"ȱ�ݳߴ�","ǳ������2",m_SurfaceParaPath[Index]);



	//[ȱ������]
	ReadIntKey(m_Surf_DeepScoreS,"ȱ������","��С����",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepScoreM,"ȱ������","��������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepScoreL,"ȱ������","�������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreS,"ȱ������","ǳС����",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreM,"ȱ������","ǳ������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreL,"ȱ������","ǳ������",m_SurfaceParaPath[Index]);
	

	ReadIntKey(m_Surf_DeepScoreS2,"ȱ������","��С����2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepScoreM2,"ȱ������","��������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_DeepScoreL2,"ȱ������","�������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreS2,"ȱ������","ǳС����2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreM2,"ȱ������","ǳ������2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_ShallowScoreL2,"ȱ������","ǳ������2",m_SurfaceParaPath[Index]);

	

	ReadIntKey(m_Surf_VertLineScore,"ȱ������","����������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_HorLineScore,"ȱ������","����������",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_TotalScore,"ȱ������","ȱ���ܷ�",m_SurfaceParaPath[Index]);	

	//[ȱ���ܶ�]
// 	ReadIntKey(m_Surf_DensitySizeWidth,"ȱ���ܶ�","���",m_SurfaceParaPath);
// 	ReadIntKey(m_Surf_DensitySizeHeight,"ȱ���ܶ�","�߶�",m_SurfaceParaPath);
// 	ReadIntKey(m_Surf_DensityCount,"ȱ���ܶ�","����",m_SurfaceParaPath);
	//[�Ƿ���]
	ReadIntKey(m_Surf_IfDeepSTag,"�Ƿ���","��С",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfDeepMTag,"�Ƿ���","����",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfDeepLTag,"�Ƿ���","���",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowSTag,"�Ƿ���","ǳС",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowMTag,"�Ƿ���","ǳ��",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowLTag,"�Ƿ���","ǳ��",m_SurfaceParaPath[Index]);

	ReadIntKey(m_Surf_IfDeepSTag2,"�Ƿ���","��С2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfDeepMTag2,"�Ƿ���","����2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfDeepLTag2,"�Ƿ���","���2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowSTag2,"�Ƿ���","ǳС2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowMTag2,"�Ƿ���","ǳ��2",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfShallowLTag2,"�Ƿ���","ǳ��2",m_SurfaceParaPath[Index]);
	//ReadIntKey(m_Surf_IfDensityTag,"�Ƿ���","�ܼ�",m_SurfaceParaPath);

	ReadIntKey(m_Surf_IfVertLineTag,"�Ƿ���","������",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_IfHorLineTag,"�Ƿ���","������",m_SurfaceParaPath[Index]);
	//[����������ʱ��]
	ReadIntKey(m_Surf_AlarmLength,"����������ʱ��","��������ʱ��",m_SurfaceParaPath[Index]);
	ReadIntKey(m_Surf_TagLength,"����������ʱ��","����������",m_SurfaceParaPath[Index]);

	//[У׼]
	ReadFloatKey(m_Surf_Calib,"У׼","ֱ��У׼",m_SurfaceParaPath[Index]);
	ReadFloatKey(m_Surf_Calib2,"У׼","���У׼",m_SurfaceParaPath[Index]);
	//[���߸���]
	ReadFloatKey(m_fHorAndVorRatio,"���߸���","���ߺ��ݱ�",m_CheckParaPath[Index]);
	ReadIntKey(m_iRecordWidthLine,"���߸���","����ȥ��",m_CheckParaPath[Index]);
	ReadIntKey(m_iMinWidthGray,"���߸���","���ߵͻҶ�ֵ",m_CheckParaPath[Index]);
	ReadIntKey(m_iMaxWidthGray,"���߸���","���߸߻Ҷ�ֵ ",m_CheckParaPath[Index]);
	
	

	/*BeforePara=m_Surf_ProdGray_Low+m_Surf_ProdGray_High+m_Surf_ProdArea
		+m_Surf_MeanW1+m_Surf_MeanH1+m_Surf_MeanW2+m_Surf_MeanH2+m_Surf_CloseW+m_Surf_CloseH+m_Surf_EroseW+m_Surf_EroseH
		+m_Surf_DynThresh1+m_Surf_DynMode_1+m_Surf_Close_W1+m_Surf_Close_H1
		+m_Surf_DynThresh2+m_Surf_DynMode_2+m_Surf_Close_W2+m_Surf_Close_H2
		+m_Surf_DynThresh3+m_Surf_DynMode_3+m_Surf_Close_1C3+m_Surf_Close_2C3
		+m_Surf_DynThresh4+m_Surf_DynMode_4+m_Surf_Close_1C4+m_Surf_Close_2C4
		+m_Surf_Stripe_Close_WC5+m_Surf_Stripe_Close_HC5+m_Surf_Stripe_W1+m_Surf_Stripe_W2+m_Surf_Stripe_H1+m_Surf_Stripe_H2
		+m_Surf_DeepScoreS+m_Surf_DeepScoreM+m_Surf_DeepScoreL+m_Surf_ShallowScoreS+m_Surf_ShallowScoreM+m_Surf_ShallowScoreL
		+m_Surf_DeepScoreS2+m_Surf_DeepScoreM2+m_Surf_DeepScoreL2+m_Surf_ShallowScoreS2+m_Surf_ShallowScoreM2+m_Surf_ShallowScoreL2
		+m_Surf_VertLineScore+m_Surf_HorLineScore+m_Surf_TotalScore
		+m_Surf_Area_Min+m_Surf_Thresh_Deep+m_Surf_DeepSizePixS+m_Surf_DeepSizePixM+m_Surf_DeepSizePixL
		+m_Surf_Thresh_Shallow+m_Surf_ShallowSizePixS+m_Surf_ShallowSizePixM+m_Surf_ShallowSizePixL
		+m_Surf_Thresh_Deep2+m_Surf_DeepSizePixS2+m_Surf_DeepSizePixM2+m_Surf_DeepSizePixL2
		+m_Surf_Thresh_Shallow2+m_Surf_ShallowSizePixS2+m_Surf_ShallowSizePixM2+m_Surf_ShallowSizePixL2
		+m_iRecordWidthLine+m_Surf_IfDeepSTag+m_Surf_IfDeepMTag+m_Surf_IfDeepLTag+m_Surf_IfShallowSTag+m_Surf_IfShallowMTag+m_Surf_IfShallowLTag
		+m_Surf_IfDeepSTag2+m_Surf_IfDeepMTag2+m_Surf_IfDeepLTag2+m_Surf_IfShallowSTag2+m_Surf_IfShallowMTag2+m_Surf_IfShallowLTag2
		+m_Surf_IfVertLineTag+m_Surf_IfHorLineTag;*/
	//CString str71,str72,str73,str74,str75,str76,str77,str78,str79,str80;
	///////////////////////////////////////////////////
	///////////////////////////////bool////////////////
	//str71.Format("%d",m_Surf_IfShallowMTag);
	//str72.Format("%d",m_Surf_IfShallowLTag);
	//str73.Format("%d",m_Surf_IfDeepSTag2);
	//str74.Format("%d",m_Surf_IfDeepMTag2);
	//str75.Format("%d",m_Surf_IfDeepLTag2);
	//str76.Format("%d",m_Surf_IfShallowSTag2);
	//str77.Format("%d",m_Surf_IfShallowMTag2);
	//str78.Format("%d",m_Surf_IfShallowLTag2);
	//str79.Format("%d",m_Surf_IfVertLineTag);
	//str80.Format("%d",m_Surf_IfHorLineTag);
	///////////////////////////////////////////////////
	///////////////////////////////bool////////////////

	//CString str61,str62,str63,str64,str65,str66,str67,str68,str69,str70;
	//str61.Format("%d",m_Surf_DeepSizePixL2);
	//str62.Format("%d",m_Surf_Thresh_Shallow2);
	//str63.Format("%d",m_Surf_ShallowSizePixS2);
	//str64.Format("%d",m_Surf_ShallowSizePixM2);
	//str65.Format("%d",m_Surf_ShallowSizePixL2);


	///////////////////////////////////////////////////
	///////////////////////////////bool////////////////
	//str66.Format("%d",m_iRecordWidthLine);
	//str67.Format("%d",m_Surf_IfDeepSTag);
	//str68.Format("%d",m_Surf_IfDeepMTag);
	//str69.Format("%d",m_Surf_IfDeepLTag);
	//str70.Format("%d",m_Surf_IfShallowSTag);
	///////////////////////////////////////////////////
	///////////////////////////////bool////////////////

	//CString str51,str52,str53,str54,str55,str56,str57,str58,str59,str60;
	//str51.Format("%d",m_Surf_DeepSizePixS);
	//str52.Format("%d",m_Surf_DeepSizePixM);
	//str53.Format("%d",m_Surf_DeepSizePixL);
	//str54.Format("%d",m_Surf_Thresh_Shallow);
	//str55.Format("%d",m_Surf_ShallowSizePixS);
	//str56.Format("%d",m_Surf_ShallowSizePixM);
	//str57.Format("%d",m_Surf_ShallowSizePixL);
	//str58.Format("%d",m_Surf_Thresh_Deep2);
	//str59.Format("%d",m_Surf_ShallowSizePixS2);
	//str60.Format("%d",m_Surf_DeepSizePixM2);

	//CString str41,str42,str43,str44,str45,str46,str47,str48,str49,str50;
	//str41.Format("%d",m_Surf_DeepScoreM2);
	//str42.Format("%d",m_Surf_DeepScoreL2);
	//str43.Format("%d",m_Surf_ShallowScoreS2);
	//str44.Format("%d",m_Surf_ShallowScoreM2);
	//str45.Format("%d",m_Surf_ShallowScoreL2);
	//str46.Format("%d",m_Surf_VertLineScore);
	//str47.Format("%d",m_Surf_HorLineScore);
	//str48.Format("%d",m_Surf_TotalScore);
	//str49.Format("%d",m_Surf_Area_Min);
	//str50.Format("%d",m_Surf_Thresh_Deep);

	//CString str31,str32,str33,str34,str35,str36,str37,str38,str39,str40;
	//str31.Format("%d",m_Surf_Stripe_W2);
	//str32.Format("%d",m_Surf_Stripe_H1);
	//str33.Format("%d",m_Surf_Stripe_H2);
	//str34.Format("%d",m_Surf_DeepScoreS);
	//str35.Format("%d",m_Surf_DeepScoreM);
	//str36.Format("%d",m_Surf_DeepScoreL);
	//str37.Format("%d",m_Surf_ShallowScoreS);
	//str38.Format("%d",m_Surf_ShallowScoreM);
	//str39.Format("%d",m_Surf_ShallowScoreL);
	//str40.Format("%d",m_Surf_DeepScoreS2);


	//CString str21,str22,str23,str24,str25,str26,str27,str28,str29,str30;
	//str21.Format("%d",m_Surf_DynMode_3);
	//str22.Format("%d",m_Surf_Close_1C3);
	//str23.Format("%d",m_Surf_Close_2C3);
	//str24.Format("%d",m_Surf_DynThresh4);
	//str25.Format("%d",m_Surf_DynMode_4);
	//str26.Format("%d",m_Surf_Close_1C4);
	//str27.Format("%d",m_Surf_Close_2C4);
	//str28.Format("%d",m_Surf_Stripe_Close_WC5);
	//str29.Format("%d",m_Surf_Stripe_Close_HC5);
	//str30.Format("%d",m_Surf_Stripe_W1);

	//CString str12,str13,str14,str15,str16,str17,str18,str19,str20;
	//str12.Format("%d",m_Surf_DynThresh1);
	//str13.Format("%d",m_Surf_DynMode_1);
	//str14.Format("%d",m_Surf_Close_W1);
	//str15.Format("%d",m_Surf_Close_H1);
	//str16.Format("%d",m_Surf_DynThresh2);
	//str17.Format("%d",m_Surf_DynMode_2);
	//str18.Format("%d",m_Surf_Close_W2);
	//str19.Format("%d",m_Surf_Close_H2);
	//str20.Format("%d",m_Surf_DynThresh3);

	//CString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11;
	//str1.Format("%d",m_Surf_ProdGray_Low);
	//str2.Format("%d",m_Surf_ProdGray_High);
	//str3.Format("%d",m_Surf_ProdArea);
	//str4.Format("%d",m_Surf_MeanW1);
	//str5.Format("%d",m_Surf_MeanH1);
	//str6.Format("%d",m_Surf_MeanW2);
	//str7.Format("%d",m_Surf_MeanH2);
	//str8.Format("%d",m_Surf_CloseW);
	//str9.Format("%d",m_Surf_CloseH);
	//str10.Format("%d",m_Surf_EroseW);
	//str11.Format("%d",m_Surf_EroseH);
	//
	//CString str81;
	//str81.Format("%d",m_SetParaMothod);
	//	



	////CString str,str1;
	////str.Format("%d",m_Surf_ProdGray_High);
	////str1.Format("%d",m_Surf_ProdGray_Low);
	//strbefore.Append(str1);
	//strbefore.Append(str2);
	//strbefore.Append(str3);
	//strbefore.Append(str4);
	//strbefore.Append(str5);
	//strbefore.Append(str6);
	//strbefore.Append(str7);
	//strbefore.Append(str8);
	//strbefore.Append(str9);
	//strbefore.Append(str10);
	//strbefore.Append(str11);
	//strbefore.Append(str12);
	//strbefore.Append(str13);
	//strbefore.Append(str14);
	//strbefore.Append(str15);
	//strbefore.Append(str16);
	//strbefore.Append(str17);
	//strbefore.Append(str18);
	//strbefore.Append(str19);
	//strbefore.Append(str20);
	//strbefore.Append(str21);
	//strbefore.Append(str22);
	//strbefore.Append(str23);
	//strbefore.Append(str24);
	//strbefore.Append(str25);
	//strbefore.Append(str26);
	//strbefore.Append(str27);
	//strbefore.Append(str28);
	//strbefore.Append(str29);
	//strbefore.Append(str30);
	//strbefore.Append(str31);
	//strbefore.Append(str32);
	//strbefore.Append(str33);
	//strbefore.Append(str34);
	//strbefore.Append(str35);
	//strbefore.Append(str36);
	//strbefore.Append(str37);
	//strbefore.Append(str38);
	//strbefore.Append(str39);
	//strbefore.Append(str40);
	//strbefore.Append(str41);
	//strbefore.Append(str42);
	//strbefore.Append(str43);
	//strbefore.Append(str44);
	//strbefore.Append(str45);
	//strbefore.Append(str46);
	//strbefore.Append(str47);
	//strbefore.Append(str48);
	//strbefore.Append(str49);
	//strbefore.Append(str50);
	//strbefore.Append(str51);
	//strbefore.Append(str52);
	//strbefore.Append(str53);
	//strbefore.Append(str54);
	//strbefore.Append(str55);
	//strbefore.Append(str56);
	//strbefore.Append(str57);
	//strbefore.Append(str58);
	//strbefore.Append(str59);
	//strbefore.Append(str60);
	//strbefore.Append(str61);
	//strbefore.Append(str62);
	//strbefore.Append(str63);
	//strbefore.Append(str64);
	//strbefore.Append(str65);
	//strbefore.Append(str66);
	//strbefore.Append(str67);
	//strbefore.Append(str68);
	//strbefore.Append(str69);
	//strbefore.Append(str70);
	//strbefore.Append(str71);
	//strbefore.Append(str72);
	//strbefore.Append(str73);
	//strbefore.Append(str74);
	//strbefore.Append(str75);
	//strbefore.Append(str76);
	//strbefore.Append(str77);
	//strbefore.Append(str78);
	//strbefore.Append(str79);
	//strbefore.Append(str80);
	//strbefore.Append(str81);
	
}

CString CParameterPool::ClearLoadToStrB()
{
	return strbefore="";
}

CString CParameterPool::ClearLoadToStrC()
{
	return strchanged="";
}


CString CParameterPool::LoadToStrB()
{
	//strbefore="";
	CString str71,str72,str73,str74,str75,str76,str77,str78,str79,str80;
	/////////////////////////////////////////////////
	/////////////////////////////bool////////////////
	str71.Format("%d",m_Surf_IfShallowMTag);
	str72.Format("%d",m_Surf_IfShallowLTag);
	str73.Format("%d",m_Surf_IfDeepSTag2);
	str74.Format("%d",m_Surf_IfDeepMTag2);
	str75.Format("%d",m_Surf_IfDeepLTag2);
	str76.Format("%d",m_Surf_IfShallowSTag2);
	str77.Format("%d",m_Surf_IfShallowMTag2);
	str78.Format("%d",m_Surf_IfShallowLTag2);
	str79.Format("%d",m_Surf_IfVertLineTag);
	str80.Format("%d",m_Surf_IfHorLineTag);
	/////////////////////////////////////////////////
	/////////////////////////////bool////////////////

	CString str61,str62,str63,str64,str65,str66,str67,str68,str69,str70;
	str61.Format("%d",m_Surf_DeepSizePixL2);
	str62.Format("%d",m_Surf_Thresh_Shallow2);
	str63.Format("%d",m_Surf_ShallowSizePixS2);
	str64.Format("%d",m_Surf_ShallowSizePixM2);
	str65.Format("%d",m_Surf_ShallowSizePixL2);


	/////////////////////////////////////////////////
	/////////////////////////////bool////////////////
	str66.Format("%d",m_iRecordWidthLine);
	str67.Format("%d",m_Surf_IfDeepSTag);
	str68.Format("%d",m_Surf_IfDeepMTag);
	str69.Format("%d",m_Surf_IfDeepLTag);
	str70.Format("%d",m_Surf_IfShallowSTag);
	/////////////////////////////////////////////////
	/////////////////////////////bool////////////////

	CString str51,str52,str53,str54,str55,str56,str57,str58,str59,str60;
	str51.Format("%d",m_Surf_DeepSizePixS);
	str52.Format("%d",m_Surf_DeepSizePixM);
	str53.Format("%d",m_Surf_DeepSizePixL);
	str54.Format("%d",m_Surf_Thresh_Shallow);
	str55.Format("%d",m_Surf_ShallowSizePixS);
	str56.Format("%d",m_Surf_ShallowSizePixM);
	str57.Format("%d",m_Surf_ShallowSizePixL);
	str58.Format("%d",m_Surf_Thresh_Deep2);
	str59.Format("%d",m_Surf_ShallowSizePixS2);
	str60.Format("%d",m_Surf_DeepSizePixM2);

	CString str41,str42,str43,str44,str45,str46,str47,str48,str49,str50;
	str41.Format("%d",m_Surf_DeepScoreM2);
	str42.Format("%d",m_Surf_DeepScoreL2);
	str43.Format("%d",m_Surf_ShallowScoreS2);
	str44.Format("%d",m_Surf_ShallowScoreM2);
	str45.Format("%d",m_Surf_ShallowScoreL2);
	str46.Format("%d",m_Surf_VertLineScore);
	str47.Format("%d",m_Surf_HorLineScore);
	str48.Format("%d",m_Surf_TotalScore);
	str49.Format("%d",m_Surf_Area_Min);
	str50.Format("%d",m_Surf_Thresh_Deep);

	CString str31,str32,str33,str34,str35,str36,str37,str38,str39,str40;
	str31.Format("%d",m_Surf_Stripe_W2);
	str32.Format("%d",m_Surf_Stripe_H1);
	str33.Format("%d",m_Surf_Stripe_H2);
	str34.Format("%d",m_Surf_DeepScoreS);
	str35.Format("%d",m_Surf_DeepScoreM);
	str36.Format("%d",m_Surf_DeepScoreL);
	str37.Format("%d",m_Surf_ShallowScoreS);
	str38.Format("%d",m_Surf_ShallowScoreM);
	str39.Format("%d",m_Surf_ShallowScoreL);
	str40.Format("%d",m_Surf_DeepScoreS2);


	CString str21,str22,str23,str24,str25,str26,str27,str28,str29,str30;
	str21.Format("%d",m_Surf_DynMode_3);
	str22.Format("%d",m_Surf_Close_1C3);
	str23.Format("%d",m_Surf_Close_2C3);
	str24.Format("%d",m_Surf_DynThresh4);
	str25.Format("%d",m_Surf_DynMode_4);
	str26.Format("%d",m_Surf_Close_1C4);
	str27.Format("%d",m_Surf_Close_2C4);
	str28.Format("%d",m_Surf_Stripe_Close_WC5);
	str29.Format("%d",m_Surf_Stripe_Close_HC5);
	str30.Format("%d",m_Surf_Stripe_W1);

	CString str12,str13,str14,str15,str16,str17,str18,str19,str20;
	str12.Format("%d",m_Surf_DynThresh1);
	str13.Format("%d",m_Surf_DynMode_1);
	str14.Format("%d",m_Surf_Close_W1);
	str15.Format("%d",m_Surf_Close_H1);
	str16.Format("%d",m_Surf_DynThresh2);
	str17.Format("%d",m_Surf_DynMode_2);
	str18.Format("%d",m_Surf_Close_W2);
	str19.Format("%d",m_Surf_Close_H2);
	str20.Format("%d",m_Surf_DynThresh3);

	CString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11;
	str1.Format("%d",m_Surf_ProdGray_Low);
	str2.Format("%d",m_Surf_ProdGray_High);
	str3.Format("%d",m_Surf_ProdArea);
	str4.Format("%d",m_Surf_MeanW1);
	str5.Format("%d",m_Surf_MeanH1);
	str6.Format("%d",m_Surf_MeanW2);
	str7.Format("%d",m_Surf_MeanH2);
	str8.Format("%d",m_Surf_CloseW);
	str9.Format("%d",m_Surf_CloseH);
	str10.Format("%d",m_Surf_EroseW);
	str11.Format("%d",m_Surf_EroseH);

	CString str81;
	str81.Format("%d",m_SetParaMothod);




	//CString str,str1;
	//str.Format("%d",m_Surf_ProdGray_High);
	//str1.Format("%d",m_Surf_ProdGray_Low);
	strbefore.Append(str1);
	strbefore.Append(str2);
	strbefore.Append(str3);
	strbefore.Append(str4);
	strbefore.Append(str5);
	strbefore.Append(str6);
	strbefore.Append(str7);
	strbefore.Append(str8);
	strbefore.Append(str9);
	strbefore.Append(str10);
	strbefore.Append(str11);
	strbefore.Append(str12);
	strbefore.Append(str13);
	strbefore.Append(str14);
	strbefore.Append(str15);
	strbefore.Append(str16);
	strbefore.Append(str17);
	strbefore.Append(str18);
	strbefore.Append(str19);
	strbefore.Append(str20);
	strbefore.Append(str21);
	strbefore.Append(str22);
	strbefore.Append(str23);
	strbefore.Append(str24);
	strbefore.Append(str25);
	strbefore.Append(str26);
	strbefore.Append(str27);
	strbefore.Append(str28);
	strbefore.Append(str29);
	strbefore.Append(str30);
	strbefore.Append(str31);
	strbefore.Append(str32);
	strbefore.Append(str33);
	strbefore.Append(str34);
	strbefore.Append(str35);
	strbefore.Append(str36);
	strbefore.Append(str37);
	strbefore.Append(str38);
	strbefore.Append(str39);
	strbefore.Append(str40);
	strbefore.Append(str41);
	strbefore.Append(str42);
	strbefore.Append(str43);
	strbefore.Append(str44);
	strbefore.Append(str45);
	strbefore.Append(str46);
	strbefore.Append(str47);
	strbefore.Append(str48);
	strbefore.Append(str49);
	strbefore.Append(str50);
	strbefore.Append(str51);
	strbefore.Append(str52);
	strbefore.Append(str53);
	strbefore.Append(str54);
	strbefore.Append(str55);
	strbefore.Append(str56);
	strbefore.Append(str57);
	strbefore.Append(str58);
	strbefore.Append(str59);
	strbefore.Append(str60);
	strbefore.Append(str61);
	strbefore.Append(str62);
	strbefore.Append(str63);
	strbefore.Append(str64);
	strbefore.Append(str65);
	strbefore.Append(str66);
	strbefore.Append(str67);
	strbefore.Append(str68);
	strbefore.Append(str69);
	strbefore.Append(str70);
	strbefore.Append(str71);
	strbefore.Append(str72);
	strbefore.Append(str73);
	strbefore.Append(str74);
	strbefore.Append(str75);
	strbefore.Append(str76);
	strbefore.Append(str77);
	strbefore.Append(str78);
	strbefore.Append(str79);
	strbefore.Append(str80);
	//strbefore.Append(str81);
	return strbefore;
}

CString CParameterPool::LoadToStrC()
{
	    //strchanged="";
		CString strc71,strc72,strc73,strc74,strc75,strc76,strc77,strc78,strc79,strc80;
		/////////////////////////////////////////////////
		/////////////////////////////bool////////////////
		strc71.Format("%d",m_Surf_IfShallowMTag);
		strc72.Format("%d",m_Surf_IfShallowLTag);
		strc73.Format("%d",m_Surf_IfDeepSTag2);
		strc74.Format("%d",m_Surf_IfDeepMTag2);
		strc75.Format("%d",m_Surf_IfDeepLTag2);
		strc76.Format("%d",m_Surf_IfShallowSTag2);
		strc77.Format("%d",m_Surf_IfShallowMTag2);
		strc78.Format("%d",m_Surf_IfShallowLTag2);
		strc79.Format("%d",m_Surf_IfVertLineTag);
		strc80.Format("%d",m_Surf_IfHorLineTag);
		/////////////////////////////////////////////////
		/////////////////////////////bool////////////////
	
		CString strc61,strc62,strc63,strc64,strc65,strc66,strc67,strc68,strc69,strc70;
		strc61.Format("%d",m_Surf_DeepSizePixL2);
		strc62.Format("%d",m_Surf_Thresh_Shallow2);
		strc63.Format("%d",m_Surf_ShallowSizePixS2);
		strc64.Format("%d",m_Surf_ShallowSizePixM2);
		strc65.Format("%d",m_Surf_ShallowSizePixL2);
	
	
		/////////////////////////////////////////////////
		/////////////////////////////bool////////////////
		strc66.Format("%d",m_iRecordWidthLine);
		strc67.Format("%d",m_Surf_IfDeepSTag);
		strc68.Format("%d",m_Surf_IfDeepMTag);
		strc69.Format("%d",m_Surf_IfDeepLTag);
		strc70.Format("%d",m_Surf_IfShallowSTag);
		/////////////////////////////////////////////////
		/////////////////////////////bool////////////////
	
		CString strc51,strc52,strc53,strc54,strc55,strc56,strc57,strc58,strc59,strc60;
		strc51.Format("%d",m_Surf_DeepSizePixS);
		strc52.Format("%d",m_Surf_DeepSizePixM);
		strc53.Format("%d",m_Surf_DeepSizePixL);
		strc54.Format("%d",m_Surf_Thresh_Shallow);
		strc55.Format("%d",m_Surf_ShallowSizePixS);
		strc56.Format("%d",m_Surf_ShallowSizePixM);
		strc57.Format("%d",m_Surf_ShallowSizePixL);
		strc58.Format("%d",m_Surf_Thresh_Deep2);
		strc59.Format("%d",m_Surf_ShallowSizePixS2);
		strc60.Format("%d",m_Surf_DeepSizePixM2);
		
		CString strc41,strc42,strc43,strc44,strc45,strc46,strc47,strc48,strc49,strc50;
		strc41.Format("%d",m_Surf_DeepScoreM2);
		strc42.Format("%d",m_Surf_DeepScoreL2);
		strc43.Format("%d",m_Surf_ShallowScoreS2);
		strc44.Format("%d",m_Surf_ShallowScoreM2);
		strc45.Format("%d",m_Surf_ShallowScoreL2);
		strc46.Format("%d",m_Surf_VertLineScore);
		strc47.Format("%d",m_Surf_HorLineScore);
		strc48.Format("%d",m_Surf_TotalScore);
		strc49.Format("%d",m_Surf_Area_Min);
		strc50.Format("%d",m_Surf_Thresh_Deep);
		
		CString strc31,strc32,strc33,strc34,strc35,strc36,strc37,strc38,strc39,strc40;
		strc31.Format("%d",m_Surf_Stripe_W2);
		strc32.Format("%d",m_Surf_Stripe_H1);
		strc33.Format("%d",m_Surf_Stripe_H2);
		strc34.Format("%d",m_Surf_DeepScoreS);
		strc35.Format("%d",m_Surf_DeepScoreM);
		strc36.Format("%d",m_Surf_DeepScoreL);
		strc37.Format("%d",m_Surf_ShallowScoreS);
		strc38.Format("%d",m_Surf_ShallowScoreM);
		strc39.Format("%d",m_Surf_ShallowScoreL);
		strc40.Format("%d",m_Surf_DeepScoreS2);
		
		
		CString strc21,strc22,strc23,strc24,strc25,strc26,strc27,strc28,strc29,strc30;
		strc21.Format("%d",m_Surf_DynMode_3);
		strc22.Format("%d",m_Surf_Close_1C3);
		strc23.Format("%d",m_Surf_Close_2C3);
		strc24.Format("%d",m_Surf_DynThresh4);
		strc25.Format("%d",m_Surf_DynMode_4);
		strc26.Format("%d",m_Surf_Close_1C4);
		strc27.Format("%d",m_Surf_Close_2C4);
		strc28.Format("%d",m_Surf_Stripe_Close_WC5);
		strc29.Format("%d",m_Surf_Stripe_Close_HC5);
		strc30.Format("%d",m_Surf_Stripe_W1);
		
		CString strc12,strc13,strc14,strc15,strc16,strc17,strc18,strc19,strc20;
		strc12.Format("%d",m_Surf_DynThresh1);
		strc13.Format("%d",m_Surf_DynMode_1);
		strc14.Format("%d",m_Surf_Close_W1);
		strc15.Format("%d",m_Surf_Close_H1);
		strc16.Format("%d",m_Surf_DynThresh2);
		strc17.Format("%d",m_Surf_DynMode_2);
		strc18.Format("%d",m_Surf_Close_W2);
		strc19.Format("%d",m_Surf_Close_H2);
		strc20.Format("%d",m_Surf_DynThresh3);
	
	CString strc1,strc2,strc3,strc4,strc5,strc6,strc7,strc8,strc9,strc10,strc11;
	strc1.Format("%d",m_Surf_ProdGray_Low);
	strc2.Format("%d",m_Surf_ProdGray_High);
	strc3.Format("%d",m_Surf_ProdArea);
	strc4.Format("%d",m_Surf_MeanW1);
	strc5.Format("%d",m_Surf_MeanH1);
	strc6.Format("%d",m_Surf_MeanW2);
	strc7.Format("%d",m_Surf_MeanH2);
	strc8.Format("%d",m_Surf_CloseW);
	strc9.Format("%d",m_Surf_CloseH);
	strc10.Format("%d",m_Surf_EroseW);
	strc11.Format("%d",m_Surf_EroseH);
	
	CString strc81;
	
	
	//CString str,str1;
	//str.Format("%d",m_Surf_ProdGray_High);
	//str1.Format("%d",m_Surf_ProdGray_Low);
	strchanged.Append(strc1);
	strchanged.Append(strc2);
	strchanged.Append(strc3);
	strchanged.Append(strc4);
	strchanged.Append(strc5);
	strchanged.Append(strc6);
	strchanged.Append(strc7);
	strchanged.Append(strc8);
	strchanged.Append(strc9);
	strchanged.Append(strc10);
	strchanged.Append(strc11);
	strchanged.Append(strc12);
	strchanged.Append(strc13);
	strchanged.Append(strc14);
	strchanged.Append(strc15);
	strchanged.Append(strc16);
	strchanged.Append(strc17);
	strchanged.Append(strc18);
	strchanged.Append(strc19);
	strchanged.Append(strc20);
	strchanged.Append(strc21);
	strchanged.Append(strc22);
	strchanged.Append(strc23);
	strchanged.Append(strc24);
	strchanged.Append(strc25);
	strchanged.Append(strc26);
	strchanged.Append(strc27);
	strchanged.Append(strc28);
	strchanged.Append(strc29);
	strchanged.Append(strc30);
	strchanged.Append(strc31);
	strchanged.Append(strc32);
	strchanged.Append(strc33);
	strchanged.Append(strc34);
	strchanged.Append(strc35);
	strchanged.Append(strc36);
	strchanged.Append(strc37);
	strchanged.Append(strc38);
	strchanged.Append(strc39);
	strchanged.Append(strc40);
	strchanged.Append(strc41);
	strchanged.Append(strc42);
	strchanged.Append(strc43);
	strchanged.Append(strc44);
	strchanged.Append(strc45);
	strchanged.Append(strc46);
	strchanged.Append(strc47);
	strchanged.Append(strc48);
	strchanged.Append(strc49);
	strchanged.Append(strc50);
	strchanged.Append(strc51);
	strchanged.Append(strc52);
	strchanged.Append(strc53);
	strchanged.Append(strc54);
	strchanged.Append(strc55);
	strchanged.Append(strc56);
	strchanged.Append(strc57);
	strchanged.Append(strc58);
	strchanged.Append(strc59);
	strchanged.Append(strc60);
	strchanged.Append(strc61);
	strchanged.Append(strc62);
	strchanged.Append(strc63);
	strchanged.Append(strc64);
	strchanged.Append(strc65);
	strchanged.Append(strc66);
	strchanged.Append(strc67);
	strchanged.Append(strc68);
	strchanged.Append(strc69);
	strchanged.Append(strc70);
	strchanged.Append(strc71);
	strchanged.Append(strc72);
	strchanged.Append(strc73);
	strchanged.Append(strc74);
	strchanged.Append(strc75);
	strchanged.Append(strc76);
	strchanged.Append(strc77);
	strchanged.Append(strc78);
	strchanged.Append(strc79);
	strchanged.Append(strc80);
	//strchanged.Append(strc81);
	return strchanged;

}

void CParameterPool::SaveCheckPara(int Index)   //������ ����
{
	WriteFloatKey(m_Resolution_H, "�ֱ���", "����",m_CheckParaPath[Index]);
	//[��������]
	WriteIntKey(m_PinHoleArea, "��������", "�׶��������", m_CheckParaPath[Index]);
	WriteIntKey(m_MaxReturnNum, "��������", "���ż�¼����", m_CheckParaPath[Index]);
	WriteIntKey(m_ProductGray, "��������", "��Ʒ�Ҷ�", m_CheckParaPath[Index]);
	WriteIntKey(m_PinHoleGray, "��������","�׶��Ҷ�", m_CheckParaPath[Index]); 
	WriteIntKey(m_WeldArea_Min, "��������", "�������MIN",m_CheckParaPath[Index]);
	WriteIntKey(m_WeldArea_Max, "��������", "�������MAX", m_CheckParaPath[Index]);
	//[��Ե���]
	WriteIntKey(m_IfCheckEdge, "��Ե���", "�Ƿ����Ե", m_CheckParaPath[Index]);
	WriteIntKey(m_EdgeArea, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	WriteIntKey(m_EdgeWidth, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	WriteIntKey(m_EdgeDepth, "��Ե���", "��Ե���", m_CheckParaPath[Index]);
	//[ȱ�ݱ���]
	WriteIntKey(m_AlarmFlag[PINHOLE], "ȱ�ݱ���", "���", m_CheckParaPath[Index]);
	WriteIntKey(m_AlarmFlag[WELD], "ȱ�ݱ���", "����", m_CheckParaPath[Index]);
	WriteIntKey(m_AlarmFlag[EDGE], "ȱ�ݱ���", "��Ե", m_CheckParaPath[Index]);
	WriteIntKey(m_AlarmFlag[OTHER], "ȱ�ݱ���", "����", m_CheckParaPath[Index]);
	//[��¼ȱ��]
	WriteIntKey(m_IfRecord[PINHOLE], "��¼ȱ��", "���", m_CheckParaPath[Index]);
	WriteIntKey(m_IfRecord[WELD], "��¼ȱ��", "����", m_CheckParaPath[Index]);
	WriteIntKey(m_IfRecord[EDGE], "��¼ȱ��", "��Ե", m_CheckParaPath[Index]);
	WriteIntKey(m_IfRecord[OTHER], "��¼ȱ��", "����", m_CheckParaPath[Index]);
	//[���]
	WriteIntKey(m_WidthGray,"���","���Ҷ�",m_CheckParaPath[Index]);
	WriteIntKey(m_StoredNum,"���","��������",m_CheckParaPath[Index]);
	WriteFloatKey(m_Overlap_Width,"���","�ص����(mm)",m_CheckParaPath[Index]);
	//CString strData;
	//strData.Format("%.2f", m_Resolution_W);				WritePrivateProfileString("�ֱ���", "����", strData, m_CheckParaPath);
	//strData.Format("%.2f", m_Resolution_H);				WritePrivateProfileString("�ֱ���", "����", strData, m_CheckParaPath);
	//*********������********//
	//[��������]
	WriteIntKey(m_Surf_ProdGray_Low,"��������","��Ʒ�Ҷ�>",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ProdGray_High,"��������","��Ʒ�Ҷ�<",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ProdArea,"��������","��Ʒ���>",m_SurfaceParaPath[Index]);
	//[ȱ��ʶ��]
	WriteIntKey(m_Surf_MeanW1,"ȱ��ʶ��","MeanW1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_MeanH1,"ȱ��ʶ��","MeanH1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_MeanW2,"ȱ��ʶ��","MeanW2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_MeanH2,"ȱ��ʶ��","MeanH2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_CloseW,"ȱ��ʶ��","CloseW",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_CloseH,"ȱ��ʶ��","CloseH",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_EroseW,"ȱ��ʶ��","EroseW",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_EroseH,"ȱ��ʶ��","EroseH",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_DynThresh1,"ȱ��ʶ��","DynThresh1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DynMode_1,"ȱ��ʶ��","DynMode1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_W1,"ȱ��ʶ��","CloseW1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_H1,"ȱ��ʶ��","CloseH1",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_DynThresh2,"ȱ��ʶ��","DynThresh2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DynMode_2,"ȱ��ʶ��","DynMode2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_W2,"ȱ��ʶ��","CloseW2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_H2,"ȱ��ʶ��","CloseH2",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_DynThresh3,"ȱ��ʶ��","DynThresh3",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DynMode_3,"ȱ��ʶ��","DynMode3",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_1C3,"ȱ��ʶ��","Close1C3",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_2C3,"ȱ��ʶ��","Close2C3",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_DynThresh4,"ȱ��ʶ��","DynThresh4",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DynMode_4,"ȱ��ʶ��","DynMode4",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_1C4,"ȱ��ʶ��","Close1C4",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Close_2C4,"ȱ��ʶ��","Close2C4",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_Stripe_Close_WC5,"ȱ��ʶ��","Close_WC5",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Stripe_Close_HC5,"ȱ��ʶ��","Close_HC5",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Stripe_W1,"ȱ��ʶ��","Stripe_W1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Stripe_W2,"ȱ��ʶ��","Stripe_W2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Stripe_H1,"ȱ��ʶ��","Stripe_H1",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Stripe_H2,"ȱ��ʶ��","Stripe_H2",m_SurfaceParaPath[Index]);
	//[����ģʽ]
	//WriteIntKey(m_Surf_IfFastCheck,"����ģʽ","ʹ�ÿ���ģʽ",m_SurfaceParaPath);
	//WriteIntKey(m_Surf_ErrGray1,"����ģʽ","ȱ�ݻҶ�>",m_SurfaceParaPath);
	//WriteIntKey(m_Surf_ErrGray2,"����ģʽ","ȱ�ݻҶ�<",m_SurfaceParaPath);
	//[ȱ�ݳߴ�]
	WriteIntKey(m_Surf_Area_Min,"ȱ�ݳߴ�","��С���",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Thresh_Deep,"ȱ�ݳߴ�","��ȱ����ֵ",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixS,"ȱ�ݳߴ�","��С����",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixM,"ȱ�ݳߴ�","��������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixL,"ȱ�ݳߴ�","�������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Thresh_Shallow,"ȱ�ݳߴ�","ǳȱ����ֵ",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixS,"ȱ�ݳߴ�","ǳС����",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixM,"ȱ�ݳߴ�","ǳ������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixL,"ȱ�ݳߴ�","ǳ������",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_Thresh_Deep2,"ȱ�ݳߴ�","��ȱ����ֵ2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixS2,"ȱ�ݳߴ�","��С����2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixM2,"ȱ�ݳߴ�","��������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepSizePixL2,"ȱ�ݳߴ�","�������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_Thresh_Shallow2,"ȱ�ݳߴ�","ǳȱ����ֵ2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixS2,"ȱ�ݳߴ�","ǳС����2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixM2,"ȱ�ݳߴ�","ǳ������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowSizePixL2,"ȱ�ݳߴ�","ǳ������2",m_SurfaceParaPath[Index]);

	//[ȱ������]
	WriteIntKey(m_Surf_DeepScoreS,"ȱ������","��С����",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepScoreM,"ȱ������","��������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepScoreL,"ȱ������","�������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreS,"ȱ������","ǳС����",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreM,"ȱ������","ǳ������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreL,"ȱ������","ǳ������",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_DeepScoreS2,"ȱ������","��С����2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepScoreM2,"ȱ������","��������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_DeepScoreL2,"ȱ������","�������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreS2,"ȱ������","ǳС����2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreM2,"ȱ������","ǳ������2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_ShallowScoreL2,"ȱ������","ǳ������2",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_VertLineScore,"ȱ������","����������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_HorLineScore,"ȱ������","����������",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_TotalScore,"ȱ������","ȱ���ܷ�",m_SurfaceParaPath[Index]);
	//[ȱ���ܶ�]
// 	WriteIntKey(m_Surf_DensitySizeWidth,"ȱ���ܶ�","���",m_SurfaceParaPath);
// 	WriteIntKey(m_Surf_DensitySizeHeight,"ȱ���ܶ�","�߶�",m_SurfaceParaPath);
// 	WriteIntKey(m_Surf_DensityCount,"ȱ���ܶ�","����",m_SurfaceParaPath);
	//[�Ƿ���]
	WriteIntKey(m_Surf_IfDeepSTag,"�Ƿ���","��С",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfDeepMTag,"�Ƿ���","����",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfDeepLTag,"�Ƿ���","���",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowSTag,"�Ƿ���","ǳС",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowMTag,"�Ƿ���","ǳ��",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowLTag,"�Ƿ���","ǳ��",m_SurfaceParaPath[Index]);

	WriteIntKey(m_Surf_IfDeepSTag2,"�Ƿ���","��С2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfDeepMTag2,"�Ƿ���","����2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfDeepLTag2,"�Ƿ���","���2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowSTag2,"�Ƿ���","ǳС2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowMTag2,"�Ƿ���","ǳ��2",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfShallowLTag2,"�Ƿ���","ǳ��2",m_SurfaceParaPath[Index]);
	//WriteIntKey(m_Surf_IfDensityTag,"�Ƿ���","�ܼ�",m_SurfaceParaPath);

	WriteIntKey(m_Surf_IfVertLineTag,"�Ƿ���","������",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_IfHorLineTag,"�Ƿ���","������",m_SurfaceParaPath[Index]);

	//[����������ʱ��]
	WriteIntKey(m_Surf_AlarmLength,"����������ʱ��","��������ʱ��",m_SurfaceParaPath[Index]);
	WriteIntKey(m_Surf_TagLength,"����������ʱ��","����������",m_SurfaceParaPath[Index]);

	//[У׼]
	WriteFloatKey(m_Surf_Calib,"У׼","ֱ��У׼",m_SurfaceParaPath[Index]);
	WriteFloatKey(m_Surf_Calib2,"У׼","���У׼",m_SurfaceParaPath[Index]);

	//[���߸���]
	WriteFloatKey(m_fHorAndVorRatio,"���߸���","���ߺ��ݱ�",m_CheckParaPath[Index]);
	WriteIntKey(m_iRecordWidthLine,"���߸���","����ȥ��",m_CheckParaPath[Index]);
	WriteIntKey(m_iMinWidthGray,"���߸���","���ߵͻҶ�ֵ",m_CheckParaPath[Index]);
	WriteIntKey(m_iMaxWidthGray,"���߸���","���߸߻Ҷ�ֵ ",m_CheckParaPath[Index]);

	

	/*ChangedPara=m_Surf_ProdGray_Low+m_Surf_ProdGray_High+m_Surf_ProdArea
		+m_Surf_MeanW1+m_Surf_MeanH1+m_Surf_MeanW2+m_Surf_MeanH2+m_Surf_CloseW+m_Surf_CloseH+m_Surf_EroseW+m_Surf_EroseH
		+m_Surf_DynThresh1+m_Surf_DynMode_1+m_Surf_Close_W1+m_Surf_Close_H1
		+m_Surf_DynThresh2+m_Surf_DynMode_2+m_Surf_Close_W2+m_Surf_Close_H2
		+m_Surf_DynThresh3+m_Surf_DynMode_3+m_Surf_Close_1C3+m_Surf_Close_2C3
		+m_Surf_DynThresh4+m_Surf_DynMode_4+m_Surf_Close_1C4+m_Surf_Close_2C4
		+m_Surf_Stripe_Close_WC5+m_Surf_Stripe_Close_HC5+m_Surf_Stripe_W1+m_Surf_Stripe_W2+m_Surf_Stripe_H1+m_Surf_Stripe_H2
		+m_Surf_DeepScoreS+m_Surf_DeepScoreM+m_Surf_DeepScoreL+m_Surf_ShallowScoreS+m_Surf_ShallowScoreM+m_Surf_ShallowScoreL
		+m_Surf_DeepScoreS2+m_Surf_DeepScoreM2+m_Surf_DeepScoreL2+m_Surf_ShallowScoreS2+m_Surf_ShallowScoreM2+m_Surf_ShallowScoreL2
		+m_Surf_VertLineScore+m_Surf_HorLineScore+m_Surf_TotalScore
		+m_Surf_Area_Min+m_Surf_Thresh_Deep+m_Surf_DeepSizePixS+m_Surf_DeepSizePixM+m_Surf_DeepSizePixL
		+m_Surf_Thresh_Shallow+m_Surf_ShallowSizePixS+m_Surf_ShallowSizePixM+m_Surf_ShallowSizePixL
		+m_Surf_Thresh_Deep2+m_Surf_DeepSizePixS2+m_Surf_DeepSizePixM2+m_Surf_DeepSizePixL2
		+m_Surf_Thresh_Shallow2+m_Surf_ShallowSizePixS2+m_Surf_ShallowSizePixM2+m_Surf_ShallowSizePixL2
		+m_iRecordWidthLine+m_Surf_IfDeepSTag+m_Surf_IfDeepMTag+m_Surf_IfDeepLTag+m_Surf_IfShallowSTag+m_Surf_IfShallowMTag+m_Surf_IfShallowLTag
		+m_Surf_IfDeepSTag2+m_Surf_IfDeepMTag2+m_Surf_IfDeepLTag2+m_Surf_IfShallowSTag2+m_Surf_IfShallowMTag2+m_Surf_IfShallowLTag2
		+m_Surf_IfVertLineTag+m_Surf_IfHorLineTag;*/

	//CString s;
	//CString str,str1;
	//str.Format("%d",m_Surf_ProdGray_High);
	//str1.Format("%d",m_Surf_ProdGray_Low);
	//s.Append(str);
	//s.Append(str1);






//
//	CString strc71,strc72,strc73,strc74,strc75,strc76,strc77,strc78,strc79,strc80;
//	/////////////////////////////////////////////////
//	/////////////////////////////bool////////////////
//	strc71.Format("%d",m_Surf_IfShallowMTag);
//	strc72.Format("%d",m_Surf_IfShallowLTag);
//	strc73.Format("%d",m_Surf_IfDeepSTag2);
//	strc74.Format("%d",m_Surf_IfDeepMTag2);
//	strc75.Format("%d",m_Surf_IfDeepLTag2);
//	strc76.Format("%d",m_Surf_IfShallowSTag2);
//	strc77.Format("%d",m_Surf_IfShallowMTag2);
//	strc78.Format("%d",m_Surf_IfShallowLTag2);
//	strc79.Format("%d",m_Surf_IfVertLineTag);
//	strc80.Format("%d",m_Surf_IfHorLineTag);
//	/////////////////////////////////////////////////
//	/////////////////////////////bool////////////////
//
//	CString strc61,strc62,strc63,strc64,strc65,strc66,strc67,strc68,strc69,strc70;
//	strc61.Format("%d",m_Surf_DeepSizePixL2);
//	strc62.Format("%d",m_Surf_Thresh_Shallow2);
//	strc63.Format("%d",m_Surf_ShallowSizePixS2);
//	strc64.Format("%d",m_Surf_ShallowSizePixM2);
//	strc65.Format("%d",m_Surf_ShallowSizePixL2);
//
//
//	/////////////////////////////////////////////////
//	/////////////////////////////bool////////////////
//	strc66.Format("%d",m_iRecordWidthLine);
//	strc67.Format("%d",m_Surf_IfDeepSTag);
//	strc68.Format("%d",m_Surf_IfDeepMTag);
//	strc69.Format("%d",m_Surf_IfDeepLTag);
//	strc70.Format("%d",m_Surf_IfShallowSTag);
//	/////////////////////////////////////////////////
//	/////////////////////////////bool////////////////
//
//	CString strc51,strc52,strc53,strc54,strc55,strc56,strc57,strc58,strc59,strc60;
//	strc51.Format("%d",m_Surf_DeepSizePixS);
//	strc52.Format("%d",m_Surf_DeepSizePixM);
//	strc53.Format("%d",m_Surf_DeepSizePixL);
//	strc54.Format("%d",m_Surf_Thresh_Shallow);
//	strc55.Format("%d",m_Surf_ShallowSizePixS);
//	strc56.Format("%d",m_Surf_ShallowSizePixM);
//	strc57.Format("%d",m_Surf_ShallowSizePixL);
//	strc58.Format("%d",m_Surf_Thresh_Deep2);
//	strc59.Format("%d",m_Surf_ShallowSizePixS2);
//	strc60.Format("%d",m_Surf_DeepSizePixM2);
//	
//	CString strc41,strc42,strc43,strc44,strc45,strc46,strc47,strc48,strc49,strc50;
//	strc41.Format("%d",m_Surf_DeepScoreM2);
//	strc42.Format("%d",m_Surf_DeepScoreL2);
//	strc43.Format("%d",m_Surf_ShallowScoreS2);
//	strc44.Format("%d",m_Surf_ShallowScoreM2);
//	strc45.Format("%d",m_Surf_ShallowScoreL2);
//	strc46.Format("%d",m_Surf_VertLineScore);
//	strc47.Format("%d",m_Surf_HorLineScore);
//	strc48.Format("%d",m_Surf_TotalScore);
//	strc49.Format("%d",m_Surf_Area_Min);
//	strc50.Format("%d",m_Surf_Thresh_Deep);
//	
//	CString strc31,strc32,strc33,strc34,strc35,strc36,strc37,strc38,strc39,strc40;
//	strc31.Format("%d",m_Surf_Stripe_W2);
//	strc32.Format("%d",m_Surf_Stripe_H1);
//	strc33.Format("%d",m_Surf_Stripe_H2);
//	strc34.Format("%d",m_Surf_DeepScoreS);
//	strc35.Format("%d",m_Surf_DeepScoreM);
//	strc36.Format("%d",m_Surf_DeepScoreL);
//	strc37.Format("%d",m_Surf_ShallowScoreS);
//	strc38.Format("%d",m_Surf_ShallowScoreM);
//	strc39.Format("%d",m_Surf_ShallowScoreL);
//	strc40.Format("%d",m_Surf_DeepScoreS2);
//	
//	
//	CString strc21,strc22,strc23,strc24,strc25,strc26,strc27,strc28,strc29,strc30;
//	strc21.Format("%d",m_Surf_DynMode_3);
//	strc22.Format("%d",m_Surf_Close_1C3);
//	strc23.Format("%d",m_Surf_Close_2C3);
//	strc24.Format("%d",m_Surf_DynThresh4);
//	strc25.Format("%d",m_Surf_DynMode_4);
//	strc26.Format("%d",m_Surf_Close_1C4);
//	strc27.Format("%d",m_Surf_Close_2C4);
//	strc28.Format("%d",m_Surf_Stripe_Close_WC5);
//	strc29.Format("%d",m_Surf_Stripe_Close_HC5);
//	strc30.Format("%d",m_Surf_Stripe_W1);
//	
//	CString strc12,strc13,strc14,strc15,strc16,strc17,strc18,strc19,strc20;
//	strc12.Format("%d",m_Surf_DynThresh1);
//	strc13.Format("%d",m_Surf_DynMode_1);
//	strc14.Format("%d",m_Surf_Close_W1);
//	strc15.Format("%d",m_Surf_Close_H1);
//	strc16.Format("%d",m_Surf_DynThresh2);
//	strc17.Format("%d",m_Surf_DynMode_2);
//	strc18.Format("%d",m_Surf_Close_W2);
//	strc19.Format("%d",m_Surf_Close_H2);
//	strc20.Format("%d",m_Surf_DynThresh3);
//
//CString strc1,strc2,strc3,strc4,strc5,strc6,strc7,strc8,strc9,strc10,strc11;
//strc1.Format("%d",m_Surf_ProdGray_Low);
//strc2.Format("%d",m_Surf_ProdGray_High);
//strc3.Format("%d",m_Surf_ProdArea);
//strc4.Format("%d",m_Surf_MeanW1);
//strc5.Format("%d",m_Surf_MeanH1);
//strc6.Format("%d",m_Surf_MeanW2);
//strc7.Format("%d",m_Surf_MeanH2);
//strc8.Format("%d",m_Surf_CloseW);
//strc9.Format("%d",m_Surf_CloseH);
//strc10.Format("%d",m_Surf_EroseW);
//strc11.Format("%d",m_Surf_EroseH);
//
//CString strc81;
//
//
////CString str,str1;
////str.Format("%d",m_Surf_ProdGray_High);
////str1.Format("%d",m_Surf_ProdGray_Low);
//strchanged.Append(strc1);
//strchanged.Append(strc2);
//strchanged.Append(strc3);
//strchanged.Append(strc4);
//strchanged.Append(strc5);
//strchanged.Append(strc6);
//strchanged.Append(strc7);
//strchanged.Append(strc8);
//strchanged.Append(strc9);
//strchanged.Append(strc10);
//strchanged.Append(strc11);
//strchanged.Append(strc12);
//strchanged.Append(strc13);
//strchanged.Append(strc14);
//strchanged.Append(strc15);
//strchanged.Append(strc16);
//strchanged.Append(strc17);
//strchanged.Append(strc18);
//strchanged.Append(strc19);
//strchanged.Append(strc20);
//strchanged.Append(strc21);
//strchanged.Append(strc22);
//strchanged.Append(strc23);
//strchanged.Append(strc24);
//strchanged.Append(strc25);
//strchanged.Append(strc26);
//strchanged.Append(strc27);
//strchanged.Append(strc28);
//strchanged.Append(strc29);
//strchanged.Append(strc30);
//strchanged.Append(strc31);
//strchanged.Append(strc32);
//strchanged.Append(strc33);
//strchanged.Append(strc34);
//strchanged.Append(strc35);
//strchanged.Append(strc36);
//strchanged.Append(strc37);
//strchanged.Append(strc38);
//strchanged.Append(strc39);
//strchanged.Append(strc40);
//strchanged.Append(strc41);
//strchanged.Append(strc42);
//strchanged.Append(strc43);
//strchanged.Append(strc44);
//strchanged.Append(strc45);
//strchanged.Append(strc46);
//strchanged.Append(strc47);
//strchanged.Append(strc48);
//strchanged.Append(strc49);
//strchanged.Append(strc50);
//strchanged.Append(strc51);
//strchanged.Append(strc52);
//strchanged.Append(strc53);
//strchanged.Append(strc54);
//strchanged.Append(strc55);
//strchanged.Append(strc56);
//strchanged.Append(strc57);
//strchanged.Append(strc58);
//strchanged.Append(strc59);
//strchanged.Append(strc60);
//strchanged.Append(strc61);
//strchanged.Append(strc62);
//strchanged.Append(strc63);
//strchanged.Append(strc64);
//strchanged.Append(strc65);
//strchanged.Append(strc66);
//strchanged.Append(strc67);
//strchanged.Append(strc68);
//strchanged.Append(strc69);
//strchanged.Append(strc70);
//strchanged.Append(strc71);
//strchanged.Append(strc72);
//strchanged.Append(strc73);
//strchanged.Append(strc74);
//strchanged.Append(strc75);
//strchanged.Append(strc76);
//strchanged.Append(strc77);
//strchanged.Append(strc78);
//strchanged.Append(strc79);
//strchanged.Append(strc80);
//strchanged.Append(strc81);
//strchanged.Append(strchanged);
}

void CParameterPool::LoadAllPara(int Index)
{
	//��ȡ�����������
	//for (int i=0; i<CAM_NUM; i++)
	//{
		//LoadCameraPara(Index);  
	//}
		LoadSetModel();
	
	//��ȡ������
	LoadCheckPara(Index);
	GenCheckRegion();
}

void CParameterPool::SaveAllPara(int Index)
{
	//���������������
	//for (int i=0; i<CAM_NUM; i++)
	//{
		//SaveCameraPara(Index);
		SaveSetModel();
	//}

	//���������
	SaveCheckPara(Index);
}

void CParameterPool::ReadStrKey( CString &data, CString strApp, CString strKey, CString filePath )
{
	char* pBuff = new char[MAX_LEN];
	GetPrivateProfileString(strApp, strKey, NULL, pBuff, MAX_LEN, filePath);
	data =  (CString)pBuff;
}

CString CParameterPool::GetErrString( int Indexs )
{
	CString m_ReturnValue;
	CString m_tempStr;
	m_tempStr.Format("%d",Indexs);
	ReadStrKey(m_ReturnValue,"ErrorIdentification",m_tempStr,m_SystemParaPath);
	CString strBuff = (m_ReturnValue);
	CString outPut0;
	AfxExtractSubString(outPut0, strBuff, 0, ',');
	return outPut0;
}

CParameterPool & CParameterPool::operator = (const CParameterPool& RightSides)
{
	if(this == &RightSides)  
	{
		return *this;
	}

	m_Resolution_H=RightSides.m_Resolution_H;
	m_PinHoleArea=RightSides.m_PinHoleArea;
	m_MaxReturnNum=RightSides.m_MaxReturnNum;
	m_ProductGray=RightSides.m_ProductGray;
	m_PinHoleGray=RightSides.m_PinHoleGray;
	m_WeldArea_Min=RightSides.m_WeldArea_Min;
	m_WeldArea_Max=RightSides.m_WeldArea_Max;
	m_IfCheckEdge=RightSides.m_IfCheckEdge;
	m_EdgeArea=RightSides.m_EdgeArea;
	m_EdgeWidth=RightSides.m_EdgeWidth;
	m_EdgeDepth=RightSides.m_EdgeDepth;
	m_AlarmFlag[PINHOLE]=RightSides.m_AlarmFlag[PINHOLE];
	m_AlarmFlag[WELD]=RightSides.m_AlarmFlag[WELD];
	m_AlarmFlag[EDGE]=RightSides.m_AlarmFlag[EDGE];
	m_AlarmFlag[OTHER]=RightSides.m_AlarmFlag[OTHER];
	m_IfRecord[PINHOLE]=RightSides.m_IfRecord[PINHOLE];
	m_IfRecord[WELD]=RightSides.m_IfRecord[WELD];
	m_IfRecord[EDGE]=RightSides.m_IfRecord[EDGE];
	m_IfRecord[OTHER]=RightSides.m_IfRecord[OTHER];
	m_WidthGray=RightSides.m_WidthGray;
	m_StoredNum=RightSides.m_StoredNum;
	m_Overlap_Width=RightSides.m_Overlap_Width;
	m_Surf_ProdGray_Low=RightSides.m_Surf_ProdGray_Low;
	m_Surf_ProdGray_High=RightSides.m_Surf_ProdGray_High;
	m_Surf_ProdArea=RightSides.m_Surf_ProdArea;
	m_Surf_MeanW1=RightSides.m_Surf_MeanW1;
	m_Surf_MeanH1=RightSides.m_Surf_MeanH1;
	m_Surf_MeanW2=RightSides.m_Surf_MeanW2;
	m_Surf_MeanH2=RightSides.m_Surf_MeanH2;
	m_Surf_CloseW=RightSides.m_Surf_CloseW;
	m_Surf_CloseH=RightSides.m_Surf_CloseH;
	m_Surf_EroseW=RightSides.m_Surf_EroseW;
	m_Surf_EroseH=RightSides.m_Surf_EroseH;
	m_Surf_DynThresh1=RightSides.m_Surf_DynThresh1;
	m_Surf_DynMode_1=RightSides.m_Surf_DynMode_1;
	m_Surf_Close_W1=RightSides.m_Surf_Close_W1;
	m_Surf_Close_H1=RightSides.m_Surf_Close_H1;
	m_Surf_DynThresh2=RightSides.m_Surf_DynThresh2;
	m_Surf_DynMode_2=RightSides.m_Surf_DynMode_2;
	m_Surf_Close_W2=RightSides.m_Surf_Close_W2;
	m_Surf_Close_H2=RightSides.m_Surf_Close_H2;
	m_Surf_DynThresh3=RightSides.m_Surf_DynThresh3;
	m_Surf_DynMode_3=RightSides.m_Surf_DynMode_3;
	m_Surf_Close_1C3=RightSides.m_Surf_Close_1C3;
	m_Surf_Close_2C3=RightSides.m_Surf_Close_2C3;
	m_Surf_DynThresh4=RightSides.m_Surf_DynThresh4;
	m_Surf_DynMode_4=RightSides.m_Surf_DynMode_4;
	m_Surf_Close_1C4=RightSides.m_Surf_Close_1C4;
	m_Surf_Close_2C4=RightSides.m_Surf_Close_2C4;
	m_Surf_Stripe_Close_WC5=RightSides.m_Surf_Stripe_Close_WC5;
	m_Surf_Stripe_Close_HC5=RightSides.m_Surf_Stripe_Close_HC5;
	m_Surf_Stripe_W1=RightSides.m_Surf_Stripe_W1;
	m_Surf_Stripe_W2=RightSides.m_Surf_Stripe_W2;
	m_Surf_Stripe_H1=RightSides.m_Surf_Stripe_H1;
	m_Surf_Stripe_H2=RightSides.m_Surf_Stripe_H2;
	m_Surf_Area_Min=RightSides.m_Surf_Area_Min;
	m_Surf_Thresh_Deep=RightSides.m_Surf_Thresh_Deep;
	m_Surf_DeepSizePixS=RightSides.m_Surf_DeepSizePixS;
	m_Surf_DeepSizePixM=RightSides.m_Surf_DeepSizePixM;
	m_Surf_DeepSizePixL=RightSides.m_Surf_DeepSizePixL;
	m_Surf_Thresh_Shallow=RightSides.m_Surf_Thresh_Shallow;
	m_Surf_ShallowSizePixS=RightSides.m_Surf_ShallowSizePixS;
	m_Surf_ShallowSizePixM=RightSides.m_Surf_ShallowSizePixM;
	m_Surf_ShallowSizePixL=RightSides.m_Surf_ShallowSizePixL;
	m_Surf_Thresh_Deep2=RightSides.m_Surf_Thresh_Deep2;
	m_Surf_DeepSizePixS2=RightSides.m_Surf_DeepSizePixS2;
	m_Surf_DeepSizePixM2=RightSides.m_Surf_DeepSizePixM2;
	m_Surf_DeepSizePixL2=RightSides.m_Surf_DeepSizePixL2;
	m_Surf_Thresh_Shallow2=RightSides.m_Surf_Thresh_Shallow2;
	m_Surf_ShallowSizePixS2=RightSides.m_Surf_ShallowSizePixS2;
	m_Surf_ShallowSizePixM2=RightSides.m_Surf_ShallowSizePixM2;
	m_Surf_ShallowSizePixL2=RightSides.m_Surf_ShallowSizePixL2;
	m_Surf_DeepScoreS=RightSides.m_Surf_DeepScoreS;
	m_Surf_DeepScoreM=RightSides.m_Surf_DeepScoreM;
	m_Surf_DeepScoreL=RightSides.m_Surf_DeepScoreL;
	m_Surf_ShallowScoreS=RightSides.m_Surf_ShallowScoreS;
	m_Surf_ShallowScoreM=RightSides.m_Surf_ShallowScoreM;
	m_Surf_ShallowScoreL=RightSides.m_Surf_ShallowScoreL;
	m_Surf_DeepScoreS2=RightSides.m_Surf_DeepScoreS2;
	m_Surf_DeepScoreM2=RightSides.m_Surf_DeepScoreM2;
	m_Surf_DeepScoreL2=RightSides.m_Surf_DeepScoreL2;
	m_Surf_ShallowScoreS2=RightSides.m_Surf_ShallowScoreS2;
	m_Surf_ShallowScoreM2=RightSides.m_Surf_ShallowScoreM2;
	m_Surf_ShallowScoreL2=RightSides.m_Surf_ShallowScoreL2;
	m_Surf_VertLineScore=RightSides.m_Surf_VertLineScore;
	m_Surf_HorLineScore=RightSides.m_Surf_HorLineScore;
	m_Surf_TotalScore=RightSides.m_Surf_TotalScore;
	m_Surf_IfDeepSTag=RightSides.m_Surf_IfDeepSTag;
	m_Surf_IfDeepMTag=RightSides.m_Surf_IfDeepMTag;
	m_Surf_IfDeepLTag=RightSides.m_Surf_IfDeepLTag;
	m_Surf_IfShallowSTag=RightSides.m_Surf_IfShallowSTag;
	m_Surf_IfShallowMTag=RightSides.m_Surf_IfShallowMTag;
	m_Surf_IfShallowLTag=RightSides.m_Surf_IfShallowLTag;
	m_Surf_IfDeepSTag2=RightSides.m_Surf_IfDeepSTag2;
	m_Surf_IfDeepMTag2=RightSides.m_Surf_IfDeepMTag2;
	m_Surf_IfDeepLTag2=RightSides.m_Surf_IfDeepLTag2;
	m_Surf_IfShallowSTag2=RightSides.m_Surf_IfShallowSTag2;
	m_Surf_IfShallowMTag2=RightSides.m_Surf_IfShallowMTag2;
	m_Surf_IfShallowLTag2=RightSides.m_Surf_IfShallowLTag2;
	m_Surf_IfVertLineTag=RightSides.m_Surf_IfVertLineTag;
	m_Surf_IfHorLineTag=RightSides.m_Surf_IfHorLineTag;
	m_Surf_AlarmLength=RightSides.m_Surf_AlarmLength;
	m_Surf_TagLength=RightSides.m_Surf_TagLength;
	m_Surf_Calib=RightSides.m_Surf_Calib;
	m_Surf_Calib2=RightSides.m_Surf_Calib2;
	m_fHorAndVorRatio=RightSides.m_fHorAndVorRatio;
	m_iRecordWidthLine=RightSides.m_iRecordWidthLine;
	m_iMinWidthGray=RightSides.m_iMinWidthGray;
	m_iMaxWidthGray=RightSides.m_iMaxWidthGray;
	/*m_ImgLeftOffset[0]=RightSides.m_ImgLeftOffset[0];
	m_ImgRightOffset[0]=RightSides.m_ImgRightOffset[0];
	m_CamPos[0]=RightSides.m_CamPos[0];
	m_Resolution_W[0]=RightSides.m_Resolution_W[0];
	m_ImgLeftOffset[1]=RightSides.m_ImgLeftOffset[1];
	m_ImgRightOffset[1]=RightSides.m_ImgRightOffset[1];
	m_CamPos[1]=RightSides.m_CamPos[1];
	m_Resolution_W[1]=RightSides.m_Resolution_W[1];
	m_ImgLeftOffset[2]=RightSides.m_ImgLeftOffset[2];
	m_ImgRightOffset[2]=RightSides.m_ImgRightOffset[2];
	m_CamPos[2]=RightSides.m_CamPos[2];
	m_Resolution_W[2]=RightSides.m_Resolution_W[2];
	m_ImgLeftOffset[3]=RightSides.m_ImgLeftOffset[3];
	m_ImgRightOffset[3]=RightSides.m_ImgRightOffset[3];
	m_CamPos[3]=RightSides.m_CamPos[3];
	m_Resolution_W[1]=RightSides.m_Resolution_W[3];
	m_ImgLeftOffset[4]=RightSides.m_ImgLeftOffset[4];
	m_ImgRightOffset[4]=RightSides.m_ImgRightOffset[4];
	m_CamPos[4]=RightSides.m_CamPos[4];
	m_Resolution_W[4]=RightSides.m_Resolution_W[4];*/
	m_SetParaMothod=RightSides.m_SetParaMothod;
	return *this;

}
