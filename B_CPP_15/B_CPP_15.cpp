// B_CPP_15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template<class T>
class TreeNode{	
	/*
		����������
	*/

public:
	T element;														// ��ǰ�ڵ�洢������	
	TreeNode<T>* pLeft;												// ָ�����ӽڵ��ָ��	
	TreeNode<T>* pRight;											// ָ�����ӽڵ��ָ��	
	TreeNode<T>* pParent;											// ָ�򸸽���ָ��					
							
	TreeNode(T& ele){						
		//��ʼ�� TreeNode �ڵ�					
		memset(&element, 0, sizeof(TreeNode));					
		//ΪԪ�ظ�ֵ					
		memcpy(&element, &ele, sizeof(T));					
		pLeft = pRight = pParent = NULL;					
	}						
	//���� == �Ƚ�������Ƿ����						
	bool operator==(TreeNode<T>* node){ 						
		return node -> element == element ? TRUE : FALSE;
	}
};

template<class T>							
class BSortTree{							
public:							
	BSortTree();													// ���캯��
	~BSortTree();													// ��������
public:																
	bool IsEmpty();													// �ж����Ƿ�Ϊ��
	DWORD Insert(T element);										// �����ڵ�
	void Delete(T element);											// ɾ���ڵ�
	TreeNode<T>* Search(T element);									// ���ҽڵ�
	void InOrderTraverse(TreeNode<T>* pNode);						// �������
	void PreOrderTraverse(TreeNode<T>* pNode);						// ǰ�����
	void PostOrderTraverse(TreeNode<T>* pNode);						// �������
private:							
	TreeNode<T>* GetMaxNode(TreeNode<T>* pNode);					// ��ȡ�� pNode Ϊ�������ڵ�
	TreeNode<T>* GetMinNode(TreeNode<T>* pNode);					// ��ȡ�� pNode Ϊ������С�ڵ�
	TreeNode<T>* SearchNode(TreeNode<T>* pNode,T element);			// ���� element ��ֵ������Ӧ�ڵ�
	DWORD InsertNode(T element, TreeNode<T>* pNode);				// �����ڵ�
	TreeNode<T>* DeleteNode(T element, TreeNode<T>* pNode);			// ɾ���ڵ�
	void Clear(TreeNode<T>* pNode);									// ������нڵ�
private:							
	TreeNode<T>* m_pRoot;											// �����ָ��
	int m_size;														// ����Ԫ������
};				
							
template<class T> 							
BSortTree<T>::BSortTree()							
{					
	/*
		���캯��
	*/ 

	m_pRoot = NULL;	
	m_size = 0;
}			
				
template<class T>
BSortTree<T>::~BSortTree()
{							
	/*
		��������
	*/		

	Clear(m_pRoot);
}			
				
template<class T>
DWORD BSortTree<T>::Insert(T element)							
{		
	/*
		�����ڵ�
	*/

	//������ڵ�Ϊ��						
	if (!m_pRoot)						
	{						
		m_pRoot = new TreeNode<T>(element);					
		m_size++;					
		return TRUE;					
	}						
	//������ڵ㲻Ϊ��						
	return InsertNode(element, m_pRoot);						
}		
					
template<class T> 							
DWORD BSortTree<T>::InsertNode(T element, TreeNode<T>* pNode)							
{						
	/*
		�����ڵ�(˽��)
	*/

	// ��Ԫ�ط�װ���ڵ���						
	TreeNode<T>* pNewNode = new TreeNode<T>(element);
	
	// ���element == ��ǰ�ڵ� ֱ�ӷ���						
	if(element == pNode -> element)						
	{						
		return TRUE;					
	}						
	// ���pNode�����ӽڵ�ΪNULL ����element < ��ǰ�ڵ�						
	if(pNode -> pLeft == NULL && element < pNode -> element)						
	{						
		pNode -> pLeft = pNewNode;					
		pNewNode -> pParent = pNode;					
		m_size++;					
		return TRUE;					
	}						
	// ���pNode�����ӽڵ�ΪNULL ����element > ��ǰ�ڵ�						
	if(pNode -> pRight == NULL && element > pNode -> element)
	{						
		pNode -> pRight = pNewNode;					
		pNewNode -> pParent = pNode;					
		m_size++;					
		return TRUE;					
	}						
	// ���element<��ǰ�ڵ� �ҵ�ǰ�ڵ����������Ϊ��						
	if(element < pNode -> element)						
	{						
		InsertNode(element, pNode -> pLeft);					
	}						
	else						
	{						
		InsertNode(element, pNode -> pRight);					
	}						
	return TRUE;						
}							
							
template<class T> 							
void BSortTree<T>::Clear(TreeNode<T>* pNode)							
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
	Clear(pNode -> pLeft);
	Clear(pNode -> pRight);

	// ����ָ���ͷ��ڴ沢��ʼ��ָ��
	delete[] &pNode -> element;
	pNode = NULL;				
}							
							
template<class T> 							
bool BSortTree<T>::IsEmpty()							
{		
	/*
		�ж����Ƿ�Ϊ��
	*/
	return size == 0 ? TRUE : FALSE;						
}							
							
template<class T> 							
TreeNode<T>* BSortTree<T>::Search(T element)							
{							
	return SearchNode(m_pRoot, element);						
}			
				
template<class T> 							
TreeNode<T>* BSortTree<T>::SearchNode(TreeNode<T>* pNode,T element)							
{				
	/*
		���� element ��ֵ������Ӧ�ڵ�
	*/

	//����ڵ�ΪNULL
	if(pNode == NULL)
	{						
		return NULL;					
	}
	//������	
	else if(element == pNode -> element)	
	{						
		return pNode;					
	}					
	//����Ƚڵ��Ԫ��С ������	
	else if(element < pNode -> element)						
	{						
		return SearchNode(pNode -> pLeft, element);					
	}	
	//����Ƚڵ��Ԫ�ش� ������	
	else					
	{
		return SearchNode(pNode -> pRight, element);					
	}
}							
							
template<class T> 							
void BSortTree<T>::Delete(T element)							
{							
	/*
		���ݸ�����Ԫ�� ɾ����Ӧ�ڵ�
	*/

	// ������ڵ�Ϊ�� ���޷�����ɾ��
	if (!m_pRoot)
	{
		return;
	}

	// ����˽�к�������ɾ��
	DeleteNode(element, m_pRoot);

	return;
}
							
template<class T> 							
TreeNode<T>* BSortTree<T>::DeleteNode(T element, TreeNode<T>* pNode)							
{							
	/*
		������������ɾ������(˽��)
	*/						

	// �ҵ����Ԫ�ض�Ӧ���׵�ַָ��
	TreeNode<T>* pElement = SearchNode(pNode, element);

	if (!pElement)
	{
		// ���û���ҵ�Ԫ��
		return NULL;
	}
			
	// ���������ֻ��һ��Ԫ��
	if (m_size == 1)
		{	
			// ɾ����Ԫ��
			delete[] pElement;

			// ��ʼ��ָ��
			pElement = NULL;

			// ���ĳ�Ա����
			m_pRoot = NULL;												
			m_size = NULL;											

			return NULL;
		}

	// �����Ҷ�ӽڵ�(û������)
	if (!pElement -> pLeft && !pElement -> pRight)
	{
		// �ҵ����ڵ��Ӧ��ָ�벢��Ϊ NULL
		if (pElement -> element < pElement -> pParent -> element)
		{
			pElement -> pParent -> pLeft = NULL;
		}
		else
		{
			pElement -> pParent -> pRight = NULL;
		}

		// �ͷŴ˽ڵ��Ӧ�Ŀռ�
		delete[] pElement;

		// ��ʼ��ָ��
		pElement = NULL;

		// ���³�Ա����
		m_size--;

		return NULL;
	}

	// �����һ������
	if (pElement -> pLeft && !pElement -> pRight)
	{
		// �����ڵ��Ӧ��ָ��ָ������
		if (pElement -> element < pElement -> pParent -> element)
		{
			pElement -> pParent -> pLeft = pElement -> pLeft;
		}
		else
		{
			pElement -> pParent -> pRight = pElement -> pLeft;
		}

		// �ͷŵ�ǰ�ڵ�Ŀռ�
		delete pElement;

		// ��ʼ��ָ��
		pElement = NULL;

		// ���³�Ա����
		m_size--;

		return NULL;
	}
	else if (!pElement -> pLeft && pElement -> pRight)
	{
		if (pElement -> element < pElement -> pParent -> element)
		{
			pElement -> pParent -> pLeft = pElement -> pRight;
		}
		else
		{
			pElement -> pParent -> pRight = pElement -> pRight;
		}

		// �ͷŵ�ǰ�ڵ�Ŀռ�
		delete pElement;

		// ��ʼ��ָ��
		pElement = NULL;

		// ���³�Ա����
		m_size--;

		return NULL;
	}

	// �������������
	if (pElement -> pLeft && pElement -> pRight)
	{
		// �ҵ�����������С�Ľڵ�
		TreeNode<T>* pMinNode = GetMinNode(pElement -> pRight);

		// ����������С�Ľڵ��ֵ��ֵ����ǰ�ڵ�
		pElement -> element = pMinNode -> element;

		// ������������С�Ľڵ�ĸ��ڵ��ָ��ָ����������
		if (!pMinNode -> pRight)
		{
			pMinNode -> pParent -> pRight = NULL;
		}
		else if (pMinNode -> pRight)
		{
			pMinNode -> pParent -> pRight = pMinNode -> pRight;
		}

		// �ͷŵ�ǰ�ڵ�Ŀռ�
		delete[] pMinNode;

		// ��ʼ��ָ��
		pMinNode = NULL;

		// ���³�Ա����
		m_size--;

		return NULL;
	}
}
			
template<class T>
TreeNode<T>* BSortTree<T>::GetMinNode(TreeNode<T>* pNode)
{
	/* 
		��ȡ�� pNode Ϊ��������������С�ڵ�
	*/ 

	if (!pNode -> pLeft)
	{
		return pNode;
	}

	GetMinNode(pNode -> pLeft);
	
}


// ***********************************************************************						


// ���Դ��룺							
			
void TestInsert()							
{							
	//12 8 5 9 17 15 13
	
	/*						
				12			
							
		8				17	
							
	5		9		15		
							
				13			
							
	*/						
							
	BSortTree<int> tree;						
							
	tree.Insert(12);						
	tree.Insert(8);						
	tree.Insert(5);						
	tree.Insert(9);						
	tree.Insert(17);						
	tree.Insert(15);						
	tree.Insert(13);						
}
						
void TestSerch()							
{							
	//12 8 5 9 17 15 13						
							
	BSortTree<int> tree;						
							
	tree.Insert(12);						
	tree.Insert(8);						
	tree.Insert(5);						
	tree.Insert(9);						
	tree.Insert(17);						
	tree.Insert(15);						
	tree.Insert(13);						
							
	TreeNode<int>* p = tree.Search(17);
	if (!p)
	{
		printf("û�д�Ԫ��\n");
		return;
	}
							
	printf("%x %d\n", p, p -> element);						
}							

void TestDelete()							
{							
	//12 8 5 9 17 15 13						
	/*						
				12			
							
		8				17	
							
	5		9		15		
							
				13			
							
	*/						
							
	BSortTree<int> tree;						
							
	tree.Insert(12);						
	tree.Insert(8);						
	tree.Insert(5);						
	tree.Insert(9);						
	tree.Insert(17);						
	tree.Insert(15);						
	tree.Insert(13);

	// tree.Delete(12);
	tree.Delete(8);
	tree.Delete(5);
	tree.Delete(9);
	tree.Delete(17);
	tree.Delete(13);
	tree.Delete(15);





	
	TreeNode<int>* ret = tree.Search(12);
	printf("%x\n", ret);
	ret = tree.Search(8);
	printf("%d\n", ret);
	ret = tree.Search(5);
	printf("%d\n", ret);
	ret = tree.Search(9);
	printf("%d\n", ret);
	ret = tree.Search(17);
	printf("%d\n", ret);
	ret = tree.Search(15);
	printf("%d\n", ret);
	ret = tree.Search(13);
	printf("%d\n", ret);

	return;
}	

int main(int argc, char* argv[])
{
	/*
		������ϰ��
		���������������ɾ������
	*/

	TestDelete();
	
	getchar();
	return 0;
}
