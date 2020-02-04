#pragma once
#include "HalconCpp.h"
using namespace Halcon;

#define CAM_NUM 6
#define MAX_WIDTH_STORED 1000   //预存张数最多1000

#define DEFAULT_CAM_SELECTED 0 //默认选中相机号 
#define CAM_POS_SINGLE 0
#define CAM_POS_LEFT 1
#define CAM_POS_CENTER 2
#define CAM_POS_RIGHT 3

#define TOTALTYPES 100
//针孔缺陷类型
#define OTHER 0
#define PINHOLE 1
#define WELD 2
#define EDGE 3
//表面缺陷类型  OTHER还是0
#define DEFECT 10   //未分类缺陷
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
#define VERT_LINE 24  //竖向暗纹
#define HOR_LINE  25  //横向暗纹

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

	//相机独立参数
public:
	Hobject m_hOriginalImage[CAM_NUM];
	Hobject m_hCheckRegion[CAM_NUM];  //手动设置的检测区域

	int m_CamPos[CAM_NUM];   //相机位置
	int m_SetParaMothod;

	int m_ImgLeftOffset[CAM_NUM];
	int m_ImgRightOffset[CAM_NUM];

	int m_ImageWidth[CAM_NUM];
	float m_Resolution_W[CAM_NUM];  //横向分辨率

	//公共参数
public:
	int m_TotalInitCamNum;   //初始化的相机数，从0开始的，使用时候请注意

	int m_ImageHeight;
	float m_Resolution_H;  //纵向分辨率
	//孔洞检测参数
	int m_PinHoleArea;   //孔洞面积（像素单位）
	int m_MaxReturnNum;   //返回的最大数量
	int m_ProductGray;   //产品区灰度值
	int m_PinHoleGray;   //孔洞灰度
	int m_WeldArea_Min;   //焊缝面积最小值
	int m_WeldArea_Max;   //焊缝面积最大值

	//边缘
	BOOL m_IfCheckEdge;   //是否检测边缘
	int m_EdgeArea;   //边缘面积（像素单位）
	int m_EdgeWidth;   //边缘宽度
	int m_EdgeDepth;    //边缘深度

	//报警参数
	BOOL m_AlarmFlag[TOTALTYPES];

	//记录参数
	BOOL m_IfRecord[TOTALTYPES];

	//测宽
	int m_WidthGray;   //测宽灰度
	int m_StoredNum;   //保存张数
	float m_Overlap_Width;   //重叠宽度

	//****************//
	//Surface
	int m_Surf_ProdGray_Low;    //表面检测产品灰度最小值
	int m_Surf_ProdGray_High; //表面检测产品灰度最大值
	int m_Surf_ProdArea;    //区域面积大于该值则认为是产品区域
	int m_Surf_MeanW1;      
	int m_Surf_MeanH1;
	int m_Surf_MeanW2;
	int m_Surf_MeanH2;
	int m_Surf_CloseW;   //预处理Close
	int m_Surf_CloseH;
	int m_Surf_EroseW;   //预处理Erose
	int m_Surf_EroseH;

	int m_Surf_DynThresh1;  //动态阈值1
	int m_Surf_DynMode_1;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_W1;
	int m_Surf_Close_H1;
	int m_Surf_DynThresh2;  //动态阈值2
	int m_Surf_DynMode_2;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_W2;
	int m_Surf_Close_H2;
	int m_Surf_DynThresh3;  //动态阈值3
	int m_Surf_DynMode_3;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_1C3;
	int m_Surf_Close_2C3;
	int m_Surf_DynThresh4;  //动态阈值4
	int m_Surf_DynMode_4;  //0:light, 1:dark, 2:not equal
	int m_Surf_Close_1C4;
	int m_Surf_Close_2C4;

	//条状暗纹
	int m_Surf_Stripe_Close_WC5;
	int m_Surf_Stripe_Close_HC5;
	int m_Surf_Stripe_W1, m_Surf_Stripe_W2;
	int m_Surf_Stripe_H1, m_Surf_Stripe_H2;

	int m_Surf_Area_Min;   //最小面积，像素单位

	int m_Surf_Thresh_Deep;   //深缺陷的阈值
	int m_Surf_DeepSizePixS;   //大中小的像素面积
	int m_Surf_DeepSizePixM;
	int m_Surf_DeepSizePixL;
	float m_Surf_DeepSizeAreaS;   //大中小的实际面积，平方毫米
	float m_Surf_DeepSizeAreaM;
	float m_Surf_DeepSizeAreaL;
	float m_Surf_DeepSizeDiamS;   //大中小的参考直径，毫米
	float m_Surf_DeepSizeDiamM;
	float m_Surf_DeepSizeDiamL;
	int m_Surf_DeepScoreS;    //大中小的评分
	int m_Surf_DeepScoreM;
	int m_Surf_DeepScoreL;

	int m_Surf_Thresh_Shallow;   //浅缺陷的阈值
	int m_Surf_ShallowSizePixS;   //大中小的像素面积
	int m_Surf_ShallowSizePixM;
	int m_Surf_ShallowSizePixL;
	float m_Surf_ShallowSizeAreaS;   //大中小的实际面积，平方毫米
	float m_Surf_ShallowSizeAreaM;
	float m_Surf_ShallowSizeAreaL;
	float m_Surf_ShallowSizeDiamS;   //大中小的参考直径，毫米
	float m_Surf_ShallowSizeDiamM;
	float m_Surf_ShallowSizeDiamL;
	int m_Surf_ShallowScoreS;    //大中小的评分
	int m_Surf_ShallowScoreM;
	int m_Surf_ShallowScoreL;

	int m_Surf_Thresh_Deep2;   //阈值3
	int m_Surf_DeepSizePixS2;   //大中小的像素面积
	int m_Surf_DeepSizePixM2;
	int m_Surf_DeepSizePixL2;
	float m_Surf_DeepSizeAreaS2;   //大中小的实际面积，平方毫米
	float m_Surf_DeepSizeAreaM2;
	float m_Surf_DeepSizeAreaL2;
	float m_Surf_DeepSizeDiamS2;   //大中小的参考直径，毫米
	float m_Surf_DeepSizeDiamM2;
	float m_Surf_DeepSizeDiamL2;
	int m_Surf_DeepScoreS2;    //大中小的评分
	int m_Surf_DeepScoreM2;
	int m_Surf_DeepScoreL2;

	int m_Surf_Thresh_Shallow2;   //阈值4
	int m_Surf_ShallowSizePixS2;   //大中小的像素面积
	int m_Surf_ShallowSizePixM2;
	int m_Surf_ShallowSizePixL2;
	float m_Surf_ShallowSizeAreaS2;   //大中小的实际面积，平方毫米
	float m_Surf_ShallowSizeAreaM2;
	float m_Surf_ShallowSizeAreaL2;
	float m_Surf_ShallowSizeDiamS2;   //大中小的参考直径，毫米
	float m_Surf_ShallowSizeDiamM2;
	float m_Surf_ShallowSizeDiamL2;
	int m_Surf_ShallowScoreS2;    //大中小的评分
	int m_Surf_ShallowScoreM2;
	int m_Surf_ShallowScoreL2;

	int m_Surf_VertLineScore;   //竖向暗纹评分
	int m_Surf_HorLineScore;    //横向暗纹评分

	int m_Surf_TotalScore;    //总分

	//密度
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
//	BOOL m_Surf_IfFastCheck;   //是否使用快速检测（固定阈值）
//	int m_Surf_ErrGray1;
//	int m_Surf_ErrGray2;
	//横向干扰滤除
	float m_fHorAndVorRatio;
	int m_iRecordWidthLine;
	int m_iMinWidthGray;
	int m_iMaxWidthGray;


	//变量操作
public:
	void ZeroArrays();
	void Convert2Himage(const char *Image, int CamIndex);   //单张图像的转换
	void GenCheckRegion();   //生成所有的检测区域

public:
	char m_CurrPath[MAX_PATH];
	CString m_SettingDirPath;   //setting文件夹路径
	CString m_CameraParaPath;   //相机独立参数配置文件名
	CString m_CheckParaPath[CAM_NUM];    //检测参数配置文件名 
	CString m_SurfaceParaPath[CAM_NUM];  //表面检测参数配置文件名
	CString m_SystemParaPath;
	CString m_ParaSetModel;

	void GetCurrPath(char **path);
	void InitSettingPath();

	void LoadAllPara(int Index);  //读取全部参数
	void SaveAllPara(int Index);  //保存全部参数
	void LoadCameraPara(int Index);  //读取指定相机参数
	void SaveCameraPara(int Index);  //保存指定相机参数

	void LoadSetModel();
	void SaveSetModel();

	void LoadCheckPara(int Index);   //读取通用检测参数
	void SaveCheckPara(int Index);  //保存通用检测参数

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
