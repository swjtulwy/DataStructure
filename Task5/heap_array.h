#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// 用数组实现的堆，可以根据输入参数确定是大顶堆还是小顶堆

void TestHeapArray();

const int DEFAULT_SIZE = 10;

template<typename T>
class HeapArray
{
public:
	HeapArray() {
		m_capacity = DEFAULT_SIZE;  // 默认数组大小
		m_heap = new T[m_capacity];
		m_greater = true;  // 默认构造大顶堆
		m_length = 0;
	}
	HeapArray(const int size, bool big = true) {  // 可以自己输入参数选择容量和堆类型
		m_capacity = size;  
		m_heap = new T[m_capacity];
		m_greater = big;
		m_length = 0;
	}
	~HeapArray() {
		delete[] m_heap;
	}
	// 判断堆是否为空
	bool IsEmpty()   
	{
		return m_length == 0;
	}
	// 获得堆的大小
	int GetSize() {
		return m_length;
	}
	// 获得堆的容量
	int GetCapacity() {
		return m_capacity;
	}
	// 获得存储堆的数组
	T* GetHeap() {
		return m_heap;
	}

	// 堆的插入{
	void Insert(T val) { 
		if (m_length < m_capacity) {
			m_heap[m_length++] = val;  // 从队尾加入
		}
		else{
			cout << "out of range!" << endl;
			return;
		}
		SiftUp(m_length - 1);
	}
	
	// 堆中删除数据
	void Delete(int i) {  // i为待删除的目标结点下标
		if (m_length == 0) {
			cout << "heap is null!" << endl;
			return;
		}
		swap(m_heap[m_length-1], m_heap[i]); //先和根结点（最值）交换
		m_length--; // 将长度缩短相当于删除
		SiftDown(0); // 从根结点向下调整
	} 
	
	// 向上调整
	void SiftUp(int i) {  
		if (m_greater) {  // 大顶堆
			while (m_heap[(i - 1) / 2] < m_heap[i] && i > 0) {
				swap(m_heap[(i - 1) / 2], m_heap[i]);
				i = (i - 1) / 2;
			}
		}
		else { // 小顶堆
			while (m_heap[(i - 1) / 2] > m_heap[i] && i > 0) {
				swap(m_heap[(i - 1) / 2], m_heap[i]);
				i = (i - 1) / 2;
			}
		}
	}  

	// 向下调整
	void SiftDown(int i) { 
		if (m_greater) {
			int j = 2 * i + 1;
			T temp = m_heap[i];
			while (j < m_length) {  // 循环条件，待交换结点下标不能越界
				if (j + 1 < m_length && m_heap[j] < m_heap[j + 1]) { // 左孩子小于右孩子
					++j; //j变为大的那个
				}
				if (temp > m_heap[j]) {
					break; // 大于最大的就不用交换了
				}
				else{  // 否则就要交换
					swap(m_heap[i], m_heap[j]);
					i = j; // 交换之后调整结点j为当前结点
					j = 2 * j + 1;
				}
			}
		}
		else{ // 小顶堆
			int j = 2 * i + 1;
			T temp = m_heap[i];
			while (j < m_length) {  // 循环条件，待交换结点下标不能越界
				if (j + 1 < m_length && m_heap[j] > m_heap[j + 1]) { // 左孩子大于右孩子
					++j; //j变为小的那个
				}
				if (temp < m_heap[j]) {
					break; // 小于最小的就不用交换了
				}
				else {  // 否则就要交换
					swap(m_heap[i], m_heap[j]);
					i = j; // 交换之后调整结点j为当前结点
					j = 2 * j + 1;
				}
			}
		}
	}  

	// 堆排序
	void HeapSort() {
		T* temp = new T[m_capacity];
		int size = m_length;
		for (int i = 0; i < size; i++) {
			temp[i] = m_heap[0];
			Delete(0);
		}
		delete[] m_heap;
		m_heap = temp;
		m_length = size;
	}
	
	// 利用数组建立堆
	void BuildHeap(vector<T> v) {
		for (int i = 0; i < v.size() && i<GetCapacity(); i++) {
			Insert(v[i]);
		}
	}


	// 输出
	void Print() {
		if (IsEmpty()) {
			cout << "none!" << endl;
			return;
		}
		for (int i = 0; i < m_length; i++) {
			cout << m_heap[i] << " ";
		}
		cout << endl;
	}


private:
	int m_capacity;  // 堆的容量，创建时就确定，不支持动态增加
	T* m_heap;         // 存储堆的数组
	bool m_greater;  // 是否是大顶堆
	int m_length;   // 堆中元素
};
