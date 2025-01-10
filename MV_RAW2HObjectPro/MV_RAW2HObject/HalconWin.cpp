#include "pch.h"
#include "HalconWin.h"

void HalconWin::display(HObject& obj)
{
	HTuple hv_cls;
	GetObjClass(obj, &hv_cls);
	CString cstr(L"image");
	if (hv_cls.S() == cstr)
	{
		HTuple width, height;
		GetImageSize(obj, &width, &height);
		SetPart(hv_WindowHandle, 0, 0, height - 1, width - 1);
		HalconCpp::DispObj(obj, hv_WindowHandle);
	}
	else {
		HalconCpp::DispObj(obj, hv_WindowHandle);
	}
}

void HalconWin::openwindow(CWnd* pwnd)
{
	//声明窗口左上角坐标和窗口长宽
	HTuple HWindowRow, HWindowColumn, HWindowWidth, HWindowHeight;
	//声明rect对象,接收pwnd的位置信息
	CRect rect;
	pwnd->GetClientRect(&rect);
	HWindowRow = rect.top;
	HWindowColumn = rect.left;
	HWindowWidth = rect.Width();
	HWindowHeight = rect.Height();

	//Halcon窗口父窗口ID(如果不指定父窗口,halcon窗口不会嵌入到mfc中)
	HTuple HWindowID;
	//得到窗口ID  
	//HWND m_hWnd：表示窗口的句柄，即窗口的唯一标识符。
	HWindowID = (Hlong)pwnd->m_hWnd;

	//设置窗口背景色
	SetWindowAttr("background_color", "black");

	//核心函数(halcon窗口的父窗口是picture,可见)
	HalconCpp::OpenWindow(HWindowRow, HWindowColumn, HWindowWidth, HWindowHeight,
				      HWindowID, "visible", "",
							 &hv_WindowHandle);
}

void HalconWin::dispobj(HObject& img)
{
	HTuple hv_cls;
	//得到img对象的类
	GetObjClass(img, &hv_cls);
	CString cstr(L"image");
	//HTuple.S()方法用于将HTuple对象转换为字符串。它返回一个CString字符串。
	if (hv_cls.S() == cstr)
	{
		//如果传入img是image,就将m_objs容器清空,重新显示原图
		m_objs.clear();
	}
	display(img);
	m_objs.push_back(img);
}

void HalconWin::dispobj(vector<HObject>& objs)
{
	int len = (int)objs.size();
	for (int i = 0; i < len; i++)
	{

		HTuple hv_cls;
		GetObjClass(objs.at(i), &hv_cls);
		CString cstr(L"image");
		//如果obj是image类型，清空m_objs
		if (hv_cls.S() == cstr)
		{
			m_objs.clear();
		}
		display(objs.at(i));
		m_objs.push_back(objs.at(i));
	}
}

void HalconWin::clearwindow()
{
	ClearWindow(hv_WindowHandle);
}

void HalconWin::dispMessage(HTuple hv_String, HTuple hv_CoordSystem, HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

	// Local control variables
	HTuple  hv_Red, hv_Green, hv_Blue, hv_Row1Part;
	HTuple  hv_Column1Part, hv_Row2Part, hv_Column2Part, hv_RowWin;
	HTuple  hv_ColumnWin, hv_WidthWin, hv_HeightWin, hv_MaxAscent;
	HTuple  hv_MaxDescent, hv_MaxWidth, hv_MaxHeight, hv_R1;
	HTuple  hv_C1, hv_FactorRow, hv_FactorColumn, hv_UseShadow;
	HTuple  hv_ShadowColor, hv_Exception, hv_Width, hv_Index;
	HTuple  hv_Ascent, hv_Descent, hv_W, hv_H, hv_FrameHeight;
	HTuple  hv_FrameWidth, hv_R2, hv_C2, hv_DrawMode, hv_CurrentColor;

	//This procedure displays text in a graphics window.
	//
	//Input parameters:
	//WindowHandle: The WindowHandle of the graphics window, where
	//   the message should be displayed
	//String: A tuple of strings containing the text message to be displayed
	//CoordSystem: If set to 'window', the text position is given
	//   with respect to the window coordinate system.
	//   If set to 'image', image coordinates are used.
	//   (This may be useful in zoomed images.)
	//Row: The row coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Column: The column coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Color: defines the color of the text as string.
	//   If set to [], '' or 'auto' the currently set color is used.
	//   If a tuple of strings is passed, the colors are used cyclically
	//   for each new textline.
	//Box: If Box[0] is set to 'true', the text is written within an orange box.
	//     If set to' false', no box is displayed.
	//     If set to a color string (e.g. 'white', '#FF00CC', etc.),
	//       the text is written in a box of that color.
	//     An optional second value for Box (Box[1]) controls if a shadow is displayed:
	//       'true' -> display a shadow in a default color
	//       'false' -> display no shadow (same as if no second value is given)
	//       otherwise -> use given string as color string for the shadow color
	//
	//Prepare window
	GetRgb(hv_WindowHandle, &hv_Red, &hv_Green, &hv_Blue);
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	SetPart(hv_WindowHandle, 0, 0, hv_HeightWin - 1, hv_WidthWin - 1);
	//
	//default settings
	if (0 != (hv_Row == -1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column == -1))
	{
		hv_Column = 12;
	}
	if (0 != (hv_Color == HTuple()))
	{
		hv_Color = "";
	}
	//
	hv_String = (("" + hv_String) + "").TupleSplit("\n");
	//
	//Estimate extentions of text depending on font size.
	GetFontExtents(hv_WindowHandle, &hv_MaxAscent, &hv_MaxDescent, &hv_MaxWidth, &hv_MaxHeight);
	if (0 != (hv_CoordSystem == HTuple("window")))
	{
		hv_R1 = hv_Row;
		hv_C1 = hv_Column;
	}
	else
	{
		//Transform image to window coordinates
		hv_FactorRow = (1. * hv_HeightWin) / ((hv_Row2Part - hv_Row1Part) + 1);
		hv_FactorColumn = (1. * hv_WidthWin) / ((hv_Column2Part - hv_Column1Part) + 1);
		hv_R1 = ((hv_Row - hv_Row1Part) + 0.5) * hv_FactorRow;
		hv_C1 = ((hv_Column - hv_Column1Part) + 0.5) * hv_FactorColumn;
	}
	//
	//Display text box depending on text size
	hv_UseShadow = 1;
	hv_ShadowColor = "gray";
	if (0 != (HTuple(hv_Box[0]) == HTuple("true")))
	{
		hv_Box[0] = "#fce9d4";
		hv_ShadowColor = "#f28d26";
	}
	if (0 != ((hv_Box.TupleLength()) > 1))
	{
		if (0 != (HTuple(hv_Box[1]) == HTuple("true")))
		{
			//Use default ShadowColor set above
		}
		else if (0 != (HTuple(hv_Box[1]) == HTuple("false")))
		{
			hv_UseShadow = 0;
		}
		else
		{
			hv_ShadowColor = ((const HTuple&)hv_Box)[1];
			//Valid color?
			try
			{
				SetColor(hv_WindowHandle, HTuple(hv_Box[1]));
			}
			// catch (Exception) 
			catch (HalconCpp::HException& HDevExpDefaultException)
			{
				HDevExpDefaultException.ToHTuple(&hv_Exception);
				hv_Exception = "Wrong value of control parameter Box[1] (must be a 'true', 'false', or a valid color string)";
				throw HalconCpp::HException(hv_Exception);
			}
		}
	}
	if (0 != (HTuple(hv_Box[0]) != HTuple("false")))
	{
		//Valid color?
		try
		{
			SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		}
		// catch (Exception) 
		catch (HalconCpp::HException& HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			hv_Exception = "Wrong value of control parameter Box[0] (must be a 'true', 'false', or a valid color string)";
			throw HalconCpp::HException(hv_Exception);
		}
		//Calculate box extents
		hv_String = (" " + hv_String) + " ";
		hv_Width = HTuple();
		{
			HTuple end_val93 = (hv_String.TupleLength()) - 1;
			HTuple step_val93 = 1;
			for (hv_Index = 0; hv_Index.Continue(end_val93, step_val93); hv_Index += step_val93)
			{
				GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent,
					&hv_Descent, &hv_W, &hv_H);
				hv_Width = hv_Width.TupleConcat(hv_W);
			}
		}
		hv_FrameHeight = hv_MaxHeight * (hv_String.TupleLength());
		hv_FrameWidth = (HTuple(0).TupleConcat(hv_Width)).TupleMax();
		hv_R2 = hv_R1 + hv_FrameHeight;
		hv_C2 = hv_C1 + hv_FrameWidth;
		//Display rectangles
		GetDraw(hv_WindowHandle, &hv_DrawMode);
		SetDraw(hv_WindowHandle, "fill");
		//Set shadow color
		SetColor(hv_WindowHandle, hv_ShadowColor);
		if (0 != hv_UseShadow)
		{
			DispRectangle1(hv_WindowHandle, hv_R1 + 1, hv_C1 + 1, hv_R2 + 1, hv_C2 + 1);
		}
		//Set box color
		SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		DispRectangle1(hv_WindowHandle, hv_R1, hv_C1, hv_R2, hv_C2);
		SetDraw(hv_WindowHandle, hv_DrawMode);
	}
	//Write text.
	{
		HTuple end_val115 = (hv_String.TupleLength()) - 1;
		HTuple step_val115 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val115, step_val115); hv_Index += step_val115)
		{
			hv_CurrentColor = ((const HTuple&)hv_Color)[hv_Index % (hv_Color.TupleLength())];
			if (0 != (HTuple(hv_CurrentColor != HTuple("")).TupleAnd(hv_CurrentColor != HTuple("auto"))))
			{
				SetColor(hv_WindowHandle, hv_CurrentColor);
			}
			else
			{
				SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
			}
			hv_Row = hv_R1 + (hv_MaxHeight * hv_Index);
			SetTposition(hv_WindowHandle, hv_Row, hv_C1);
			WriteString(hv_WindowHandle, HTuple(hv_String[hv_Index]));
		}
	}
	//Reset changed window settings
	SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
	SetPart(hv_WindowHandle, hv_Row1Part, hv_Column1Part, hv_Row2Part, hv_Column2Part);
	return;
}

void HalconWin::setWndColor(HTuple color)
{
	HalconCpp::SetColor(hv_WindowHandle, color);
}

void HalconWin::setWndColored(unsigned int colorNum)
{
	HalconCpp::SetColored(hv_WindowHandle, (int)colorNum);
}

void HalconWin::setDraw(CString cString)
{
	//CString转换为HTuple
	HTuple hv_String = CString2HTuple(cString);
	HalconCpp::SetDraw(hv_WindowHandle, hv_String);
}

HTuple HalconWin::CString2HTuple(CString cString)
{
	//USES_CONVERSION宏在编译时会根据项目的字符集设置选择适当的转换函数。
	//如果项目使用了Unicode字符集，宏会使用A2W或W2A函数进行转换；
	//如果项目使用了多字节字符集，宏会使用W2A或A2W函数进行转换。
	//CString转换为HTuple
	USES_CONVERSION;
	//T2A是一个在MFC中常用的宏，用于将Unicode字符串转换为ASCII字符串。
	HTuple hv_String = T2A(cString);
	return hv_String;
}

void HalconWin::setLineWidth(HTuple hv_Width)
{
	HalconCpp::SetLineWidth(hv_WindowHandle, hv_Width);
}

HTuple HalconWin::getWindow()
{
	return hv_WindowHandle;
}

void HalconWin::SetDisplayFont(HTuple size, HTuple fontName, bool bold, bool slant)
{
	HTuple  hv_Font;
	HTuple _slant = slant ? "1" : "*";
	HTuple _bold = bold ? "1" : "*";
	hv_Font = "-" + fontName + "-" + size + "-*-" + _slant + "-*-*-" + _bold + "-";
	HalconCpp::SetFont(hv_WindowHandle, hv_Font);

	//HTuple  hv_Font;
	//HTuple _bold = bold ? "1" : "*";
	//HTuple _slant = slant ? "1" : "*";
	//hv_Font = "-" + fontName + "-" + size + "-*-" + _bold + "-*-*-" + _slant + "-";
	//HalconCpp::SetFont(hv_WindowHandle, hv_Font);
}


