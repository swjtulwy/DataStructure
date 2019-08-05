#include "single_linked_list.h"
#include<iostream>

void TestSingleLinkedList() {
	LinkedList<int> *L = new LinkedList<int>(1);
	L->inputFront(-1); // 输入
	L->Print();
	L->Sort(); // 排序
	L->Print();
	L->Reverse(); //翻转链表
	L->Print();
	LinkedList<int>* L1 = new LinkedList<int>(2); // 合并有序列表
	L1->inputFront(-1);
	L1->Print();
	L->Merge(*L1);
	L->Print();
	cout<<L->GetMidNode()->data;// 中间结点
}