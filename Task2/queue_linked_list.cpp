#include "queue_linked_list.h"


void TestQueneLinkedList() {
	QueueLinkedList<int>* Q = new QueueLinkedList<int>;
	cout << "we enqueued 8 items!" << endl;
	for (int i = 1; i < 9; i++) {
		Q->EnQueue(i);
	}
	cout << "the size now is: " << Q->Size() << endl;
	Q->Print();
	cout << "we dequeued a item!" << endl;
	Q->Dequene();
	cout << "the size now is: " << Q->Size() << endl;
	Q->Print();
	cout << "front: " << Q->Front() << " rear: " << Q->Rear() << endl;
	Q->Clear();
	Q->Print();
}