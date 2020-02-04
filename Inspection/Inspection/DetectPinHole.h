#pragma once

#include <vector>
#include "datatype.h"
#include "halconcpp.h"
#include "ParameterPool.h"
#include "Result.h"
using namespace std;
using namespace Halcon;


class CDetectPinHole
{
public:
	CDetectPinHole(void);
	~CDetectPinHole(void);

private:
	int m_CamIndex;
public:
	typedef struct{
		ErrorRegion retResults;  //���ص�����

		Hlong regionWidthPix, regionHeightPix;  //ȱ�ݱ���Ŀ��

		Hlong errAreaPix;
		Hlong sImgLeft, sImgRight, sImgTop, sImgBotton;  //���ɵ�Сͼ���� 
		bool ifInterWithEdge;   //�Ƿ����Ե�����н���
		bool ifNearEdge; //�Ƿ񿿽���Ե
		Hlong errHeight, errWidth;  //�ָ�Ĵ���Ե������
		Hlong sImageHeight, sImageWidth;   //Сͼ������
	}Features;   //����
	char m_DefectName[100][64];  //����ȱ�ݱ��
public:
	Hobject m_hImgReduced;  //���ú��ͼ��
	Hobject m_hProductRegion;   //��Ʒ����
	Hobject m_hRegionMoved;   //�ƶ�������
	Hlong m_ProdC1, m_ProdC2, m_ProdR1, m_ProdR2;   //��Ʒ�������
	Hlong m_WidthC1, m_WidthC2, m_WidthR1, m_WidthR2;  //���
	Hobject m_hSelectedRegion;   //ѡ�е�Ҫ����������
	Hobject m_hProcessRegion;   //�����е�����
	Hobject m_hWidthRegion;  //�������õ�����
	Hobject m_hTagRegion;   //����ǩ�õ�

public:
	bool m_ifContinue;   //ȷ���Ƿ��⵽����
	HTuple m_ImageCenterRow, m_ImageCenterCol;   //����������������

public:
	vector<ErrorRegion> m_TheBlackList;   //ȱ���б�
	vector<Features> m_Features;   //���ڷ������������

public:
	int m_DefectOcc[TOTALTYPES];

public:
	void InitCamIndex(int Index);
	int  DetectPinHole(vector<ErrorRegion> **DefectList, int &ErrorCount);
	int  ClassifyDefects(const Halcon::Hobject &InputRegion, long Index);
	void CalculateFeatures(const Halcon::Hobject &InputRegion, long Index);
	void CopyResults(int &ErrorCount);  //���ƽ��
};
