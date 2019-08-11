#include "sorting.h"

void TestSort() {
	int array[] = {1,9,3,4,7,6,5};
	//Sort<int>::BubbleSort(array, sizeof(array) / sizeof(int)); // ²âÊÔÃ°ÅİÅÅĞò
	//Sort<int>::SelectSort(array, sizeof(array) / sizeof(int)); // ²âÊÔÑ¡ÔñÅÅĞò
	//Sort<int>::InsertSort(array, sizeof(array) / sizeof(int)); // ²âÊÔ²åÈëÅÅĞò
	//Sort<int>::MergeSort(array, 0, sizeof(array) / sizeof(int) - 1); // ²âÊÔ¹é²¢ÅÅĞò
	//Sort<int>::QuickSort(array, 0, sizeof(array) / sizeof(int) - 1); // ²âÊÔ¿ìËÙÅÅĞò
	//Sort<int>::QuickSortStandard(array, 0, sizeof(array) / sizeof(int) - 1); // ²âÊÔ¿ìËÙÅÅĞò¸Ä½ø°æ
	//Sort<int>::HeapSort(array, sizeof(array) / sizeof(int)); // ²âÊÔ¶ÑÅÅĞò
	// ²âÊÔÑ°ÕÒµÚk´óµÄÊı
	cout << "the k th number: " << Sort<int>::BigK(array, 3,
		sizeof(array) / sizeof(int), 0, sizeof(array) / sizeof(int) - 1) << endl;
	Sort<int>::Print(array, sizeof(array) / sizeof(int));
}