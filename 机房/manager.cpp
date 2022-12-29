#include<iostream>
#include"manager.h"


//无参构造
Manager::Manager()
{
	
}
//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取到文件中学生、老师的数量
	this->initVector();

	//初始化机房信息
	this->initComputerRoom();
}
//菜单界面
void Manager::openMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}
//添加账号
void Manager::addPerson()
{
	cout << "请输入添加的账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName;//操作文件名
	string tip;//提示id号
	string errorTip;//重复错误提示

	ofstream ofs;

	int select = 0;
	cin >> select;//接收用户选项
	
	if (select == 1)
	{
		//添加的是学生
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		//添加的是老师
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";

	}

	//利用追加的方式写文件
	ofs.open(fileName, ios::out | ios::app);

	int id;	//学号  职工号
	string name;//姓名
	string pwd;//密码

	cout << tip << endl;

	//检测重复
	while (true)
	{
		cin >> id;
		bool ret=checkRepeat(id, select);
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

	cout << "请输入密码" << endl;
	cin >> pwd;


	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();

	//调用初始化容器接口，重新获取文件内的数据
	this->initVector();

}
void printStudent(Student& s)
{
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& s)
{
	cout << "职工号： " << s.m_EmpId << " 姓名： " << s.m_Name << " 密码：" << s.m_Pwd << endl;
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//查看学生
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(),printStudent);
	}
	else
	{
		//查看老师
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}
//查看机房信息
void Manager::showComputer()
{
	cout << "机房的信息如下：" << endl;
	for (auto& x : vCom)
	{
		cout << "机房的编号：" << x.m_ComId << " 机房的最大容量：" << x.m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功" << endl;

	system("pause");
	system("cls");
}
//初始化容器
void Manager::initVector()
{

	//确保容器清空状态
	vStu.clear();
	vTea.clear();


	//读取学生
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;

	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	cout << "当前学生数量为：" << vStu.size() << endl;

	ifs.close();


	//读取老师信息

	ifs.open(TEACHER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
	}

	Teacher t;

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "当前老师的数量：" << vTea.size() << endl;

	ifs.close();
}
//检测重复  参数1  检测学号/职工号  参数2  检测类型
bool Manager::checkRepeat(int id,int type)
{
	/*if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
	*/
	if (type == 1)//学生
	{//遍历查重
		for (auto& x : vStu)
		{
			if(id==x.m_Id) return true;

		}	
	}
	else//老师
	{
		for (auto& x : vTea)
		{
			if(id==x.m_EmpId) return true;
		}
	}

	return false;
}

void Manager::initComputerRoom()
{
	fstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
	cout << "机房的数量为：" << vCom.size() << endl;
}

