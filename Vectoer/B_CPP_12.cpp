// B_CPP_12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <class T_Dynamic> class Vector  // һ������
{
private:	// ˽�б���
	DWORD			e_dwMagic;			// ��ǰ�����ĳ�Ա����
	DWORD			e_dwNextIndex;		// ��һ������
	DWORD			e_dwLfanew;			// Ĭ�ϵĴ�������ĸ���
	DWORD			e_dwLength;			// ��ǰ�����ĳ���
	DWORD			e_dwIncrement;		// ÿ�����ݵĴ�С
	T_Dynamic*		e_pAddress;			// �����׵�ַָ��

private:	// ˽�к���
	BOOL WINAPI expand(void);			// ��������С����ʱ��������

public:		// ���캯������������
	Vector();
	Vector(IN DWORD dwNumberOfTypes);
	~Vector();

public:		// ���к���
	T_Dynamic*		WINAPI append(void);														// ��ĩβ׷��һ��Ԫ��
	T_Dynamic*		WINAPI append(IN DWORD dwAppendNumber);										// ��ĩβ׷�Ӷ��Ԫ��(��������� 5 ��)
	T_Dynamic*		WINAPI insert(IN DWORD dwIndexNumber);										// �����±����Ԫ�� 
	T_Dynamic*		WINAPI insert(IN DWORD dwIndexNumber, IN T_Dynamic pT_Dynamic);				// �����±����ָ����Ԫ��
	T_Dynamic*		WINAPI pointerToIndex(IN DWORD dwIndexNumber);								// ���������±귵��һ����Ԫ�ص�ָ��
	T_Dynamic*		WINAPI pointerToIndex(IN DWORD dwIndexNumber,OUT T_Dynamic pT_Dynamic);		// ���ݸ����������õ�Ԫ�� ����ֵ���Ƶ� Vector ������λ��
	T_Dynamic*		WINAPI push(IN T_Dynamic pT_Dynamic);										// ��ĩβ����ָ��Ԫ��
	VOID			WINAPI pop(void);															// ɾ�����һ��Ԫ��
	DWORD			WINAPI capacity(void);														// ���ػ��ܴ洢����Ԫ��
	VOID			WINAPI clear(void);															// �������Ԫ��	
	BOOL			WINAPI IsEmpty(void);														// �ж� Vector �Ƿ�Ϊ�� ���� TURE ʱΪ��	
	VOID			WINAPI erase(IN DWORD dwIndexNumber);										// �����±�ɾ��ָ��Ԫ��
	DWORD			WINAPI size(void);															// ���� Vector ȫ��Ԫ�������Ĵ�С
	VOID			WINAPI ReadVectorMemberInfo(const Vector& pVector);							// ��ȡ Vector �еı�����ֵ

public:		// ���� >�� >= �� < �� <=�� ==
	BOOL			WINAPI operator > (const Vector& pVector);		// ���� ">"  :	��� A -> e_dwLength >  B.e_dwLength	��A ���� B
	BOOL			WINAPI operator >= (const Vector& pVector);		// ���� ">=" :	��� A -> e_dwLength >= B.e_dwLength	��A ���� B
	BOOL			WINAPI operator < (const Vector& pVector);		// ���� "<"  :	��� A -> e_dwLength <  B.e_dwLength	��A ���� B
	BOOL			WINAPI operator <= (const Vector& pVector);		// ���� "<=" :	��� A -> e_dwLength <= B.e_dwLength	��A ���� B
	BOOL			WINAPI operator == (const Vector& pVector);		// ���� "==" :	��� A -> e_dwLength == B.e_dwLength	��A ���� B
};

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::expand(void)
{
	/* 
		���������Ҫ������ִ�д˺���
		�˺���ÿ�����ݵĴ�СΪ e_dwIncrement
		�˺����Ὣ�ɵ����ݸ��Ƶ�����������ݺ�ĵ�ַ
		����ִ�гɹ��򷵻�0 ���򷵻�-1
	*/


	// ��������һ��ռ� (ԭ���� + 0xA)
	T_Dynamic* New_e_pAddress = new T_Dynamic[this -> e_dwMagic + this -> e_dwIncrement];

	if (!New_e_pAddress)
	{
		printf("�� expand �ռ�����ʧ��");
		return 0xFFFFFFFF;
	}

	// ��ʼ���ռ�
	memset(New_e_pAddress, 0x00000000, (this -> e_dwMagic + this -> e_dwIncrement) * sizeof(T_Dynamic));

	// �����ݸ��Ƶ��µĿռ�
	memcpy(New_e_pAddress, this -> e_pAddress, sizeof(CHAR) * this -> e_dwLength);

	// �ͷžɵĿռ�
	delete[] this -> e_pAddress;

	// ���³�Ա������
	this -> e_dwMagic += this -> e_dwIncrement;
	this -> e_dwLength = sizeof(T_Dynamic) * this -> e_dwMagic;
	this -> e_pAddress = New_e_pAddress;
	
	return NULL;
}

template <class T_Dynamic> Vector<T_Dynamic>::Vector()
: e_dwLfanew(0x0000000A), e_dwMagic(0x0000000A), e_dwNextIndex(0x00000001), e_dwIncrement(0x000000A)
{
	// ���ṹ���еı�����ֵ						
	this -> e_dwLength = sizeof(T_Dynamic) * this -> e_dwMagic;						

	//���ʹ�ô˺������г�ʼ�� ��ʹ��Ĭ�ϵ� e_lfanew = 10 ���д���
	this -> e_pAddress = new T_Dynamic[this -> e_dwLfanew];	
	
	if (!this -> e_pAddress)
	{
		// ����ռ�ʧ��
		printf("�ڹ��캯�� Vector ���ڴ�����ʧ��\n");
	}

	// ��ʼ���ռ�
	memset(this -> e_pAddress, 0x00000000, sizeof(T_Dynamic) * this -> e_dwLfanew);
}

template <class T_Dynamic> Vector<T_Dynamic>::Vector(IN DWORD dwNumberOfTypes)
: e_dwLfanew(0x0000000A), e_dwIncrement(0x0000000A)
{
	// ���ṹ���еı�����ֵ							
	this -> e_dwMagic = dwNumberOfTypes;								
	this -> e_dwNextIndex = this -> e_dwMagic;					
	this -> e_dwLength = sizeof(T_Dynamic) * this -> e_dwMagic;	
						
	// ���ݸ����� NumberOfTypes ��ֵ�� T_Dynamic ����������ռ�
	this -> e_pAddress = new T_Dynamic[this -> e_dwMagic];	

	// ��ʼ���ռ�
	memset(this -> e_pAddress, 0x00000000, sizeof(T_Dynamic) * this -> e_dwMagic);
}

template <class T_Dynamic> Vector<T_Dynamic>::~Vector()
{
	// �ͷſռ�
	delete[] this -> e_pAddress;
	this -> e_pAddress = NULL;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::append(void)
{
	/* 
		��� append ����û�в��������׷��һ����λ�ĳ��� 
		����ֵΪ������Ԫ�ص�ָ�� 
	*/
	
	// �ж��Ƿ�ռ��㹻
	if (this -> e_dwNextIndex >= this -> e_dwMagic)
	{
		// �����ǰ�����������ڵ����˵�ǰ�����ĳ�Ա�������ʾ��Ҫ����
		this -> expand();
	}

	// ���³�Ա����
	this -> e_dwNextIndex++;		// ��һ����������

	// ���ش˳�Ա��ָ��
	T_Dynamic* pAppendElement = this -> e_pAddress + this -> e_dwNextIndex - 1;

	return pAppendElement;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::append(IN DWORD dwAppendNumber)
{
	/* 
		��� append �����в��������׷�� appendNumber ����λ�ĳ��� 
		����ֵΪ������Ԫ�ص�ָ�� 
	*/

	// �� dwAppendNumber ��������
	if ((INT)dwAppendNumber < 1 || (INT)dwAppendNumber > 5)
	{
		printf("Ԫ�����ʧ��! �����ֵ����С��1�����5\n");
		return NULL;
	}

	// �ж��Ƿ�ռ��㹻
	if ((this -> e_dwNextIndex + dwAppendNumber) > this -> e_dwMagic)
	{
		// �����ǰ�������������˵�ǰ�����ĳ�Ա�������ʾ��Ҫ����
		this -> expand();
	}

	// ���³�Ա����
	this -> e_dwNextIndex += dwAppendNumber;		// ��һ����������

	// ���ش˳�Ա��ָ��
	T_Dynamic* pAppendElement = this -> e_pAddress + this -> e_dwNextIndex - 1;

	return pAppendElement;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::insert(IN DWORD dwIndexNumber)
{
	/*
		����������±��ڴ��±괦����Ԫ��
		����ֵΪ�˲����Ԫ�صĽṹ��ָ��
	*/

	// �ж��Ƿ�����ڴ��±���в���
	if ((INT)dwIndexNumber >= (INT)this -> e_dwNextIndex || (INT)dwIndexNumber < 0)
	{
		printf("--------- �������±� %d ���в��� ---------\n", dwIndexNumber);
		return NULL;
	}
	// �ҵ����λ��
	T_Dynamic* pInsertElement = this -> e_pAddress + dwIndexNumber;

	// �ж��Ƿ����� Vector ��������ƶ�һ����λ�Ĵ�С
	if (this -> e_dwNextIndex >= this -> e_dwMagic)
	{
		printf("%d\n%d\n", this -> e_dwNextIndex, this -> e_dwMagic);
		// �����Ϊ�ռ䲻�㲻������ƶ� ����Ҫ����
		this -> expand();

		// ���� pInsertElement
		pInsertElement = this -> e_pAddress + dwIndexNumber;
	}

	// ������Ҫ�����Ĵ�С ������±��λ�ÿ�ʼȫ������ƶ�һ����λ��С
	memcpy(pInsertElement + 1, pInsertElement, sizeof(T_Dynamic) * (this -> e_dwNextIndex - dwIndexNumber));

	// �������λ�õ�ֵ����
	memset(pInsertElement, 0x00000000, sizeof(T_Dynamic));

	// ���³�Ա����
	this -> e_dwNextIndex++;

	// ����ֵ�ǵ�ǰ�����Ԫ�ص�ָ��
	return pInsertElement;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::insert(IN DWORD dwIndexNumber, IN T_Dynamic pT_Dynamic)
{
	/*
		����������±��ڴ��±괦����ָ����Ԫ��
		����ֵΪ�˲����Ԫ�صĽṹ��ָ��
	*/

	// �ж��Ƿ�����ڴ��±���в���
	if ((INT)dwIndexNumber >= (INT)this -> e_dwNextIndex || (INT)dwIndexNumber < 0)
	{
		printf("--------- �������±� %d ���в��� ---------\n", dwIndexNumber);
		return NULL;
	}
	// �ҵ����λ��
	T_Dynamic* pInsertElement = this -> e_pAddress + dwIndexNumber;

	// �ж��Ƿ����� Vector ��������ƶ�һ����λ�Ĵ�С
	if (this -> e_dwNextIndex >= this -> e_dwMagic)
	{
		printf("%d\n%d\n", this -> e_dwNextIndex, this -> e_dwMagic);
		// �����Ϊ�ռ䲻�㲻������ƶ� ����Ҫ����
		this -> expand();

		// ���� pInsertElement
		pInsertElement = this -> e_pAddress + dwIndexNumber;
	}

	// ������Ҫ�����Ĵ�С ������±��λ�ÿ�ʼȫ������ƶ�һ����λ��С
	memcpy(pInsertElement + 1, pInsertElement, sizeof(T_Dynamic) * (this -> e_dwNextIndex - dwIndexNumber));

	// �������λ�õ�ֵ��Ϊָ��������
	memcpy(pInsertElement, &pT_Dynamic, sizeof(T_Dynamic));

	// ���³�Ա����
	this -> e_dwNextIndex++;

	// ����ֵ�ǵ�ǰ�����Ԫ�ص�ָ��
	return pInsertElement;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::pointerToIndex(IN DWORD dwIndexNumber)
{
	/*
		���������±귵�ش˽ṹ��ָ��
	*/
	// �ж��Ƿ�������±�
	if (dwIndexNumber >= this -> e_dwNextIndex)
	{
		printf("--------- ����,��������±� %d ������ ����ʹ�� append ����������Ԫ�� ---------\n", dwIndexNumber);
		return NULL;
	}

	// �õ����±��Ԫ�ص�ָ�벢����
	T_Dynamic* pTemp_T_Dynamic = this -> e_pAddress + dwIndexNumber;

	return pTemp_T_Dynamic;
}


template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::pointerToIndex(IN DWORD dwIndexNumber,OUT T_Dynamic pT_Dynamic)
{
	// �ж��Ƿ�������±�
	if (dwIndexNumber >= this -> e_dwNextIndex)
	{
		printf("--------- ����,��������±� %d ������ ����ʹ�� append ����������Ԫ�� ---------\n", dwIndexNumber);
		return NULL;
	}

	// �õ����±��Ԫ�ص�ָ��
	T_Dynamic* pTemp_T_Dynamic = this -> e_pAddress + dwIndexNumber;

	// ����Ԫ�ص����ݸ��Ƶ�ָ��λ��
	memcpy(&pT_Dynamic, pTemp_T_Dynamic, sizeof(T_Dynamic));

	// ����ֵΪ��Ҫ���Ƶ�Ԫ�ص�ָ��
	return pTemp_T_Dynamic;
}

template <class T_Dynamic> T_Dynamic* WINAPI Vector<T_Dynamic>::push(IN T_Dynamic pT_Dynamic)
{
	/* 
		��ĩβ����ָ����Ԫ�� 
	*/

	// �ж��Ƿ�ռ��㹻
	if (this -> e_dwNextIndex >= this -> e_dwMagic)
	{
		// �����ǰ�����������ڵ����˵�ǰ�����ĳ�Ա�������ʾ��Ҫ����
		this -> expand();
	}

	// �ҵ�ĩβ��ָ��
	T_Dynamic* pPush_back = this -> e_pAddress + e_dwNextIndex;

	// ��ָ����Ԫ�ؿ���������ĩβ(������ĩβ)
	memcpy(pPush_back, &pT_Dynamic, sizeof(T_Dynamic));

	// ���³�Ա����
	this -> e_dwNextIndex++;

	return pPush_back;

}

template <class T_Dynamic> VOID WINAPI Vector<T_Dynamic>::pop(void)
{
	/*
		�����һ��Ԫ�ص�����
		������������
	*/

	// �ҵ����һ��Ԫ�ص�ָ��
	T_Dynamic* pPop_back = this -> e_pAddress + this -> e_dwNextIndex - 1;

	// ������������
	memset(pPop_back, 0x00000000, sizeof(T_Dynamic));
	
	// ���³�Ա����
	this -> e_dwNextIndex--;
	
	return; 
}

 
template <class T_Dynamic> DWORD WINAPI Vector<T_Dynamic>::capacity(void)
{
	/*
		�����ڲ����ݵ�����£����ܴ洢����Ԫ��
	*/
	return this -> e_dwMagic - this -> e_dwNextIndex;
}

template <class T_Dynamic> VOID WINAPI Vector<T_Dynamic>::clear(void)
{
	/*
		�������Ԫ��
	*/

	// �Ƚ��ڴ����
	memset(this -> e_pAddress, 0x00000000, sizeof(T_Dynamic) * this -> e_dwMagic);

	// ���³�Ա����
	this -> e_dwNextIndex = NULL;

	return;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::IsEmpty(void)
{
	/*
		�ж� Vector �Ƿ�Ϊ�� ���� true ʱΪ��
	*/

	if (!this -> e_dwNextIndex)
	{
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> VOID WINAPI Vector<T_Dynamic>::erase(IN DWORD dwIndexNumber)
{
	/*
		�����±�ɾ��ָ��Ԫ��
		ɾ����λ�ö�����������ոõ�ַ��ֵ
	*/

	// �ж��Ƿ��д��±�
	if(dwIndexNumber >= this -> e_dwNextIndex || dwIndexNumber < 0)
	{
		printf("û������±�\n");
		return;
	}
	
	// �ҵ����λ�õ�ָ��
	T_Dynamic* pErase = this -> e_pAddress + dwIndexNumber;
	
	// �������Ԫ��ȫ����ǰ���� 1 ����λ��С
	memcpy(pErase, pErase + 1, sizeof(T_Dynamic) * (this -> e_dwNextIndex - dwIndexNumber - 1));

	// �����һ��ֵ���
	memset(e_pAddress + this -> e_dwNextIndex - 1, 0x00000000, sizeof(T_Dynamic));

	// ���³�Ա����
	this -> e_dwNextIndex--;
	
	return;
}
 
template <class T_Dynamic> DWORD WINAPI Vector<T_Dynamic>::size(void)
{
	/*
		���� Vector Ԫ�������Ĵ�С
	*/

	return sizeof(T_Dynamic) * this -> e_dwNextIndex;
}

template <class T_Dynamic> VOID WINAPI Vector<T_Dynamic>::ReadVectorMemberInfo(const Vector& pVector)
{
	/* 
		��ȡ Vector ��ȫ����Ա����Ϣ ����ӡ���� 
	*/  

	printf("��ǰ�����ĳ�Ա����: %d\n", pVector.e_dwMagic);
	printf("��һ����������: %d\n", pVector.e_dwNextIndex);
	printf("Ĭ�ϵĴ�������ĸ���: %d\n", pVector.e_dwLfanew);
	printf("��ǰ�����ĳ���(�ֽ�): %d\n", pVector.e_dwLength);
	printf("ÿ�����ݵĵ�λ��: %d\n", pVector.e_dwIncrement);
	printf("�����׵�ַָ��: %x\n\n", pVector.e_pAddress);

	return;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::operator > (const Vector& pVector)
{
	/* 
		���� ">" �����
		����ʹ�� > ���Ƚ������ṹ�����Ĵ�С
	*/
	if (this -> e_dwLength > pVector.e_dwLength)
	{
		// ��� A -> e_dwLength > B.e_dwLength �� A Vector ���� B Vector
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::operator >= (const Vector& pVector)
{
	/* 
		���� ">=" �����
		����ʹ�� > ���Ƚ������ṹ�����Ĵ�С
	*/
	if (this -> e_dwLength >= pVector.e_dwLength)
	{
		// ��� A -> e_dwLength >= B.e_dwLength �� A Vector ���ڵ��� B Vector
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::operator < (const Vector& pVector)
{
	/* 
		���� "<" �����
		����ʹ�� < ���Ƚ������ṹ�����Ĵ�С
	*/
	if (this -> e_dwLength < pVector.e_dwLength)
	{
		// ��� A -> e_dwLength < B.e_dwLength �� A Vector С�� B Vector
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::operator <= (const Vector& pVector)
{
	/* 
		���� "<=" �����
		����ʹ�� <= ���Ƚ������ṹ�����Ĵ�С
	*/
	if (this -> e_dwLength <= pVector.e_dwLength)
	{
		// ��� A -> e_dwLength <= B.e_dwLength �� A Vector С�ڵ��� B Vector
		return TRUE;
	}

	return FALSE;
}

template <class T_Dynamic> BOOL WINAPI Vector<T_Dynamic>::operator == (const Vector& pVector)
{
	/* 
		���� "==" �����
		����ʹ�� == ���Ƚ������ṹ�����Ĵ�С
	*/
	if (this -> e_dwLength == pVector.e_dwLength)
	{
		// ��� A -> e_dwLength == B.e_dwLength �� A Vector ���� B Vector
		return TRUE;
	}

	return FALSE;
}

class mystruct
{
public:
	int a;
	int b;
	void func()
	{
		printf("��ִ����!\n%d", this -> a);
		return;
	}
};

void function()
{
	/* 
		�� Vector �Ľṹ��Ա����ջ�� 
	*/

	Vector<mystruct> Example_List;
	Vector<mystruct> AAA;

	if (Example_List == AAA)
	{
		printf("������ Vector �Ĵ�С���\n");
	}

	mystruct* answer1 = Example_List.append();
	answer1 -> a = 0x9;
	answer1 -> b = 0xA;

	Example_List.append(2);
	Example_List.insert(2);
	Example_List.insert(4, *answer1);

	mystruct* answer2 = Example_List.pointerToIndex(5);	
	answer2 -> a = 0x5;
	answer2 -> b = 0x6;

	Example_List.pointerToIndex(3, *answer2);

	Example_List.push(*answer1);

	Example_List.pop();

	printf("���ܴ洢��Ԫ�������� %d\n", Example_List.capacity());

	printf("vector�Ĵ�С�ǣ�%d\n", Example_List.size());

	Example_List.ReadVectorMemberInfo(Example_List);
	
	Example_List.erase(3);

	printf("vector�Ĵ�С�ǣ�%d\n", Example_List.size());

	Example_List.clear();

	if(Example_List.IsEmpty())
	{
		printf("��� Vector �ǿյ�\n");
	}
}

void function2()
{
	/* 
		�� Vector �Ľṹ��Ա���ڶ��� 
	*/

	// Vector<int>* pVector_1 = new Vector<int>()
	// Vector<int>* pVector_1 = new Vector<int>(5)
	Vector<int>* pVector_1 = new Vector<int>;
	int* pa = pVector_1 -> pointerToIndex(0);
	pVector_1 -> push(1);
	pVector_1 -> push(2);
	pVector_1 -> push(3);
	pVector_1 -> push(4);
	pVector_1 -> insert(2, 10);
	pVector_1 -> push(5);
	pVector_1 -> push(6);
	pVector_1 -> push(7);
	pVector_1 -> push(8);
	pVector_1 -> push(9);
	pVector_1 -> push(10);
	int* pb = pVector_1 -> pointerToIndex(0);
	pVector_1 -> push(11);
	pVector_1 -> push(12);
	pVector_1 -> push(13);
	pVector_1 -> push(14);
	

}

int main(int argc, char* argv[])
{
	/*
		������ϰ��			
			1��ʵ��һ��Vector��			
			2������ÿһ�������ķ����ʵ��			
	*/

	/* 
		�м���������Ҫ�����
			1.  ��ʹ��ģ������� ��ôʹ����Ԫ���� 
			2.  ��ô�̳�ʹ��ģ�����
			3.  ����̳и���� ����ͨ����д�����麯����ʵ��
			ͨ������ָ��������ຯ���Ĺ��� ��ô����ʹ�ó�������ʲôʱ��
	*/


	function();

	function2();

	getchar();

	return 0;
}

