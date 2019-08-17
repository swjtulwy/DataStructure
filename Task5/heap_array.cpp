#include "heap_array.h"

void TestHeapArray() {
	HeapArray<int>* H = new HeapArray<int>(7,false);
	vector<int> v = {4,3,6,7,2,1,5};
	cout << "small root heap: ";
	H->BuildHeap(v);
	H->Print();
	cout << "sorted: ";
	H->HeapSort();
	H->Print();

	HeapArray<int>* H1 = new HeapArray<int>(7);
	vector<int> v1 = { 4,3,6,7,2,1,5 };
	cout << "big root heap: ";
	H1->BuildHeap(v1);
	H1->Print();
	cout << "sorted: ";
	H1->HeapSort();
	H1->Print();

}