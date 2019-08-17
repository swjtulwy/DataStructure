#pragma once
#include <iostream>
#include "heap_array.h"
using namespace std;

void TestPriorityQueue();

// 用堆实现优先队列

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
	// 获取队列长度
	int GetSize() {
		return m_queue->GetSize();
	} 
	// 判断队列是否非空
	bool IsEmpty() {
		return m_queue->IsEmpty();
	}
	// 获取队头元素
	T GetFront() {
		return m_queue->GetHeap()[0];
	}
	// 入队
	void Enqueue(T val) {
		m_queue->Insert(val);
	}
	// 出队
	void Dequeue() {
		m_queue->Delete(0);
	}

private:
	HeapArray<T>* m_queue;
	bool type; // 队列类型，最大优先还是最小优先
};


