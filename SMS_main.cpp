#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "SMS_DataStructure.h"
#include "SMS_string.h"
using namespace std;

//输入数字的宏定义，用来解决输入非法问题
#define INPUT_INT_LU(i,l,u) while(cin>>i,i<l||i>u||cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}
#define INPUT_INT_L(i,l) while(cin>>i,i<l||cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}
#define INPUT_INT(i) while(cin>>i,cin.fail()){cout<<strInputFault;cin.clear();cin.sync();}

//一级函数
void StartProcess(void);
void StuLogin(void);
void TeaLogin(void);
bool QuitConfirm(void);
void EndProcess(void);

//二级函数 of StuLogin
void StuPasswordChange(Student*);
void StuCourseChoose(Student*);
void StuGradesQuery(Student*);

//二级函数 of TeaLogin
void TeaPasswordChange(void);
void TeaStuManage(void);
void TeaCouManage(void);
void TeaCouChooseManage(void);
void TeaGradesInput(void);
void TeaGradesChange(void);
void TeaGradesQuery(void);

//三级函数 of TeaStuManage
void TeaStuAdd(void);
void TeaStuDelete(void);
void TeaStuChange(void);

//三级函数 of TeaCouManage
void TeaCouAdd(void);
void TeaCouDelete(void);
void TeaCouChange(void);

//三级函数 of TeaGradesQuery
void TeaGQStu(void);
void TeaGQCla(void);
void TeaGQCou(void);

Data data;

int main()
{
	bool quit = false;

	StartProcess();//系统启动处理

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
		}
	}while(!quit);
	EndProcess();

	return 0;
}

void StartProcess(void)
{
	fstream file(“data.dat”, ios_base::in);// attempt open for read
	if (!file)
	{
		// file doesn't exist; create a new one
		file.open(“data.dat”, ios_base::out); 
		file.close();
		return;
	}
	else //ok, file exists
	{
		int iStudent=0, iCourse=0;
		string TeaPassword;

		file>>iStudent;
		for(int i=0; i<iStudent; ++i)
		{
			Student temStu;
			string name;
			long id;
			string Class;
			string password;
			file>>name>>id>>Class>>password;
			temStu.SetName(name);
			temStu.SetId(id);
			temStu.SetClass(Class);
			temStu.SetPassword(password);

			int n;
			file>>n;
			int *cn=new int[n], *grade=new int[n];
			for(int i=0; i<n; ++i)
				file>>cn[i]>>grade[i];
			temStu.Initialize(n,cn,grade);
			delete[] cn, grade;

			Data.AddStu(temStu);
		}
		file>>iCourse;
		for(int i=0; i<iCourse; ++i)
		{
			Course temCou;
			string name;
			int Number;
			int credit;
			file>>name>>Number>>credit;
			temCou.SetName(name);
			temCou.SetNumber(Number);
			temCou.SetCredit(credit);

			int n;
			file>>n;
			int *id=new int[n], *grade=new int[n];
			for(int i=0; i<n; ++i)
				file>>id[i]>>grade[i];
			temCou.Initialize(n,id,grade);
			delete[] id, grade;

			Data.AddCou(temCou);
		}
		file>>TeaPassword;
		Data.SetTeaPassword(TeaPassword);
		file.close();
	}
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

		INPUT_INT_LU(iMenu,0,7);
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
			TeaGradesChange();
			break;
		case 7:
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
	fstream file(“data.dat”, ios_base::out|ios_base::trunc);

	file<<Data.StuNumber<<'\t';
	for(StuNode* pStuNode=Data.StuHead; pStuNode!=NULL; pStuNode=pStuNode->next)
	{
		file<<pStuNode->Student.GetName()<<'\t';
		file<<pStuNode->Student.GetId()<<'\t';
		file<<pStuNode->Student.GetClass()<<'\t';
		file<<pStuNode->Student.GetPassword()<<'\t';

		int n=pStuNode->Student.Getnumber();
		file<<n<<'\t';
		for(int i=0; i<n; ++i)
		{
			int cn, grade;
			cn=pStuNode->Student.GetCourseNumber(i);
			grade=pStuNode->Student.GetGrade(cn);
			file<<cn<<'\t'<<grade<<'\t';
		}
	}
	file<<Data.CouNumber<<'\t';
	for(CouNode* pCouNode=Data.CouHead; pCouNode!=NULL; pCouNode=pCouNode->next)
	{
		file<<pCouNode->Course.GetName()<<'\t';
		file<<pCouNode->Course.GetNumber()<<'\t';
		file<<pCouNode->Course.GetCredit()<<'\t';
		
		int n=pCouNode->Course.Getnumber();
		file<<n<<'\t';
		for(int i=0; i<n; ++i)
		{
			long id;
			int grade;
			id=pCouNode->Course.GetStudentId(i);
			grade=pCouNode->Course.GetGrade(id);
			file<<id<<'\t'<<grade<<'\t';
		}
	}
	file<<Data.GetTeaPassword();
	file.close();
	return;
}

//二级函数 of StuLogin
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
	cout.setf(ios::fixed);
	cout<<strStuGQHead4<<setprecision(1)<<student->GPA_40(&data)/10.0<<"/4.0"<<endl;
	student->CouShow(&data);
	cout<<strLine;

	system("pause");
	return;
}

//二级函数 of TeaLogin
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
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		cout<<strTeaGI1;
		int Number;
		INPUT_INT_L(Number,0);
		if(Number==0)	break;
		Course* course=data.CouSearch(Number);
		if(course==NULL)
		{
			cout<<strTeaGIF1;
			system("pause");
		}
		else
		{
			bool clear = true;		//是否清空屏幕并先显示Head
			do
			{
				if(course->CheckGrade()==0)	//所有学生成绩均已登记
				{
					system("cls");
					cout<<strTeaGIConfirm5;
					int i;
					INPUT_INT_LU(i,0,1);
					if(i==0)
						break;
					clear=true;
				}
				if(clear)
				{
					system("cls");
					cin.clear();
					cin.sync();
					cout<<strTeaGIHead1<<course->GetName()<<strTeaGIHead2<<course->GetNumber();
					cout<<strTeaGIHead3<<course->GetCredit()<<strTeaGIHead4<<course->CheckGrade()<<endl;
					cout<<strLine;
				}
				cout<<strTeaGI2;
				long id;
				INPUT_INT_L(id,-1);
				if(id==-1)		//查看未录入成绩学生名单
				{
					course->StuSort_id();
					cout<<strStuShowHead<<endl;
					for(int i=0; i<course->Getnumber(); i++)
					{
						long id=course->GetStudentId(i);
						if(course->GetGrade(id)==-1)
							data.StuSearch(id)->StuShow();
					}
					clear=false;
				}
				else if(id==0)	//返回上一级
				{
					int n=course->CheckGrade();
					if(n==0)	//未录入成绩人数为0
					{
						cout<<strTeaGIS;
						system("pause");
						break;
					}
					else		//有学生的成绩未录入 是否还要退出
					{
						cout<<strTeaGIConfirm1<<n<<strTeaGIConfirm2;
						int s;
						INPUT_INT_LU(s,0,1);
						if(s==0)
							break;
						clear=true;
					}
				}
				else if(course->Search(id)==-1)	//该课程名单中无此学生
				{
					cout<<strTeaGIF2;
					system("pause");
					clear=true;
				}
				else
				{
					int s=1;
					if(course->GetGrade(id)!=-1)	//重复录入提醒
					{
						cout<<strTeaGIConfirm3<<course->GetGrade(id);
						cout<<strTeaGIConfirm4;
						INPUT_INT_LU(s,0,1);
						clear=true;
					}
					if(s==1)
					{
						Student* student=data.StuSearch(id);
						cout<<strTeaGI3<<id<<strTeaGI4<<student->GetName();
						cout<<strTeaGI5<<student->GetClass()<<strTeaGI6;
						int grade;
						INPUT_INT_L(grade,-1);
						if(grade!=-1)
						{
							student->SetGrade(course->GetNumber(),grade);
							course->SetGrade(id,grade);
						}
						clear=true;
					}
				}
			}while(1);
		}
	}while(1);
	return;
}

void TeaGradesChange(void)
{
	return;
}

void TeaGradesQuery(void)
{
	bool quit=false;
	do
	{
		system("cls");
		cin.clear();
		cin.sync();
		int iMenu=-1;
		cout<<strTeaGQMenu;

		INPUT_INT_LU(iMenu,0,3);
		switch(iMenu)
		{
		case 1:
			TeaGQStu();
			break;
		case 2:
			TeaGQCla();
			break;
		case 3:
			TeaGQCou();
			break;
		case 0:
			quit = true;
			break;
		}
	}while(!quit);
	return;
}

//三级函数 of TeaStuManage
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
		stuNew.SetPassword(strStuPassword);	//初始密码

		if(data.AddStu(stuNew))
			cout<<strTeaSAS;
		else
			cout<<strTeaSAF;	//学号冲突
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

//三级函数 of TeaCouManage
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
			cout<<strTeaCAF;	//课程编号冲突
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

//三级函数 of TeaGradesQuery
void TeaGQStu(void)
{
	long id;
	while(1)
	{
		system("cls");
		cout<<strTeaGQStu1;
		INPUT_INT_L(id,0);
		if(id==0)	break;

		Student* student=data.StuSearch(id);

		student->CouSort();
		
		system("cls");
		cout<<strStuGQHead1<<student->GetName();
		cout<<strStuGQHead2<<student->GetId();
		cout<<strStuGQHead3<<student->GetClass();
		cout.setf(ios::fixed);
		cout<<strStuGQHead4<<setprecision(1)<<student->GPA_40(&data)/10.0<<"/4.0"<<endl;
		student->CouShow(&data);
		cout<<strLine;

		system("pause");
	}
	return;
}

void TeaGQCla(void)
{
	system("cls");
	cin.clear();
	cin.sync();

	cout<<strTeaGQCla1;
	string Class;
	cin>>Class;
	
	int Number;
	INPUT_INT_L(Number,0);
	if(Number==0)	break;
	Course* course=data.CouSearch(Number);
	if(course==NULL)	cout<<strTeaGQClaF;
	else
	{
		course->StuSort_grade();
		
	}
	return;
}

void TeaGQCou(void)
{
	return;
}
