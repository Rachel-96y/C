// B_CPP_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct MyStruct 
{
	// ���� Int ���͵ĳ�ԱX��Y
	INT X;
	INT Y;
	
	// �ֱ�ʵ�ֶ�X Y�ļӷ����������˷�������Ĺ���.
	Plus()
	{
		return X + Y;
	}

	Sub()
	{
		return X - Y;
	}

	Mul()
	{
		return X * Y;
	}

	Div()
	{
		return X / Y;
	}

} MySt, *PMySt;

typedef struct StructVoid 
{
	
} St, *PSt; 


int main(int argc, char* argv[])				
{			
	/*
		������ϰ��								
								
			1�����һ���ṹ�壬������Int���͵ĳ�ԱX��Y �ڽṹ���ڲ�����4������								
											
			�ֱ�ʵ�ֶ�X Y�ļӷ����������˷�������Ĺ���.								
				
				  
			2���۲���Щ�������õ�ʱ���������ĺ�����������Щ��ͬ��								
											
			�Ӳ������ݡ�ѹջ˳�򡢶�ջƽ�����ܽ�.								
				
				  
			3���սṹ��Ĵ�С�Ƕ��٣�Ϊʲô��								
				
				  
			4����������ܷ�ִ�У�								
																	
			struct Person  								
			{  								
				int x ;							
				void Fn_1()								
				{							
					printf("Person:Fn_1()\n");						
				}							
				void Fn_2() 								
				{							
					x = 10;						
					printf("Person:Fn_2()%x\n");						
				}							
			};  								
  											
											
			int main(int argc, char* argv[])								
			{								
				Person* p = NULL;							
											
				p -> Fn_1();							
				p -> Fn_2();							
											
				return 0;							
			}								

	*/
	
	/*
		1�����һ���ṹ�壬������Int���͵ĳ�ԱX��Y �ڽṹ���ڲ�����4������																
		�ֱ�ʵ�ֶ�X Y�ļӷ����������˷�������Ĺ���.
	*/

	MySt mySt;
	mySt.X = 10;
	mySt.Y = 5;
	INT result1 = mySt.Plus();
	INT result2 = mySt.Sub();
	INT result3 = mySt.Mul();
	INT result4 = mySt.Div();

	// answer = 15 ,5 ,50 ,2
	printf("%d, %d, %d, %d \n", result1, result2, result3, result4);

	
	

	/*
		2���۲���Щ�������õ�ʱ���������ĺ�����������Щ��ͬ��								
		�Ӳ������ݡ�ѹջ˳�򡢶�ջƽ�����ܽ�.

		��Щ�����ڵ���ǰ����ͨ�� ECX ����һ�� this ָ��(�ṹ����׵�ַ)��������
		ѹջ˳�����ȴ�������ѹ������Ҫ�Ĳ�����ѹ�� this ָ��
		�����Ķ�ջƽ�����ƽջ�������ƽջ

	*/

	/*
		3���սṹ��Ĵ�С�Ƕ��٣�Ϊʲô��

		�սṹ��Ĵ�С�� 1 �ֽ� 
		C++��׼�й涨 �κβ�ͬ�Ķ�����ӵ����ͬ���ڴ��ַ��������СΪ0��
		��������һ�������Ķ������飬��ô�����е�ÿ������ӵ������ͬ�ĵ�ַ

		�սṹ�壨�������ݳ�Ա����sizeofֵΪ1������һ������ռ�ռ䡰�ı�����α�ȡ��ַ��
		������ͬ�ġ��սṹ�塱��������ε��������أ����ǣ����սṹ�塱����Ҳ�ñ��洢��
		����������Ҳ��ֻ��Ϊ�����һ���ֽڵĿռ�����ռλ��


	*/
	printf("%d\n", sizeof(St));
	
	
	/*	
  		4����������ܷ�ִ�У�								
											
											
			struct Person  								
			{  								
				int x ;							
				void Fn_1()								
				{							
					printf("Person:Fn_1()\n");						
				}							
				void Fn_2() 								
				{							
					x = 10;						
					printf("Person:Fn_2()%x\n");						
				}							
			};  								
  											
											
			int main(int argc, char* argv[])								
			{								
				Person* p = NULL;							
											
				p -> Fn_1();							
				p -> Fn_2();							
											
				return 0;							
			}	

		����ִ�� ��Ϊû��ʹ������ṹ�������ṹ�����
		��������������ṹ���ָ�� ��������ṹ���ָ��
		ȴָ���� NULL �⽫���� C00000005 ����
	*/

	getchar();

	return 0;			
}



								
  								
								
