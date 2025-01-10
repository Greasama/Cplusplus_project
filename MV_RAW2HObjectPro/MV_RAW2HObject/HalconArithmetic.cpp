#include "pch.h"
#include "HalconArithmetic.h"

HTuple HalconArithmetic::CString2HTuple(CString cString)
{
	//CStringת��ΪHTuple
	USES_CONVERSION;
	HTuple hv_String = T2A(cString.GetBuffer(0));
	cString.ReleaseBuffer();
	return hv_String;
}

CString HalconArithmetic::HTuple2CString(HTuple hv_str)
{
	//0��ʾHTuple�е�һ������
	CString cstr;
	cstr = hv_str[0].S();
	return cstr;
}

void HalconArithmetic::ListImages(CString filedir, vector<CString>* vec)
{
	vec->clear();
	HTuple hv_filedir, hv_ImageFiles, hv_Index;
	hv_filedir = CString2HTuple(filedir);
	ListFiles(hv_filedir, ((HTuple("files").Append("follow_links")).Append("recursive")),
		&hv_ImageFiles);
	TupleRegexpSelect(hv_ImageFiles, (HTuple("\\.(tif|tiff|gif|bmp|jpg|jpeg|jp2|png|pcx|pgm|ppm|pbm|xwd|ima|hobj)$").Append("ignore_case")),
		&hv_ImageFiles);
	HTuple end_val3 = (hv_ImageFiles.TupleLength()) - 1;
	HTuple step_val3 = 1;
	for (hv_Index = 0; hv_Index.Continue(end_val3, step_val3); hv_Index += step_val3)
	{
		CString str;
		str = hv_ImageFiles[hv_Index].S();
		vec->push_back(str);
	}
}

HObject HalconArithmetic::readimage(const CString imageFile)
{
	HObject image;
	try
	{
		ReadImage(&image, CString2HTuple(imageFile));
		return image;
	}
	catch (...)
	{
		MessageBox(NULL, L"ͼ����ش�������·��", L"�쳣", MB_ICONERROR);
		return HObject();
	}
}

VisionCheckResult HalconArithmetic::action(HObject srcImg)
{
    ho_Image = srcImg;
    GetImageSize(ho_Image, &hv_Width1, &hv_Height1);
    //***************�������************************
   //��Ʒ״̬ OK(�ޱ������޶���)  NG(�б��߻��ж���)  NO(��������)
    hv_product_status = OK;
    //���߸���
    hv_missing_edge = 0;
    //�������
    hv_excess_edge = 0;
    //��������
    GenEmptyRegion(&ho_missing_regions);
    //��������
    GenEmptyRegion(&ho_excess_regions);
    //***************�������************************

    //Image Acquisition 01: Do something

    //**********ͼ�����任��ͼƬ����**********
    Rgb1ToGray(ho_Image, &ho_GrayImage);
    BinaryThreshold(ho_GrayImage, &ho_Region, "max_separability", "dark", &hv_UsedThreshold);
    SmallestRectangle2(ho_Region, &hv_Row, &hv_Column, &hv_Phi, &hv_Length1, &hv_Length2);
    VectorAngleToRigid(hv_Row, hv_Column, hv_Phi, hv_Height1 / 2, hv_Width1 / 2, 0, &hv_HomMat2D);
    AffineTransImage(ho_GrayImage, &ho_ImageAffinTrans, hv_HomMat2D, "constant",
        "false");
    AffineTransRegion(ho_Region, &ho_RegionAffineTrans, hv_HomMat2D, "nearest_neighbor");


    //���任����
    VectorAngleToRigid(hv_Height1 / 2, hv_Width1 / 2, 0, hv_Row, hv_Column, hv_Phi, &hv_HomMat2D_inv);


    //**********ץ�����ĸ���**********
    Boundary(ho_RegionAffineTrans, &ho_RegionBorder, "inner");
    DilationCircle(ho_RegionBorder, &ho_RegionDilation, 5);
    //***��ȡ����**************
    OpeningRectangle1(ho_RegionDilation, &ho_Regionheng, 50, 2);
    //***��ȡ����**************
    OpeningRectangle1(ho_RegionDilation, &ho_Regionshu, 2, 50);
    Union2(ho_Regionheng, ho_Regionshu, &ho_RegionUnion);
    ReduceDomain(ho_ImageAffinTrans, ho_RegionUnion, &ho_ImageReduced);
    EdgesSubPix(ho_ImageReduced, &ho_Edges, "canny", 1, 20, 40);
    SegmentContoursXld(ho_Edges, &ho_ContoursSplit, "lines_circles", 10, 2, 1);


    //��ȡ��,�ų�Բ��
    GenEmptyObj(&ho_Lines);
    CountObj(ho_ContoursSplit, &hv_Number);
    {
        HTuple end_val58 = hv_Number;
        HTuple step_val58 = 1;
        for (hv_Index1 = 1; hv_Index1.Continue(end_val58, step_val58); hv_Index1 += step_val58)
        {
            SelectObj(ho_ContoursSplit, &ho_ObjectSelected, hv_Index1);
            GetContourGlobalAttribXld(ho_ObjectSelected, "cont_approx", &hv_Attrib);
            if (0 != (hv_Attrib == -1))
            {
                ConcatObj(ho_Lines, ho_ObjectSelected, &ho_Lines);
            }
        }
    }

    //����ɸѡ
    SelectShapeXld(ho_Lines, &ho_SelectedXLD, "contlength", "and", 150, 99999);
    CountObj(ho_SelectedXLD, &hv_Number1);

    //*****��������******
    if (0 != (hv_Number1 != 4))
    {
        hv_product_status = NO;
    }
    else
    {
        //*****��Ͼ���******
        GenEmptyObj(&ho_line_rect);
        for (hv_Index2 = 1; hv_Index2 <= 4; hv_Index2 += 1)
        {
            SelectObj(ho_SelectedXLD, &ho_ObjectSelected1, hv_Index2);
            FitLineContourXld(ho_ObjectSelected1, "tukey", -1, 0, 5, 2, &hv_RowBegin,
                &hv_ColBegin, &hv_RowEnd, &hv_ColEnd, &hv_Nr, &hv_Nc, &hv_Dist);

            if (0 != (((hv_ColBegin - hv_ColEnd).TupleAbs()) < 5))
            {
                //������
                if (0 != (hv_RowBegin > hv_RowEnd))
                {
                    GenContourPolygonXld(&ho_Contour, (hv_RowBegin + 200).TupleConcat(hv_RowEnd - 200),
                        hv_ColBegin.TupleConcat(hv_ColEnd));
                }
                else
                {
                    GenContourPolygonXld(&ho_Contour, (hv_RowBegin - 200).TupleConcat(hv_RowEnd + 200),
                        hv_ColBegin.TupleConcat(hv_ColEnd));
                }

            }
            else
            {
                //�Ǻ��
                if (0 != (hv_ColBegin > hv_ColEnd))
                {
                    GenContourPolygonXld(&ho_Contour, hv_RowBegin.TupleConcat(hv_RowEnd),
                        (hv_ColBegin + 200).TupleConcat(hv_ColEnd - 200));
                }
                else
                {
                    GenContourPolygonXld(&ho_Contour, hv_RowBegin.TupleConcat(hv_RowEnd),
                        (hv_ColBegin - 200).TupleConcat(hv_ColEnd + 200));
                }
            }

            GenRegionContourXld(ho_Contour, &ho_Region1, "filled");

            ConcatObj(ho_line_rect, ho_Region1, &ho_line_rect);

        }

        Union1(ho_line_rect, &ho_RegionUnion1);
        FillUp(ho_RegionUnion1, &ho_RegionFillUp);
        OpeningRectangle1(ho_RegionFillUp, &ho_Object_Region, 2, 2);


        //********�ұ���*****************
        Difference(ho_Object_Region, ho_RegionAffineTrans, &ho_RegionBengbian);
        OpeningRectangle1(ho_RegionBengbian, &ho_RegionOpening, 2, 2);
        Connection(ho_RegionOpening, &ho_ConnectedRegions);
        SelectShape(ho_ConnectedRegions, &ho_SelectedRegionBengbian, "area", "and",
            500, 99999);
        CountObj(ho_SelectedRegionBengbian, &hv_Number2);
        if (0 != (hv_Number2 == 0))
        {
            //�ޱ���
        }
        else
        {
            //�б���
            hv_missing_edge = hv_Number2;
            //����������ԭͼ
            AffineTransRegion(ho_SelectedRegionBengbian, &ho_RegionAffineTrans2, hv_HomMat2D_inv,
                "nearest_neighbor");
            ho_missing_regions = ho_RegionAffineTrans2;
        }

        //********�Ҷ���*****************
        Difference(ho_RegionAffineTrans, ho_Object_Region, &ho_RegionDifference);
        OpeningRectangle1(ho_RegionDifference, &ho_RegionOpening1, 3, 3);
        Connection(ho_RegionOpening1, &ho_ConnectedRegions1);
        SelectShape(ho_ConnectedRegions1, &ho_SelectedRegions1, "area", "and", 500,
            99999);
        CountObj(ho_SelectedRegions1, &hv_Number3);
        if (0 != (hv_Number3 == 0))
        {
            //�޶���
        }
        else
        {
            //�ж���
            hv_excess_edge = hv_Number3;
            //����������ԭͼ
            AffineTransRegion(ho_SelectedRegions1, &ho_RegionAffineTrans1, hv_HomMat2D_inv,
                "nearest_neighbor");
            ho_excess_regions = ho_RegionAffineTrans1;
        }

        if (0 != (HTuple(hv_Number2 == 0).TupleAnd(hv_Number3 == 0)))
        {
            hv_product_status = OK;
        }
        else
        {
            hv_product_status = NG;
        }
    }
    re.product_State = hv_product_status;
    re.missing_edge = hv_missing_edge;
    re.excess_edge = hv_excess_edge;
    re.missing_regions = ho_missing_regions;
    re.excess_regions = ho_excess_regions;
    return re;
}
