#include "doubly_linked_list.h"

void TestDoublyLinkedList() {
	DoublyLinkedList<int>* L = new DoublyLinkedList<int>;
	// ��������
	L->InputBack(-1);
	// ���Գ���
	cout << "L's size: "<< L->Length()<<endl;
	// �������
	L->Print();
	// ���Զ�λ
	cout << "the 3rd item: " << L->Locate(3)->data << endl;
	// �������
	//L->Clear();
	//L->Print();
	// ���Բ��� ԭ����1 2 3 4 5
	L->Insert(190, 0);
	cout << "inserted 190 at 0: ";
	L->Print();
	L->Insert(222, 6);
	cout << "inserted 222 at 6: ";
	L->Print();
	// ����ɾ��
	int x;
	L->Delete(0, x);
	cout << "deleted "<<x<<" at 0: ";
	L->Print();
	L->Delete(5, x);
	cout << "deleted " << x << " at 5: ";
	L->Print();


}