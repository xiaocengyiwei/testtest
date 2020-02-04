#pragma once

class CParaFiles
{
public:
	CParaFiles(void);
	~CParaFiles(void);

private:
	int		m_lCameraIndex;
	CString m_ModelPath;			//Model�ļ���·��
	CString m_ModelImagePath;       //ͼ��·������
	CString m_ModelRegionPath;		//����·������
	CString m_ModelParaPath;		//���������ļ�·������
	//CString m_ModelComPath;			//����ͨ�������ļ�·������
	//CString m_ModelExposurePath;	//������������ļ�

	CString m_StylePath;			//Ʒ�ֶ�Ӧ���ļ���·��
	CString m_StyleImagePath;       //ͼ��·������
	CString m_StyleRegionPath;		//����·������
	CString m_StyleParaPath;		//���������ļ�·������
	//CString m_StyleComPath;			//����ͨ�������ļ�·������
	//CString m_StyleExposurePath;

	//CString m_ShareFilePath;		//user.ini·��

public:
	char	sCurrentPath[MAX_PATH];
	bool	GetCurrentAppPath(char **path);
	void	GenerateFilePath();
	void	SetCameraIndex(int Index);
	void	LoadParaIniFile();
	void	WriteParaIniFile();
	//void	ShareFilePath();//user.ini·��
	//void	ReadSharePara();//��ȡ�������
	//void	WriteSharePara();//д�빲�����



};
