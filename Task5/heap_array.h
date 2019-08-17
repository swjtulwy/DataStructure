#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// ������ʵ�ֵĶѣ����Ը����������ȷ���Ǵ󶥶ѻ���С����

void TestHeapArray();

const int DEFAULT_SIZE = 10;

template<typename T>
class HeapArray
{
public:
	HeapArray() {
		m_capacity = DEFAULT_SIZE;  // Ĭ�������С
		m_heap = new T[m_capacity];
		m_greater = true;  // Ĭ�Ϲ���󶥶�
		m_length = 0;
	}
	HeapArray(const int size, bool big = true) {  // �����Լ��������ѡ�������Ͷ�����
		m_capacity = size;  
		m_heap = new T[m_capacity];
		m_greater = big;
		m_length = 0;
	}
	~HeapArray() {
		delete[] m_heap;
	}
	// �ж϶��Ƿ�Ϊ��
	bool IsEmpty()   
	{
		return m_length == 0;
	}
	// ��öѵĴ�С
	int GetSize() {
		return m_length;
	}
	// ��öѵ�����
	int GetCapacity() {
		return m_capacity;
	}
	// ��ô洢�ѵ�����
	T* GetHeap() {
		return m_heap;
	}

	// �ѵĲ���{
	void Insert(T val) { 
		if (m_length < m_capacity) {
			m_heap[m_length++] = val;  // �Ӷ�β����
		}
		else{
			cout << "out of range!" << endl;
			return;
		}
		SiftUp(m_length - 1);
	}
	
	// ����ɾ������
	void Delete(int i) {  // iΪ��ɾ����Ŀ�����±�
		if (m_length == 0) {
			cout << "heap is null!" << endl;
			return;
		}
		swap(m_heap[m_length-1], m_heap[i]); //�Ⱥ͸���㣨��ֵ������
		m_length--; // �����������൱��ɾ��
		SiftDown(0); // �Ӹ�������µ���
	} 
	
	// ���ϵ���
	void SiftUp(int i) {  
		if (m_greater) {  // �󶥶�
			while (m_heap[(i - 1) / 2] < m_heap[i] && i > 0) {
				swap(m_heap[(i - 1) / 2], m_heap[i]);
				i = (i - 1) / 2;
			}
		}
		else { // С����
			while (m_heap[(i - 1) / 2] > m_heap[i] && i > 0) {
				swap(m_heap[(i - 1) / 2], m_heap[i]);
				i = (i - 1) / 2;
			}
		}
	}  

	// ���µ���
	void SiftDown(int i) { 
		if (m_greater) {
			int j = 2 * i + 1;
			T temp = m_heap[i];
			while (j < m_length) {  // ѭ������������������±겻��Խ��
				if (j + 1 < m_length && m_heap[j] < m_heap[j + 1]) { // ����С���Һ���
					++j; //j��Ϊ����Ǹ�
				}
				if (temp > m_heap[j]) {
					break; // �������ľͲ��ý�����
				}
				else{  // �����Ҫ����
					swap(m_heap[i], m_heap[j]);
					i = j; // ����֮��������jΪ��ǰ���
					j = 2 * j + 1;
				}
			}
		}
		else{ // С����
			int j = 2 * i + 1;
			T temp = m_heap[i];
			while (j < m_length) {  // ѭ������������������±겻��Խ��
				if (j + 1 < m_length && m_heap[j] > m_heap[j + 1]) { // ���Ӵ����Һ���
					++j; //j��ΪС���Ǹ�
				}
				if (temp < m_heap[j]) {
					break; // С����С�ľͲ��ý�����
				}
				else {  // �����Ҫ����
					swap(m_heap[i], m_heap[j]);
					i = j; // ����֮��������jΪ��ǰ���
					j = 2 * j + 1;
				}
			}
		}
	}  

	// ������
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
	
	// �������齨����
	void BuildHeap(vector<T> v) {
		for (int i = 0; i < v.size() && i<GetCapacity(); i++) {
			Insert(v[i]);
		}
	}


	// ���
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
	int m_capacity;  // �ѵ�����������ʱ��ȷ������֧�ֶ�̬����
	T* m_heap;         // �洢�ѵ�����
	bool m_greater;  // �Ƿ��Ǵ󶥶�
	int m_length;   // ����Ԫ��
};
