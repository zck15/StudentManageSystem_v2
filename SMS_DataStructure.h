#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "SMS_string.h"
using namespace std;

class Data;

class SC
{
protected:
	int* CourseNumber;
	int* grade;
	int number;
public:
	SC():number(0),CourseNumber(NULL),grade(NULL){}
	SC(SC &sc);	//复制构造函数，进行深复制
	~SC()
	{delete[]CourseNumber;delete[]grade;}	//delete[] NULL 不会出错

	int Search(int cn);		//查找课程编号为cn的课所在位置，无结果返回-1
	bool Add(int cn);			//增加选课，返回是否成功，参数课程编号，增加课程成绩记为-1
	bool Delete(int cn);
	int Getnumber(void)	{return number;}
	int GetCourseNumber(int i)	{return CourseNumber[i];}		//i<number
	void SetGrade( int cn, int grade )	//未处理参数代表课程非已选课程的情况
	{this->grade[Search(cn)]=grade;return;}
	int GetGrade( int cn )		//未处理参数代表课程非已选课程的情况
	{return grade[Search(cn)];}
	void CouSort(void);		//将课程按课程编号由小到大冒泡排序
	int GPA_40(Data *data);	//40满分制
	void CouShow(Data* data);
	void Initialize(int n,int cn[], int grade[]);//从文件中读取时用到的初始化函数

};

class Student:public SC
{
private:
	string name;
	long id;
	string Class;
	string password;
public:
	Student(){}
	~Student(){}
	void SetName(string name)
	{this->name=name;return;}
	void SetId(long id)
	{this->id=id;return;}
	void SetClass(string Class)
	{this->Class=Class;return;}
	void SetPassword(string password)
	{this->password=password;return;}
	string GetName(void)
	{return name;}
	long GetId(void)
	{return id;}
	string GetClass(void)
	{return Class;}
	bool PasswordCheck(string pw)
	{return password==pw;}
	string GetPassword(void)//存储到文件时使用
	{return password;}

	void operator= (Student student);
	void StuShow(void);

};

class CS
{
protected:
	int* StudentId;
	int* grade;
	int number;
public:
	CS():number(0),StudentId(NULL),grade(NULL){}
	CS(CS &cs);	//复制构造函数，进行深复制
	~CS()
	{delete[]StudentId;delete[]grade;}	//delete[] NULL 不会出错
	
	int Search(long id);		//查找学号为id的学生所在位置，无结果返回-1
	bool Add(long id);
	bool Delete(long id);
	int Getnumber(void)	{return number;}
	long GetStudentId(int i)	{return StudentId[i];}
	void SetGrade( long id, int grade )	//未处理参数代表课程非已选课程的情况
	{this->grade[Search(id)]=grade;return;}
	int GetGrade( long id )		//未处理参数代表课程非已选课程的情况
	{return grade[Search(id)];}
	int CheckGrade(void);		//检查未录入成绩的学生个数
	void StuSort_id(void);		//将学生按学号由小到大冒泡排序
	void StuSort_grade(void);		//将学生按grade由大到小冒泡排序
	void Initialize(int n,int id[], int grade[]);//从文件中读取时用到的初始化函数
};

class Course:public CS
{
private:
	string name;
	int Number;
	int credit;
public:
	Course(){}
	~Course(){}
	void SetName(string name)
	{this->name=name;return;}
	void SetCredit(int credit)
	{this->credit=credit;return;}
	void SetNumber(int Number)
	{this->Number=Number;return;}
	string GetName(void)
	{return name;}
	int GetCredit(void)
	{return credit;}
	int GetNumber(void)
	{return Number;}
	Course operator= (Course course);
	void CouShow1(void);		//显示课程信息时使用
	void CouShow2(void);		//显示个人成绩单时使用
	void CouShow(Data* data);	//显示该课程所有学生成绩
	void CouShow(Data* data, string Class);	//显示该课程某班级所有学生成绩
};

struct StuNode
{
	Student Student;
	StuNode* next;
};

struct CouNode
{
	Course Course;
	CouNode* next;
};

class Data
{
private:
	StuNode* StuHead;
	CouNode* CouHead;
	int StuNumber;
	int CouNumber;
	string TeaPassword;
public:
	Data():StuHead(NULL),CouHead(NULL),StuNumber(0),CouNumber(0)
	{TeaPassword=strTeaPassword;}
	~Data();
	bool AddStu(Student student);
	bool AddCou(Course course);
	void DelStuCS(Student* student);	//不考虑无此学生情况，用来删除CS中该学生的成绩
	void DelCouSC(Course* course);		//不考虑无此课程情况，用来删除SC中该课程的成绩
	bool DelStu(long id);
	bool DelCou(int cn);
	Student* StuSearch(long id);
	Course* CouSearch(int Number);
	bool TeaPasswordCheck(string pw)
	{return TeaPassword==pw;}
	void SetTeaPassword(string pw)
	{TeaPassword=pw;return;}
	void StuSort(void);
	void CouSort(void);
	void CouShowHead(void)
	{cout<<strCouShow1Head<<endl;return;}
	void StuShowHead(void)
	{cout<<strStuShowHead<<endl;return;}
	void CouShow(void);
	void StuShow(void);
	//保存文件所用函数
	friend void EndProcess(void);
	string GetTeaPassword(void)
	{return TeaPassword;}
};

////函数定义
////辅助函数
int length(int x)
{
	if(x>0)	return (((int)log10(x))+1);
	else if(x==0) return 1;
	else//if(x<0)
		return (((int)log10(-x))+2);
}

int length(long x)
{
	if(x>0)	return (((int)log10(x))+1);
	else if(x==0) return 1;
	else//if(x<0)
		return (((int)log10(-x))+2);
}

////SC类函数定义
SC::SC(SC &sc)
{
	number=sc.number;
	if(number==0)
	{
		CourseNumber=NULL;
		grade=NULL;
		return;
	}
	else
	{
		CourseNumber=new int[number];
		grade=new int[number];
		for(int i=0; i<number; ++i)
		{
			CourseNumber[i]=sc.CourseNumber[i];
			grade[i]=sc.grade[i];
		}
		return;
	}
}

int SC::Search(int cn)		//查找课程编号为cn的课所在位置，无结果返回-1
{
	for(int i=0; i<number; ++i)
		if(CourseNumber[i]==cn)
			return i;
	return -1;
}

bool SC::Add(int cn)			//增加选课，返回是否成功，参数课程编号，增加课程成绩记为-1
{
	if(Search(cn)==-1)
	{
		number++;
		int*CNnew=new int[number];
		int*Gnew=new int[number];
		for(int i=0; i<number-1; ++i)
		{
			CNnew[i]=CourseNumber[i];
			Gnew[i]=grade[i];
		}
		CNnew[number-1]=cn;
		Gnew[number-1]=-1;		//未登记分数时，分数记为-1
		delete[]CourseNumber;	//delete[] NULL 不会出错
		delete[]grade;
		CourseNumber=CNnew;
		grade=Gnew;
		return true;
	}
	else
		return false;
}

bool SC::Delete(int cn)
{
	int i=Search(cn);
	if(i!=-1)
	{
		number--;
		for(int j=i; j<number; j++)
		{
			CourseNumber[j]=CourseNumber[j+1];
			grade[j]=grade[j+1];
		}
		delete &CourseNumber[number];
		delete &grade[number];
		if(number==0){CourseNumber=NULL;grade=NULL;}	//删干净时将指针置为空
		return true;
	}
	else
		return false;
}

void SC::CouSort(void)		//将课程按课程编号由小到大冒泡排序
{
	int ub, lb, nub, nlb, i;
	int temN, temG;
	ub = number-1;	lb = 0;
	do
	{
		nub = lb;
		for ( i = lb; i < ub; ++i)
		{
			if ( CourseNumber[i] > CourseNumber[i+1] )
			{
					temN = CourseNumber[i]; CourseNumber[i] = CourseNumber[i+1]; CourseNumber[i+1] = temN;
				temG = grade[i]; grade[i] = grade[i+1]; grade[i+1] = temG;
				nub = i;
			}
		}
		ub = nub;
		nlb = ub;
		for ( i = ub; i > lb; --i)
		{
			if ( CourseNumber[i-1] > CourseNumber[i] )
			{
				temN = CourseNumber[i-1]; CourseNumber[i-1] = CourseNumber[i]; CourseNumber[i] = temN;
				temG = grade[i-1]; grade[i-1] = grade[i]; grade[i] = temG;
				nlb = i;
			}
		}
		lb = nlb;
	}while(ub!=lb);
	return;
}

int SC::GPA_40(Data *data)	//40满分制
{
	int gpa=0, creditsum=0, credit;
	for(int i=0; i < number; ++i)
	{
		if(grade[i]!=-1)
		{
			credit=data->CouSearch(CourseNumber[i])->GetCredit();
			gpa += grade[i] * credit;
			creditsum += credit;
		}
	}
	if(creditsum==0)
		return 0;
	//else
	return gpa*4/creditsum/10;
}

void SC::CouShow(Data* data)
{
	cout<<strCouShow2Head<<endl;
	for(int i=0; i < number; ++i)
	{
		Course* course = data->CouSearch(CourseNumber[i]);
		course->CouShow2();
		if(grade[i]!=-1)
			cout<<setw(18-length(course->GetCredit())/2+length(grade[i])/2)<<grade[i]<<endl;
		else
			cout<<setw(18-length(course->GetCredit())/2+4/2)<<"暂无"<<endl;
	}
	return;
}

void SC::Initialize(int n,int cn[], int grade[])
{
	if(n==0)	return;
	this->number=n;
	this->CourseNumber=new int[n];
	this->grade=new int[n];
	for(int i=0; i<n; ++i)
	{
		this->CourseNumber[i]=cn[i];
		this->grade[i]=grade[i];
	}
	return;
}

////Student类函数定义
void Student::operator= (Student student)
{
	name = student.name;
	id = student.id;
	Class = student.Class;
	password = student.password;
	number = student.number;
	if(number==0)
	{
		CourseNumber=NULL;
		grade=NULL;
		return;
	}
	//else
	CourseNumber = new int[number];
	grade = new int[number];
	for(int i=0; i<number; i++)
	{
		CourseNumber[i]=student.CourseNumber[i];
		grade[i]=student.grade[i];
	}
	return;
}

void Student::StuShow(void)
{
	cout<<setw(19+name.length()/2)<<name;
	cout<<setw(21-name.length()/2+length(id)/2)<<id;
	cout<<setw(21-length(id)/2+Class.length()/2)<<Class<<endl;
	return;
}

////CS类函数定义
CS::CS(CS &cs)
{
	number=cs.number;
	if(number==0)
	{
		StudentId=NULL;
		grade=NULL;
		return;
	}
	else
	{
		StudentId=new int[number];
		grade=new int[number];
		for(int i=0; i<number; ++i)
		{
			StudentId[i]=cs.StudentId[i];
			grade[i]=cs.grade[i];
		}
		return;
	}
}

int CS::Search(long id)		//查找学号为id的学生所在位置，无结果返回-1
{
	for(int i=0; i<number; ++i)
		if(StudentId[i]==id)
			return i;
	return -1;
}

bool CS::Add(long id)
{
	if(Search(id)==-1)
	{
		number++;
		int*SInew=new int[number];
		int*Gnew=new int[number];
		for(int i=0; i<number-1; ++i)
		{
			SInew[i]=StudentId[i];
			Gnew[i]=grade[i];
		}
		SInew[number-1]=id;
		Gnew[number-1]=-1;
		delete[]StudentId;	//delete[] NULL 不会出错
		delete[]grade;
		StudentId=SInew;
		grade=Gnew;
		return true;
	}
	else
		return false;
}

bool CS::Delete(long id)
{
	int i=Search(id);
	if(i!=-1)
	{
		number--;
		for(int j=i; j<number; j++)
		{
			StudentId[j]=StudentId[j+1];
			grade[j]=grade[j+1];
		}
		delete &StudentId[number];
		delete &grade[number];
		if(number==0){StudentId=NULL;grade=NULL;}	//删干净时将指针置为空
		return true;
	}
	else
		return false;
}

int CS::CheckGrade(void)		//检查未录入成绩的学生个数
{
	int n=0;
	for (int i = 0; i < number; ++i)
		if(grade[i]==-1)
			n++;
	return n;
}

void CS::StuSort_id(void)		//将学生按学号由小到大冒泡排序
{
	int ub, lb, nub, nlb, i;
	int temI, temG;
	ub = number-1;	lb = 0;
	do
	{
		nub = lb;
		for ( i = lb; i < ub; ++i)
		{
			if ( StudentId[i] > StudentId[i+1] )
			{
				temI = StudentId[i]; StudentId[i] = StudentId[i+1]; StudentId[i+1] = temI;
				temG = grade[i]; grade[i] = grade[i+1]; grade[i+1] = temG;
				nub = i;
			}
		}
		ub = nub;
		nlb = ub;
		for ( i = ub; i > lb; --i)
		{
			if ( StudentId[i-1] > StudentId[i] )
			{
				temI = StudentId[i-1]; StudentId[i-1] = StudentId[i]; StudentId[i] = temI;
				temG = grade[i-1]; grade[i-1] = grade[i]; grade[i] = temG;
				nlb = i;
			}
		}
		lb = nlb;
	}	while ( ub != lb );
	return;
}

void CS::StuSort_grade(void)		//将学生按grade由大到小冒泡排序
{
	int ub, lb, nub, nlb, i;
	int temI, temG;
	ub = number-1;	lb = 0;
	do
	{
		nub = lb;
		for ( i = lb; i < ub; ++i)
		{
			if ( grade[i] < grade[i+1] )
			{
				temI = StudentId[i]; StudentId[i] = StudentId[i+1]; StudentId[i+1] = temI;
				temG = grade[i]; grade[i] = grade[i+1]; grade[i+1] = temG;
				nub = i;
			}
		}
		ub = nub;
		nlb = ub;
		for ( i = ub; i > lb; --i)
		{
			if ( grade[i-1] < grade[i] )
			{
				temI = StudentId[i-1]; StudentId[i-1] = StudentId[i]; StudentId[i] = temI;
				temG = grade[i-1]; grade[i-1] = grade[i]; grade[i] = temG;
				nlb = i;
			}
		}
		lb = nlb;
	}	while ( ub != lb );
	return;
}

void CS::Initialize(int n,int id[], int grade[])//从文件中读取时用到的初始化函数
{
	if(n==0)	return;
	this->number=n;
	this->StudentId=new int[n];
	this->grade=new int[n];
	for(int i=0; i<n; ++i)
	{
		this->StudentId[i]=id[i];
		this->grade[i]=grade[i];
	}
	return;
}

////Course类函数定义
Course Course::operator= (Course course)
{
	name = course.name;
	Number = course.Number;
	credit = course.credit;
	number = course.number;
	if(number==0)
	{
		StudentId=NULL;
		grade=NULL;
		return *this;
	}
	//else
	StudentId = new int[number];
	grade = new int[number];
	for(int i=0; i<number; i++)
	{
		StudentId[i]=course.StudentId[i];
		grade[i]=course.grade[i];
	}
	return *this;
}

void Course::CouShow1(void)			//显示课程信息时使用
{
	cout<<setw(13+name.length()/2)<<name;
	cout<<setw(18-name.length()/2+length(Number)/2)<<Number;
	cout<<setw(18-length(Number)/2+length(credit)/2)<<credit;
	cout<<setw(18-length(credit)/2+length(number)/2)<<number<<endl;
	return;
}

void Course::CouShow2(void)			//显示个人成绩单时使用
{
	cout<<setw(13+name.length()/2)<<name;
	cout<<setw(18-name.length()/2+length(Number)/2)<<Number;
	cout<<setw(18-length(Number)/2+length(credit)/2)<<credit;
	return;
}

void Course::CouShow(Data* data)	//显示该课程所有学生成绩
{
	cout<<setw(40+name.length()/2)<<name<<endl;
	cout<<strLine;
	for(int i=0; i<number; ++i)
	{
		Student* student = data->StuSearch(StudentId[i]);
		cout<<setw(13+(student->GetName()).length()/2)<<student->GetName();
		cout<<setw(18-(student->GetName()).length()/2+length(StudentId[i])/2)<<StudentId[i];
		cout<<setw(18-length(StudentId[i])/2+(student->GetClass()).length()/2)<<student->GetClass();
		if(grade[i]!=-1)
			cout<<setw(18-(student->GetClass()).length()/2+length(grade[i])/2)<<grade[i]<<endl;
		else
			cout<<setw(18-(student->GetClass()).length()/2+4/2)<<"暂无"<<endl;
	}
	return;
}

void Course::CouShow(Data* data, string Class)	//显示该课程某班级所有学生成绩
{
	cout<<setw(40+name.length()/2)<<name<<endl;
	cout<<setw(40+Class.length()/2)<<Class<<endl;
	cout<<strLine;
	for(int i=0; i<number; ++i)
	{
		Student* student = data->StuSearch(StudentId[i]);
		if(student->GetClass()==Class)
		{
			cout<<setw(20+(student->GetName()).length()/2)<<student->GetName();
			cout<<setw(20-(student->GetName()).length()/2+length(StudentId[i])/2)<<StudentId[i];
			if(grade[i]!=-1)
				cout<<setw(20-length(StudentId[i])/2+length(grade[i])/2)<<grade[i]<<endl;
			else
				cout<<setw(20-length(StudentId[i])/2+4/2)<<"暂无"<<endl;
		}
	}
	return;
}

////Data类函数定义
Data::~Data()
{
	if(StuHead!=NULL)
	{
		StuNode *p=StuHead->next,*q;
		while(p!=NULL)
		{
			q=p;
			p=p->next;
			delete q;
		}
		delete StuHead;
	}
	if(CouHead!=NULL)
	{
		CouNode *r=CouHead->next,*s;
		while(r!=NULL)
		{
			s=r;
			r=r->next;
			delete s;
		}
		delete CouHead;
	}
}

bool Data::AddStu(Student student)
{
	if(StuHead==NULL)
	{
		StuHead=new StuNode;
		StuHead->Student=student;
		StuHead->next=NULL;
		StuNumber++;
		return true;
	}
	//else
	bool success=true;
	StuNode* tem;
	for(StuNode* p=StuHead; p!=NULL; p=p->next)
	{
		if(p->Student.GetId()==student.GetId())
		{success=false;break;}
		tem=p;
	}
	if(success)
	{
		tem->next=new StuNode;
		tem->next->Student=student;
		tem->next->next=NULL;
		StuNumber++;
	}
	return success;
}

bool Data::AddCou(Course course)
{
	if(CouHead==NULL)
	{
		CouHead=new CouNode;
		CouHead->Course=course;
		CouHead->next=NULL;
		CouNumber++;
		return true;
	}
	//else
	bool success=true;
	CouNode* tem;
	for(CouNode* p=CouHead; p!=NULL; p=p->next)
	{
		if(p->Course.GetNumber()==course.GetNumber())
		{success=false;break;}
		tem=p;
	}
	if(success)
	{
		tem->next=new CouNode;
		tem->next->Course=course;
		tem->next->next=NULL;
		CouNumber++;
	}
	return success;
}

void Data::DelStuCS(Student* student)	//不考虑无此学生情况，用来删除CS中该学生的成绩
{
	for(int i=0; i<student->Getnumber(); i++)
	{
		Course* course=CouSearch(student->GetCourseNumber(i));
		course->Delete(student->GetId());
	}
}

void Data::DelCouSC(Course* course)	//不考虑无此课程情况，用来删除SC中该课程的成绩
{
	for(int i=0; i<course->Getnumber(); i++)
	{
		Student* student=StuSearch(course->GetStudentId(i));
		student->Delete(course->GetNumber());
	}
}

bool Data::DelStu(long id)
{
	StuNode* q=StuHead;
	if(q==NULL)	return false;
	if(q->Student.GetId()==id)
	{
			StuHead=StuHead->next;
		DelStuCS(&q->Student);
		delete q;
		StuNumber--;
		return true;
	}
	for(StuNode* p=StuHead->next; p!=NULL; q=p, p=p->next)
	{
		if(p->Student.GetId()==id)
		{
			q->next=p->next;
			DelStuCS(&p->Student);
			delete p;
			StuNumber--;
			return true;
		}
	}
	return false;
}

bool Data::DelCou(int cn)
{
	CouNode* q=CouHead;
	if(q==NULL)	return false;
	if(q->Course.GetNumber()==cn)
	{
		CouHead=CouHead->next;
		delete q;
		CouNumber--;
		return true;
	}
	for(CouNode* p=CouHead->next; p!=NULL; q=p, p=p->next)
	{
		if(p->Course.GetNumber()==cn)
		{
			q->next=p->next;
			delete p;
			CouNumber--;
			return true;
		}
	}
	return false;
}

Student* Data::StuSearch(long id)
{
	for(StuNode* p=StuHead; p!=NULL; p=p->next)
	{
		if(p->Student.GetId()==id)
			return &p->Student;
	}
	return NULL;
}

Course* Data::CouSearch(int Number)
{
	for(CouNode* p=CouHead; p!=NULL; p=p->next)
	{
		if(p->Course.GetNumber()==Number)
			return &p->Course;
	}
	return NULL;
}

void Data::StuSort(void)
{
	if(StuNumber<=1)	return;
	// StuNumber>=2
	StuNode *t, *t_new, *p, *p_pr, *p_af, *tem;

	t = NULL;
	do
	{
		t_new = StuHead;
		p=StuHead;p_af=StuHead->next;
		if( p->Student.GetId() > p_af->Student.GetId() )
		{
			p->next=p_af->next;p_af->next=p;StuHead=p_af;
			tem=p;p=p_af;p_af=tem;
			t_new = p_af;
		}
		if(p_af==t)	break;
		for(p_pr=StuHead,p=p_af,p_af=p_af->next; p_af!=t; p_pr=p, p=p_af, p_af=p_af->next )
		{
			if ( p->Student.GetId() > p_af->Student.GetId() )
			{
				p->next=p_af->next;p_af->next=p;p_pr->next=p_af;
				tem=p;p=p_af;p_af=tem;
				t_new = p_af;
			}
		}
		t=t_new;
	}	while ( t!=StuHead );
	return;
}

void Data::CouSort(void)
{
	if(CouNumber<=1)	return;
	// CouNumber>=2
	CouNode *t, *t_new, *p, *p_pr, *p_af, *tem;

	t = NULL;
	do
	{
		t_new = CouHead;
		p=CouHead;p_af=CouHead->next;
		if( p->Course.GetNumber() > p_af->Course.GetNumber() )
		{
			p->next=p_af->next;p_af->next=p;CouHead=p_af;
			tem=p;p=p_af;p_af=tem;
			t_new = p_af;
		}
		if(p_af==t)	break;
		for(p_pr=CouHead,p=p_af,p_af=p_af->next; p_af!=t; p_pr=p, p=p_af, p_af=p_af->next )
		{
			if ( p->Course.GetNumber() > p_af->Course.GetNumber() )
			{
				p->next=p_af->next;p_af->next=p;p_pr->next=p_af;
				tem=p;p=p_af;p_af=tem;
				t_new = p_af;
			}
		}
		t=t_new;
	}	while ( t!=CouHead );
	return;
}

void Data::CouShow(void)
{
	for(CouNode* p=CouHead; p!=NULL; p=p->next)
		p->Course.CouShow1();
	return;
}

void Data::StuShow(void)
{
	for(StuNode* p=StuHead; p!=NULL; p=p->next)
		p->Student.StuShow();
	return;
}
