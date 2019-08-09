#include "queue_circle.h"


void TestQueueCircle() {
	QueueCircle<int>* Q = new QueueCircle<int>(8);
	Q->Dequeue();
	cout << "inserted 8 number:" << endl;
	for (int i = 1; i < 9; i++) {
		Q->Enqueue(i);
	}
	cout << "the size: " <<Q->Size()<< endl;
	Q->Print();
	cout << "we dequeued!" << endl;
	Q->Dequeue();
	cout << "the size: " << Q->Size() << endl;
	Q->Print();
	Q->Enqueue(9);
	cout << "the size: " << Q->Size() << endl;
	Q->Print();
	cout << "we enqueued when it's  overflow!" << endl;
	Q->Enqueue(10);
	cout << "the size: " << Q->Size() << endl;
	Q->Print();
}