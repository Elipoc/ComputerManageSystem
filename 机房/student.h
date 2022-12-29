#pragma once
#include<iostream>
#include"Identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFIle.h"
#include"orderFIle.h"
using namespace std;
//学生类
class Student:public Identity
{
public:
	
	//默认构造
	Student();
	//有参构造 参数：学号 姓名 密码
	Student(int id,string name,string pwd);
	//菜单界面
	virtual void openMenu() ;

	//申请预约	
	void applyOder();

	// 查看预约
	void showMyOrder();

	// 查看所有预约
	void showAllOrder();

	// 取消预约
	void cancelOrder();

	//学生学号
	int m_Id;
	
	//机房信息
	vector<ComputerRoom> vCom;
};