
// MV_RAW2HObjectDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MV_RAW2HObject.h"
#include "MV_RAW2HObjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMVRAW2HObjectDlg 对话框



CMVRAW2HObjectDlg::CMVRAW2HObjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MV_RAW2HOBJECT_DIALOG, pParent)
    , m_dGainEdit(0)
    , m_dFrameRateEdit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    memset(m_chPixelFormat, 0, MV_MAX_SYMBOLIC_LEN);
}

void CMVRAW2HObjectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DEVICE_COMBO, m_ctrlDeviceCombo);
    DDX_CBIndex(pDX, IDC_DEVICE_COMBO, m_nDeviceCombo);
    DDX_Text(pDX, IDC_EXPOSURE_EDIT, m_dExposureEdit);
    DDX_Text(pDX, IDC_GAIN_EDIT, m_dGainEdit);
    DDX_Text(pDX, IDC_FRAME_RATE_EDIT, m_dFrameRateEdit);
    DDX_Text(pDX, IDC_PIXEL_FORMAT_EDIT, (CString)(m_chPixelFormat));
}

BEGIN_MESSAGE_MAP(CMVRAW2HObjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENUM_BUTTON, &CMVRAW2HObjectDlg::OnBnClickedEnumButton)
    ON_BN_CLICKED(IDC_OPEN_BUTTON, &CMVRAW2HObjectDlg::OnBnClickedOpenButton)
    ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CMVRAW2HObjectDlg::OnBnClickedCloseButton)
    ON_BN_CLICKED(IDC_BUTTON2, &CMVRAW2HObjectDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMVRAW2HObjectDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CMVRAW2HObjectDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMVRAW2HObjectDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMVRAW2HObjectDlg 消息处理程序

BOOL CMVRAW2HObjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//打开halcon窗口
	CWnd* pwnd = GetDlgItem(IDC_DEV_PIC);
	m_halconWin.openwindow(pwnd);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMVRAW2HObjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMVRAW2HObjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMVRAW2HObjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMVRAW2HObjectDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

//查找设备
void CMVRAW2HObjectDlg::OnBnClickedEnumButton()
{
	// TODO: 在此添加控件通知处理程序代码
    CString strMsg;

    // ch: 1. 清除设备列表框中的信息 || en: 1. clear the information in the device list
    m_ctrlDeviceCombo.ResetContent();

    // ch: 2. 初始化设备信息列表 || en: 2. initialize information list of device
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    // ch:3. 枚举子网内所有设备 || en: 3. enumerate all of devices in the subnetwork
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    if (MV_OK != nRet)
    {
        // ch: 枚举设备失败 || en: fail to enumerate devices
        return;
    }

    // ch: 将值加入到信息列表框中并显示出来 || en: add value to the information list and display it
    unsigned int i;
    int nIp1, nIp2, nIp3, nIp4;
    for (i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
        {
            continue;
        }

        wchar_t* pUserName = NULL;
        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

            if (strcmp("", (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
            {
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
            }
            else
            {

                char strUserName[256];
                sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
                    pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
                    pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
            }
            strMsg.Format(_T("[%d]GigE:    %s  (%d.%d.%d.%d)"), i,
                pUserName, nIp1, nIp2, nIp3, nIp4);

        }
        else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
        {
            if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
            {
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
            }
            else
            {
                char strUserName[256] = { 0 };
                sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
                    pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName,
                    pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
                DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
                pUserName = new wchar_t[dwLenUserName];
                MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
            }
            strMsg.Format(_T("[%d]UsbV3:  %s"), i, pUserName);
        }
        else
        {
        }
        m_ctrlDeviceCombo.AddString(strMsg);

        if (NULL != pUserName)
        {
            delete(pUserName);
            pUserName = NULL;
        }
    }
    m_ctrlDeviceCombo.SetCurSel(CB_ERR);

    // ch: 枚举到设备之后要显示出来 || en: display the device after enumeration
    UpdateData(FALSE);

    if (0 == m_stDevList.nDeviceNum)
    {
        MessageBox(TEXT("No device"));
        return;
    }
}

//打开设备
void CMVRAW2HObjectDlg::OnBnClickedOpenButton()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    int nIndex = m_nDeviceCombo;
    if ((nIndex < 0) | (nIndex >= MV_MAX_DEVICE_NUM))
    {
        MessageBox(TEXT("Please select device"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    // ch: 由设备信息创建设备实例 || en:get and create example from the device information list
    if (NULL == m_stDevList.pDeviceInfo[nIndex])
    {
        MessageBox(TEXT("Device does not exist"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    m_pcMyCamera = new CMvCamera;
    // ch: 创建设备失败 || en:fail to create device
    if (NULL == m_pcMyCamera)
    {
        return;
    }

    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);
    // ch: 创建设备失败 || en:fail to create device
    if (MV_OK != nRet)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        MessageBox(TEXT("Open Fail"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        return;
    }

    // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    if (m_stDevList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
    {
        unsigned int nPacketSize = 0;
        nRet = m_pcMyCamera->GetOptimalPacketSize(&nPacketSize);
        if (nRet == MV_OK)
        {
            nRet = m_pcMyCamera->SetIntValue("GevSCPSPacketSize", nPacketSize);
            if (nRet != MV_OK)
            {
                MessageBox(TEXT("Warning: Set Packet Size fail!"), TEXT("warning"), MB_OK | MB_ICONWARNING);
            }
        }
        else
        {
            MessageBox(TEXT("Warning: Get Packet Size fail!"), TEXT("warning"), MB_OK | MB_ICONWARNING);
        }
    }


    MessageBox(L"打开相机成功");
}


void CMVRAW2HObjectDlg::OnBnClickedCloseButton()
{
    // TODO: 在此添加控件通知处理程序代码
    CloseDevice();
    MessageBox(L"关闭相机成功");
}

int CMVRAW2HObjectDlg::CloseDevice(void)
{
    if (m_pcMyCamera)
    {
        m_pcMyCamera->Close();
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
    }
    return MV_OK;
}

//采集一帧
void CMVRAW2HObjectDlg::OnBnClickedButton2()
{
    // TODO: 在此添加控件通知处理程序代码
    int nRet = MV_OK;
    CMVRAW2HObjectDlg* pBasicDemo = (CMVRAW2HObjectDlg*)this;
    HObject Hobj;
    unsigned char* pTemp = NULL;
    MV_FRAME_OUT stImageInfo = { 0 };
    unsigned char* pImageBuf = NULL;
    unsigned int nImageBufSize = 0;
    m_pcMyCamera->StartGrabbing();
    nRet = pBasicDemo->m_pcMyCamera->GetImageBuffer(&stImageInfo, 1000);
    if (MV_OK == nRet)
    {
        if (IsBayer8PixelFormat(stImageInfo.stFrameInfo.enPixelType))
        {
            nRet = ConvertBayer8ToHalcon(&Hobj, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nWidth, stImageInfo.stFrameInfo.enPixelType, stImageInfo.pBufAddr);
            if (MV_OK != nRet)
            {
                return;
            }
        }
        else if (IsColorPixelFormat(stImageInfo.stFrameInfo.enPixelType))//Color
        {
            if (PixelType_Gvsp_RGB8_Packed == stImageInfo.stFrameInfo.enPixelType)
            {
                pTemp = stImageInfo.pBufAddr;
            }
            else
            {
                if (NULL == pImageBuf || nImageBufSize < (stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight * 3))
                {
                    if (pImageBuf)
                    {
                        free(pImageBuf);
                        pImageBuf = NULL;
                    }

                    pImageBuf = (unsigned char*)malloc(stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight * 3);
                    if (pImageBuf == NULL)
                    {
                        return;
                    }
                    nImageBufSize = stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight * 3;
                }

                MV_CC_PIXEL_CONVERT_PARAM stPixelConvertParam;
                memset(&stPixelConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
                stPixelConvertParam.pSrcData = stImageInfo.pBufAddr;
                stPixelConvertParam.nWidth = stImageInfo.stFrameInfo.nWidth;
                stPixelConvertParam.nHeight = stImageInfo.stFrameInfo.nHeight;
                stPixelConvertParam.enSrcPixelType = stImageInfo.stFrameInfo.enPixelType;
                stPixelConvertParam.nSrcDataLen = stImageInfo.stFrameInfo.nFrameLen;
                stPixelConvertParam.nDstBufferSize = nImageBufSize;
                stPixelConvertParam.pDstBuffer = pImageBuf;
                stPixelConvertParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed;
                nRet = pBasicDemo->m_pcMyCamera->ConvertPixelType(&stPixelConvertParam);
                if (MV_OK != nRet)
                {
                    return;
                }
                pTemp = pImageBuf;
            }

            nRet = ConvertRGBToHalcon(&Hobj, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nWidth, pTemp);
            if (MV_OK != nRet)
            {
                return;
            }
        }
        else if (IsMonoPixelFormat(stImageInfo.stFrameInfo.enPixelType))//Mono
        {
            if (PixelType_Gvsp_Mono8 == stImageInfo.stFrameInfo.enPixelType)
            {
                pTemp = stImageInfo.pBufAddr;
            }
            else
            {
                if (NULL == pImageBuf || nImageBufSize < (stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight))
                {
                    if (pImageBuf)
                    {
                        free(pImageBuf);
                        pImageBuf = NULL;
                    }

                    pImageBuf = (unsigned char*)malloc(stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight);
                    if (pImageBuf == NULL)
                    {
                        return;
                    }
                    nImageBufSize = stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight;
                }

                MV_CC_PIXEL_CONVERT_PARAM stPixelConvertParam;
                memset(&stPixelConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
                stPixelConvertParam.pSrcData = stImageInfo.pBufAddr;
                stPixelConvertParam.nWidth = stImageInfo.stFrameInfo.nWidth;
                stPixelConvertParam.nHeight = stImageInfo.stFrameInfo.nHeight;
                stPixelConvertParam.enSrcPixelType = stImageInfo.stFrameInfo.enPixelType;
                stPixelConvertParam.nSrcDataLen = stImageInfo.stFrameInfo.nFrameLen;
                stPixelConvertParam.nDstBufferSize = nImageBufSize;
                stPixelConvertParam.pDstBuffer = pImageBuf;
                stPixelConvertParam.enDstPixelType = PixelType_Gvsp_Mono8;
                nRet = pBasicDemo->m_pcMyCamera->ConvertPixelType(&stPixelConvertParam);
                if (MV_OK != nRet)
                {
                    return;
                }
                pTemp = pImageBuf;
            }

            nRet = ConvertMono8ToHalcon(&Hobj, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nWidth, pTemp);
            if (MV_OK != nRet)
            {
                return;
            }
        }
        else
        {
            pBasicDemo->m_pcMyCamera->FreeImageBuffer(&stImageInfo);
            return;
        }

        pBasicDemo->m_pcMyCamera->FreeImageBuffer(&stImageInfo);
    }
    else
    {
        return;
    }
    if (pImageBuf)
    {
        free(pImageBuf);
        pImageBuf = NULL;
    }

    m_halconWin.dispobj(Hobj);
    Current_Hobj = Hobj;
}

//保存图像
void CMVRAW2HObjectDlg::OnBnClickedButton3()
{
    // TODO: 在此添加控件通知处理程序代码
    WriteImage(Current_Hobj, "bmp", 0, "./1.bmp");
    MessageBox(L"保存图片成功");
}

//获取参数
void CMVRAW2HObjectDlg::OnBnClickedButton4()
{
    // TODO: 在此添加控件通知处理程序代码
  
    int nRet = GetTriggerMode();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Trigger Mode Fail"), nRet);
    }

    nRet = GetExposureTime();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Exposure Time Fail"), nRet);
    }

    nRet = GetGain();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Gain Fail"), nRet);
    }

    nRet = GetFrameRate();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Frame Rate Fail"), nRet);
    }

    nRet = GetTriggerSource();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Trigger Source Fail"), nRet);
    }

    nRet = GetPixelFormat();
    if (nRet != MV_OK)
    {
        ShowErrorMsg(TEXT("Get Pixel Format Fail"), nRet);
    }

    UpdateData(FALSE);
}

void CMVRAW2HObjectDlg::ShowErrorMsg(CString csMessage, int nErrorNum)
{
    CString errorMsg;
    if (nErrorNum == 0)
    {
        errorMsg.Format(_T("%s"), csMessage);
    }
    else
    {
        errorMsg.Format(_T("%s: Error = %x: "), csMessage, nErrorNum);
    }

    switch (nErrorNum)
    {
    case MV_E_HANDLE:           errorMsg += "Error or invalid handle ";                                         break;
    case MV_E_SUPPORT:          errorMsg += "Not supported function ";                                          break;
    case MV_E_BUFOVER:          errorMsg += "Cache is full ";                                                   break;
    case MV_E_CALLORDER:        errorMsg += "Function calling order error ";                                    break;
    case MV_E_PARAMETER:        errorMsg += "Incorrect parameter ";                                             break;
    case MV_E_RESOURCE:         errorMsg += "Applying resource failed ";                                        break;
    case MV_E_NODATA:           errorMsg += "No data ";                                                         break;
    case MV_E_PRECONDITION:     errorMsg += "Precondition error, or running environment changed ";              break;
    case MV_E_VERSION:          errorMsg += "Version mismatches ";                                              break;
    case MV_E_NOENOUGH_BUF:     errorMsg += "Insufficient memory ";                                             break;
    case MV_E_ABNORMAL_IMAGE:   errorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
    case MV_E_UNKNOW:           errorMsg += "Unknown error ";                                                   break;
    case MV_E_GC_GENERIC:       errorMsg += "General error ";                                                   break;
    case MV_E_GC_ACCESS:        errorMsg += "Node accessing condition error ";                                  break;
    case MV_E_ACCESS_DENIED:	errorMsg += "No permission ";                                                   break;
    case MV_E_BUSY:             errorMsg += "Device is busy, or network disconnected ";                         break;
    case MV_E_NETER:            errorMsg += "Network error ";                                                   break;
    }

    MessageBox(errorMsg, TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

int CMVRAW2HObjectDlg::SetTriggerMode()
{
    return m_pcMyCamera->SetEnumValue("TriggerMode", m_nTriggerMode);
}

int CMVRAW2HObjectDlg::GetTriggerMode()
{
   
    return MV_OK;

}

int CMVRAW2HObjectDlg::GetExposureTime()
{
    MVCC_FLOATVALUE stFloatValue = { 0 };

    int nRet = m_pcMyCamera->GetFloatValue("ExposureTime", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    m_dExposureEdit = stFloatValue.fCurValue;

    return MV_OK;
}

int CMVRAW2HObjectDlg::SetExposureTime()
{
    m_pcMyCamera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

    return m_pcMyCamera->SetFloatValue("ExposureTime", (float)m_dExposureEdit);
}

int CMVRAW2HObjectDlg::GetGain()
{
    MVCC_FLOATVALUE stFloatValue = { 0 };

    int nRet = m_pcMyCamera->GetFloatValue("Gain", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    m_dGainEdit = stFloatValue.fCurValue;

    return MV_OK;
}

int CMVRAW2HObjectDlg::SetGain()
{
    // ch:设置增益前先把自动增益关闭，失败无需返回
    //en:Set Gain after Auto Gain is turned off, this failure does not need to return
    m_pcMyCamera->SetEnumValue("GainAuto", 0);

    return m_pcMyCamera->SetFloatValue("Gain", (float)m_dGainEdit);
}

int CMVRAW2HObjectDlg::GetFrameRate()
{

    MVCC_FLOATVALUE stFloatValue = { 0 };

    int nRet = m_pcMyCamera->GetFloatValue("ResultingFrameRate", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    m_dFrameRateEdit = stFloatValue.fCurValue;

    return 0;
}

int CMVRAW2HObjectDlg::SetFrameRate()
{
    int nRet = m_pcMyCamera->SetBoolValue("AcquisitionFrameRateEnable", true);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    return m_pcMyCamera->SetFloatValue("AcquisitionFrameRate", (float)m_dFrameRateEdit);
}

int CMVRAW2HObjectDlg::GetTriggerSource()
{

    return 0;
}

int CMVRAW2HObjectDlg::SetTriggerSource()
{
    return 0;
}

int CMVRAW2HObjectDlg::GetPixelFormat()
{
    MVCC_ENUMVALUE stEnumValue = { 0 };
    MVCC_ENUMENTRY stPixelFormatInfo = { 0 };

    int nRet = m_pcMyCamera->GetEnumValue("PixelFormat", &stEnumValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    stPixelFormatInfo.nValue = stEnumValue.nCurValue;
    nRet = m_pcMyCamera->GetEnumEntrySymbolic("PixelFormat", &stPixelFormatInfo);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    strcpy_s(m_chPixelFormat, MV_MAX_SYMBOLIC_LEN, stPixelFormatInfo.chSymbolic);

    return MV_OK;
}


void CMVRAW2HObjectDlg::OnBnClickedButton5()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    bool bIsSetSucceed = true;
    int nRet = SetExposureTime();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        ShowErrorMsg(TEXT("Set Exposure Time Fail"), nRet);
    }
    nRet = SetGain();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        ShowErrorMsg(TEXT("Set Gain Fail"), nRet);
    }
    nRet = SetFrameRate();
    if (nRet != MV_OK)
    {
        bIsSetSucceed = false;
        ShowErrorMsg(TEXT("Set Frame Rate Fail"), nRet);
    }

    if (true == bIsSetSucceed)
    {
        ShowErrorMsg(TEXT("Set Parameter Succeed"), nRet);
    }
}
