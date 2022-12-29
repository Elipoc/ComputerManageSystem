#include<iostream>
#include"Identity.h"
#include<fstream>
#include"globalFIle.h"
#include<string>
#include"student.h"
#include"manager.h"
#include"teacher.h"
using namespace std;

//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学习子菜单
		student->openMenu();

		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;//接收用户选择
		
		if (select == 1)//申请预约
		{
			stu->applyOder();
		}
		else if (select == 2)//查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select == 3)//查看所有预约
		{
			stu->showAllOrder();
		}
		else if(select == 4)//取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			//注销登录
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
		}

		
	 }
}

//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用子菜单界面
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;

		int select = 0; //接受用户选择

		cin >> select;

		if (select == 1) //查看所有预约
		{
			tea->showAllOrder();
		}
		else if (select == 2) //审核预约
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入管理员子菜单界面
void managerMenu(Identity*& manager)
{
	while (true)
	{ 
		//调用管理员子菜单
		manager->openMenu();

		//将父类的指针  转为子类的指针 调用子类里其他接口
		Manager* man = (Manager*)manager;
		
		int select=0;
		//接受用户的选择
		cin >> select;

		if (select == 1)//添加账号
		{
			//cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2)//查看账号
		{
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)//查看机房信息
		{
			//cout << "查看机房信息" << endl;
			man->showComputer();
		}
		else if(select==4)//清空预约
		{
			//cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;//销毁堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}


//登录功能       文件名      操作身份类型
void LoginIn(string filename, int type)
{
	//父类指针  用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(filename, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接受用户信息

	int id = 0;
	string name;
	string pwd;


	// 判断身份
	if (type == 1)//学生身份
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;//从文件中读取的id号
		string fName;//从文件中获取的姓名
		string fPwd;//从文件中获取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Student(id,name,pwd);
				//进入学生身份子菜单
				studentMenu(person);
				return;
			}
		}

	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;//从文件中读取的id号
		string fName;//从文件中获取的姓名
		string fPwd;//从文件中获取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			/*cout << fId << endl;
			cout << fName << endl;
			cout << fPwd << endl;*/
			//与用户输入的信息对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				
				cout << "教师验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				//进入教师身份子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Manager(name, pwd);

				//进入管理员子菜单界面
				managerMenu(person);
				 
				return;
				
			}
		}
	}

	cout << "身份验证失败" << endl;
	system("pause");
	system("cls"); 

	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "======================  欢迎来到湖南信息学院机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";
		cin >> select;
		switch (select)//根据用户选择 实现不同接口
		{
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误 请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}