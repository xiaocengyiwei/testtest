#if !defined(CHECKPARA)
#define CHECKPARA

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector"
//#include "StdAfx.h"

using namespace std;
/*
typedef struct{
	int  nRegionType; //�����������
	//����
	char strRegionType[64];  //��������ַ���������ֵΪ�����桱�����桱
	// end fo ����
	RECT rect;		 // ������������������
	int  Errortype;  // ��������
	//���ӣ�
	char strErrortype[64];  //���������ַ���������ֵΪ�����ߡ��������ϡ���ȱ����������
	// end of ����
	int ErrorContrast; //ȱ�ݶԱȶ�
	float  ErrorArea;  // �������
	float Diameter;
	char Descript[256];  //�ַ������� 
	int  nLevel;	 // ����̶�
	int x;          //ȱ��ˮƽ��������
	int y;          //ȱ�ݴ�ֱ��������
	float fFeature[20];
	BOOL ifTag;  //�Ƿ���
	int tagLength;  //����������
}ErrorRegion;		// ��������
*/
typedef struct{
	int Defection;   //ȱ�ݼ�Ȩ�ܶ�
	bool AlarmFlag;    //�Ƿ񱨾�
	int AlarmLength;   //��������ʱ��
	int Width;      //ͼ��������
	int Height;    //ͼ��߶�����
	char Comment[128];   //����˵��
	float Calc_Width;   //�����ͼ���ȣ����ף�
}Assesment;

typedef struct{
	long ErrArea;
	double  CenterGrayVal;
}ErrClassifier;

#endif