#pragma once
#include <iostream>

using namespace std;

void TestSort();


//实现归并排序、快速排序、插入排序、冒泡排序、选择排序、堆排序（完成leetcode上的返回滑动窗口中的最大值(239)，
//这是上一期第三天的任务进行保留（涉及队列可以对第二天进行整理复习））


// 本文件中所有的排序默认为非递减排序
// 排序函数全部用静态成员函数实现

template<typename T>
class Sort
{
public:
	static void BubbleSort(T* array, int size);
	static void SelectSort(T* array, int size);
	static void InsertSort(T* array, int size);
	static void MergeSort(T* array, int left, int right);
	static void Merge(T* array, int left, int mid, int right);
	static void QuickSort(T* array, int left, int right);
	static void QuickSortStandard(T* array, int left, int right);
	static  int Partition(T* array, int left, int right);
	static void HeapSort(T* array,int size);
	static void MaxHeap(T* array, int i, int size);
	static void Print(T* array, int size);
	static T& BigK(T* array, int k, int size, int left, int right);
private:
	static void Swap(T* array, int a, int b);
};

// 交换值操作
template<typename T>
void Sort<T>::Swap(T* array, int a, int b) {
	T temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

// 打印数组
template<typename T>
void Sort<T>::Print(T* array, int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}


// 冒泡排序(蛮力法)
// 时间复杂度：最优O(n)(优化版,即下面的实现,未优化O(n²)),平均O(n²),最差O(n²)
// 空间复杂度: O(1)
template<typename T>
void Sort<T>::BubbleSort(T* array, int size) {
	bool flag = true; // 用标识符针对基本有序情况改进
	// j从0开始，从左往右遍历，已排序的在右边，即往右边冒泡
	for (int i = 0; i < size - 1 && flag; i++) { // 外循环为排序趟数，长度为size，排序 size-1 趟（如果每次都未有序）
		flag = false;
		for (int j = 0; j < size - 1 - i; j++) { // 内循环为每趟比较的次数，第i趟比较 size-i 次
			if (array[j] > array[j + 1]) {  // 增序排序，<为减序
				Swap(array, j, j + 1);
				flag = true; // 如果内循环跑完了一趟都没有更改标志说明已经有序
			}
		}
	}
}

// 直接选择排序(蛮力法)
// 时间复杂度：最优O(n²),平均O(n²),最差O(n²)
// 空间复杂度: O(1)
template<typename T>
void Sort<T>::SelectSort(T* array, int size) {
	for (int i = 0; i < size - 1; i++) {      // 外循环为排序趟数，排序 size-1 趟
		T minScript = i;                      // 设置最小值得下标
		for (int j = i + 1; j < size; j++) {  // 内循环每一次都是找到后面的数中的最小值
			if (array[j] < array[minScript]) {
				minScript = j;
			}
		}
		Swap(array, i, minScript);            // 将前面的数替换为后面数中的最小值
	}
}

// 直接插入排序(减治法)
// 时间复杂度：最优O(n),平均O(n²),最差O(n²)
// 空间复杂度: O(1)
template<typename T>
void Sort<T>::InsertSort(T* array, int size) {
	for (int i = 1; i < size; i++) { // 从第二个数开始遍历到最后一个
		T temp = array[i]; // 每次遍历的数作为候选插入数
		int j = i - 1; // 从候选插入数的前一位开始寻找插入位置
		while (array[j] > temp && j >= 0) { // 往前寻找直到出现小于候选数的存在，同时j不能越界 
			array[j + 1] = array[j];   // 如果大于候选数，就往后稍稍
			j--;
		}
		array[j+1] = temp; // 在第一个小于候选数的后面一位插入候选数
	}
}

// 归并排序(分治法)
// 时间复杂度：最优O(nlog(n)),平均O(nlog(n)),最差O(nlog(n))
// 空间复杂度: O(n)(需要一个临时空间temp[]存储归并的结果)
// 可以将空间复杂度由 O(n) 降低至 O(1)，然而相对的时间复杂度则由 O(nlogn) 升至 O(n²)
template<typename T>
void Sort<T>::MergeSort(T* array, int left, int right) { //left 为待排序序列最左端，right为最右端
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(array, left, mid); // 左边的递归
		MergeSort(array, mid + 1, right); // 右边的递归
		Merge(array, left, mid, right); // 归并
	}
}

// 归并函数
template<typename T>
void Sort<T>::Merge(T* array, int left, int mid, int right) {
	// 分成两部分[left,mid], [mid+1,right]
	T* temp = new T[right - left + 1];
	int i = left, j = mid + 1, k=0;
	while (i <= mid && j <= right) { // 都在遍历范围内
		if (array[i] < array[j]) {
			temp[k++] = array[i++]; // array[i]更小就放入临时数组,下标都加一
		}
		else{
			temp[k++] = array[j++];
		}
	}
	// 对于其中剩余部分进行复制
	while (i <= mid) {
		temp[k++] = array[i++];
	}
	while (j <= right) {
		temp[k++] = array[j++];
	}
	// 将临时数组拷贝到原数组对应的位置
	for (int m = left, n=0; m < right + 1; m++, n++) {
		array[m] = temp[n];
	}
	delete temp;
}

// 快速排序(分治法)
// 时间复杂度：最优O(nlog(n)),平均O(nlog(n)),最差O(n²)
// 空间复杂度: O(log(n))(递归栈的深度)或O(n)
template<typename T>
void Sort<T>::QuickSort(T* array, int left, int right) {
	if (left < right) { // 递归停止条件
		int i = left - 1, j = right + 1; // 避免因自增漏掉首尾的数据比较 
		T pivot = array[(left+right) / 2]; // 用来划分的标杆，左边应都小于它，右边应都大于它
		while (true) {
			// 找到左边大于pivot的值
			// 使用前置运算符++是因为要先对下标自增操作再判断
			while (array[++i] < pivot); 
			// 找到右边小于pivot的值
			while (array[--j] > pivot);
			if (i >= j) {
				break;
			}
			// 交换这两个值
			Swap(array, i, j);
		}
		// 下标小于i的都<=pivot，大于j的都>=pivot
		// 两种情况，一种递归时不包括pivot,pivot已存在于最终位置,pivot左右分别是两个递归的子序列
		// 另一种是pivot继续包含在递归中，完整地将原序列划分为两个子序列递归
		QuickSort(array, left, i - 1); 
		QuickSort(array, j + 1, right);
	}
}


// 另一种通用的快速快序方式
template<typename T>
void Sort<T>::QuickSortStandard(T* array, int left, int right) {
	if (left < right) {
		int pivot = Partition(array, left, right);
		QuickSortStandard(array, left, pivot - 1);
		QuickSortStandard(array, pivot + 1, right);
	}
}

// 划分数组(核心)
template<typename T>
int Sort<T>::Partition(T* array, int left, int right) {
	// 取最右边的数作为主元
	T temp = array[right]; 
	// i，j俩指针都从头出发,j在前,i在后
	int i = left - 1; // i指向元素的前一个位置,j指向待排序数列中的第一个元素。
	for (int j = left; j < right; j++) {
		if (array[j] <= temp) { // 如果有小于等于主元的数就交换到数列的前面去
			i++;   
			Swap(array, i, j);  // i位置上的数小于等于主元
		}
	}
	Swap(array, i + 1, right);
	return i + 1;
}

//堆排序(变治法)
// 时间复杂度：最优O(nlog(n)),平均O(nlog(n)),最差O(nlog(n))
// 初始化建堆时的时间复杂度为O(n)，更改堆元素后重建堆的时间复杂度为O(nlogn)
// 空间复杂度: O(1),就地排序

template<typename T>
void Sort<T>::HeapSort(T* array, int size) {
	// 从最后一个非叶子结点开始向前遍历
	for (int i = size/2 - 1; i >= 0; i--) {
		MaxHeap(array, i, size);
	}
	for (int i = size - 1; i >= 1; i--) {
		Swap(array, 0, i); // 交换堆顶元素，放在最后
		MaxHeap(array, 0, i); // 再次调整
	}
}

// 大顶堆调整函数
template<typename T>
void Sort<T>::MaxHeap(T* array, int i, int size) { // i为调整的结点
	int j = 2 * i + 1; // 找到当前结点的左孩子
	T temp = array[i]; // 先临时存储当前结点的值
	while (j < size) { // 结点下标不能越界
		if (j + 1 < size && array[j] < array[j+1]) { //如果存在右孩子且左孩子小于右孩子
			++j;
		}
		if (temp > array[j]) {  // 未破坏原有的堆序,则直接完成调整
			break;
		}
		else{
			Swap(array, i, j);  // 孩子结点中最大的与父结点交换
			i = j; //当前结点变为最大的孩子结点
			j = 2 * j + 1; // 下一个孩子结点，递归执行
		}
	}
}


// 找出第k大的数O(n)
template<typename T>
T& Sort<T>::BigK(T* array, int k, int size, int left, int right) {
	// 输入条件判断
	if (k<1 || k>size || array == nullptr || left >= right) {
		cout << "value error!" << endl; 
		exit(1);
	}
	// 借用快排的划分函数
	int pos = Partition(array, left, right);
	// 如果划分结果pos大于指定值size-k,则在pos左边找，否则在pos右边找，一次只对其中一组递归
	while (pos != size - k) {
		pos = pos > size - k ? Partition(array, left, pos - 1) : Partition(array, pos + 1, right);
	}
	return array[pos];
}