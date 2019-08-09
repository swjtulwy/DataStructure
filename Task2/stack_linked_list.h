#pragma once
#include <iostream>

using namespace std;

void TestStackLinkedList();

template<typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node() :next(nullptr) {};
	Node(T val) :data(val), next(nullptr) {};
};

// 不包含dummy结点
template<typename T>
class StackLinkedList
{
public:
	StackLinkedList() :m_length(0), m_top(nullptr) {};
	~StackLinkedList() { Clear(); };
	void Push(T val);
	void Pop();
	void Clear();
	void Print();
	int Size() { return m_length; };
	T Top();
	bool IsEmpty() { return m_top == nullptr; };

private:
	Node<T>* m_top;
	int m_length;
};

template<typename T>
T StackLinkedList<T>::Top() {
	if (!IsEmpty()) {
		return m_top->data;
	}
	else{
		cout << "stack is empty! " << endl;
		exit(1);
	}
}

template<typename T>
void StackLinkedList<T>::Push(T val) {
	Node<T>* newNode = new Node<T>(val);
	newNode->next = m_top;
	m_top = newNode;
	m_length++;
}

template<typename T>
void StackLinkedList<T>::Pop() {
	Node<T>* q;
	if (!IsEmpty()) {
		q = m_top;
		m_top = m_top->next;
		delete q;
		m_length--;
	}

}

template<typename T>
void StackLinkedList<T>::Print() {
	if (!IsEmpty()) {
		Node<T>* p = m_top;
		while (p)
		{
			cout << p->data << " ";
			p = p->next;
		}
	}
	else{
		cout << "stack is empty!";
	}
	cout << endl;
}

template<typename T>
void StackLinkedList<T>::Clear() {
	Node<T>* q;
	while (m_top) {
		q = m_top;
		m_top = m_top->next;
		delete q;
	}
	cout << "stack cleared! " << endl;
}