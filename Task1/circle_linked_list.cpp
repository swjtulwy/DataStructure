#include "circle_linked_list.h"
#include <iostream>

using namespace std;

void TestCircleLinkedList() {
	CircleLinkedList<int> *L = new CircleLinkedList<int>;
	// ��������
	L->InputBack(-1);
	// �������
	L->Print();
	cout << "-----------------------------" << endl;
	// �������� 1, 2, 3Ϊ����
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
	// ����ɾ��
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

	// ���Է��س���
	cout << "length: " << L->Length() << endl;
	cout << "-----------------------------" << endl;
	
	// ���Է���β��ָ��
	cout << "tail: "<< L->Tail()->data << endl;

	// �������
	L->Clear();
	L->Print();

	cout << "-----------------------------" << endl;
	cout << "length: " << L->Length() << endl;

	// ��ʱ����Ϊ�գ����ص���head�������
	cout << "tail: " << L->Tail()->data << endl;


}