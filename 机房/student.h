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
//ѧ����
class Student:public Identity
{
public:
	
	//Ĭ�Ϲ���
	Student();
	//�вι��� ������ѧ�� ���� ����
	Student(int id,string name,string pwd);
	//�˵�����
	virtual void openMenu() ;

	//����ԤԼ	
	void applyOder();

	// �鿴ԤԼ
	void showMyOrder();

	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();

	//ѧ��ѧ��
	int m_Id;
	
	//������Ϣ
	vector<ComputerRoom> vCom;
};