#pragma once
#include <HalconCpp.h>
#include <stdio.h>
#include "MvCamera.h"

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
int ConvertMono8ToHalcon(HObject* Hobj, int nHeight, int nWidth, unsigned char* pData);

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
int ConvertBayer8ToHalcon(HObject* Hobj, int nHeight, int nWidth, MvGvspPixelType nPixelType, unsigned char* pData);

/************************************************************************
 *  @fn     ConvertRGBToHalcon()
 *  @brief  RGBת��ΪHalcon��ʽ����
 *  @param  Hobj                   [OUT]          ת��������Hobject����
 *  @param  nHeight                [IN]           ͼ��߶�
 *  @param  nWidth                 [IN]           ͼ����
 *  @param  pData                  [IN]           Դ����
 *  @return �ɹ�������STATUS_OK�����󣬷���STATUS_ERROR
 ************************************************************************/
int ConvertRGBToHalcon(HObject* Hobj, int nHeight, int nWidth,
    unsigned char* pData);

/************************************************************************
 *  @fn     IsBayer8PixelFormat()
 *  @brief  �ж��Ƿ���Bayer8��ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsBayer8PixelFormat(MvGvspPixelType enType);

/************************************************************************
 *  @fn     IsColorPixelFormat()
 *  @brief  �ж��Ƿ��ǲ�ɫ��ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsColorPixelFormat(MvGvspPixelType enType);

/************************************************************************
 *  @fn     IsMonoPixelFormat()
 *  @brief  �ж��Ƿ��Ǻڰ׸�ʽ
 *  @param  enType                [IN]            ���ظ�ʽ
 *  @return �ǣ�����true���񣬷���false
 ************************************************************************/
bool IsMonoPixelFormat(MvGvspPixelType enType);
