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
	//记录所有预约信息的容器，key记录条数，value具体记录键值对信息
	map<int, map<string, string>>m_orderData;
	int m_Size;
};