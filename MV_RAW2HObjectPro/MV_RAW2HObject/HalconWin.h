/*********************************************************************************
  *Copyright(C): 深圳市元创兴科技有限公司
  *FileName:	 HalconWin.h
  *Author:       高振华
  *Version:      1.0
  *Date:	     2023.9.20
  *Description:  Halcon封装C++的可视化类
**********************************************************************************/


#pragma once
#include "HalconCpp.h"
using namespace HalconCpp;
#include <vector>
using namespace std;

class HalconWin
{
private:
	//窗口句柄
	HTuple hv_WindowHandle;
	//当前窗口所显示的内容(push_back对象是image,之前的会clear)
	vector<HObject> m_objs;
	//显示HObject对象
	void display(HObject& obj);

public:

	/**
	 * @breif 函数简要说明-打开Halcon窗口并绑定CWnd
	 * @param name: halcon窗口打开在mfc中哪个对话框上
	 */
	void openwindow(CWnd* pwnd);

	/**
	 * @breif 函数简要说明-将HObject类型的图像(Image region xld)显示在绑定的窗口上
	 * @param name 作用
	 */
	void dispobj(HObject& img);
	void dispobj(vector<HObject>& objs);

	/**
	 * @breif 函数简要说明-清理窗口-清空窗口显示
	 */
	void clearwindow();

	/**
	 * @breif 函数简要说明-将字符串的显示在绑定的窗口上
	 * @hv_String :显示的字符串
	 * @hv_CoordSystem:坐标系统,默认"image",可选window
	 * @hv_Row :字符串左上角行坐标
	 * @hv_Column :字符串左上角列坐标
	 * @hv_Color :字符串颜色
	 * @hv_Box :是否附加背景框
	 */
	void dispMessage(HTuple hv_String, HTuple hv_CoordSystem = "image",
						HTuple hv_Row = 10, HTuple hv_Column = 10, \
						HTuple hv_Color = "blue", HTuple hv_Box = "false");

	/**
	 * @breif 函数简要说明-HALCON->SetColor算子的接口,设置显示颜色
	 * @color 显示的颜色 "green", "red" ...
	 */
	void setWndColor(HTuple color);


	/**
	 * @breif 函数简要说明-HALCON->SetColor算子的接口，设置多种混合颜色
	 * @colorNum : 显示的颜色种类	3,6,12
	 */
	void setWndColored(unsigned int colorNum = 12);


	/**
	 * @breif 函数简要说明-HALCON->SetDraw算子的接口,显示区域填充还是边界
	 * @cString : 显示的模式   边框："margin", 填充："fill" 
	 */
	void setDraw(CString cString);

	/**
	 * @breif 函数简要说明-CString转HTuple
	 * @cString: 输入CString类型字符串
	 * @return : HTuple
	 */
	HTuple CString2HTuple(CString cString);

	/**
	 * @breif 函数简要说明-HALCON->SetLineWidth算子的接口，设置线宽
	 * @hv_Width 1,2,3...
	 */
	void setLineWidth(HTuple hv_Width);


	/**
	 * @breif 函数简要说明-得到窗口句柄
	 * @return HTuple类型窗口句柄
	 */
	HTuple getWindow();

	/**
	 * @breif 函数简要说明-设置窗口显示字体大小
	 * @size :字体大小
	 * @fontName:字体名称
	 * @bold: 是否粗体
	 * @slant: 是否斜体
	 */
	void SetDisplayFont(HTuple size = 18, HTuple fontName = "宋体", bool bold = true,
		bool slant = false);
};

