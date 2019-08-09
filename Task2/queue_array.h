#pragma once
#include<iostream>
#define kMAXSIZE 0xffff

using namespace std;

void TestQueueArray();

template<typename T>
class QueueArray
{
public:
	QueueArray();
	QueueArray(int capacity); // 初始化最大容量
	~QueueArray() { delete[] m_queue; };
	void Enqueue(const T& item);
	void Dequeue();
	void Print();
	T Front() { return m_queue[m_front]; };
	T Rear() { return m_queue[m_rear-1]; };
	bool IsEmpty() { return m_front == m_rear; };
private:
	int m_front; // 指向第一位
	int m_rear; //指向最后一位的下一位
	int m_maxSize; // 队列的最大容量
	T* m_queue; // 数组表示
};


template<typename T>
QueueArray<T>::QueueArray() {
	m_maxSize = kMAXSIZE;
	m_queue = new T[m_maxSize];
	m_front = m_rear = 0;
}

template<typename T>
QueueArray<T>::QueueArray(int capacity) {
	if (capacity <= 0) {
		cout << "capacity must greater than zero!" << endl;
	}
	m_maxSize = capacity;
	m_queue = new T[m_maxSize];
	m_front = m_rear = 0;
}


template<typename T>
void QueueArray<T>::Enqueue(const T& item) {
	if (m_rear == m_maxSize && m_front == 0) {
		cout << "queue is full!" << endl;
		return;
	}
	else if(m_rear==m_maxSize&& m_front!=0){ 
		// 假溢出,采用将后面的数据往前移动的方式解决
		// 另一种方法是采用循环队列
		copy(m_queue + m_front, m_queue + m_maxSize, m_queue);
		m_rear = m_rear - m_front;
		m_front = 0;
	}
	m_queue[m_rear++] = item;
}

template<typename T>
void QueueArray<T>::Dequeue() {
	if (IsEmpty()) {
		cout << "queue is empty. cannot be delete!" << endl;
		return;
	}
	m_front++;
}

template<typename T>
void QueueArray<T>::Print() {
	if (IsEmpty()) {
		cout << "empty queue!" << endl;
		return;
	}
	cout << "the queue now is:";
	for (int i = m_front; i < m_rear; i++) {
		cout << m_queue[i] << " ";
	}
	cout << endl;
}