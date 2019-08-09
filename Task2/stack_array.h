#pragma once
#include <iostream>
#define kMAXSIZE 0xffff

using namespace std;

void TestStackArray();

template<typename T>
class StackArray
{
public:
	// 不指定大小，默认为kMAXSIZE大小
	StackArray():m_top(-1),m_maxSize(kMAXSIZE) {
		m_stack = new T[m_maxSize];
		if (m_stack == nullptr) {
			cerr << "dynamic memory allocate failed!" << endl;
			return;
		}
	};
	// 初始化指定大小的栈
	StackArray(int size) :m_top(-1), m_maxSize(size) {
		m_stack = new T[m_maxSize];
		if (m_stack == nullptr) {
			cerr << "dynamic memory allocate failed!" << endl;
			return;
		}
	}
	~StackArray() {
		delete[] m_stack;
	};
	void Push(T val);
	void Pop();
	T Top();
	bool IsEmpty();
	bool IsFull();
	int Size();
private:
	int m_maxSize;
	int m_top;
	T *m_stack;
};

template<typename T>
bool StackArray<T>::IsEmpty() {
	return m_top == -1;
}

template<typename T>
bool StackArray<T>::IsFull() {
	return m_top >= m_maxSize - 1;
}

template<typename T>
int StackArray<T>::Size() {
	return m_top + 1;
}

template<typename T>
T StackArray<T>::Top() {
	if (!IsEmpty()) {
		return m_stack[m_top];
	}
	else{
		cout << "stack is empty!  " << endl;
		exit(1);
	}
}

template<typename T>
void StackArray<T>::Push(T val) {
	if (!IsFull()) {
		m_stack[++m_top] = val;
	}
	else{
		cout << "stack is full! " << endl;
		return;
	}
}

template<typename T>
void StackArray<T>::Pop() {
	if (!IsEmpty()) {
		m_top--;
	}
	else{
		cout << "stack is empty! " << endl;
		return;
	}
}