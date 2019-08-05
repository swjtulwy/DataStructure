#pragma once
#include <iostream>

using namespace std;

void TestDynamicArray();

// ����ģ��ʵ�ֶ�̬���飬���Լ��ݸ�����������
template <typename T, int N>
class DynamicArray {
private:
	T* m_Array;
	int m_Length;
public:
	// ���캯��,����������ռ�
	DynamicArray();
	//�������캯��, ��ʹ����������ʵ������ʼ����������һ���µ�ʵ��
	template <int X>
	DynamicArray(const DynamicArray<T, X>&);

	// ����=�������ʹ������֮���ܹ�ʵ��=��ֵ������
	template <int Y>
	DynamicArray& operator = (const DynamicArray<T, Y>&);

	//�����±������ ʹ���±����������Խ���⹦��!
	T& operator [](int);

	// ��̬����
	DynamicArray* Expand(unsigned int);

	// ��̬����,�����±����
	bool Insert(T, unsigned int);

	// ��̬ɾ���������±�ɾ��
	bool Delete(unsigned int);

	// ��������, ������ֱ�ӱȽϵ���������
	bool Sort();

	// �ϲ�����������
	template <int Z>
	bool MergeSortedArray(DynamicArray<T, Z>&);

	// ������������ȡ��˽������
	int GetSize() const { return m_Length; };
	T* GetData() const { return m_Array; };

	// ��Ԫ����ʵ�������<<����,ģ�������Ԫ����Ҫ���������涨��
	friend ostream& operator << (ostream& os, DynamicArray<T, N>& arr) {
		for (int i = 0; i < arr.m_Length; i++) {
			os << arr[i] << " ";
		}
		return os;
	};
};


template <typename T, int N>
DynamicArray<T, N>:: DynamicArray() {
	m_Array = new T[N];
	m_Length = N;
}

template <typename T, int N> 
	template <int X> 
DynamicArray<T, N>:: DynamicArray(const DynamicArray<T, X>& that) {	
	m_Length = that.GetSize();
	m_Array = new T[m_Length];
	memset(m_Array, 0, m_Length * sizeof(T)); // �ڴ��ʼ��Ϊ0
	memcpy(m_Array, that.GetData(), m_Length * sizeof(T)); //��������
}

template <typename T, int N>
	template<int Y>
DynamicArray<T, N>&  DynamicArray<T, N>:: operator = (const DynamicArray<T, Y>& other) {
	if ((int)this != (int)&other) {
		T* tempArray = new T[other.GetSize()];
		memset(tempArray, 0, other.GetSize() * sizeof(T));
		memcpy(tempArray, other.GetData(), other.GetSize() * sizeof(T));
		delete[] m_Array;
		m_Array = tempArray;
		m_Length = other.GetSize();
	}
	return *this;
}

// ����[]������
template <typename T, int N>
T& DynamicArray<T, N>::operator[](int index) {
	if (index > m_Length - 1 || index < 0) {
		cout << "out of range, return the last item"<<endl;
		return m_Array[m_Length-1];
	}
	else {
		return m_Array[index];
	}
}

// ����Ҫ��չ�����Ĵ�С��������չ�������
template <typename T, int N>
DynamicArray<T, N> *DynamicArray<T, N>::Expand(unsigned int len) {
	T* temp = new T[m_Length + len];
	memset(temp, 0, (m_Length + len) * sizeof(T));
	memcpy(temp, m_Array, m_Length * sizeof(T));
	delete[] m_Array;
	m_Array = temp;
	m_Length += len;
	return this;
}


// ��indexλ�ö�̬���룬�����˳��
template <typename T, int N>
bool DynamicArray<T, N>::Insert(T data, unsigned int index) {
	if (index<0 || index>m_Length - 1) {
		cout << "out of range!" << endl;
		return false;
	}
	this->Expand(1);
	for (int i = m_Length - 1; i > index; i--) {
		m_Array[i] = m_Array[i - 1];
	}
	m_Array[index] = data;
	return true;
}

// ɾ��Indexλ�õ�ֵ��������ǰ�ƶ�
template <typename T, int N>
bool DynamicArray<T, N>::Delete(unsigned int index) {
	if (index<0 || index> (m_Length - 1)) {
		cout << "out of range!" << endl;
		return false;
	}
	for (int i = index; i < m_Length- 1; i++) {
		m_Array[i] = m_Array[i + 1];
	}
	T* tempArray = new T[m_Length - 1];
	memset(tempArray, 0, (m_Length - 1) * sizeof(T));
	memcpy(tempArray, m_Array, (m_Length - 1) * sizeof(T));
	delete[] m_Array;
	m_Array = tempArray;
	m_Length -= 1;
	return true;
}

template <typename T, int N>
bool DynamicArray<T, N>::Sort() {
	for (int i = 0; i < m_Length - 1; i++) {
		for (int j = m_Length - 1; j > i; j--) {
			if (m_Array[j - 1] > m_Array[j]) {
				T temp = m_Array[j - 1];
				m_Array[j - 1] = m_Array[j];
				m_Array[j] = temp;
			}
		}
	}
	return true;
}

template <typename T, int N>
	template<int Z>
bool DynamicArray<T, N>::MergeSortedArray(DynamicArray<T, Z>& arr) {
	this->Sort();
	arr.Sort();
	T* tempArray = new T[m_Length + arr.GetSize()];
	int index1 = 0, index2 = 0, index = 0;
	while (index1 < m_Length && index2 < arr.GetSize()) {
		if (m_Array[index1] < arr.GetData()[index2]) {
			tempArray[index++] = m_Array[index1++];
		}
		else {
			tempArray[index++] = arr.GetData()[index2++];
		}
	}
	while (index1<m_Length)
		tempArray[index++] = m_Array[index1++];
	while (index2<arr.GetSize())
		tempArray[index++] = arr.GetData()[index2++];

	delete[] m_Array;
	m_Array = tempArray;
	m_Length = m_Length + arr.GetSize();
	return true;
}