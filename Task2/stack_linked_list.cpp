#include "stack_linked_list.h"

void TestStackLinkedList() {
	StackLinkedList<int>* S = new StackLinkedList<int>;
	for (int i = 0; i < 10; i++) {
		S->Push(i);
	}
	cout << "pushed 10 item: " << endl;
	S->Print();
	cout <<"the top item is: "<< S->Top() << endl;
	cout << "size: "<< S->Size() << endl;
	S->Pop();
	cout << "after popped a item: " << endl;
	cout << "the top item is: " << S->Top() << endl;
	S->Print();
	cout << "size: " << S->Size() << endl;
	S->Clear();
	S->Print();
}