#include "stdafx.h"
#include "Log.h"
#include "FileOperate.h"
#include "Inspection.h"


///ȫ����־��ʵ��,��Ҫ��LOG,LOG1,...LOG4��ʹ��.
CLog __g_log;		

///���캯��.
void CLog::GetCurrPath( char **path )
{
	char str[MAX_PATH], drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	strcpy_s(m_CurrPath,drive);
	*path = m_CurrPath;
}


void CLog::InitSettingPath()
{
	char* dir = NULL;
	GetCurrPath(&dir);
	m_SystemParaPath.Format("%s\\SystemConfiguration\\system.ini",dir);
}

void CLog::ReadIntKey( int &data, CString strApp, CString strKey, CString filePath )
{
	data = GetPrivateProfileInt(strApp, strKey, 0, filePath);
}
void CLog::LoadCheckPara()   //������ ��ȡ
{
	char* pBuff = new char[MAX_LEN];

}

CLog::CLog()  
{
	InitSettingPath();
	::InitializeCriticalSection(&m_crit);   //��ʼ���ٽ���
	m_LogFileTime = CTime::GetCurrentTime();
	m_nLineCount = 0;
	ReadIntKey(m_level, "��־", "����", m_SystemParaPath);
	//m_level = LOG_INFO;
}


CLog::~CLog()
{
	::DeleteCriticalSection(&m_crit);    //�ͷ����ٽ���
}

///��ʼ����־(������־�ļ���·��).
/*================================================================ 
* ��������    InitLog
* ������      LPCTST lpszLogPath
* ��������:   ��ʼ����־(������־�ļ���·��)
* ����ֵ��    void
* �� �ߣ�     �̺��� 2005��01��06�� 
================================================================*/ 
void CLog::InitLog(LPCTSTR lpszLogPath)   
{ 
	//m_strLogFilename=lpszLogPath;
	m_strLogPath = lpszLogPath;
	CString sLogPath = m_strLogPath;
	int nPos = m_strLogPath.ReverseFind('\\');
	if(nPos == -1)
	{
		sLogPath = "";
	}
	else
	{
		sLogPath = sLogPath.Left(nPos);
	}

	//AfxGetApp()->m_
	CTime ct = CTime::GetCurrentTime();
	CString sLogFile,sLogFullname;
	//sLogFile.Format("grab.%s.log",ct.Format("%Y%m%d_%H%M"));
	//sLogFullname.Format("%s\\%s",sLogPath,sLogFile);
	sLogFile.Format("%s.log",ct.Format("%Y%m%d"));
	sLogFullname.Format("%s\\%s",sLogPath,sLogFile);


	if (IsFileExist(sLogFullname))
	{
		m_strLogFilename = sLogFullname;
		return;
	}

	//���Ŀ¼�����ھʹ���Ŀ¼
	BOOL bRet = FALSE;
	bRet = CreateMultiLevelPath(sLogPath);
	if(bRet == FALSE)
	{
		TRACE("Failed on creating log folder!\n");
		return ;
	}
	//����Log�ļ�
	HANDLE hFile = ::CreateFile(sLogFullname,
		GENERIC_WRITE ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE) {
		//TRACE("Failed on creating log file!\n");
		return;
	}
	else
	{
		CloseHandle(hFile);
	}

	m_strLogFilename = sLogFullname;
	m_LogFileTime = ct;
	m_nLineCount = 0;
}

void CLog::InitLog(LPCTSTR lpszLogPath, int level)   
{ 
	InitLog(lpszLogPath);
	SetLevel(level);
}

void CLog::Add(int level, const char* fmt, ...)
{
	if (level < m_level)
	{
		return;
	}

	if (m_strLogFilename.IsEmpty())
		return ;

	if (!AfxIsValidString(fmt, -1))
		return ;
	/*-----------------------�����ٽ���(д�ļ�)------------------------------------*/ 
	::EnterCriticalSection(&m_crit);   
	try      
	{
		va_list argptr;          //�����ַ����ĸ�ʽ
		va_start(argptr, fmt);
		_vsnprintf(m_tBuf, BUFSIZE, fmt, argptr);
		va_end(argptr);
	}
	catch (...)
	{
		m_tBuf[0] = 0;
	}

	m_nLineCount++;
	CTime ct = CTime::GetCurrentTime();
	if (ct.GetDay() != m_LogFileTime.GetDay())
	{
		InitLog(m_strLogPath);
	}
	else
	{
		// 		CTimeSpan tspan = ct - m_LogFileTime;
		// 		if (tspan > CTimeSpan(60*5))//����10����
		// 		{
		// 			DWORD dwFileSize=0;
		// 			HANDLE hFile = CreateFile(m_strLogFilename, 
		// 				GENERIC_READ | GENERIC_WRITE, 
		// 				0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 			
		// 			if (hFile != INVALID_HANDLE_VALUE) 
		// 			{ 				
		// 				dwFileSize = GetFileSize(hFile, NULL); 
		// 				CloseHandle(hFile);
		// 			}
		// 			if (dwFileSize > 400000)//4M
		// 			{
		// 				InitLog(m_strLogPath);
		// 			}
		// 		}

		if (m_nLineCount > 40000)//4����
		{
			InitLog(m_strLogPath);
		}

	}



	FILE *fp = fopen(m_strLogFilename, "a"); //����ӵķ�ʽ������ļ�
	if (fp)
	{
		fprintf(fp,"%s:  ", AfxGetApp()->m_pszExeName);  //���뵱ǰ������

		//���뵱ǰʱ��
		fprintf(fp,"%s : ",ct.Format("%m/%d/%Y %H:%M:%S"));
		fprintf(fp, "%s\n", m_tBuf);  
		fclose(fp);  
	} 
	::LeaveCriticalSection(&m_crit);  
	/*-------------------�˳��ٽ���----------------------------------------*/ 
}

void CLog::SetLevel(int level)
{
	m_level = level;
}

int CLog::GetLevel()
{
	return m_level;
}

void CLog::InitPCUsingLevel( LPCTSTR lpszLogPath )
{
	m_strLogPath = lpszLogPath;
	CString sLogPath = m_strLogPath;
	int nPos = m_strLogPath.ReverseFind('\\');
	if(nPos == -1)
	{
		sLogPath = "";
	}
	else
	{
		sLogPath = sLogPath.Left(nPos);
	}

	//AfxGetApp()->m_
	CTime ct = CTime::GetCurrentTime();
	// 	CString sLogFile,sLogFullname;
	// 	sLogFile.Format("pc.%s.log",ct.Format("%Y%m%d_%H%M%S"));
	// 	sLogFullname.Format("%s\\%s",sLogPath,sLogFile);

	if (IsFileExist(lpszLogPath))
	{
		m_strLogFilename = lpszLogPath;
		return;
	}

	//���Ŀ¼�����ھʹ���Ŀ¼
	BOOL bRet = FALSE;
	bRet = CreateMultiLevelPath(sLogPath);
	if(bRet == FALSE)
	{
		TRACE("Failed on creating log folder!\n");
		return ;
	}
	//����Log�ļ�
	HANDLE hFile = ::CreateFile(lpszLogPath,
		GENERIC_WRITE ,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE) {
		//TRACE("Failed on creating log file!\n");
		return;
	}
	else
	{
		CloseHandle(hFile);
	}

	m_strLogFilename = lpszLogPath;
	m_LogFileTime = ct;
	m_nLineCount = 0;
}

void CLog::DeletePCUsingLevel( LPCTSTR lpszLogPath )
{
	DeleteFile(lpszLogPath);

}
