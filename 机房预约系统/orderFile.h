#pragma once
#include<iostream>
using namespace std;
#include<map>
#include"globalFile.h"
#include<fstream>
#include<string>
class OrderFile
{
public:
	OrderFile();
	void updateOrder();
	//��¼����ԤԼ��Ϣ��������key��¼������value�����¼��ֵ����Ϣ
	map<int, map<string, string>>m_orderData;
	int m_Size;
};