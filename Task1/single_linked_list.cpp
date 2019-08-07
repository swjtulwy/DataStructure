#include "single_linked_list.h"
#include<iostream>

void TestSingleLinkedList() {
	LinkedList<int> *L = new LinkedList<int>;
	cout << "\n------------------------------\n";
	cout << "input area:" << endl;
	L->InputBack(-1); // 输入
	cout << "\n------------------------------\n";
	cout << "LinkedList L's view:" << endl;
	L->Print();
	L->Sort(); // 排序
	cout << "\n------------------------------\n";
	cout << "Sorted LinkedList L's view:" << endl;
	L->Print();
	L->Reverse(); //翻转链表
	cout << "\n------------------------------\n";
	cout << "Reversed LinkedList L's view:" << endl;
	L->Print();
	cout << "\n------------------------------\n";
	LinkedList<int>* L1 = new LinkedList<int>; // 合并有序列表
	cout << "input area:" << endl;
	L1->InputBack(-1);
	cout << "\n------------------------------\n";
	cout << "LinkedList L1's view:" << endl;
	L1->Print();
	L->Merge(*L1);
	cout << "L Merged L1, LinkedList L's view:" << endl;
	L->Print();
	cout << "\n------------------------------\n";
	cout << "LinkedList L's MidNote's data:" << endl;
	cout<<L->GetMidNode()->data;// 中间结点
}