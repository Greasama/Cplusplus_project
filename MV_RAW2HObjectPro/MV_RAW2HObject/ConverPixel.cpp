/***************************************************************************************************
*
* ��Ȩ��Ϣ����Ȩ���� (c) 2016, ������Ԫ�������޹�˾, ��������Ȩ��
*
* �ļ����ƣ�ConvertPixel.cpp
* ժ    Ҫ�����ݸ�ʽת��
*
* ��ǰ�汾��1.0.0.1
* ��    �ߣ�����
* ��    �ڣ�2023-10-07
* ��    ע���½�
***************************************************************************************************/
#include "pch.h"
#include "ConverPixel.h"

using namespace HalconCpp;

/************************************************************************
 *  @fn     ConvertMono8ToHalcon()
 *  @brief  Mono8ת��ΪHalcon��ʽ����
 *  @param  Hobj                   [OUT]          ת��������Hobject����
 *  @param  nHeight                [IN]           ͼ��߶�
 *  @param  nWidth                 [IN]           ͼ����
 *  @param  pData                  [IN]           Դ����
 *  @return �ɹ�������STATUS_OK�����󣬷���STATUS_ERROR
 ************************************************************************/
int ConvertMono8ToHalcon(HObject* Hobj, int nHeight, int nWidth, unsigned char* pData)
{
    if (NULL == Hobj || NULL == pData)
    {
        return MV_E_PARAMETER;
    }

    GenImage1(Hobj, "byte", nWidth, nHeight, (Hlong)pData);

    return MV_OK;
}

/************************************************************************
 *  @fn     ConvertBayer8ToHalcon()
 *  @brief  Bayer8ת��ΪHalcon��ʽ����
 *  @param  Hobj                   [OUT]          ת��������Hobject����
 *  @param  nHeight                [IN]           ͼ��߶�
 *  @param  nWidth                 [IN]           ͼ����
 *  @param  nPixelType             [IN]           Դ���ݸ�ʽ
 *  @param  pData                  [IN]           Դ����
 *  @return �ɹ�������STATUS_OK�����󣬷���STATUS_ERROR
 ************************************************************************/
int ConvertBayer8ToHalcon(HObject* Hobj, int nHeight, int nWidth, MvGvspPixelType nPixelType, unsigned char* pData)
{
    if (NULL == Hobj || NULL == pData)
    {
        return MV_E_PARAMETER;
    }

    GenImage1(Hobj, "byte", nWidth, nHeight, (Hlong)pData);

    if (nPixelType == PixelType_Gvsp_BayerGR8)
    {
        CfaToRgb(*Hobj, Hobj, "bayer_gr", "bilinear");
    }
    else if (nPixelType == PixelType_Gvsp_BayerRG8)
    {
        CfaToRgb(*Hobj, Hobj, "bayer_rg", "bilinear");
    }
    else if (nPixelType == PixelType_Gvsp_BayerGB8)
    {
        CfaToRgb(*Hobj, Hobj, "bayer_gb", "bilinear");
    }
    else if (nPixelType == PixelType_Gvsp_BayerBG8)
    {
        CfaToRgb(*Hobj, Hobj, "bayer_bg", "bilinear");
    }

    return MV_OK;
}

/************************************************************************
 *  @fn     ConvertRGBToHalcon()
 *  @brief  RGBת��ΪHalcon��ʽ����
 *  @param  Hobj                   [OUT]          ת��������Hobject����
 *  @param  nHeight                [IN]           ͼ��߶�
 *  @param  nWidth                 [IN]           ͼ����
 *  @param  pData                  [IN]           Դ����
 *  @param  pDataSeparate          [IN]           �洢������ɫԴ���ݵĻ�����
 *  @return �ɹ�������STATUS_OK�����󣬷���STATUS_ERROR
 ************************************************************************/
int ConvertRGBToHalcon(HObject* Hobj, int nHeight, int nWidth, unsigned char* pData)
{
    if (NULL == Hobj || NULL == pData)
    {
        return MV_E_PARAMETER;
    }

    GenImageInterleaved(Hobj, (Hlong)pData, "rgb", nWidth, nHeight, -1, "byte", 0, 0, 0, 0, -1, 0);

    return MV_OK;
}

/************************************************************************
 *  @fn     IsBayer8PixelFormat()
 *  @brief  �ж��Ƿ���Bayer8��ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsBayer8PixelFormat(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_BayerGR8:
    case PixelType_Gvsp_BayerRG8:
    case PixelType_Gvsp_BayerGB8:
    case PixelType_Gvsp_BayerBG8:
        return true;
    default:
        return false;
    }
}

/************************************************************************
 *  @fn     IsColorPixelFormat()
 *  @brief  �ж��Ƿ��ǲ�ɫ��ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsColorPixelFormat(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_RGB8_Packed:
    case PixelType_Gvsp_BGR8_Packed:
    case PixelType_Gvsp_RGBA8_Packed:
    case PixelType_Gvsp_BGRA8_Packed:
    case PixelType_Gvsp_YUV422_Packed:
    case PixelType_Gvsp_YUV422_YUYV_Packed:
    case PixelType_Gvsp_BayerGB10:
    case PixelType_Gvsp_BayerGB10_Packed:
    case PixelType_Gvsp_BayerBG10:
    case PixelType_Gvsp_BayerBG10_Packed:
    case PixelType_Gvsp_BayerRG10:
    case PixelType_Gvsp_BayerRG10_Packed:
    case PixelType_Gvsp_BayerGR10:
    case PixelType_Gvsp_BayerGR10_Packed:
    case PixelType_Gvsp_BayerGB12:
    case PixelType_Gvsp_BayerGB12_Packed:
    case PixelType_Gvsp_BayerBG12:
    case PixelType_Gvsp_BayerBG12_Packed:
    case PixelType_Gvsp_BayerRG12:
    case PixelType_Gvsp_BayerRG12_Packed:
    case PixelType_Gvsp_BayerGR12:
    case PixelType_Gvsp_BayerGR12_Packed:
        return true;
    default:
        return false;
    }
}

/************************************************************************
 *  @fn     IsMonoPixelFormat()
 *  @brief  �ж��Ƿ��Ǻڰ׸�ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsMonoPixelFormat(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_Mono8:
    case PixelType_Gvsp_Mono10:
    case PixelType_Gvsp_Mono10_Packed:
    case PixelType_Gvsp_Mono12:
    case PixelType_Gvsp_Mono12_Packed:
        return true;
    default:
        return false;
    }
}