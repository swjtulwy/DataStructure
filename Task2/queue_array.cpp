#include "queue_array.h"


void TestQueueArray() {
	QueueArray<int>* Q = new QueueArray<int>(8);
	Q->Dequeue();
	cout << "inserted 8 number:" << endl;
	for (int i = 1; i < 9; i++) {
		Q->Enqueue(i);
	}
	Q->Print();
	cout << "we dequeued!"<<endl;
	Q->Dequeue();
	Q->Print();
	cout << "we enqueued when it's false overflow!" << endl;
	Q->Enqueue(9);
	Q->Print();
	Q->Enqueue(10);
}