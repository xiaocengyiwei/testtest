#pragma once


// CFileOperate



#if !defined(FileOperate_h_)
#define FileOperate_h_

#include <afxtempl.h>//Ϊ��ʹ��CList

///����BMPͼ��ĺ���
BOOL SaveBMPFile(LPCSTR lpFileName, const BITMAPINFO *pBmpInfo, const BYTE *pImageBuffer);

///��ȡ��ִ�г������ڵ�·��
CString GetCurrentAppPath();

///�ж�·���Ƿ����
BOOL IsPathExist(const CString &strPath);

///�ж��ļ��Ƿ����
BOOL IsFileExist(const CString &strFileName);

///����һ�����Ŀ¼��������ھͲ�����.
///(strPath  �Ϸ�: "D:\\abc\\me" �� "me\\you" �� ""; 
///			���Ϸ�: "D:\\abc\\me\\" �� "me\\you\\" �� "\\")
BOOL CreateMultiLevelPath(const CString &strPath);

///дINI�ļ�
BOOL MyWriteIniFile(const CString& strFilePath, const CString& strSession, const CString& str);

///дBMP�ļ�
BOOL MyWriteBMPFile(const CString& strFileFullName, const PBITMAPINFO pBmpInfo, const BYTE *pImageBuffer);

///д�������е��ַ���˳��д���ļ�
BOOL MyWriteStringFile(const CString& strFilePath, const CString& strFileName, const CList<CString,CString&>& lCheckRltStrList);

///��ͼ���ļ�����
BOOL OpenBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer);

///ɾ��Ŀ¼(�ݹ�ɾ��)
BOOL DeleteDirectory(char* sDirName);


#endif // !define(FileOperate_h_)
