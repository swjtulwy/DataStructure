#include "stack_array.h"

void TestStackArray() {
	StackArray<int> *S = new StackArray<int>(5);
	//cout << S->Top(); // stack is empty
	for (int i = 0; i < 5; i++) {
		S->Push(i);
	}
	S->Push(6);
	cout << "stack size: " << S->Size() << endl;
	for (int i = 0; i < 5; i++) {
		cout << S->Top() << " ";
		S->Pop();
	}
	cout << endl;
	S->Pop();
}
