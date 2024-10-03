// B_CPP_14.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

class Monster								
{	
	/* 
		����Ľṹ�� 
		�洢������Ϣ ��ID����Level����Name��
		��һ���вεĹ��캯�� 
		�޲εĹ��캯��û�н����κβ���
	*/
public:								
	int ID;							
	int Level;							
	char Name[20];							
public:								
	Monster(){}	
	Monster(int ID, int Level, char* Name)							
	{							
		this -> ID = ID;						
		this -> Level = Level;						
		memcpy(&this -> Name, Name, strlen(Name) + 1);						
	}							
};								
								
template<class T>								
class TreeNode{	
	/*
		���ڵ�
		�洢һ����̬���� + 2����ַ ��pLeft����pRight��
		��һ�����캯�����ڳ�ʼ���ڵ㲢ΪԪ�ظ�ֵ
	*/
public:								
	T element;												// ��ǰ�ڵ�洢������		
	TreeNode<T>* pLeft;										// ָ�����ӽڵ��ָ��		
	TreeNode<T>* pRight;									// ָ�����ӽڵ��ָ��		
								
	TreeNode(T& ele){							
		//��ʼ��Node�ڵ�						
		memset(&element,0,sizeof(TreeNode));						
		//ΪԪ�ظ�ֵ						
		memcpy(&element,&ele,sizeof(T));						
		pLeft = pRight = NULL;						
	}							
};								
								
template<class T>								
class BSortTree{
	/*
		������Ҫ����
		�ж������Ĺ��켰��������
		֧�ֶ��ַ�����Ԫ�ؽ��в�ѯ�����������롢ɾ����
	*/

public:								
	BSortTree();												// ���캯��		
	~BSortTree();												// ��������		
public:								
	void InOrderTraverse(TreeNode<T>* pNode);					// �������		
	void PreOrderTraverse(TreeNode<T>* pNode);					// ǰ�����		
	void PostOrderTraverse(TreeNode<T>* pNode);					// �������		
	TreeNode<T>* GetRoot();										// ���ظ��ڵ�		
	int GetDepth(TreeNode<T>* pNode);							// ����ĳ���ڵ�ĸ߶�/���	
private:						
	void Init();												// ר�����ܣ�Ϊ�������е�Ԫ�ظ�ֵ��Monster��
	void ReleaseMemory(TreeNode<T>* pNode);						// ���ڵݹ��ͷ��ڴ�ĺ���
private:								
	TreeNode<T>* m_pRoot;										// �����ָ��		
	int size;													// ����Ԫ���ܸ���		
};			
					
template<class T>
void BSortTree<T>::ReleaseMemory(TreeNode<T>* pNode)
{
	/*
		���ú��������(�� �� ��)�ͷ��ڴ�
	*/
	// �ж��Ƿ�ڵ��ǿ�ֵ
	if(!pNode)
	{
		return;
	}
	
	// �ݹ����
	ReleaseMemory(pNode -> pLeft);
	ReleaseMemory(pNode -> pRight);

	// ����ָ���ͷ��ڴ沢��ʼ��ָ��
	delete[] &pNode -> element;
	pNode = NULL;
}				
	
template<class T> 								
BSortTree<T>::BSortTree()								
{						
	/*
		�ṹ�� BSortTree �Ĺ��캯��
		ʹ�ýṹ������ Moster �����ṹ�����
		���Խڵ�Ԫ�ؽ��и�ֵ 
	*/
	Init();							
}								
template<class T> 								
BSortTree<T>::~BSortTree(){								
								
	/* 
		�ͷ����нڵ�Ŀռ䲢��ʼ��ָ�� 
	*/

	// ���ݶ������ĸ��ڵ��ҵ�ȫ���Ľڵ�ָ�벢�ͷ��ڴ�
	ReleaseMemory(m_pRoot);
	
}								
								
template<class T> 								
void BSortTree<T>::Init()								
{				
	/*
		ʹ�ýṹ������ Moster �����ṹ�����
		���Խڵ�Ԫ�ؽ��и�ֵ 
	*/

	// ��������ṹ����󲢸�ֵ��m1~m7��
	Monster m1(1, 1, "���");							
	Monster m2(2, 2, "Ұ��");							
	Monster m3(3, 3, "Ұ��");							
	Monster m4(4, 4, "ʿ��");							
	Monster m5(5, 5, "����");							
	Monster m6(6, 6, "������");							
	Monster m7(7, 7, "�������");							
					
	// �ڶ��д������ TreeNode ���͵��ڴ沢�� Monster ��С�����ݸ�ֵΪ��m1-m7��
	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);							
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);							
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);							
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);							
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);							
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);							
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);							
					
	// �Զ������ڵ㡾TreeNode���еĵ�ַ��pLeft��pRight�����и�ֵ
	m_pRoot = n5;							
	n5 -> pLeft = n4;							
	n5 -> pRight = n6;							
	n4 -> pLeft = n1;							
	n1 -> pRight = n2;							
	n6 -> pLeft = n3;							
	n3 -> pRight = n7;							
	size = 7;			
}
				
template<class T> 								
TreeNode<T>* BSortTree<T>::GetRoot()								
{				
	/* 
		���ظ��ڵ� 
	*/
	
	return m_pRoot;							
}				
				
template<class T>								
int BSortTree<T>::GetDepth(TreeNode<T>* pNode)								
{					
	/* 
		����ĳ���ڵ�ĸ߶�/��� 
	*/ 

    if(!pNode) 								
    {								
		return NULL;  							
    }								
    else  								
    {  								
        int m = GetDepth(pNode -> pLeft);  								
        int n = GetDepth(pNode -> pRight);  								
        return (m > n) ? (m+1) : (n+1);   								
    }  								
}		
						
template<class T> 								
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)								
{								
	/* ����������й���,�г��ֵ����� */
	// ���������(�� �� ��)

	if (!pNode)
	{
		return;
	}

	// �ݹ����
	InOrderTraverse(pNode -> pLeft);

	// �ҵ����ֵĵ�ַ
	LPSTR name = (LPSTR)((DWORD)&pNode -> element + sizeof(INT) * 2);
	printf("%s\n", name);

	InOrderTraverse(pNode -> pRight);
}								
								
template<class T> 								
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)								
{											
	/* ǰ��������й���,�г��ֵ����� */
	// ǰ�������(�� �� ��)

	if (!pNode)
	{
		return;
	}

	// �ҵ����ֵĵ�ַ
	LPSTR name = (LPSTR)((DWORD)&pNode -> element + sizeof(INT) * 2);
	printf("%s\n", name);

	// �ݹ����
	PreOrderTraverse(pNode -> pLeft);
	PreOrderTraverse(pNode -> pRight);
}								
								
template<class T> 								
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)								
{										
	/* ����������й���,�г��ֵ����� */
	// ���������(�� �� ��)

	if (!pNode)
	{
		return;
	}

	// �ݹ����
	PostOrderTraverse(pNode -> pLeft);
	PostOrderTraverse(pNode -> pRight);

	// �ҵ����ֵĵ�ַ
	LPSTR name = (LPSTR)((DWORD)&pNode -> element + sizeof(INT) * 2);
	printf("%s\n", name);
}								


VOID function()
{
	/*
		�����������еĹ����б�
	*/
	
	// ʹ�� Monster ���� ����һ�� test ���͵ı���
	// �����˶�� TreeNode ���͵ı��������ݶ��������ص㸳ֵ���
	BSortTree<Monster> test;

	// ��ȡ�������ĸ��ڵ�
	TreeNode<Monster>* pRoot = test.GetRoot();

	// �������й���,�г��ֵ�����

	printf("ǰ�����:\n");
	test.PreOrderTraverse(pRoot);
	printf("\n�������:\n");
	test.InOrderTraverse(pRoot);
	printf("\n�������:\n");
	test.PostOrderTraverse(pRoot);

}

int main(int argc, char* argv[])
{
	/*
		������ϰ��
			1�������������еĹ����б�.		
			2��������������еĴ���			
			˼���⣺			
			������ֶ���������˫������		
	*/

	// ������ֶ���������˫������?
	// ����û��һ����ַָ����һ�����׵�ַ

	function();
		
	getchar();
	return 0;
}