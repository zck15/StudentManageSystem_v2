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
	~SC()
	{delete[]CourseNumber;delete[]grade;}	//delete[] NULL �������

	int Search(int cn);		//���ҿγ̱��Ϊcn�Ŀ�����λ�ã��޽������-1
	bool Add(int cn);			//����ѡ�Σ������Ƿ�ɹ��������γ̱�ţ����ӿγ̳ɼ���Ϊ-1
	bool Delete(int cn);
	int Getnumber(void)	{return number;}
	int GetCourseNumber(int i)	{return CourseNumber[i];}		//i<number
	void SetGrade( int cn, int grade )	//δ�����������γ̷���ѡ�γ̵����
	{this->grade[Search(cn)]=grade;return;}
	int GetGrade( int cn )		//δ�����������γ̷���ѡ�γ̵����
	{return grade[Search(cn)];}
	void CouSort(void);		//���γ̰��γ̱����С����ð������
	int GPA_40(Data *data);	//40������
	void CouShow(Data* data);
	void Initialize(int n,int cn[], int grade[]);//���ļ��ж�ȡʱ�õ��ĳ�ʼ������

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
	string GetPassword(void)//�洢���ļ�ʱʹ��
	{return password;}

	Student operator= (Student student);
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
	~CS()
	{delete[]StudentId;delete[]grade;}	//delete[] NULL �������
	
	int Search(long id);		//����ѧ��Ϊid��ѧ������λ�ã��޽������-1
	bool Add(long id);
	bool Delete(long id);
	int Getnumber(void)	{return number;}
	long GetStudentId(int i)	{return StudentId[i];}
	void SetGrade( long id, int grade )	//δ�����������γ̷���ѡ�γ̵����
	{this->grade[Search(id)]=grade;return;}
	int GetGrade( long id )		//δ�����������γ̷���ѡ�γ̵����
	{return grade[Search(id)];}
	int CheckGrade(void);		//���δ¼��ɼ���ѧ������
	void StuSort_id(void);		//��ѧ����ѧ����С����ð������
	void StuSort_grade(void);		//��ѧ����grade�ɴ�Сð������
	void Initialize(int n,int id[], int grade[]);//���ļ��ж�ȡʱ�õ��ĳ�ʼ������
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
	void CouShow1(void);		//��ʾ�γ���Ϣʱʹ��
	void CouShow2(void);		//��ʾ���˳ɼ���ʱʹ��
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
	void DelStuCS(Student* student);	//�������޴�ѧ�����������ɾ��CS�и�ѧ���ĳɼ�
	void DelCouSC(Course* course);		//�������޴˿γ����������ɾ��SC�иÿγ̵ĳɼ�
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
	//�����ļ����ú���
	friend void EndProcess(void);
	string GetTeaPassword(void)
	{return TeaPassword;}
};

////��������
////��������
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

////SC�ຯ������
int SC::Search(int cn)		//���ҿγ̱��Ϊcn�Ŀ�����λ�ã��޽������-1
{
	for(int i=0; i<number; ++i)
		if(CourseNumber[i]==cn)
			return i;
	return -1;
}

bool SC::Add(int cn)			//����ѡ�Σ������Ƿ�ɹ��������γ̱�ţ����ӿγ̳ɼ���Ϊ-1
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
		Gnew[number-1]=-1;		//δ�ǼǷ���ʱ��������Ϊ-1
		delete[]CourseNumber;	//delete[] NULL �������
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
		if(number==0){CourseNumber=NULL;grade=NULL;}	//ɾ�ɾ�ʱ��ָ����Ϊ��
		return true;
	}
	else
		return false;
}

void SC::CouSort(void)		//���γ̰��γ̱����С����ð������
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

int SC::GPA_40(Data *data)	//40������
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
			cout<<setw(18-length(course->GetCredit())/2+4/2)<<"����"<<endl;
	}
	return;
}

void SC::Initialize(int n,int cn[], int grade[])
{
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

////Student�ຯ������
Student Student::operator= (Student student)
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
		return *this;
	}
	//else
	CourseNumber = new int[number];
	grade = new int[number];
	for(int i=0; i<number; i++)
	{
		CourseNumber[i]=student.CourseNumber[i];
		grade[i]=student.grade[i];
	}
	return *this;
}

void Student::StuShow(void)
{
	cout<<setw(19+name.length()/2)<<name;
	cout<<setw(21-name.length()/2+length(id)/2)<<id;
	cout<<setw(21-length(id)/2+Class.length()/2)<<Class<<endl;
	return;
}

////CS�ຯ������
int CS::Search(long id)		//����ѧ��Ϊid��ѧ������λ�ã��޽������-1
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
		delete[]StudentId;	//delete[] NULL �������
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
		if(number==0){StudentId=NULL;grade=NULL;}	//ɾ�ɾ�ʱ��ָ����Ϊ��
		return true;
	}
	else
		return false;
}

int CS::CheckGrade(void)		//���δ¼��ɼ���ѧ������
{
	int n=0;
	for (int i = 0; i < number; ++i)
		if(grade[i]==-1)
			n++;
	return n;
}

void CS::StuSort_id(void)		//��ѧ����ѧ����С����ð������
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

void CS::StuSort_grade(void)		//��ѧ����grade�ɴ�Сð������
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

void CS::Initialize(int n,int id[], int grade[])//���ļ��ж�ȡʱ�õ��ĳ�ʼ������
{
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

////Course�ຯ������
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

void Course::CouShow1(void)			//��ʾ�γ���Ϣʱʹ��
{
	cout<<setw(13+name.length()/2)<<name;
	cout<<setw(18-name.length()/2+length(Number)/2)<<Number;
	cout<<setw(18-length(Number)/2+length(credit)/2)<<credit;
	cout<<setw(18-length(credit)/2+length(number)/2)<<number<<endl;
	return;
}

void Course::CouShow2(void)			//��ʾ���˳ɼ���ʱʹ��
{
	cout<<setw(13+name.length()/2)<<name;
	cout<<setw(18-name.length()/2+length(Number)/2)<<Number;
	cout<<setw(18-length(Number)/2+length(credit)/2)<<credit;
	return;
}

////Data�ຯ������
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

void Data::DelStuCS(Student* student)	//�������޴�ѧ�����������ɾ��CS�и�ѧ���ĳɼ�
{
	for(int i=0; i<student->Getnumber(); i++)
	{
		Course* course=CouSearch(student->GetCourseNumber(i));
		course->Delete(student->GetId());
	}
}

void Data::DelCouSC(Course* course)	//�������޴˿γ����������ɾ��SC�иÿγ̵ĳɼ�
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
