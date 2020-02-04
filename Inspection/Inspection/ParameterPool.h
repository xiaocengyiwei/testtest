#pragma once
#include "HalconCpp.h"
using namespace Halcon;

#define CAM_NUM 6
#define MAX_WIDTH_STORED 1000   //Ԥ���������1000

#define DEFAULT_CAM_SELECTED 0 //Ĭ��ѡ������� 
#define CAM_POS_SINGLE 0
#define CAM_POS_LEFT 1
#define CAM_POS_CENTER 2
#define CAM_POS_RIGHT 3

#define TOTALTYPES 100
//���ȱ������
#define OTHER 0
#define PINHOLE 1
#define WELD 2
#define EDGE 3
//����ȱ������  OTHER����0
#define DEFECT 10   //δ����ȱ��
#define DEEP_S 11
#define DEEP_M 12
#define DEEP_L 13
#define SHALLOW_S 14
#define SHALLOW_M 15
#define SHALLOW_L 16
#define OVER_CROWDED 17
#define DEEP_S2 18
#define DEEP_M2 19
#define DEEP_L2 20
#define SHALLOW_S2 21
#define SHALLOW_M2 22
#define SHALLOW_L2 23
#define VERT_LINE 24  //������
#define HOR_LINE  25  //������

#define DEEP_REGION 0
#define SHALLOW_REGION 1
#define DEEP_REGION2 2
#define SHALLOW_REGION2 3
#define WIDTH_STRIPE 4
#define HEIGHT_STRIPE 5

#define GRAY_MIN 0
#define GRAY_MAX 255

#define DYN_MODE_LIGHT 0
#define DYN_MODE_DARK  1
#define DYN_MODE_NOTEQUAL  2
#define DYN_MODE_DIRECE 3

#define  MAX_LEN 256
#define  AREA_MAX 99999999



class CParameterPool
{
public:
	CParameterPool(void);
	~CParameterPool(void);

	//�����������
public:
	Hobject m_hOriginalImage[CAM_NUM];
	Hobject m_hCheckRegion[CAM_NUM];  //�ֶ����õļ������

	int m_CamPos[CAM_NUM];   //���λ��
	int m_SetParaMothod;

	int m_ImgLeftOffset[CAM_NUM];
	int m_ImgRightOffset[CAM_NUM];

	int m_ImageWidth[CAM_NUM];
	float m_Resolution_W[CAM_NUM];  //����ֱ���

	//��������
public:
	int m_TotalInitCamNum;   //��ʼ�������������0��ʼ�ģ�ʹ��ʱ����ע��

	int m_ImageHeight;
	float m_Resolution_H;  //����ֱ���
	//�׶�������
	int m_PinHoleArea;   //�׶���������ص�λ��
	int m_MaxReturnNum;   //���ص��������
	int m_ProductGray;   //��Ʒ���Ҷ�ֵ
	int m_PinHoleGray;   //�׶��Ҷ�
	int m_WeldArea_Min;   //���������Сֵ
	int m_WeldArea_Max;   //����������ֵ

	//��Ե
	BOOL m_IfCheckEdge;   //�Ƿ����Ե
	int m_EdgeArea;   //��Ե��������ص�λ��
	int m_EdgeWidth;   //��Ե���
	int m_EdgeDepth;    //��Ե���

	//��������
	BOOL m_AlarmFlag[TOTALTYPES];

	//��¼����
	BOOL m_IfRecord[TOTALTYPES];

	//���
	int m_WidthGray;   //���Ҷ�
	int m_StoredNum;   //��������
	float m_Overlap_Width;   //�ص����

	//****************//
	//Surface
	int m_Surf_ProdGray_Low;    //�������Ʒ�Ҷ���Сֵ
	int m_Surf_ProdGray_High; //�������Ʒ�Ҷ����ֵ
	int m_Surf_ProdArea;    //����������ڸ�ֵ����Ϊ�ǲ�Ʒ����
	int m_Surf_MeanW1;      
	int m_Surf_MeanH1;
	int m_Surf_MeanW2;
	int m_Surf_MeanH2;
	int m_Surf_CloseW;   //Ԥ����Close
	int m_Surf_CloseH;
	int m_Surf_EroseW;   //Ԥ����Erose
	int m_Surf_EroseH;

	int m_Surf_DynThresh1;  //��̬��ֵ1
	int m_Surf_DynMode_1;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_W1;
	int m_Surf_Close_H1;
	int m_Surf_DynThresh2;  //��̬��ֵ2
	int m_Surf_DynMode_2;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_W2;
	int m_Surf_Close_H2;
	int m_Surf_DynThresh3;  //��̬��ֵ3
	int m_Surf_DynMode_3;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_1C3;
	int m_Surf_Close_2C3;
	int m_Surf_DynThresh4;  //��̬��ֵ4
	int m_Surf_DynMode_4;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_1C4;
	int m_Surf_Close_2C4;

	//��״����
	int m_Surf_Stripe_Close_WC5;
	int m_Surf_Stripe_Close_HC5;
	int m_Surf_Stripe_W1, m_Surf_Stripe_W2;
	int m_Surf_Stripe_H1, m_Surf_Stripe_H2;

	int m_Surf_Area_Min;   //��С��������ص�λ

	int m_Surf_Thresh_Deep;   //��ȱ�ݵ���ֵ
	int m_Surf_DeepSizePixS;   //����С���������
	int m_Surf_DeepSizePixM;
	int m_Surf_DeepSizePixL;
	float m_Surf_DeepSizeAreaS;   //����С��ʵ�������ƽ������
	float m_Surf_DeepSizeAreaM;
	float m_Surf_DeepSizeAreaL;
	float m_Surf_DeepSizeDiamS;   //����С�Ĳο�ֱ��������
	float m_Surf_DeepSizeDiamM;
	float m_Surf_DeepSizeDiamL;
	int m_Surf_DeepScoreS;    //����С������
	int m_Surf_DeepScoreM;
	int m_Surf_DeepScoreL;

	int m_Surf_Thresh_Shallow;   //ǳȱ�ݵ���ֵ
	int m_Surf_ShallowSizePixS;   //����С���������
	int m_Surf_ShallowSizePixM;
	int m_Surf_ShallowSizePixL;
	float m_Surf_ShallowSizeAreaS;   //����С��ʵ�������ƽ������
	float m_Surf_ShallowSizeAreaM;
	float m_Surf_ShallowSizeAreaL;
	float m_Surf_ShallowSizeDiamS;   //����С�Ĳο�ֱ��������
	float m_Surf_ShallowSizeDiamM;
	float m_Surf_ShallowSizeDiamL;
	int m_Surf_ShallowScoreS;    //����С������
	int m_Surf_ShallowScoreM;
	int m_Surf_ShallowScoreL;

	int m_Surf_Thresh_Deep2;   //��ֵ3
	int m_Surf_DeepSizePixS2;   //����С���������
	int m_Surf_DeepSizePixM2;
	int m_Surf_DeepSizePixL2;
	float m_Surf_DeepSizeAreaS2;   //����С��ʵ�������ƽ������
	float m_Surf_DeepSizeAreaM2;
	float m_Surf_DeepSizeAreaL2;
	float m_Surf_DeepSizeDiamS2;   //����С�Ĳο�ֱ��������
	float m_Surf_DeepSizeDiamM2;
	float m_Surf_DeepSizeDiamL2;
	int m_Surf_DeepScoreS2;    //����С������
	int m_Surf_DeepScoreM2;
	int m_Surf_DeepScoreL2;

	int m_Surf_Thresh_Shallow2;   //��ֵ4
	int m_Surf_ShallowSizePixS2;   //����С���������
	int m_Surf_ShallowSizePixM2;
	int m_Surf_ShallowSizePixL2;
	float m_Surf_ShallowSizeAreaS2;   //����С��ʵ�������ƽ������
	float m_Surf_ShallowSizeAreaM2;
	float m_Surf_ShallowSizeAreaL2;
	float m_Surf_ShallowSizeDiamS2;   //����С�Ĳο�ֱ��������
	float m_Surf_ShallowSizeDiamM2;
	float m_Surf_ShallowSizeDiamL2;
	int m_Surf_ShallowScoreS2;    //����С������
	int m_Surf_ShallowScoreM2;
	int m_Surf_ShallowScoreL2;

	int m_Surf_VertLineScore;   //����������
	int m_Surf_HorLineScore;    //����������

	int m_Surf_TotalScore;    //�ܷ�

	//�ܶ�
// 	int m_Surf_DensitySizeWidth;
// 	int m_Surf_DensitySizeHeight;
// 	float m_Surf_DensitySizeWidthMM;
// 	float m_Surf_DensitySizeHeightMM;
// 	int m_Surf_DensityCount;

	//Alarm & Tag
//	BOOL m_Surf_IfDensityTag;    //17
	BOOL m_Surf_IfDeepSTag;      //11
	BOOL m_Surf_IfDeepMTag;      //12
	BOOL m_Surf_IfDeepLTag;      //13
	BOOL m_Surf_IfShallowSTag;   //14
	BOOL m_Surf_IfShallowMTag;   //15
	BOOL m_Surf_IfShallowLTag;   //16

	BOOL m_Surf_IfDeepSTag2;      //
	BOOL m_Surf_IfDeepMTag2;      //
	BOOL m_Surf_IfDeepLTag2;      //
	BOOL m_Surf_IfShallowSTag2;   //
	BOOL m_Surf_IfShallowMTag2;   //
	BOOL m_Surf_IfShallowLTag2;   //

	BOOL m_Surf_IfVertLineTag;
	BOOL m_Surf_IfHorLineTag;
	
	int m_Surf_AlarmLength;
	int m_Surf_TagLength;

	float m_Surf_Calib;  //Diameter
	float m_Surf_Calib2;   //Area

	//fast check
//	BOOL m_Surf_IfFastCheck;   //�Ƿ�ʹ�ÿ��ټ�⣨�̶���ֵ��
//	int m_Surf_ErrGray1;
//	int m_Surf_ErrGray2;
	//��������˳�
	float m_fHorAndVorRatio;
	int m_iRecordWidthLine;
	int m_iMinWidthGray;
	int m_iMaxWidthGray;


	//��������
public:
	void ZeroArrays();
	void Convert2Himage(const char *Image, int CamIndex);   //����ͼ���ת��
	void GenCheckRegion();   //�������еļ������

public:
	char m_CurrPath[MAX_PATH];
	CString m_SettingDirPath;   //setting�ļ���·��
	CString m_CameraParaPath;   //����������������ļ���
	CString m_CheckParaPath[CAM_NUM];    //�����������ļ��� 
	CString m_SurfaceParaPath[CAM_NUM];  //��������������ļ���
	CString m_SystemParaPath;
	CString m_ParaSetModel;

	void GetCurrPath(char **path);
	void InitSettingPath();

	void LoadAllPara(int Index);  //��ȡȫ������
	void SaveAllPara(int Index);  //����ȫ������
	void LoadCameraPara(int Index);  //��ȡָ���������
	void SaveCameraPara(int Index);  //����ָ���������

	void LoadSetModel();
	void SaveSetModel();

	void LoadCheckPara(int Index);   //��ȡͨ�ü�����
	void SaveCheckPara(int Index);  //����ͨ�ü�����

	CString LoadToStrB();
	CString LoadToStrC();
	CString ClearLoadToStrB();
	CString ClearLoadToStrC();

	CString GetErrString(int Indexs);
	void ReadIntKey(int &data, CString strApp, CString strKey, CString filePath);
	void ReadFloatKey(float &data, CString strApp, CString strKey, CString filePath);
	void ReadStrKey(CString &data, CString strApp, CString strKey, CString filePath);
	void WriteIntKey(int data, CString strApp, CString strKey, CString filePath);
	void WriteFloatKey(float data, CString strApp, CString strKey, CString filePath);
	CParameterPool& operator = (const CParameterPool&);
};
