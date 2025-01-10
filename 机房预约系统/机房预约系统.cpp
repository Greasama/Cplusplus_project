#include<iostream>
using namespace std;
#include"ID.h"
#include<fstream>
#include"globalFile.h"
#include"Admin.h"
#include"Student.h"
#include"Teacher.h"

void TeacherMenu(ID* teacher)
{
	while (true)
	{
		teacher->openMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void studentMenu(ID * student)
{
	while (true)
	{
		student->openMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1)//申请预约
		{
			stu->applyOrder();
		}
		else if (select == 2)//查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)//查看所有预约
		{
			stu->showAllOrder();
		}
		else if (select == 4)//取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void AdminMenu(ID* administrators)
{
	while (true)
	{
		administrators->openMenu();
		Administrators* man = (Administrators*)administrators;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{
			delete administrators;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录功能函数
void LoginIn(string filename, int type)
{
	ID* person = NULL;
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//学生登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师验证登录
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登录成功！" << endl;
				//登陆成功后，进入管理员界面
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Administrators(name, pwd);
				AdminMenu(person);
				return;
			}
		}
	}
	cout << "登录验证失败！" << endl;
	system("pause");
	system("cls");
	return;
}

int main() 
{
	int select = 0;
	while (true) 
	{
		cout << "---------------欢迎使用智能机房预约系统---------------" << endl;
		cout << endl << "请输入您的身份：" << endl;
		cout << "\t\t--------------------------------\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         1·学生登录          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         2·教师登录          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         3·管理登录          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         0·退出系统          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t--------------------------------\n" << endl;
		cout << "请输入您的选择：" ;
		cin >> select;
		switch (select)
		{
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://教师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎再次使用" << endl;
			system("pause");
			return 0;
			break;
		default://报错
			cout << "输入有误，请重新输入选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
