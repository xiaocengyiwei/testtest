// FileOperate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Inspection.h"
#include "FileOperate.h"


// CFileOperate

// CFileOperate ��Ϣ�������





/************************************************************************/
/* Copyright (c) 2005, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�Ӿ�������     
/* All rights reserved.													
/*																		
/* �ļ����ƣ� FileOperate.cpp											
/* �ļ���ʶ�� �����ù���ƻ���
/* ժҪ�� ���漰�ļ������ĸ��ֺ������л���, �ṩ�ļ���·�����ò���,
/*    ���漰��ͼ���ļ�, �����ı��ļ��ȹ���
/*
/* ��ǰ�汾�� 1.0
/* ���ߣ� ��׿��
/* ������ڣ� 2005��10��10��
/************************************************************************/

#include "stdafx.h"
#include "FileOperate.h"


#define WIDTH_BYTES(bits) (((bits) + 31) / 32 * 4)

//����BMPͼ��ĺ���
BOOL SaveBMPFile(LPCSTR lpFileName, const BITMAPINFO *pBmpInfo, const BYTE *pImageBuffer)
{
	BOOL bRVal				= TRUE;
	DWORD dwBytesRead		= 0;
	DWORD dwSize			= 0;
	BITMAPFILEHEADER bfh	= {0};
	int nTable				= 0;
	DWORD dwImageSize		= 0;
	
	if (pBmpInfo->bmiHeader.biBitCount > 8) 
	{
		nTable = 0;
	}
	else
	{
		nTable = 256;	//����biBitCount == 24�������Ǵ�256����ɫ����ɫ.
	}
	
	dwImageSize =  (pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biHeight) 
		* ((pBmpInfo->bmiHeader.biBitCount + 7) / 8);
	//����4Bytes�ж���ĵ�imageSize,256ɫ��24bit��BMPͼƬ����4B�����.modified by Hongbo
	dwImageSize =  WIDTH_BYTES(pBmpInfo->bmiHeader.biWidth*pBmpInfo->bmiHeader.biBitCount)
				   * pBmpInfo->bmiHeader.biHeight;
	
	if (dwImageSize <= 0) 
	{
		bRVal = FALSE;
	}
	else{
		bfh.bfType		= (WORD)'M' << 8 | 'B';
		bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nTable * sizeof(RGBQUAD);
		bfh.bfSize		= bfh.bfOffBits + dwImageSize;			
		
		HANDLE hFile = ::CreateFile(lpFileName,
			GENERIC_WRITE ,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (hFile == INVALID_HANDLE_VALUE) {
			bRVal = FALSE;
		}
		else{
			dwSize = sizeof(BITMAPFILEHEADER);
			::WriteFile(hFile, &bfh, dwSize, &dwBytesRead, NULL );
			
			dwSize = sizeof(BITMAPINFOHEADER) + nTable * sizeof(RGBQUAD);
			::WriteFile(hFile, pBmpInfo, dwSize, &dwBytesRead, NULL );
			
			dwSize = dwImageSize;
			WriteFile(hFile, pImageBuffer, dwSize, &dwBytesRead, NULL );
			
			CloseHandle(hFile);
		}
	}
	
	return bRVal;
}

// ��ȡ��ִ�г������ڵ�·��
CString GetCurrentAppPath()
{
	/*char str[MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	CString AppPath;
	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath(str, drive, dir, fname, ext);
	strcat(drive, dir);
	AppPath = drive;

	return AppPath;
	*/
	//addbyqq
	char str[MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	CString AppPath;
	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath(str, drive, dir, fname, ext);
	sprintf(str,"%s%s",drive, dir);
	AppPath = str;
	return AppPath;
	//end add
	
}

//�ж�·���Ƿ����
BOOL IsPathExist(const CString &strPath)
{
	WIN32_FIND_DATA fd; 
	HANDLE hFind = FindFirstFile(strPath, &fd); 
	if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{ 
		FindClose(hFind);
		return TRUE; 
	} 
	else
	{
		FindClose(hFind); 
		return FALSE;
	}
}

//�ж��ļ��Ƿ����
BOOL IsFileExist(const CString &strFileName)
{
	CFileFind searcher;

	if(searcher.FindFile(strFileName))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//����һ�����Ŀ¼��������ھͲ�����
//(strPath  �Ϸ�: "D:\\abc\\me" �� "me\\you" �� ""; 
//			���Ϸ�: "D:\\abc\\me\\" �� "me\\you\\" �� "\\")
BOOL CreateMultiLevelPath(const CString &strPath)
{
	CString tmpPath = strPath;
	CList<CString,CString&> FolderStrList;
	int nStrLen = 0;
	
	for(;;)
	{
		nStrLen = tmpPath.GetLength();
		if(nStrLen <= 0)
		{
			break;//��ͷ���ļ���
		}		
	
		BOOL bPathExist = FALSE;//��·���Ƿ��Ѿ�����
		bPathExist = IsPathExist(tmpPath);
		if(bPathExist)//���·������
		{
			break;//���Ѵ��ڵ�·���½��ļ���
		}
		
		//���·��������		
		//ÿ�ν�����һ���ļ��������
		
		int nPos = 0;
		nPos = tmpPath.ReverseFind('\\');//�Ӻ���ǰȷ���ļ�����
		if(nPos == -1)//�ѵ����һ���ļ�����
		{
			nPos = 0;//����һ���ļ��������
		}
		
		//���ļ��������
		CString tmpStr = tmpPath.Right(nStrLen - nPos);
		FolderStrList.AddHead(tmpStr);
		tmpPath.Delete(nPos, nStrLen - nPos);		
	}	
	
	//�����ļ���������˳����
	while(FolderStrList.IsEmpty() == FALSE)
	{
		tmpPath += FolderStrList.RemoveHead();
		BOOL bRet = FALSE;
		bRet = CreateDirectory(tmpPath, NULL);
		if(bRet == FALSE)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL DeleteDirectory(char* sDirName) 
{ 
    CFileFind tempFind;
    char sTempFileFind[MAX_PATH];
    
    sprintf(sTempFileFind,"%s\\*.*",sDirName);
    BOOL IsFinded = tempFind.FindFile(sTempFileFind);
    while (IsFinded)
    {
        IsFinded = tempFind.FindNextFile();
        
		if (!tempFind.IsDots())   //�鿴�ļ����Ƿ��ǰ���"."��".."���Ա�������ȷ��һ��Ŀ¼//IsDots�ж��Ƿ�Ϊ�㣭�����Ҫ˵��һ�£��ù�Dos�Ļ�����Ӧ��֪����ÿ��Ŀ¼�¶���ȱʡ������Ŀ¼�����Ʒֱ�Ϊ '. '�� '.. '���ֱ������һ��Ŀ¼�ͱ���Ŀ¼����ˣ��������ڱ���Ŀ¼���ļ�ʱ����Ҫ���˵�������ȱʡĿ¼��

        { 
            char sFoundFileName[MAX_PATH]; 
            strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(MAX_PATH)); //CString תchar
            
            if (tempFind.IsDirectory()) 
            { 
                char sTempDir[MAX_PATH]; 
                sprintf(sTempDir,"%s\\%s",sDirName,sFoundFileName); 
                DeleteDirectory(sTempDir); 
            } 
            else 
            { 
                char sTempFileName[MAX_PATH]; 
                sprintf(sTempFileName,"%s\\%s",sDirName,sFoundFileName); 
                DeleteFile(sTempFileName); 
            } 
        } 
    } 
    tempFind.Close(); 
    if(!RemoveDirectory(sDirName)) //�����ʾ�ɹ������ʾʧ��
    { 
        return FALSE; 
    } 
    return TRUE; 
}



//дINI�ļ�
BOOL MyWriteIniFile(const CString& strFilePath, const CString& strSession, const CString& str)
{
	//����INI�ļ�Ŀ¼��ini�ļ���
	CString strIniPath, strIniFileName, strTime;
	CTime curTime = CTime::GetCurrentTime();
	
	strIniPath.Format("%s%s%4d%s%02d%s", strFilePath, "\\Ini\\", curTime.GetYear(), "��",curTime.GetMonth(), "��");
	strIniFileName.Format("%s%s%4d%02d%02d%s", strIniPath, "\\", curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), ".ini");
	strTime.Format("%02d%s%02d%s%02d", curTime.GetHour(), ":", curTime.GetMinute(), ":", curTime.GetSecond());
	
	//���Ŀ¼�����ھʹ���Ŀ¼
	BOOL bRet = FALSE;
	bRet = CreateMultiLevelPath(strIniPath);
	if(bRet == FALSE)
	{
		return FALSE;
	}

	//дini�ļ�
	bRet = WritePrivateProfileString(strSession, strTime, str, strIniFileName);
	return bRet;
}

//дBMP�ļ�
BOOL MyWriteBMPFile(const CString& strFileFullName, const PBITMAPINFO pBmpInfo, const BYTE *pImageBuffer)
{
	if(pBmpInfo == NULL || pImageBuffer == NULL)
	{
		return FALSE;
	}

	CString strFilePath;
	int nPos = strFileFullName.ReverseFind('\\');
	if(nPos == -1)
	{
		strFilePath = "";
	}
	else
	{
		strFilePath = strFileFullName.Left(nPos);
	}

	//���Ŀ¼�����ھʹ���Ŀ¼
	BOOL bRet = FALSE;
	bRet = CreateMultiLevelPath(strFilePath);
	if(bRet == FALSE)
	{
		return FALSE;
	}
	
	//дBMP�ļ�
	bRet = SaveBMPFile(strFileFullName, pBmpInfo, pImageBuffer);
	return bRet;	
	
/*	//����INI�ļ�Ŀ¼��ini�ļ���
	CString strBMPPath, strBMPFileName;
	CTime curTime = CTime::GetCurrentTime();
	
	strBMPPath.Format("%s\\ErrorImage", strAppPath);
	strBMPFileName.Format("%s\\%04d_%02d_%02d_%02d_%02d_%02d.bmp",
		strBMPPath, 
		curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 
		curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond()
		);
*/
}

//д�������е��ַ���˳��д���ļ�
BOOL MyWriteStringFile(const CString& strFilePath, const CString& strFileName, const CList<CString,CString&>& lCheckRltStrList)
{ 
	//////////////////////////////////////////////////////////////////////////
	//
	BOOL bRet = FALSE;
	bRet = CreateMultiLevelPath(strFilePath);
	if(bRet == FALSE)
	{
		return FALSE;
	}

	CString strFileFullName;
	strFileFullName.Format("%s\\%s", strFilePath, strFileName);
	
	CString cstr ;
	POSITION pos = lCheckRltStrList.GetHeadPosition();
	int nSumL = lCheckRltStrList.GetCount() ;
	for (int i=0; i<nSumL ; i++)
	{
		cstr.Format( "NO.%d", i) ;
		bRet = WritePrivateProfileString("Start",cstr,(LPCSTR) lCheckRltStrList.GetNext(pos), strFileFullName);
		if(bRet == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
	//
	//////////////////////////////////////////////////////////////////////////

	/*
	CTime ctm = CTime::GetCurrentTime();
	CString strName = ctm.Format( "D:\\TXT" );
	CreateDirectory(strName, NULL) ;
	strName = ctm.Format( "D:\\TXT\\%b-%d" );
	CreateDirectory(strName, NULL) ;
	
	strName = ctm.Format( "D:\\TXT\\%b-%d\\T-%H-%M-%S.TXT" );*/
}

//////////////////////////////////////////////////////////////////////////
//��ͼ���ļ�����
BOOL OpenBMPFile(LPCSTR lpFileName, BITMAPINFO *pBmpInfo, BYTE *pImageBuffer)
{
	BOOL bRVal = TRUE;
	DWORD dwBytesRead = 0;
	DWORD dwSize = 0;
	BITMAPFILEHEADER bfh;
	
	HANDLE hFile = ::CreateFile(lpFileName,
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL
								);
	if (hFile == INVALID_HANDLE_VALUE) {
		bRVal = FALSE;
	}
	else{
		dwSize = sizeof(BITMAPFILEHEADER);
		::ReadFile(hFile, &bfh, dwSize, &dwBytesRead, NULL );
		if (bfh.bfType != ((WORD)'M' << 8 | 'B')) {
			bRVal = FALSE;
		}
		else{
			dwSize = sizeof(BITMAPINFOHEADER);
			::ReadFile(hFile, pBmpInfo, dwSize, &dwBytesRead, NULL);
			if(bfh.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) > 0)//if (pBmpInfo->bmiHeader.biBitCount <= 8)//[2006-11-02]		
			{
				dwSize = bfh.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
				if (dwSize > 4)
				{
					BYTE* pTempBuff = new BYTE[dwSize];
					ReadFile(hFile,
						pTempBuff,	//����ĿΪ�Ҷ�ͼ,��ɫ����Ϣû����,����.
						dwSize,
						&dwBytesRead,
						NULL
						);
					delete[] pTempBuff;
				}
				else
				ReadFile(hFile,
					(char *)pBmpInfo + sizeof(BITMAPINFOHEADER),//sizeof(RGBQUAD) = 4,if dwSize>4,error!!! ACCESS VIOLATION!!!
					dwSize,
					&dwBytesRead,
					NULL
					);
			}
			
			dwSize = WIDTH_BYTES(pBmpInfo->bmiHeader.biWidth * pBmpInfo->bmiHeader.biBitCount) *
				pBmpInfo->bmiHeader.biHeight;
			
			ReadFile(hFile, pImageBuffer, dwSize, &dwBytesRead, NULL);
			ASSERT(dwSize == dwBytesRead);
		}
		
		CloseHandle(hFile);
	}
	
	return bRVal;
}
