#include "circle_linked_list.h"
#include <iostream>

using namespace std;

void TestCircleLinkedList() {
	CircleLinkedList<int> *L = new CircleLinkedList<int>;
	// 测试输入
	L->InputBack(-1);
	// 测试输出
	L->Print();
	cout << "-----------------------------" << endl;
	// 测试增加 1, 2, 3为输入
	cout << "inserted: 100 at pos: 1" << endl;
	L->Insert(100, 1);
	L->Print();
	cout << "inserted: 101 at pos: 0" << endl;
	L->Insert(101, 0);
	L->Print();
	cout << "inserted: 102 at pos: 5" << endl;
	L->Insert(102, 5);
	L->Print();
	cout << "-----------------------------" << endl;
	// 测试删除
	int tmp;
	L->Delete(1, tmp);
	cout << "deleted: " << tmp << endl;
	L->Print();
	L->Delete(4, tmp);
	cout << "deleted: " << tmp << endl;
	L->Print();
	L->Delete(0, tmp);
	cout << "deleted: " << tmp << endl;
	L->Print();

	// 测试返回长度
	cout << "length: " << L->Length() << endl;
	cout << "-----------------------------" << endl;
	
	// 测试返回尾部指针
	cout << "tail: "<< L->Tail()->data << endl;

	// 测试清空
	L->Clear();
	L->Print();

	cout << "-----------------------------" << endl;
	cout << "length: " << L->Length() << endl;

	// 此时链表为空，返回的是head里的数据
	cout << "tail: " << L->Tail()->data << endl;


}