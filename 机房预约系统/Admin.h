#pragma once
#include<iostream>
using namespace std;
#include"ID.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"Student.h"
#include"Teacher.h"
#include<algorithm>
#include"computerRoom.h"
class Administrators :public ID
{
public:
	Administrators();
	Administrators(string name, string pwd);
	virtual void openMenu();
	void addPerson();
	void showPerson();
	void showComputer();
	void cleanFile();
	void initVector();
	bool checkRepeat(int id, int type);
	vector<Student>vStu;
	vector<Teacher>vTea;
	vector<ComputerRoom>vCom;
};