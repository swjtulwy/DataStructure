#include "sorting.h"

void TestSort() {
	int array[] = {1,9,3,4,7,6,5};
	//Sort<int>::BubbleSort(array, sizeof(array) / sizeof(int)); // ����ð������
	//Sort<int>::SelectSort(array, sizeof(array) / sizeof(int)); // ����ѡ������
	//Sort<int>::InsertSort(array, sizeof(array) / sizeof(int)); // ���Բ�������
	//Sort<int>::MergeSort(array, 0, sizeof(array) / sizeof(int) - 1); // ���Թ鲢����
	//Sort<int>::QuickSort(array, 0, sizeof(array) / sizeof(int) - 1); // ���Կ�������
	//Sort<int>::QuickSortStandard(array, 0, sizeof(array) / sizeof(int) - 1); // ���Կ�������Ľ���
	//Sort<int>::HeapSort(array, sizeof(array) / sizeof(int)); // ���Զ�����
	// ����Ѱ�ҵ�k�����
	cout << "the k th number: " << Sort<int>::BigK(array, 3,
		sizeof(array) / sizeof(int), 0, sizeof(array) / sizeof(int) - 1) << endl;
	Sort<int>::Print(array, sizeof(array) / sizeof(int));
}