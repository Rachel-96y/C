// B_CPP_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Base				
{				
public:				
	int x;			
public:				
	Base()			
	{			
		x = 100;		
	}			
    void Function_1()				
    {				
        printf("Base:Function_1...\n");				
    }				
    virtual void Function_2()				
    {				
        printf("Base:Function_2...virtual\n");				
    }				
};
				
class Sub:public Base				
{				
public:				
	int x;			
public:				
	Sub()			
	{			
		x = 200;		
	}			
    void Function_1()				
    {				
        printf("Sub:Function_1...\n");				
    }				
    virtual void Function_2()				
    {				
        printf("Sub:Function_2...virtual\n");				
    }				
};				

void TestBound(Base* pb)				
{				
	int n = pb->x;	
	
	printf("%x\n",n);			
				
	pb->Function_1();		//��������	
				
	pb->Function_2();			
}				


int main(int argc, char* argv[])
{
	/*
		������ϰ��	
	
			1������һ�����ࣺBase ��������ԱX,Y ��һ������ Print (�� virtul )	
			�ܹ���ӡX,Y��ֵ.	
				
			����3�����ࣺSub1  ��һ����ԱA	
				
					Sub2  ��һ����ԱB
				
					Sub3  ��һ����ԱC
				
					
			ÿ��������һ������ Print (�� virtul )����ӡ���г�Ա.	
				
			Sub1:��ӡX Y A	
				
			Sub2:��ӡX Y B	
				
			Sub3:��ӡX Y C	
				
			2������һ�����飬�洢 Base Sub1 Sub2 Sub3 ʹ��һ��ѭ�����	
			�������е� Print ������	
				
			3�����������е� Print �����ĳ� virtul �����۲�Ч��.	
				
			4��˼���⣺Ϊʲô������������д�� virtul �ģ�	
				
			5��дһ�����ӳ��������ֶ�̬������.	

				#include <iostream>
				#include <cmath>
				using namespace std;
				class CShape  //���ࣺ������
				{
					public:
						virtual double Area() { };  //�����
						virtual void PrintInfo() { }; //��ʾ��Ϣ
				};
				class CRectangle:public CShape  //�����ࣺ������
				{
					public:
						int w,h;     //��͸�
						virtual double Area();
						virtual void PrintInfo();
				};
				class CCircle:public CShape  //�����ࣺԲ��
				{
					public:
						int r;      //�뾶
						virtual double Area();
						virtual void PrintInfo();
				};
				class CTriangle:public CShape //�����ࣺ��������
				{
					public:
						int a,b,c;      //���߳�
						virtual double Area();
						virtual void PrintInfo();
				};
				double CRectangle::Area()  {
					return w * h;
				}
				void CRectangle::PrintInfo()  {
					cout << "Rectangle:" << Area() << endl;
				}
				double CCircle::Area()  {
					return 3.14 * r * r ;
				}
				void CCircle::PrintInfo()  {
					cout << "Circle:" << Area() << endl;
				}
				double CTriangle::Area()  {   //���ݺ��׹�ʽ�������������
					double p = ( a + b + c) / 2.0;
					return sqrt(p * ( p - a)*(p- b)*(p - c));
				}
				void CTriangle::PrintInfo()  {
					cout << "Triangle:" << Area() << endl;
				}
				CShape *pShapes[100]; //������Ÿ��ּ������壬���費����100��
				int MyCompare(const void *s1, const void *s2)  //�����������ĺ���
				{
					CShape **p1 = (CShape **)s1; //s1��ָ��ָ���ָ��,��ָ���ָ��ΪCShape* ����
					CShape **p2 = ( CShape **)s2;
					double a1 = (*p1)->Area(); //p1ָ�򼸺���������ָ��, *p1��ָ�򼸺��������
					double a2 = (*p2)->Area();
					if( a1 < a2 )
						return -1;   //���С����ǰ��
					else if (a2 < a1)
						return 1;
					else
						return 0;
				}
				int main()
				{
					int i; int n;
					CRectangle *pr; CCircle *pc; CTriangle *pt;
					cin >> n;
					for( i = 0;i < n;++i ) {
						char c;
						cin >> c;
						switch(c) {
							case 'R': //����
							pr = new CRectangle();
							cin >> pr->w >> pr->h;
							pShapes[i] = pr;
							break;
							 case 'C': //Բ
							pc  = new CCircle();
							cin >> pc->r;
							pShapes[i] = pc;
							break;
							case 'T': //������
							pt = new CTriangle();
							cin >> pt->a >> pt->b >> pt->c;
							pShapes[i] = pt;
							break;
						}
					}
					qsort(pShapes,n,sizeof(Cshape *),MyCompare);
					for(i = 0;i <n;++i) {
						pShapes[i]->PrintInfo();
						delete pShapes[i]; //�ͷſռ�
					}
					return 0;
				}

	*/
	Base a;
	Sub b;
	Base* arr[2] = {&a, &b};
	for (int i = 0; i < 2; i++)
	{
		TestBound(arr[i]);
	}
	getchar();
	return 0;
}
