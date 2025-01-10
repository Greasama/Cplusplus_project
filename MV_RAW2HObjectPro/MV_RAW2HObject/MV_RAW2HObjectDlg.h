
// MV_RAW2HObjectDlg.h: 头文件
//

#pragma once
#include "HalconCpp.h"
#include "HalconWin.h"
#include "MvCamera.h"
#include "ConverPixel.h"

using namespace HalconCpp;


// CMVRAW2HObjectDlg 对话框
class CMVRAW2HObjectDlg : public CDialogEx
{
// 构造
public:
	CMVRAW2HObjectDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MV_RAW2HOBJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
public:
	
	afx_msg void OnBnClickedEnumButton();
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedButton5();




	afx_msg void OnCbnSelchangeCombo1();

	HalconWin m_halconWin;
	CComboBox m_ctrlDeviceCombo;
	int     m_nDeviceCombo;

	/*设备相关*/
	CMvCamera* m_pcMyCamera;               //CMyCamera封装了常用接口

	HObject Current_Hobj;


	MV_CC_DEVICE_INFO_LIST m_stDevList;         //设备信息列表结构体变量，用来存储设备列表


	/*关闭销毁操作*/
	int CloseDevice(void);                   //关闭设备
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	int m_nTriggerMode;                   // ch:触发模式 | en:Trigger Mode

	void ShowErrorMsg(CString csMessage, int nErrorNum);
	int SetTriggerMode();                // ch:设置触发模式 | en:Set Trigger Mode
	int GetTriggerMode();

	int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
	int SetExposureTime();

	int GetGain();                       // ch:设置增益 | en:Set Gain
	int SetGain();
	int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
	int SetFrameRate();
	int GetTriggerSource();              // ch:设置触发源 | en:Set Trigger Source
	int SetTriggerSource();
	int GetPixelFormat();                // ch:获取像素格式 | en:Get Pixel Format



	double m_dExposureEdit;
	double m_dGainEdit;
	double m_dFrameRateEdit;
	char m_chPixelFormat[MV_MAX_SYMBOLIC_LEN];
	
};
