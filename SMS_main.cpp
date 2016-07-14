#include <iostream>
#include <string>
#include <iomanip>
#include "SMS_DataStructure.h"
#include "SMS_string.h"
using namespace std;

//�������ֵĺ궨�壬�����������Ƿ�����
#define INPUT_INT_LU(i,l,u) while(cin>>i,i<l||i>u||cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}
#define INPUT_INT_L(i,l) while(cin>>i,i<l||cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}
#define INPUT_INT(i) while(cin>>i,cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}

//һ������
void StartProcess(void);
void StuLogin(void);
void TeaLogin(void);
bool QuitConfirm(void);
void EndProcess(void);

//�������� of StuLogin
void StuPasswordChange(Student*);
void StuCourseChoose(Student*);
void StuGradesQuery(Student*);

//�������� of TeaLogin
void TeaPasswordChange(void);
void TeaStuManage(void);
void TeaCouManage(void);
void TeaCouChooseManage(void);
void TeaGradesInput(void);
void TeaGradesQuery(void);

//�������� of TeaStuManage
void TeaStuAdd(void);
void TeaStuDelete(void);
void TeaStuChange(void);

//�������� of TeaCouManage
void TeaCouAdd(void);
void TeaCouDelete(void);
void TeaCouChange(void);

Data data;

int main()
{
	bool quit = false;

	StartProcess();//ϵͳ��������

	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strMainMenu;
		INPUT_INT_LU(iMenu,0,2);
		switch(iMenu)
		{
		case 1:
			TeaLogin();
			break;
		case 2:
			StuLogin();
			break;
		case 0:
			if(QuitConfirm())
				quit = true;
			break;
		// default:
		// 	cout<<strInputFault;
		// 	break;
		}
	}while(!quit);
	EndProcess();

	return 0;
}

void StartProcess(void)
{
	return;
}

void StuLogin(void)
{
	system("cls");
	cin.clear();
	cin.sync();
	cout<<strInputStuId;
	long id;
	INPUT_INT_L(id,0);
	cout<<strInputStuPassword;
	string password;
	cin>>password;
	Student* student = data.StuSearch(id);
	if(student==NULL||!student->PasswordCheck(password))
	{
		cout<<strInputStuError;
		system("pause");
		return;
	}

	bool quit=false;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strStuWelcome1<<student->GetName()<<endl;
		cout<<strStuWelcome2<<student->GetId()<<endl;
		cout<<strStuWelcome3<<student->GetClass()<<endl;
		cout<<strStuMenu;

		INPUT_INT_LU(iMenu,0,3);
		switch(iMenu)
		{
		case 1:
			StuPasswordChange(student);
			break;
		case 2:
			StuCourseChoose(student);
			break;
		case 3:
			StuGradesQuery(student);
			break;
		case 0:
			quit = true;
			break;
		}
	}while(!quit);
	return;
}

void TeaLogin(void)
{
	system("cls");
	cin.clear();
	cin.sync();
	cout<<strInputTeaPassword;
	string password;
	cin>>password;
	if(!data.TeaPasswordCheck(password))
	{
		cout<<strInputTeaError;
		system("pause");
		return;
	}

	bool quit=false;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strTeaMenu;

		INPUT_INT_LU(iMenu,0,6);
		switch(iMenu)
		{
		case 1:
			TeaPasswordChange();
			break;
		case 2:
			TeaStuManage();
			break;
		case 3:
			TeaCouManage();
			break;
		case 4:
			TeaCouChooseManage();
			break;
		case 5:
			TeaGradesInput();
			break;
		case 6:
			TeaGradesQuery();
			break;
		case 0:
			quit = true;
			break;
		}
	}while(!quit);
	return;
}

bool QuitConfirm(void)
{
	int i = 1;
	system("cls");
	cout<<strQuitConfirm;
	cin>>i;
	cin.clear();
	cin.sync();
	return !i;
}

void EndProcess(void)
{
	return;
}

//�������� of StuLogin
void StuPasswordChange(Student* student)
{
	string pwO, pwN1, pwN2;
	system("cls");
	cin.clear();
	cin.sync();
	cout<<strPwCh1;
	cin>>pwO;
	if(!student->PasswordCheck(pwO))
	{
		cout<<strPwError1;
		system("pause");
		return;
	}
	int again = 1;
	do
	{
		cin.clear();
		cin.sync();
		system("cls");
		cout<<strPwCh2;
		cin>>pwN1;
		system("cls");
		cout<<strPwCh3;
		cin>>pwN2;
		if(pwN1!=pwN2)
		{
			system("cls");
			cout<<strPwError2;
			INPUT_INT_LU(again,0,1);
		}
		else
		{
			student->SetPassword(pwN1);
			system("cls");
			cout<<strPwChS;
			system("pause");
			return;
		}
	}while(again);
	return;
}

void StuCourseChoose(Student* student)
{
	cin.clear();
	cin.sync();
	system("cls");
	data.CouSort();

	int s=-1;
	do
	{
		bool p=true;
		if(s==-1)
		{
			system("cls");
			cout<<strStuCC1;
			data.CouShowHead();
			data.CouShow();
			cout<<endl;
		}
		else if(s==-2)
		{
			system("cls");
			cout<<strStuCC2;
			data.CouShowHead();
			for(int i=0; i<student->Getnumber(); ++i)
				data.CouSearch(student->GetCourseNumber(i))->CouShow1();
			cout<<endl;
		}
		else//if(s>0)
		{
			Course* course=data.CouSearch(s);
			if(course==NULL)
			{
				system("cls");
				cout<<strStuCCF1;
			}
			else if(course->Search(student->GetId())!=-1)
			{
				system("cls");
				cout<<strStuCCF2;
			}
			else
			{
				system("cls");
				cout<<strStuCCConfirm1;
				data.CouShowHead();
				course->CouShow1();
				cout<<strStuCCConfirm2;
				int i;
				INPUT_INT_LU(i,0,1);
				if(i)
				{
					student->Add(course->GetNumber());
					course->Add(student->GetId());
					system("cls");
					cout<<strStuCCS;
				}
				else
					p=false;
			}
			if(p) system("pause");
			system("cls");
		}
		cout<<strStuCC3;
		INPUT_INT_L(s,-2);
	}while(s!=0);
	return;
}

void StuGradesQuery(Student* student)
{
	student->CouSort();
	system("cls");

	cout<<strStuGQHead1<<student->GetName();
	cout<<strStuGQHead2<<student->GetId();
	cout<<strStuGQHead3<<student->GetClass();
	cout<<strStuGQHead4<<setfill('0')<<setprecision(1)<<student->GPA_40(&data)<<"/4.0"<<endl;
	cout<<strLine<<setfill(' ');
	student->CouShow(&data);
	cout<<strLine;

	system("pause");
	return;
}

//�������� of TeaLogin
void TeaPasswordChange(void)
{
	string pwO, pwN1, pwN2;
	system("cls");
	cin.clear();
	cin.sync();
	cout<<strPwCh1;
	cin>>pwO;
	if(!data.TeaPasswordCheck(pwO))
	{
		cout<<strPwError1;
		system("pause");
		return;
	}
	int again = 1;
	do
	{
		cin.clear();
		cin.sync();
		system("cls");
		cout<<strPwCh2;
		cin>>pwN1;
		system("cls");
		cout<<strPwCh3;
		cin>>pwN2;
		if(pwN1!=pwN2)
		{
			system("cls");
			cout<<strPwError2;
			INPUT_INT_LU(again,0,1);
		}
		else
		{
			data.SetTeaPassword(pwN1);
			system("cls");
			cout<<strPwChS;
			system("pause");
			return;
		}
	}while(again);
	return;
}

void TeaStuManage(void)
{
	bool quit=false;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strTeaSMMenu;

		INPUT_INT_LU(iMenu,0,3);
		switch(iMenu)
		{
		case 1:
			TeaStuAdd();
			break;
		case 2:
			TeaStuDelete();
			break;
		case 3:
			TeaStuChange();
			break;
		case 0:
			quit = true;
			break;
		}
	}while(!quit);
	return;
}

void TeaCouManage(void)
{
	bool quit=false;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strTeaCMMenu;

		INPUT_INT_LU(iMenu,0,3);
		switch(iMenu)
		{
		case 1:
			TeaCouAdd();
			break;
		case 2:
			TeaCouDelete();
			break;
		case 3:
			TeaCouChange();
			break;
		case 0:
			quit = true;
			break;
		}
	}while(!quit);
	return;
}

void TeaCouChooseManage(void)
{
	return;
}

void TeaGradesInput(void)
{
	return;
}

void TeaGradesQuery(void)
{
	return;
}

//�������� of TeaStuManage
void TeaStuAdd(void)
{
	int s, again;
	Student stuNew;
	string name; long id; string Class;
	do
	{
		do
		{
			system("cls");
			cin.clear();
			cin.sync();
			
			cout<<strTeaSA1;
			cin>>name;
			cout<<strTeaSA2;
			INPUT_INT_L(id,1);
			cout<<strTeaSA3;
			cin>>Class;

			cout<<strTeaSAConfirm1<<name<<' '<<id<<' '<<Class<<' ';
			cout<<strTeaSAConfirm2<<strStuPassword<<strTeaSAConfirm3;
			
			INPUT_INT_LU(s,0,2);
		}while(s==2);
		if(s==0)	return;
		//else  (s==1)
		stuNew.SetName(name);
		stuNew.SetId(id);
		stuNew.SetClass(Class);
		stuNew.SetPassword(strStuPassword);	//��ʼ����

		if(data.AddStu(stuNew))
			cout<<strTeaSAS;
		else
			cout<<strTeaSAF;	//ѧ�ų�ͻ
		INPUT_INT_LU(again,0,1);
	}while(again==1);
	return;
}

void TeaStuDelete(void)
{
	Student* student;
	long id;
	int again;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();

		cout<<strTeaSD1;
		INPUT_INT_L(id,1);
		student=data.StuSearch(id);
		if(student==NULL)
			cout<<strTeaSDF;
		else
		{
			cout<<strTeaSDConfirm1<<student->GetName()<<strTeaSDConfirm2<<student->GetId();
			cout<<strTeaSDConfirm3<<student->GetClass()<<strTeaSDConfirm4;
			int i;
			INPUT_INT_LU(i,0,1);
			if(i)
			{
				data.DelStu(id);
				cout<<strTeaSDS;
			}
		}
		cout<<strTeaSD2;
		INPUT_INT_LU(again,0,1);
	}while(again);
	return;
}

void TeaStuChange(void)
{
	Student* student;
	long id;
	int again;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();

		cout<<strTeaSC1;
		INPUT_INT_L(id,1);
		student=data.StuSearch(id);
		if(student==NULL)
			cout<<strTeaSCF;
		else
		{
			cout<<strTeaSCConfirm1<<student->GetName()<<strTeaSCConfirm2<<student->GetId();
			cout<<strTeaSCConfirm3<<student->GetClass()<<strTeaSCConfirm4;
			int i;
			INPUT_INT_LU(i,0,1);
			if(i)
			{
				string Class;
				cout<<strTeaSC2;
				cin>>Class;
				student->SetClass(Class);
				cout<<strTeaSCS;
			}
		}
		cout<<strTeaSC3;
		INPUT_INT_LU(again,0,1);
	}while(again);
	return;
}

//�������� of TeaCouManage
void TeaCouAdd(void)
{
	int s, again;
	Course couNew;
	string name; int Number; int credit;
	do
	{
		do
		{
			system("cls");
			cin.clear();
			cin.sync();
			
			cout<<strTeaCA1;
			cin>>name;
			cout<<strTeaCA2;
			INPUT_INT_L(Number,1);
			cout<<strTeaCA3;
			INPUT_INT_L(credit,0);

			cout<<strTeaCAConfirm1<<name<<strTeaCAConfirm2<<Number;
			cout<<strTeaCAConfirm3<<credit<<strTeaCAConfirm4;
			
			INPUT_INT_LU(s,0,2);
		}while(s==2);
		if(s==0)	return;
		//else  (s==1)
		couNew.SetName(name);
		couNew.SetNumber(Number);
		couNew.SetCredit(credit);

		if(data.AddCou(couNew))
			cout<<strTeaCAS;
		else
			cout<<strTeaCAF;	//�γ̱�ų�ͻ
		INPUT_INT_LU(again,0,1);
	}while(again==1);
	return;
}

void TeaCouDelete(void)
{
	Course* course;
	int Number;
	int again;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();

		cout<<strTeaCD1;
		INPUT_INT_L(Number,1);
		course=data.CouSearch(Number);
		if(course==NULL)
			cout<<strTeaCDF;
		else
		{
			cout<<strTeaCDConfirm1<<course->GetName()<<strTeaCDConfirm2<<course->GetNumber();
			cout<<strTeaCDConfirm3<<course->GetCredit()<<strTeaCDConfirm4;
			int i;
			INPUT_INT_LU(i,0,1);
			if(i)
			{
				data.DelCou(Number);
				cout<<strTeaCDS;
			}
		}
		cout<<strTeaCD2;
		INPUT_INT_LU(again,0,1);
	}while(again);
	return;
}

void TeaCouChange(void)
{
	Course* course;
	int Number;
	int again;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();

		cout<<strTeaCC1;
		INPUT_INT_L(Number,1);
		course=data.CouSearch(Number);
		if(course==NULL)
			cout<<strTeaCCF;
		else
		{
			cout<<strTeaCCConfirm1<<course->GetName()<<strTeaCCConfirm2<<course->GetNumber();
			cout<<strTeaCCConfirm3<<course->GetCredit()<<strTeaCCConfirm4;
			int i;
			INPUT_INT_LU(i,0,1);
			if(i)
			{
				int credit;
				cout<<strTeaCC2;
				INPUT_INT_L(credit,0);
				course->SetCredit(credit);
				cout<<strTeaCCS;
			}
		}
		cout<<strTeaCC3;
		INPUT_INT_LU(again,0,1);
	}while(again);
	return;
}
