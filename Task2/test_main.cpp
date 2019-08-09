#include <vector>
#include "stack_array.h"
#include "stack_linked_list.h"
#include "queue_array.h"
#include "queue_linked_list.h"
#include "queue_circle.h"

int main() {
	extern void TestFibonacci();
	extern void TestFactorial();
	extern void TestFullPermutation();

	//TestStackArray();			// 测试数组实现的栈
	//TestStackLinkedList();	// 测试链表实现的栈
	//TestQueueArray();			// 测试数组实现的顺序队列
	//TestQueneLinkedList();	// 测试链表实现的队列
	//TestQueueCircle();        // 测试数组实现的循环队列
	TestFibonacci();			// 测试斐波那契数列
	TestFactorial();		    // 测试阶乘
	TestFullPermutation();		// 测试全排列
	return 0;
}