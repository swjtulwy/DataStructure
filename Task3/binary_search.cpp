#include "binary_search.h"

void TestSearch() {
	int array[] = { 1,9,3,11,7,17,5 };
	Sort<int>::HeapSort(array, sizeof(array) / sizeof(int));
	Sort<int>::Print(array, sizeof(array) / sizeof(int));
	cout << "7 is in: " << Search<int>::BinarySearch(array, 7, sizeof(array) / sizeof(int)) << endl;
	cout << "script of the first num >= 4 is: " << 
		Search<int>::FuzzyBinarySearch(array, 4, sizeof(array) / sizeof(int)) << endl;
}