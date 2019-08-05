#include "dynamic_array.h"
#include <iostream>



void TestDynamicArray() {
	DynamicArray<int, 6> arr1;
	arr1[0] = 7;
	arr1[1] = 9;
	arr1[2] = 4;
	arr1[3] = 5;
	arr1[4] = 3;
	arr1[7] = 8; // ��֤�±�������Ч��
	cout << "\n------------------------------\n";
	cout << "arr1[7] is out of range!"<<endl;
	cout << "\n------------------------------\n";
	//��֤�޸���������Ч��;
	cout << "array1 :"<< arr1 << endl;
	cout << "array1[3] was changed:" << endl;
	arr1[3] = 23819023;
	cout << "array1: "<< arr1 << endl;

	cout << "\n------------------------------\n";
	// ����һ�����ʼ������֤���
	DynamicArray<int, 2> arr2(arr1);
	cout << "get array2 by a instance initialization" << endl;
	cout << "array2: " << arr2 << endl;
	cout << "array2's size: " << arr2.GetSize() << endl;
	cout << "array1's size: " << arr1.GetSize() << endl;
	cout << "\n------------------------------\n";
	// ��֤��̬����Ч��
	arr1.Expand(10);
	cout << "we expand the capacity with 10 " << endl;
	cout << "so array1's size: " << arr1.GetSize() << endl;
	cout << "array1: " << arr1 << endl;
	cout << "\n------------------------------\n";
	// ��֤=�Ÿ�ֵЧ��
	DynamicArray<int, 5> arr3;
	cout << "get array3 by \'=\' " << endl;
	arr3 = arr1;
	cout << "array3's size: " << arr3.GetSize() << endl;
	cout << "array3: " << arr3 << endl;
	cout << "\n------------------------------\n";
	// ��֤��̬����Ч��
	cout << "insert a item dynamicly " << endl;
	arr1.Insert(99, 13);
	cout << "so array1's size: "<<arr1.GetSize() << endl;
	cout << "array1: "<< arr1 <<endl;
	cout << "\n------------------------------\n";
	// ��֤��̬ɾ��Ч��
	cout << "delete a item dynamicly " << endl;
	arr1.Delete(13);
	cout << "so array1's size: "<< arr1.GetSize()<<endl;
	cout << "array1: "<< arr1<<endl;
	cout << "\n------------------------------\n";
	// ��֤����(����)
	cout << "sorted array " << endl;
	arr1.Sort();
	cout << "sorted array1: "<< arr1 << endl;
	cout << "\n------------------------------\n";
	// ��֤�ϲ���������
	cout << "merge two sorted array: array4 and array5" << endl;
	DynamicArray<int, 3> arr4;
	arr4[0] = 8;
	arr4[1] = 3;
	arr4[2] = 5;
	cout << "array4: " <<arr4 << endl;
	DynamicArray<int, 5> arr5;
	arr5[0] = 19;
	arr5[1] = 4;
	arr5[2] = 3;
	arr5[3] = 11;
	arr5[4] = 7;
	cout << "array5: "<<arr5 << endl;
	arr4.MergeSortedArray(arr5);
	cout << "merged array4: "<<arr4 << endl;
	cout << "array4's size: "<< arr4.GetSize() << endl;
}