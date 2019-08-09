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

	//TestStackArray();			// ��������ʵ�ֵ�ջ
	//TestStackLinkedList();	// ��������ʵ�ֵ�ջ
	//TestQueueArray();			// ��������ʵ�ֵ�˳�����
	//TestQueneLinkedList();	// ��������ʵ�ֵĶ���
	//TestQueueCircle();        // ��������ʵ�ֵ�ѭ������
	TestFibonacci();			// ����쳲���������
	TestFactorial();		    // ���Խ׳�
	TestFullPermutation();		// ����ȫ����
	return 0;
}