#pragma once


// CFileOperate



#if !defined(FileOperate_h_)
#define FileOperate_h_

#include <afxtempl.h>//为了使用CList

///保存BMP图像的函数
BOOL SaveBMPFile(LPCSTR lpFileName, const BITMAPINFO *pBmpInfo, const BYTE *pImageBuffer);

///获取本执行程序所在的路径
CString GetCurrentAppPath();

///判断路径是否存在
BOOL IsPathExist(const CString &strPath);

///判断文件是否存在
BOOL IsFileExist(const CString &strFileName);

///创建一个多层目录，如果存在就不创建.
///(strPath  合法: "D:\\abc\\me" 或 "me\\you" 或 ""; 
///			不合法: "D:\\abc\\me\\" 或 "me\\you\\" 或 "\\")
BOOL CreateMultiLevelPath(const CString &strPath);

///写INI文件
BOOL MyWriteIniFile(const CString& strFilePath, const CString& strSession, const CString& str);

///写BMP文件
BOOL MyWriteBMPFile(const CString& strFileFullName, const PBITMAPINFO pBmpInfo, const BYTE *pImageBuffer);

///写将链表中的字符串顺序写入文件
BOOL MyWriteStringFile(const CString& strFilePath, const CString& strFileName, const CList<CString,CString&>& lCheckRltStrList);

///打开图像文件函数
BOOL OpenBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer);

///删除目录(递归删除)
BOOL DeleteDirectory(char* sDirName);


#endif // !define(FileOperate_h_)
