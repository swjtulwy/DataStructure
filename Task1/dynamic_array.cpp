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

	//��֤�޸���������Ч��;
	cout << arr1 << endl;
	arr1[3] = 23819023;
	cout << arr1 << endl;

	// ����һ�����ʼ������֤���
	DynamicArray<int, 2> arr2(arr1);
	cout << arr2 << endl;
	cout << arr2.GetSize() << endl;
	cout << arr1.GetSize() << endl;

	// ��֤��̬����Ч��
	arr1.Expand(10);
	cout << arr1.GetSize() << endl;
	cout << arr1 << endl;

	// ��֤=�Ÿ�ֵЧ��
	DynamicArray<int, 5> arr3;
	arr3 = arr1;
	cout << arr3.GetSize() << endl;
	cout << arr3 << endl;

	// ��֤��̬����Ч��
	arr1.Insert(99, 13);
	cout << arr1.GetSize() << endl;
	cout << arr1 <<endl;

	// ��֤��̬ɾ��Ч��
	arr1.Delete(13);
	cout << arr1.GetSize()<<endl;
	cout << arr1<<endl;

	// ��֤����(����)
	arr1.Sort();
	cout << arr1 << endl;

	// ��֤�ϲ���������
	DynamicArray<int, 3> arr4;
	arr4[0] = 8;
	arr4[1] = 3;
	arr4[2] = 5;
	cout << arr4 << endl;
	DynamicArray<int, 5> arr5;
	arr5[0] = 19;
	arr5[1] = 4;
	arr5[2] = 3;
	arr5[3] = 11;
	arr5[4] = 7;
	cout << arr5 << endl;
	arr4.MergeSortedArray(arr5);
	cout << arr4 << endl;
	cout << arr4.GetSize() << endl;
}