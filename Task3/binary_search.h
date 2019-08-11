#pragma once
#include <iostream>
#include "sorting.h"

void TestSearch();

template<typename T>
class Search
{
public:
	// һ����������Ķ��ֲ����㷨
	static int BinarySearch(T* array, T target, int size);
	//ģ�����ֲ����㷨
	static int FuzzyBinarySearch(T* array, T val, int size);
};

// һ����������Ķ��ֲ����㷨
template<typename T>
int Search<T>::BinarySearch(T* array, T target, int size) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2; //�м���
		if (array[mid] > target) { // �����Ѱ��
			right = mid - 1;
		}
		else if(array[mid] < target){ // ���ұ�Ѱ��
			left = mid + 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}

// ���Ҵ��ڵ��ڸ���ֵ�ĵ�һ��Ԫ��(������)
template<typename T>
int Search<T>::FuzzyBinarySearch(T* array, T val, int size) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (array[mid] < val) { // �м���С��Ŀ����
			left = mid + 1;
		}
		else { // �м������ڵ���Ŀ����
			right = mid;  // �м�������������
		}
		// ѭ����ֹ����
		if (left == right && array[left] >= val) {
			return left;
		}
	}
	return -1;
}