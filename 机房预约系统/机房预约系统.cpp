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
			cout << "ע���ɹ���" << endl;
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
		if (select == 1)//����ԤԼ
		{
			stu->applyOrder();
		}
		else if (select == 2)//�鿴����ԤԼ
		{
			stu->showMyOrder();
		}
		else if (select == 3)//�鿴����ԤԼ
		{
			stu->showAllOrder();
		}
		else if (select == 4)//ȡ��ԤԼ
		{
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "ע���ɹ���" << endl;
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
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else
		{
			delete administrators;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��¼���ܺ���
void LoginIn(string filename, int type)
{
	ID* person = NULL;
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string name;
	string pwd;
	if (type == 1)
	{
		cout << "���������ѧ��" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ����" << endl;
		cin >> id;
	}
	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//ѧ����¼��֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ������Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ��֤��¼
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ����Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��¼��֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				//��½�ɹ��󣬽������Ա����
				system("pause");
				system("cls");
				//��������Ա����
				person = new Administrators(name, pwd);
				AdminMenu(person);
				return;
			}
		}
	}
	cout << "��¼��֤ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}

int main() 
{
	int select = 0;
	while (true) 
	{
		cout << "---------------��ӭʹ�����ܻ���ԤԼϵͳ---------------" << endl;
		cout << endl << "������������ݣ�" << endl;
		cout << "\t\t--------------------------------\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         1��ѧ����¼          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         2����ʦ��¼          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         3�������¼          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t|         0���˳�ϵͳ          |\n" << endl;
		cout << "\t\t|                              |\n" << endl;
		cout << "\t\t--------------------------------\n" << endl;
		cout << "����������ѡ��" ;
		cin >> select;
		switch (select)
		{
		case 1://ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�ϵͳ
			cout << "��ӭ�ٴ�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default://����
			cout << "������������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
