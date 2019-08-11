#pragma once
#include <iostream>
#include "sorting.h"

void TestSearch();

template<typename T>
class Search
{
public:
	// 一个有序数组的二分查找算法
	static int BinarySearch(T* array, T target, int size);
	//模糊二分查找算法
	static int FuzzyBinarySearch(T* array, T val, int size);
};

// 一个有序数组的二分查找算法
template<typename T>
int Search<T>::BinarySearch(T* array, T target, int size) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2; //中间数
		if (array[mid] > target) { // 在左边寻找
			right = mid - 1;
		}
		else if(array[mid] < target){ // 在右边寻找
			left = mid + 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}

// 查找大于等于给定值的第一个元素(已排序)
template<typename T>
int Search<T>::FuzzyBinarySearch(T* array, T val, int size) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (array[mid] < val) { // 中间数小于目标数
			left = mid + 1;
		}
		else { // 中间数大于等于目标数
			right = mid;  // 中间数被包含进来
		}
		// 循环终止条件
		if (left == right && array[left] >= val) {
			return left;
		}
	}
	return -1;
}