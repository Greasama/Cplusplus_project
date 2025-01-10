#pragma once
#include<iostream>
using namespace std;
#include"ID.h"
#include<string>
#include<fstream>
#include<vector>
#include"globalFile.h"
#include"computerRoom.h"
#include"orderFile.h"
class Student :public ID
{
public:
	Student();
	Student(int id,string name,string pwd);
	virtual void openMenu();
	void applyOrder();
	void showMyOrder();
	void showAllOrder();
	void cancelOrder();
	int m_Id;//Ñ§Éú±àºÅ
	vector<ComputerRoom> vCom;
};