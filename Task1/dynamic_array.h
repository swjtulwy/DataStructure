#pragma once
#include <iostream>

using namespace std;

void TestDynamicArray();

// 用类模板实现动态数组，可以兼容各种数据类型
template <typename T, int N>
class DynamicArray {
private:
	T* m_Array;
	int m_Length;
public:
	// 构造函数,给数组申请空间
	DynamicArray();
	//拷贝构造函数, 在使用这个对象的实例来初始化这个对象的一个新的实例
	template <int X>
	DynamicArray(const DynamicArray<T, X>&);

	// 重载=运算符，使得数组之间能够实现=赋值操作！
	template <int Y>
	DynamicArray& operator = (const DynamicArray<T, Y>&);

	//重载下标运算符 使得下标运算符具有越界检测功能!
	T& operator [](int);

	// 动态扩容
	DynamicArray* Expand(unsigned int);

	// 动态增加,根据下标插入
	bool Insert(T, unsigned int);

	// 动态删除，根据下标删除
	bool Delete(unsigned int);

	// 数组排序, 仅限能直接比较的数据类型
	bool Sort();

	// 合并已排序数组
	template <int Z>
	bool MergeSortedArray(DynamicArray<T, Z>&);

	// 内联函数，获取类私有属性
	int GetSize() const { return m_Length; };
	T* GetData() const { return m_Array; };

	// 友元函数实现运算符<<重载,模板类的友元函数要放在类里面定义
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
	memset(m_Array, 0, m_Length * sizeof(T)); // 内存初始化为0
	memcpy(m_Array, that.GetData(), m_Length * sizeof(T)); //复制数组
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

// 重载[]操作符
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

// 输入要扩展容量的大小，返回扩展后的数组
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


// 在index位置动态插入，后面的顺延
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

// 删除Index位置的值，后面往前移动
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