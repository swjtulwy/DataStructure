#pragma once
#include <iostream>
#include "heap_array.h"
using namespace std;

void TestPriorityQueue();

// �ö�ʵ�����ȶ���

template<typename T>
class PriorityQueue
{
public:
	PriorityQueue() {
		m_queue = new HeapArray<T>;
	}
	PriorityQueue(int size, bool type) {
		m_queue = new HeapArray<T>(size, type);
	}
	// ��ȡ���г���
	int GetSize() {
		return m_queue->GetSize();
	} 
	// �ж϶����Ƿ�ǿ�
	bool IsEmpty() {
		return m_queue->IsEmpty();
	}
	// ��ȡ��ͷԪ��
	T GetFront() {
		return m_queue->GetHeap()[0];
	}
	// ���
	void Enqueue(T val) {
		m_queue->Insert(val);
	}
	// ����
	void Dequeue() {
		m_queue->Delete(0);
	}

private:
	HeapArray<T>* m_queue;
	bool type; // �������ͣ�������Ȼ�����С����
};


