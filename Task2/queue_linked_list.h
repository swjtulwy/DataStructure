#pragma once
#include "stack_linked_list.h"

void TestQueneLinkedList();
// ������dummy���
template<typename T>
class QueueLinkedList
{
public:
	QueueLinkedList() :m_front(nullptr), m_rear(nullptr) { };
	~QueueLinkedList() { Clear(); };
	void EnQueue(T& item);
	void Dequene();
	void Print();
	void Clear();
	int Size();

	// ���ض�ͷԪ��
	T Front() { 
		if (IsEmpty()) {
			cout << "queue is empty!" << endl;
			exit(1);
		}
		return m_front->data; 
	};

	// ���ض�βԪ��
	T Rear() {
		if (IsEmpty()) {
			cout << "queue is empty!" << endl;
			exit(1);
		}
		return m_rear->data;
	};

	bool IsEmpty() { return m_front==nullptr; };
private:
	Node<T>* m_front;
	Node<T>* m_rear;
};

// ��ӡ����
template<typename T>
void QueueLinkedList<T>::Print() {
	if (IsEmpty()) {
		cout << "queue is empty!" << endl;
		return;
	}
	Node<T>* p = m_front;
	while (p != nullptr) {
		if (p != m_rear) {
			cout << p->data << "->";
		}
		else{
			cout << p->data << endl;
		}
		p = p->next;
	}
}

// ���������С
template<typename T>
int QueueLinkedList<T>::Size() {
	int count = 0;
	Node<T>* p = m_front;
	while (p != nullptr) {
		count++;
		p = p->next;
	}
	return count;
}

// �������
template<typename T>
void QueueLinkedList<T>::Clear() {
	Node<T>* q;
	while (!IsEmpty()) {
		q = m_front;
		m_front = m_front->next;
		delete q;
	}
	cout << "queue cleared!" << endl;
}

// ���
template<typename T>
void QueueLinkedList<T>::EnQueue(T& item) {
	Node<T>* newNode = new Node<T>(item);
	if (IsEmpty()) {
		m_rear = newNode;
		m_front = newNode;
	}
	else
	{
		m_rear->next = newNode;
		m_rear = m_rear->next;
	}
}

// ����
template<typename T>
void QueueLinkedList<T>::Dequene() {
	if (IsEmpty()) {
		cout << "queue is empty!" << endl;
		return;
	}
	Node<T>* p = m_front;
	m_front = m_front->next;
	delete p;
}