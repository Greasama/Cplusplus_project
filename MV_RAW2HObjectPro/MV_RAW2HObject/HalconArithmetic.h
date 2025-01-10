/*********************************************************************************
  *Copyright(C): 深圳市元创兴科技有限公司
  *FileName:	 HalconArithmetic.h
  *Author:       高振华
  *Version:      1.0
  *Date:	     2023.9.20
  *Description:  Halcon封装C++的算法类
**********************************************************************************/
#pragma once
#include "HalconCpp.h"
#include "HalconWin.h"
using namespace HalconCpp;
#include <vector>
using namespace std;

//-------根据检测需求定义的检测结果数据结构------
enum ReState
{
	NO = -1,
	NG,
	OK
};

struct VisionCheckResult
{
	int product_State;	 //检测结果状态  NO(崩边严重)  NG(有崩边或有多余)
	int missing_edge;   
	int excess_edge;
	HObject missing_regions;     //崩边区域
	HObject excess_regions;     //多余区域
};
//------------------ end --------------------


class HalconArithmetic
{
public:
	/************************************************
	*   名称：CString2HTuple
	*   功能：
	*	参数：
	cString：  输入CString类型字符串

	*	返回值：空
	* 	修改日期：2019年8月3日
	************************************************/

	HTuple CString2HTuple(CString cString);

	/************************************************
	*   名称：HTuple2CString
	*   功能：HTuple中第一个变量转为CString
	*	参数：
	hv_str：  输入HTuple类型

	*	返回值：空
	* 	修改日期：2019年8月3日
	************************************************/

	CString HTuple2CString(HTuple hv_str);

	/************************************************
	*   名称：ListImages
	*   功能：封装了HALCON的ListFiles算子，
		遍历文件夹下所有图片地址，并转为CString格式保存在容器vec中
	*	参数：
	filedir：  文件夹路径
	vec: 保存图像地址的CString类型容器

	*	返回值：空
	* 	修改日期：2019年8月3日
	************************************************/
	void ListImages(CString filedir, vector<CString>* vec);

	/************************************************
	*   名称：loadImage
	*   功能：封装了HALCON的ReadImage算子，
		加载制定的图像
	*	参数：
	imageFile：  加载的图片路径

	*	返回值：加载的图像对象是一个HObject类型
	* 	修改日期：2019年8月3日
	************************************************/
	HObject readimage(const CString imageFile);


	/*******************************************
	*  以下是根据视觉检测需求单独添加的自定义接口  *
	********************************************/
	VisionCheckResult action(HObject srcImg);
private:

	// Local iconic variables
	HObject  ho_Image1, ho_missing_regions, ho_excess_regions;
	HObject  ho_Image, ho_GrayImage, ho_Region, ho_ImageAffinTrans;
	HObject  ho_RegionAffineTrans, ho_RegionBorder, ho_RegionDilation;
	HObject  ho_Regionheng, ho_Regionshu, ho_RegionUnion, ho_ImageReduced;
	HObject  ho_Edges, ho_ContoursSplit, ho_Lines, ho_ObjectSelected;
	HObject  ho_SelectedXLD, ho_line_rect, ho_ObjectSelected1;
	HObject  ho_Contour, ho_Region1, ho_RegionUnion1, ho_RegionFillUp;
	HObject  ho_Object_Region, ho_RegionBengbian, ho_RegionOpening;
	HObject  ho_ConnectedRegions, ho_SelectedRegionBengbian;
	HObject  ho_RegionAffineTrans2, ho_RegionDifference, ho_RegionOpening1;
	HObject  ho_ConnectedRegions1, ho_SelectedRegions1, ho_RegionAffineTrans1;

	// Local control variables
	HTuple  hv_ImageFiles, hv_Width1, hv_Height1;
	HTuple  hv_WindowHandle, hv_Index, hv_product_status, hv_missing_edge;
	HTuple  hv_excess_edge, hv_UsedThreshold, hv_Row, hv_Column;
	HTuple  hv_Phi, hv_Length1, hv_Length2, hv_HomMat2D, hv_HomMat2D_inv;
	HTuple  hv_Number, hv_Index1, hv_Attrib, hv_Number1, hv_Index2;
	HTuple  hv_RowBegin, hv_ColBegin, hv_RowEnd, hv_ColEnd;
	HTuple  hv_Nr, hv_Nc, hv_Dist, hv_Number2, hv_Number3, hv_info;
	HTuple  hv_colors;

	//结果定义
	VisionCheckResult re;
};

