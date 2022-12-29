#pragma once
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFIle.h"  
#include<vector>
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include"computerRoom.h"
using namespace std;

class Manager :public Identity
{
public:
	//�޲ι���
	Manager();

	//�вι���
	Manager(string name,string pwd);

	//�˵�����
	virtual void openMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;
	
	//����ظ�
	bool checkRepeat(int id,int type);

	//������Ϣ
	vector<ComputerRoom> vCom;


	void initComputerRoom();
};