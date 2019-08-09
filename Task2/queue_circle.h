#pragma once
#include <iostream>
#define MAXSIZE 100

using namespace std;

void TestQueueCircle();


// ѭ�����е��ѵ������пպ�����
// ������ʵ�ַ�ʽ��һ�ֲ��ñ�־λ����պ���
// ��һ�ּ�������õ�������һ��Ԫ�ؿռ���Լ���ķ�ʽ��
template<typename T>
class QueueCircle
{
public:
	QueueCircle();
	QueueCircle(int capacity);
	~QueueCircle() { delete[] m_queue; };
	void Enqueue(const T& item);
	void Dequeue();
	void Print();
	int Size();
	T Front() { return m_queue[m_front]; };
	T Rear() { return m_queue[m_rear - 1]; };
	bool IsEmpty();
	bool IsFull();

private:
	int m_front; // ָ���ͷ
	int m_rear; // ָ���β����һ��Ԫ��
	int m_maxSize;
	T* m_queue;
};

template<typename T>
QueueCircle<T>::QueueCircle() {
	m_maxSize = MAXSIZE;
	m_queue = new T[m_maxSize];
	m_front = m_rear = 0;
}

template<typename T>
QueueCircle<T>::QueueCircle(int capacity) {
	if (capacity <= 0) {
		cout << "capacity must greater than zero!" << endl;
	}
	m_maxSize = capacity + 1;
	m_queue = new T[m_maxSize];
	m_front = m_rear = 0;
}

// ���
template<typename T>
void QueueCircle<T>::Enqueue(const T& item) {
	if (IsFull()) {
		cout << "queue is full!" << endl;
		return;
	}
	m_queue[m_rear] = item;
	m_rear = (m_rear + 1) % m_maxSize;
}

// ����
template<typename T>
void QueueCircle<T>::Dequeue() {
	if (IsEmpty()) {
		cout << "queue is empty!" << endl;
		return;
	}
	m_front = (m_front + 1) % m_maxSize;
}

// �����п�
template<typename T>
bool QueueCircle<T>::IsEmpty(){
	return m_rear == m_front;
}

// ��������
template<typename T>
bool QueueCircle<T>::IsFull() {
	return this->Size() == m_maxSize - 1;
}

// ���ض��г���
template<typename T>
int QueueCircle<T>::Size() {
	return(m_rear - m_front + m_maxSize) % m_maxSize;
}

// �������
template<typename T>
void QueueCircle<T>::Print() {
	if (IsEmpty()) {
		cout << "queue is empty!" << endl;
		return;
	}
	for (int i = m_front; i < m_front+this->Size(); i++) {
		cout << m_queue[i % m_maxSize] << " ";
	}
	cout << endl;
}