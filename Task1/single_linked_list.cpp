#include "single_linked_list.h"
#include<iostream>

void TestSingleLinkedList() {
	LinkedList<int> *L = new LinkedList<int>(1);
	L->inputFront(-1); // ÊäÈë
	L->Print();
	L->Sort(); // ÅÅÐò
	L->Print();
	L->Reverse(); //·­×ªÁ´±í
	L->Print();
	LinkedList<int>* L1 = new LinkedList<int>(2);
	L1->inputFront(-1);
	L1->Print();
	L->Merge(*L1);
	L->Print();

}