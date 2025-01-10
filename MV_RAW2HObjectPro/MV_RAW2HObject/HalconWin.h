/*********************************************************************************
  *Copyright(C): ������Ԫ���˿Ƽ����޹�˾
  *FileName:	 HalconWin.h
  *Author:       ����
  *Version:      1.0
  *Date:	     2023.9.20
  *Description:  Halcon��װC++�Ŀ��ӻ���
**********************************************************************************/


#pragma once
#include "HalconCpp.h"
using namespace HalconCpp;
#include <vector>
using namespace std;

class HalconWin
{
private:
	//���ھ��
	HTuple hv_WindowHandle;
	//��ǰ��������ʾ������(push_back������image,֮ǰ�Ļ�clear)
	vector<HObject> m_objs;
	//��ʾHObject����
	void display(HObject& obj);

public:

	/**
	 * @breif ������Ҫ˵��-��Halcon���ڲ���CWnd
	 * @param name: halcon���ڴ���mfc���ĸ��Ի�����
	 */
	void openwindow(CWnd* pwnd);

	/**
	 * @breif ������Ҫ˵��-��HObject���͵�ͼ��(Image region xld)��ʾ�ڰ󶨵Ĵ�����
	 * @param name ����
	 */
	void dispobj(HObject& img);
	void dispobj(vector<HObject>& objs);

	/**
	 * @breif ������Ҫ˵��-������-��մ�����ʾ
	 */
	void clearwindow();

	/**
	 * @breif ������Ҫ˵��-���ַ�������ʾ�ڰ󶨵Ĵ�����
	 * @hv_String :��ʾ���ַ���
	 * @hv_CoordSystem:����ϵͳ,Ĭ��"image",��ѡwindow
	 * @hv_Row :�ַ������Ͻ�������
	 * @hv_Column :�ַ������Ͻ�������
	 * @hv_Color :�ַ�����ɫ
	 * @hv_Box :�Ƿ񸽼ӱ�����
	 */
	void dispMessage(HTuple hv_String, HTuple hv_CoordSystem = "image",
						HTuple hv_Row = 10, HTuple hv_Column = 10, \
						HTuple hv_Color = "blue", HTuple hv_Box = "false");

	/**
	 * @breif ������Ҫ˵��-HALCON->SetColor���ӵĽӿ�,������ʾ��ɫ
	 * @color ��ʾ����ɫ "green", "red" ...
	 */
	void setWndColor(HTuple color);


	/**
	 * @breif ������Ҫ˵��-HALCON->SetColor���ӵĽӿڣ����ö��ֻ����ɫ
	 * @colorNum : ��ʾ����ɫ����	3,6,12
	 */
	void setWndColored(unsigned int colorNum = 12);


	/**
	 * @breif ������Ҫ˵��-HALCON->SetDraw���ӵĽӿ�,��ʾ������仹�Ǳ߽�
	 * @cString : ��ʾ��ģʽ   �߿�"margin", ��䣺"fill" 
	 */
	void setDraw(CString cString);

	/**
	 * @breif ������Ҫ˵��-CStringתHTuple
	 * @cString: ����CString�����ַ���
	 * @return : HTuple
	 */
	HTuple CString2HTuple(CString cString);

	/**
	 * @breif ������Ҫ˵��-HALCON->SetLineWidth���ӵĽӿڣ������߿�
	 * @hv_Width 1,2,3...
	 */
	void setLineWidth(HTuple hv_Width);


	/**
	 * @breif ������Ҫ˵��-�õ����ھ��
	 * @return HTuple���ʹ��ھ��
	 */
	HTuple getWindow();

	/**
	 * @breif ������Ҫ˵��-���ô�����ʾ�����С
	 * @size :�����С
	 * @fontName:��������
	 * @bold: �Ƿ����
	 * @slant: �Ƿ�б��
	 */
	void SetDisplayFont(HTuple size = 18, HTuple fontName = "����", bool bold = true,
		bool slant = false);
};

