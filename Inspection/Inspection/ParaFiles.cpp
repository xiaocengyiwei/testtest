#include "stdafx.h"
#include "ParaFiles.h"

CParaFiles::CParaFiles(void)
{
}

CParaFiles::~CParaFiles(void)
{
}
void CParaFiles::SetCameraIndex(int Index)
{
	m_lCameraIndex = Index;
}
void CParaFiles::GenerateFilePath()
{
	char* dir=NULL;
	GetCurrentAppPath(&dir);
	//model路径
	m_ModelPath.Format("%sModel\\Model",dir);
	m_ModelImagePath.Format("%s\\ModelImage-%d.bmp",m_ModelPath,m_lCameraIndex);
	m_ModelRegionPath.Format("%s\\CheckRegion-%d.region",m_ModelPath,m_lCameraIndex);
	m_ModelParaPath.Format("%s\\checkpara-%d.ini",m_ModelPath,m_lCameraIndex);
	/*m_ModelComPath.Format("%s\\common_para.ini",m_ModelPath);
	m_ModelExposurePath.Format("%s\\Dalas.ini",m_ModelPath);*/
	//品种对应路径
	int nMaxLen=256;
	char* pBuff = new char[nMaxLen];
	GetPrivateProfileString("色差仪", "当前薄膜种类", NULL, pBuff, nMaxLen, m_ModelComPath);
	CString StyleFileName = pBuff;
	m_StylePath.Format("%sModel\\%s",dir,StyleFileName);
	m_StyleImagePath.Format("%s\\ModelImage-%d.bmp",m_StylePath,m_lCameraIndex);
	m_StyleRegionPath.Format("%s\\CheckRegion-%d.region",m_StylePath,m_lCameraIndex);
	m_StyleParaPath.Format("%s\\checkpara-%d.ini",m_StylePath,m_lCameraIndex);
	/*m_StyleComPath.Format("%s\\common_para.ini",m_StylePath);
	m_StyleExposurePath.Format("%s\\Dalas.ini",m_StylePath);*/
}
bool CParaFiles::GetCurrentAppPath(char **path)
{
	char str[MAX_PATH], drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	strcpy_s(sCurrentPath,drive);
	*path = sCurrentPath;

	return true;
}

void CParaFiles::LoadParaIniFile()
{

}

void CParaFiles::WriteParaIniFile()
{

}