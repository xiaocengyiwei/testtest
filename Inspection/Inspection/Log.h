#pragma once


#ifndef _LOG_H
#define _LOG_H

#define LOG_TRACE 1
#define LOG_DEBUG 2
#define LOG_INFO  3
#define LOG_WARN  4
#define LOG_ERROR 5
#define LOG_FATAL 6
#define LOG_OFF   7

#define INITLOG(path)			__g_log.InitLog(path)
#define INITPCUSINGLOG(path)    __g_log.InitPCUsingLevel(path)
#define DELETEPCUSINGLOG(path)  __g_log.DeletePCUsingLevel(path)
//#define INITLOG(path,level)		__g_log.InitLog(path,level)
#define LogSetLevel(level)		__g_log.SetLevel(level)
#define LogGetLevel()			__g_log.GetLevel()

#define LOG(p1)					__g_log.Add(LOG_INFO, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LOG1(fmt,p1)			__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LOG2(fmt,p1,p2)			__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LOG3(fmt,p1,p2,p3)		__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LOG4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogTrace(p1)				__g_log.Add(LOG_TRACE, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogTrace1(fmt,p1)			__g_log.Add(LOG_TRACE, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LogTrace2(fmt,p1,p2)		__g_log.Add(LOG_TRACE, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogTrace3(fmt,p1,p2,p3)		__g_log.Add(LOG_TRACE, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogTrace4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_TRACE, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogDebug(p1)				__g_log.Add(LOG_DEBUG, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogDebug1(fmt,p1)			__g_log.Add(LOG_DEBUG, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LogDebug2(fmt,p1,p2)		__g_log.Add(LOG_DEBUG, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogDebug3(fmt,p1,p2,p3)		__g_log.Add(LOG_DEBUG, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogDebug4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_DEBUG, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogInfo(p1)					__g_log.Add(LOG_INFO, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogInfo1(fmt,p1)			__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1)
//LogInfo1("OnBegin():开始检测:%d", GetTickCount()); 
#define LogInfo2(fmt,p1,p2)			__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogInfo3(fmt,p1,p2,p3)		__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogInfo4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_INFO, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogWarn(p1)					__g_log.Add(LOG_WARN, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogWarn1(fmt,p1)			__g_log.Add(LOG_WARN, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LogWarn2(fmt,p1,p2)			__g_log.Add(LOG_WARN, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogWarn3(fmt,p1,p2,p3)		__g_log.Add(LOG_WARN, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogWarn4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_WARN, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogError(p1)				__g_log.Add(LOG_ERROR, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogError1(fmt,p1)			__g_log.Add(LOG_ERROR, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LogError2(fmt,p1,p2)		__g_log.Add(LOG_ERROR, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogError3(fmt,p1,p2,p3)		__g_log.Add(LOG_ERROR, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogError4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_ERROR, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)

#define LogFatal(p1)				__g_log.Add(LOG_FATAL, "%s,%d: %s",__FILE__,__LINE__,p1)
#define LogFatal1(fmt,p1)			__g_log.Add(LOG_FATAL, "%s,%d: "fmt,__FILE__,__LINE__,p1)
#define LogFatal2(fmt,p1,p2)		__g_log.Add(LOG_FATAL, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2)
#define LogFatal3(fmt,p1,p2,p3)		__g_log.Add(LOG_FATAL, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3)
#define LogFatal4(fmt,p1,p2,p3,p4)	__g_log.Add(LOG_FATAL, "%s,%d: "fmt,__FILE__,__LINE__,p1,p2,p3,p4)
#define  MAX_LEN 256
///日志类.
class CLog
{
public:
	CLog();
	~CLog();

public:
	void InitLog(LPCTSTR lpszLogPath);  
	void InitLog(LPCTSTR lpszLogPath, int level);  
	void Add(const char* fmt, ...);  //输出文字，参数就跟printf一样
	void Add(int level ,const char* fmt, ...);

	void SetLevel(int level);
	int  GetLevel();
	void InitPCUsingLevel(LPCTSTR lpszLogPath);
	void DeletePCUsingLevel(LPCTSTR lpszLogPath);


	CString m_SystemParaPath;
	char m_CurrPath[MAX_PATH];
	void GetCurrPath(char **path);
	void InitSettingPath();
	void ReadIntKey(int &data, CString strApp, CString strKey, CString filePath);
	void LoadCheckPara(); 


protected:
	enum {BUFSIZE = 4069};  //工作缓冲区
	char  m_tBuf[BUFSIZE];

	CString  m_strLogFilename;
	CString  m_strLogPath;
	CRITICAL_SECTION  m_crit;  //设置一个临界区
private:
	CTime m_LogFileTime;
	DWORD m_nLineCount;
	int   m_level;				//Log的级别,大于该级别的log信息才写入文件.
};

extern CLog __g_log;

#endif



