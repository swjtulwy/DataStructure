#include "doubly_linked_list.h"

void TestDoublyLinkedList() {
	DoublyLinkedList<int>* L = new DoublyLinkedList<int>;
	L->InputBack(-1);
	L->Print();
	L->Clear();
	L->Print();

}