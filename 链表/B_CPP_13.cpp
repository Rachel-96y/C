// B_CPP_13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class T_Dynamic> class ChainList // һ���������
{
private:	// ˽�нṹ��
	typedef struct _NODE {
		T_Dynamic			e_T_Date;									// ��̬����
		_NODE*				e_pAddress;									// ��̬���͵�ָ�� ָ����һ����ͬ�Ľṹ��
	} NODE, *PNODE;

private:	// ˽�б���
	DWORD					e_dwCount;									// �����е�Ԫ������
	PNODE					e_pChainListHeader;							// ����ͷָ��

private:	// ˽�к���
	PNODE WINAPI m_GetIndexCurrentNode(IN DWORD dwIndex);				// ��ȡ����Ϊ dwIndex ��ָ��
	PNODE WINAPI m_GetIndexPreviousNode(IN DWORD dwIndex);				// ��ȡ����Ϊ dwIndex ��ǰһ���ڵ�ָ��
	PNODE WINAPI m_GetIndexNextNode(IN DWORD dwIndex);					// ��ȡ����Ϊ dwIndex �ĺ�һ���ڵ�ָ��	

public:		// ���켰��������
	WINAPI ChainList();													// Ĭ�Ͻ�����һ������
	WINAPI ChainList(IN DWORD dwInputeNumber);							// ���������ֵ��������
	WINAPI ~ChainList();												// �ͷ�ȫ������Ŀռ�

public:		// ���к���
	BOOL  WINAPI IsEmpty(void);											// �ж������Ƿ�Ϊ�� �շ���1 �ǿշ���0			
	BOOL  WINAPI Clear(void);											// �������
	DWORD WINAPI GetElement(IN DWORD dwIndex,OUT T_Dynamic& Element);	// ����������ȡԪ��
	DWORD WINAPI GetElementIndex(IN const T_Dynamic& Element);			// ����Ԫ�ػ�ȡ�����е�����
	DWORD WINAPI Append(IN T_Dynamic Element);							// ��ĩβ׷��Ԫ��
	DWORD WINAPI Insert(IN DWORD dwIndex, IN T_Dynamic Element);		// ������������Ԫ��
	DWORD WINAPI Delete(IN DWORD dwIndex);								// ��������ɾ��Ԫ��
	DWORD WINAPI GetSize(void);											// ��ȡ������Ԫ�ص�����

public:		// ���� >�� >= �� < �� <=�� ==
	BOOL WINAPI operator > (const ChainList& pChainList);				// ���� ">"  ��� A -> e_dwCount > B.e_dwCount ��Ϊ TRUE
	BOOL WINAPI operator >= (const ChainList& pChainList);				// ���� ">=" ��� A -> e_dwCount >= B.e_dwCount ��Ϊ TRUE
	BOOL WINAPI operator < (const ChainList& pChainList);				// ���� "<"  ��� A -> e_dwCount < B.e_dwCount ��Ϊ TRUE
	BOOL WINAPI operator <= (const ChainList& pChainList);				// ���� "<=" ��� A -> e_dwCount <= B.e_dwCount ��Ϊ TRUE
	BOOL WINAPI operator == (const ChainList& pChainList);				// ���� "==" ��� A �ڴ�� B �ڴ���ȫ�����Ϊ TRUE
};

template <class T_Dynamic> ChainList<T_Dynamic>::PNODE WINAPI ChainList<T_Dynamic>::m_GetIndexCurrentNode(IN DWORD dwIndex)
{
	/*
		��ȡ����Ϊ dwIndex ��ָ��
	*/
	
	// �ж���������� dwIndex �Ƿ���Ч
	if (dwIndex < 0 || dwIndex >= this -> e_dwCount)
	{
		// ��Ч���±�
		return NULL;
	}

	// ��ȡ����ͷָ�� 
	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;

	// ����±���Ч���ȡ��Ӧ�ĵ�ַ
	for (int i = 0; i < (INT)dwIndex; i++)
	{
		// �ҵ���һ����ַ
		pTempNode = pTempNode -> e_pAddress;
	}
	
	return pTempNode;
}

template <class T_Dynamic> ChainList<T_Dynamic>::PNODE WINAPI ChainList<T_Dynamic>::m_GetIndexPreviousNode(IN DWORD dwIndex)
{
	/*
		��ȡ����Ϊ dwIndex ��ǰһ���ڵ�ָ��
	*/

	// �õ���ǰ�ڵ��±��ǰһ���ڵ��±�
	INT dwPreviousIndex = (INT)dwIndex - 1;

	// �ж���������� dwIndex ��ǰһ���ڵ�ָ���Ƿ���Ч
	if (dwPreviousIndex < 0 || dwPreviousIndex >= (INT)this -> e_dwCount)
	{
		// ��Ч���±�
		return NULL;
	}

	// ��ȡ����ͷָ�� 
	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;

	// ����±���Ч���ȡ��Ӧ�ĵ�ַ
	for (int i = 0; i < (INT)dwPreviousIndex; i++)
	{
		// �ҵ���һ����ַ
		pTempNode = pTempNode -> e_pAddress;
	}
	
	return pTempNode;
}

template <class T_Dynamic> ChainList<T_Dynamic>::PNODE WINAPI ChainList<T_Dynamic>::m_GetIndexNextNode(IN DWORD dwIndex)
{
	/*
		��ȡ����Ϊ dwIndex �ĺ�һ���ڵ�ָ��
	*/

	// �õ���ǰ�ڵ��±�ĺ�һ���ڵ��±�
	INT dwNextIndex = (INT)dwIndex + 1;

	// �ж���������� dwIndex ��ǰһ���ڵ�ָ���Ƿ���Ч
	if (dwNextIndex < 0 || dwNextIndex >= (INT)this -> e_dwCount)
	{
		// ��Ч���±�
		return NULL;
	}

	// ��ȡ����ͷָ�� 
	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;

	// ����±���Ч���ȡ��Ӧ�ĵ�ַ
	for (int i = 0; i < (INT)dwNextIndex; i++)
	{
		// �ҵ���һ����ַ
		pTempNode = pTempNode -> e_pAddress;
	}
	
	return pTempNode;
}

template <class T_Dynamic> WINAPI ChainList<T_Dynamic>::ChainList()
: e_dwCount(0x00000000), e_pChainListHeader(0x00000000)
{
	// Ĭ�Ͻ�����һ��Ԫ�صĿռ�
	ChainList<T_Dynamic>::PNODE pNode = new ChainList<T_Dynamic>::NODE;
	if (!pNode)
	{
		// �ڴ�����ʧ��
		printf("���޲εĹ��캯���� �ռ�����ʧ��\n");
		return;
	}
	memset(pNode, 0x00000000, sizeof(ChainList<T_Dynamic>::NODE));

	// �������еĳ�Ա����
	this -> e_dwCount = 0x00000001;
	this -> e_pChainListHeader = pNode;
}

template <class T_Dynamic> WINAPI ChainList<T_Dynamic>::ChainList(IN DWORD dwInputNumber)
: e_dwCount(0x00000000), e_pChainListHeader(0x00000000)
{
	// ������ת��Ϊ����ֵ
	if ((INT)dwInputNumber < 0x00000000)
	{
		dwInputNumber = -(INT)dwInputNumber;
	}

	// ����������������ֵ
	if (dwInputNumber > 100)
	{
		dwInputNumber = 100;
	}

	// �������������ֵ ���� e_dwCount ��ֵ
	if (!dwInputNumber)
	{
		this -> e_dwCount = NULL;
		this -> e_pChainListHeader = NULL;
		return;
	}
	else
	{
		this -> e_dwCount = dwInputNumber;
	}

	// �� ChainListNode �ṹ���еĵ�ַָ�븳ֵ
	for (int i = 0; i < (INT)this -> e_dwCount; i++)
	{
		ChainList<T_Dynamic>::PNODE pTempNode;
		ChainList<T_Dynamic>::PNODE pNode = new ChainList<T_Dynamic>::NODE;
		if (!pNode)
		{
			// �ڴ�����ʧ��
			printf("�ڴ������Ĺ��캯���� �ռ�����ʧ��\n");
			return;
		}
		memset(pNode, 0x00000000, sizeof(ChainList<T_Dynamic>::NODE));
		if (!i)
		{
			// ������ͷָ�븳ֵ
			this -> e_pChainListHeader = pNode;
		}
		if (i)
		{
			// ѭ����ÿ���ṹ���е� e_pAddress ��ֵΪ��һ���ṹ����׵�ַ
			pTempNode -> e_pAddress = pNode;
		}
		pTempNode = pNode;
	}
}

template <class T_Dynamic> WINAPI ChainList<T_Dynamic>::~ChainList()
{
	// ��ȡ����ͷָ�뼰Ԫ�ظ���

	// �������ͷָ��Ϊ NULL �������ٽ��пռ���ͷ�
	if (!this -> e_pChainListHeader && !this -> e_dwCount)
	{
		// ����Ϊ��
		return;
	}

	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;
	DWORD dwTempCount = this -> e_dwCount;

	// ѭ������ȫ��ָ���ͷ�������Ŀռ�
	do
	{
		if (!pTempNode -> e_pAddress)
		{
			// �����ַ��ֵ��ȫ0������������
			delete[] pTempNode;
			break;
		}

		// �ҵ���һ����ַ������
		ChainList<T_Dynamic>::PNODE pNextNode = pTempNode -> e_pAddress;

		// �ͷ���һ������ĵ�ַ�ռ�
		delete[] pTempNode;
		pTempNode = pNextNode;
	}
	// ��� e_dwCount ����0������������
	while(--dwTempCount);
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::IsEmpty(void)
{
	/* 
		�ж������Ƿ�Ϊ�� �շ���1 �ǿշ���0 
	*/

	if (this -> e_dwCount && this -> e_pChainListHeader)
	{
		return FALSE;
	}

	return TRUE;
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::Clear(void)
{
	/* 
		�������
	*/

	// �������ͷָ��Ϊ NULL �������ٽ��пռ���ͷ�
	if (!this -> e_pChainListHeader && !this -> e_dwCount)
	{
		// ����Ϊ��
		printf("��ǰ�����ǿյ�\n");
		return TRUE;
	}

	// ��ȡ����ͷָ�뼰Ԫ�ظ���
	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;
	DWORD dwTempCount = this -> e_dwCount;

	// ѭ������ȫ��ָ���ͷ�������Ŀռ�
	do
	{
		if (!pTempNode -> e_pAddress)
		{
			// �����ַ��ֵ��ȫ0������������
			delete[] pTempNode;
			break;
		}

		// �ҵ���һ����ַ������
		ChainList<T_Dynamic>::PNODE pNextNode = pTempNode -> e_pAddress;

		// �ͷ���һ������ĵ�ַ�ռ�
		delete[] pTempNode;
		pTempNode = pNextNode;
	}
	// ��� e_dwCount ����0������������
	while(--dwTempCount);

	// ���³�Ա����
	this -> e_dwCount = NULL;
	this -> e_pChainListHeader = NULL;

	return FALSE;
}

template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::GetElement(IN DWORD dwIndex, OUT T_Dynamic& Element)
{
	/*
		����������ȡԪ�� ����ֵ�Ǵ�Ԫ���������е�ָ��
	*/

	// �ж������Ƿ��ں���Χ
	if (dwIndex < 0 || dwIndex >= this -> e_dwCount)
	{
		// �������Ϸ�
		return NULL;
	}
	ChainList<T_Dynamic>::PNODE pTempNode = m_GetIndexCurrentNode(dwIndex);
	memcpy(&Element, pTempNode, sizeof(T_Dynamic));

	return TRUE;
}

template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::GetElementIndex(IN const T_Dynamic& Element)
{
	/* 
		����Ԫ�ػ�ȡ�����еĵ�һ������ 
	*/
	
	// �������ͷָ��Ϊ NULL ��������Ϊ��
	if (!this -> e_pChainListHeader && !this -> e_dwCount)
	{
		// ����Ϊ��
		printf("��ǰ�����ǿյ�\n");
		return 0xFFFFFFFF;
	}

	// ��ȡ����ͷָ�뼰Ԫ�ظ���
	ChainList<T_Dynamic>::PNODE pTempNode = this -> e_pChainListHeader;

	// ѭ������ȫ����ַ
	for (int ElementIndex = 0; ElementIndex < (INT)this -> e_dwCount; ElementIndex++)
	{
		// �ҵ���һ����ַ�ж��Ƿ�Ԫ�����
		int result = memcmp(&Element, pTempNode, sizeof(T_Dynamic));
		if (!result)
		{
			return ElementIndex;
		}

		// ����һ����ַ
		pTempNode = pTempNode -> e_pAddress;
	}
	
	printf("û����ͬ��Ԫ��\n");
	return 0xFFFFFFFE;
}

template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::Append(IN T_Dynamic Element)
{
	/*
		��ĩβ׷��Ԫ�� ���ش�Ԫ���������е�����
	*/

	// ��������һ��ռ�
	ChainList<T_Dynamic>::PNODE pNode = new ChainList<T_Dynamic>::NODE;

	// ��ʼ���˿ռ�
	memset(pNode, 0x00000000, sizeof(ChainList<T_Dynamic>::NODE));

	// ��������Ԫ�ظ�ֵ
	memcpy(pNode, &Element, sizeof(T_Dynamic));

	if (!this -> e_dwCount && !this -> e_pChainListHeader)
	{
		// ���������û��Ԫ��
		this -> e_pChainListHeader = pNode;
		this -> e_dwCount++;

		return this -> e_dwCount - 1;
	}
	
	// �ҵ����һ��Ԫ�صĵ�ַ
	ChainList<T_Dynamic>::PNODE pTempNode = m_GetIndexPreviousNode(this -> e_dwCount);
	
	// ����ָ��
	pTempNode -> e_pAddress = pNode;
	this -> e_dwCount++;

	return this -> e_dwCount - 1;
}

template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::Insert(IN DWORD dwIndex, IN T_Dynamic Element)
{
	/*
		������������Ԫ�� ���ش�Ԫ���������е�����
	*/

	// �ж������Ƿ���������Χ
	if ((INT)dwIndex < 0 || (INT)dwIndex > (INT)this -> e_dwCount)
	{
		// ���ں���Χ�򲻽��пռ�����
		printf("������±겻�ںϷ���Χ��\n");
		return NULL;
	}

	// ��������һ��ռ�
	ChainList<T_Dynamic>::PNODE pNode = new ChainList<T_Dynamic>::NODE;

	// ��ʼ���˿ռ�
	memset(pNode, 0x00000000, sizeof(ChainList<T_Dynamic>::NODE));

	// ��������Ԫ�ظ�ֵ
	memcpy(pNode, &Element, sizeof(T_Dynamic));


	// ���������±���0
	if (!dwIndex)
	{
		this -> e_pChainListHeader = pNode;
		this -> e_dwCount++;

		return e_dwCount - 1;
	}

	// ���������±������һ��Ԫ��֮��
	if (dwIndex == this -> e_dwCount)
	{
		// �ҵ����һ��Ԫ���׵�ַ
		ChainList<T_Dynamic>::PNODE pLastNode = m_GetIndexPreviousNode(this -> e_dwCount);

		// �������һ��Ԫ�ص� e_pAddress ��ָ��
		pLastNode -> e_pAddress = pNode;
		this -> e_dwCount++;

		return e_dwCount - 1;
	}

	// ���������±�����Ԫ��֮��
	// ��ȡ��һ��Ԫ�ؼ���һ��Ԫ�ص��׵�ַ
	ChainList<T_Dynamic>::PNODE pPreviousNode = m_GetIndexPreviousNode(dwIndex);
	ChainList<T_Dynamic>::PNODE pNextNode = m_GetIndexNextNode(dwIndex);

	// ����ָ��
	pPreviousNode -> e_pAddress = pNode;
	pNode -> e_pAddress = pNextNode;
	this -> e_dwCount++;

	return e_dwCount - 1;
}


template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::Delete(IN DWORD dwIndex)
{
	/*
		��������ɾ��Ԫ�� ����ʣ���Ԫ�ظ���
	*/

	// �ж��Ƿ���Ԫ��
	if (!this -> e_dwCount)
	{	
		// ������û��Ԫ��
		printf("������û��Ԫ��\n");
		return NULL;
	}

	// �ж������Ƿ���������Χ
	if ((INT)dwIndex < 0 || (INT)dwIndex >= (INT)this -> e_dwCount)
	{
		// ���ں���Χ�򲻽��пռ�����
		printf("Ҫɾ����Ԫ�ص��±겻�ںϷ���Χ��\n");
		return NULL;
	}

	// ������������� �ҵ���һ��Ԫ�� / ��ǰԪ�� / ��һ��Ԫ�صĵ�ַ ���û���򷴷���NULL
	ChainList<T_Dynamic>::PNODE	pPreviousNode = m_GetIndexPreviousNode(dwIndex);
	ChainList<T_Dynamic>::PNODE pCurrentNode = m_GetIndexCurrentNode(dwIndex);
	ChainList<T_Dynamic>::PNODE	pNextNode = m_GetIndexNextNode(dwIndex);

	// ���ֻ��һ��Ԫ��
	if (!(this -> e_dwCount ^ 0x00000001))
	{
		// �ͷſռ�
		delete[]  pCurrentNode;
		pCurrentNode = NULL;

		// ���³�Ա����
		this -> e_pChainListHeader = NULL;
		this -> e_dwCount = NULL;

		return this -> e_dwCount;
	}

	// ���Ҫɾ����λ���ǵ�һ��Ԫ��
	if (!(INT)dwIndex)
	{
		// ������ͷָ��ָ��ڶ���Ԫ�ص��׵�ַ
		this -> e_pChainListHeader = pNextNode;

		// �ͷſռ�
		delete[]  pCurrentNode;
		pCurrentNode = NULL;

		// ���³�Ա����
		this -> e_dwCount--;

		return this -> e_dwCount;
	}

	// ���Ҫɾ����λ�������һ��Ԫ��
	if ((INT)dwIndex == this -> e_dwCount)
	{
		// �������ڶ���Ԫ�ص� e_pAddress ����
		pPreviousNode -> e_pAddress = 0x00000000;

		// �ͷſռ�
		delete[]  pCurrentNode;
		pCurrentNode = NULL;

		// ���³�Ա����
		this -> e_dwCount--;
		
		return this -> e_dwCount;
	}

	// ���ɾ����λ��������Ԫ��֮��
	// ��ǰһ��Ԫ��ָ��ָ���һ��Ԫ���׵�ַ
	pPreviousNode -> e_pAddress = pNextNode;

	// �ͷſռ�
	delete[]  pCurrentNode;
	pCurrentNode = NULL;

	// ���³�Ա����
	this -> e_dwCount--;
	
	return this -> e_dwCount;
}

template <class T_Dynamic> DWORD WINAPI ChainList<T_Dynamic>::GetSize(void)
{
	/*
		��ȡ������Ԫ�ص�����
	*/

	return this -> e_dwCount;
}

/*
	BOOL WINAPI operator == (const ChainList& pChainList);				// ���� "==" ��� A �ڴ�� B �ڴ���ȫ�����Ϊ TRUE
*/
template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::operator > (const ChainList& pChainList)
{
	/* 
		���� ">"  ��� A -> e_dwCount > B.e_dwCount ��Ϊ TRUE 
	*/

	if (this -> e_dwCount > pChainList.e_dwCount)
	{
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::operator >= (const ChainList& pChainList)
{
	/* 
		���� ">=" ��� A -> e_dwCount >= B.e_dwCount ��Ϊ TRUE
	*/

	if (this -> e_dwCount >= pChainList.e_dwCount)
	{
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::operator < (const ChainList& pChainList)
{
	/* 
		���� "<"  ��� A -> e_dwCount < B.e_dwCount ��Ϊ TRUE
	*/

	if (this -> e_dwCount < pChainList.e_dwCount)
	{
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::operator <= (const ChainList& pChainList)
{
	/* 
		���� "<=" ��� A -> e_dwCount <= B.e_dwCount ��Ϊ TRUE
	*/

	if (this -> e_dwCount <= pChainList.e_dwCount)
	{
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI ChainList<T_Dynamic>::operator == (const ChainList& pChainList)
{
	/*
		���� "==" ��� A �ڴ�� B �ڴ���ȫ�����Ϊ TRUE
	*/
	
	// ��� A �� B ��û��Ԫ�������
	if (!this -> e_dwCount && !pChainList.e_dwCount)
	{
		return TRUE;
	}

	// ���A �� B Ԫ�ظ�������ͬ�����
	if (this -> e_dwCount != pChainList.e_dwCount)
	{
		return FALSE;
	}
	
	// �ֱ��ȡ A �� B �����ͷ��ַ
	ChainList<T_Dynamic>::PNODE pChainListHeader_A = this -> e_pChainListHeader;
	ChainList<T_Dynamic>::PNODE pChainListHeader_B = pChainList.e_pChainListHeader;

	// ��ȡԪ�ظ���
	DWORD dwTempCount = this -> e_dwCount;

	// �������ж�ÿ���ڵ���ڴ��Ƿ����
	do
	{
		if (memcmp(pChainListHeader_A, pChainListHeader_B, sizeof(T_Dynamic)))
		{
			// �������Ԫ���нڵ㲻��ͬ�� A �� B����ͬ
			return FALSE;
		}

		if (!pChainListHeader_A -> e_pAddress && !pChainListHeader_B -> e_pAddress)
		{
			// ��� A ��ַ�� B ��ַ��ֵ����ȫ0������������
			break;
		}
		
		// �ҵ���һ����ַ
		pChainListHeader_A = pChainListHeader_A -> e_pAddress;
		pChainListHeader_B = pChainListHeader_B -> e_pAddress;

	}
	// ��� e_dwCount ����0������������
	while(--dwTempCount);

	return TRUE;
}


// **********************************************************************************************


struct mystruct
{
	int a;
	int b;
};

void func()
{
	mystruct flag1;
	flag1.a = 1;
	flag1.b = 2;

	mystruct flag2;
	flag2.a = 3;
	flag2.b = 4;

	mystruct flag3;
	flag3.a = 6;
	flag3.b = 6;


	ChainList <mystruct> b1;
	b1.Append(flag1);
	b1.Append(flag2);

	ChainList <mystruct> b2;
	b2.Append(flag1);
	b2.Append(flag2);
	
	b1.Insert(2, flag3);
	b2.Insert(2, flag3);
	int ret = b2.GetElementIndex(flag3);
	printf("%d\n", ret);
	if (b1 == b2)
	{
		printf("flag1 == flag\n");
	}
	else
	{
		printf("flag1 != flag\n");
	}
	b2.GetElement(0, flag1);
	printf("%d\n%d\n", flag1.a, flag1.b);
}

int main(int argc, char* argv[])
{
	/*
		������ϰ��			
			1��ʵ��һ����������			
			2������ÿһ�������ķ����ʵ��			
	*/
	func();

	getchar();
	return 0;
}

