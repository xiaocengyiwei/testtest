#pragma once

class CParaFiles
{
public:
	CParaFiles(void);
	~CParaFiles(void);

private:
	int		m_lCameraIndex;
	CString m_ModelPath;			//Model文件夹路径
	CString m_ModelImagePath;       //图像路径名称
	CString m_ModelRegionPath;		//区域路径名称
	CString m_ModelParaPath;		//参数配置文件路径名称
	//CString m_ModelComPath;			//串口通信配置文件路径名称
	//CString m_ModelExposurePath;	//相机参数配置文件

	CString m_StylePath;			//品种对应的文件夹路径
	CString m_StyleImagePath;       //图像路径名称
	CString m_StyleRegionPath;		//区域路径名称
	CString m_StyleParaPath;		//参数配置文件路径名称
	//CString m_StyleComPath;			//串口通信配置文件路径名称
	//CString m_StyleExposurePath;

	//CString m_ShareFilePath;		//user.ini路径

public:
	char	sCurrentPath[MAX_PATH];
	bool	GetCurrentAppPath(char **path);
	void	GenerateFilePath();
	void	SetCameraIndex(int Index);
	void	LoadParaIniFile();
	void	WriteParaIniFile();
	//void	ShareFilePath();//user.ini路径
	//void	ReadSharePara();//读取共享参数
	//void	WriteSharePara();//写入共享参数



};
