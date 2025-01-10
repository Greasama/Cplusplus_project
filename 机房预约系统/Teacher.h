#pragma once
#include<iostream>
using namespace std;
#include"ID.h"
#include<string>
#include<fstream>
#include<vector>
#include"globalFile.h"
#include"orderFile.h"
class Teacher :public ID
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);
	virtual void openMenu();
	void showAllOrder();
	void validOrder();
	int m_EmpId;//ΩÃ ¶±‡∫≈
};