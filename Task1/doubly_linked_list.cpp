#include "doubly_linked_list.h"

void TestDoublyLinkedList() {
	DoublyLinkedList<int>* L = new DoublyLinkedList<int>;
	// ≤‚ ‘ ‰»Î
	L->InputBack(-1);
	// ≤‚ ‘≥§∂»
	cout << "L's size: "<< L->Length()<<endl;
	// ≤‚ ‘ ‰≥ˆ
	L->Print();
	// ≤‚ ‘∂®Œª
	cout << "the 3rd item: " << L->Locate(3)->data << endl;
	// ≤‚ ‘«Âø’
	//L->Clear();
	//L->Print();
	// ≤‚ ‘≤Â»Î ‘≠ ˝æ›1 2 3 4 5
	L->Insert(190, 0);
	cout << "inserted 190 at 0: ";
	L->Print();
	L->Insert(222, 6);
	cout << "inserted 222 at 6: ";
	L->Print();
	// ≤‚ ‘…æ≥˝
	int x;
	L->Delete(0, x);
	cout << "deleted "<<x<<" at 0: ";
	L->Print();
	L->Delete(5, x);
	cout << "deleted " << x << " at 5: ";
	L->Print();


}