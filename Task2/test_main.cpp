#include "stack_array.h"
#include "stack_linked_list.h"
#include "queue_array.h"
#include "queue_linked_list.h"
#include "queue_circle.h"

int main() {
	//TestStackArray();			// 测试数组实现的栈
	//TestStackLinkedList();	// 测试链表实现的栈
	//TestQueueArray();			// 测试数组实现的顺序队列
	//TestQueneLinkedList();	// 测试链表实现的队列
	TestQueueCircle();          // 测试数组实现的循环队列
	return 0;
}