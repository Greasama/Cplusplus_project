#include"Admin.h"

Administrators::Administrators()//默认构造
{
}
Administrators::Administrators(string name, string pwd)//有参构造
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
	cout << "机房的数量为：" << vCom.size() << endl;
}
void Administrators::openMenu()//选择菜单
{
	cout << "---------------欢迎使用智能机房预约系统---------------" << endl;
	cout << "欢迎管理员："<<this->m_Name<<"登录！" << endl;
	cout << "\t\t--------------------------------\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t|         1·添加账号          |\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t|         2·查看账号          |\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t|         3·查看机房          |\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t|         4·清空预约          |\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t|         0·注销登录          |\n" << endl;
	cout << "\t\t|                              |\n" << endl;
	cout << "\t\t--------------------------------\n" << endl;
	cout << "请输入您的操作：" << endl;
}
void Administrators::addPerson()//添加账号
{
	cout << "请输入添加账号的类型：" << endl;
	cout << "1·添加学生" << endl;
	cout << "2·添加教师" << endl;
	string fileName;
	string tip;
	string errorTip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true)//重复检测
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}
void printStudent(Student & s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher & t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}
void Administrators::showPerson()//查看账号
{
	cout << "请选择查看内容：" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);//！无法打印所有老师信息
	}
	system("pause");
	system("cls");
}
void Administrators::showComputer()//查看机房信息
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin();it!=vCom.end();it++)
	{
		cout << "机房的编号：" << it->m_ComId << " 机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
void Administrators::cleanFile()//清空预约记录
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
void Administrators::initVector()//初始化容器
{
	vStu.clear();
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "当前职工数量为：" << vTea.size() << endl;
	ifs.close();
}

//检测重复
bool Administrators::checkRepeat(int id, int type)
{
	if (type == 1)//检测学生
	{
		for (vector<Student>::iterator it = vStu.begin();it!=vStu.end();it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else//检测老师
	{
		for (vector<Teacher>::iterator it = vTea.begin();it!=vTea.end();it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}