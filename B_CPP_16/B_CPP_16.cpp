// B_CPP_16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class T_Dynamic> class BinarySearchTree								// ����������(����������)
{	
private:		// ˽�нṹ��
	typedef struct _NODE {														// �ڵ�
		T_Dynamic			e_T_Date;											// ��̬����
		DWORD				e_dwID;												// ���ڱȽϽṹ���С
		_NODE*				e_pLeft;											// ������ָ��
		_NODE*				e_pRight;											// ������ָ��
		_NODE*				e_pParent;											// ��ָ��
	} NODE, *PNODE;

private:		// ˽�б���							
	PNODE					e_pRoot;											// ���ڵ�ָ��
	DWORD					e_dwCount;											// Ԫ������

private:		// ˽�к���
	PNODE   WINAPI   m_GetMaxNode(PNODE pNode);									// ��ȡ�� pNode Ϊ�������ڵ�
	PNODE	WINAPI	 m_GetMinNode(PNODE pNode);									// ��ȡ�� pNode Ϊ������С�ڵ�
	PNODE	WINAPI	 m_SearchNode(PNODE pNode, T_Dynamic T_element);			// ����ָ��Ԫ��(˽��)
	DWORD	WINAPI	 m_InsertNode(PNODE pNode, T_Dynamic T_element);			// �����ڵ�(˽��)
	BOOL	WINAPI	 m_DeleteNode(PNODE pNode, T_Dynamic T_element);			// ɾ���ڵ�(˽��)
	BOOL	WINAPI	 m_ClearNode(void);											// �������

public:			// ���켰��������
	WINAPI   BinarySearchTree(void);											// Ĭ�ϴ���һ��Ԫ��
	WINAPI	 BinarySearchTree(DWORD dwNumber);									// ���������ֵ����Ԫ��
	WINAPI	 ~BinarySearchTree(void);											// �ͷ��ڴ�

public:			// ���к���
	PNODE   WINAPI   Search(T_Dynamic T_element);								// ����ָ��Ԫ��
	PNODE	WINAPI	 Insert(T_Dynamic T_element);								// �����ڵ�
	BOOL	WINAPI	 Delete(T_Dynamic T_element);								// ɾ���ڵ�
	BOOL	WINAPI	 IsEmpty(void);												// �ж������Ƿ�Ϊ��
	BOOL	WINAPI	 Clear(void);												// �������

public:			// ���� >�� >= �� < �� <=�� ==
	BOOL WINAPI operator > (const BinarySearchTree& pBinarySearchTree);			// ���� ">"  ��� A -> e_dwID > B.e_dwID  ��Ϊ TRUE
	BOOL WINAPI operator >= (const BinarySearchTree& pBinarySearchTree);		// ���� ">=" ��� A -> e_dwID >= B.e_dwID ��Ϊ TRUE
	BOOL WINAPI operator < (const BinarySearchTree& pBinarySearchTree);			// ���� "<"  ��� A -> e_dwID < B.e_dwID  ��Ϊ TRUE
	BOOL WINAPI operator <= (const BinarySearchTree& pBinarySearchTree);		// ���� "<=" ��� A -> e_dwID <= B.e_dwID ��Ϊ TRUE
	BOOL WINAPI operator == (const BinarySearchTree& pBinarySearchTree);		// ���� "==" ��� A �ڴ�� B �ڴ���ȫ��� ��Ϊ TRUE
};

int main(int argc, char* argv[])
{
	/* 
		ʵ��һ���Լ������������� 
	*/

	return 0;
}