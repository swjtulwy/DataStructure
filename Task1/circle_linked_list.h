#pragma once
#include <iostream>
#include "single_linked_list.h"
using namespace std;

void TestCircleLinkedList();

// ����dummy node��Ϊͷ��㣬��ͷ��㲻�洢ʵ������
template <typename T>
class CircleLinkedList {
public:
	// Ĭ�Ϲ��캯��
	CircleLinkedList() { head = new Node<T>; };
	// �вι��캯��
	CircleLinkedList(const T& item) { head = new Node<T>(item); };
	void Clear();
	void Print();
	void InputBack(const T endTag);
	Node<T>* Locate(const int pos);
	Node<T>* Tail();
	int Length();
	bool Insert(const T& item,const int pos);
	bool Delete(const int pos, T& item);
	bool IsEmpty() { return head == nullptr; };
	Node<T>* GetHead() { return this->head; };
	~CircleLinkedList() { Clear(); };
private:
	Node<T>* head;
};

template<typename T>
void CircleLinkedList<T>::Clear() {
	Node<T>* q, *first =head->next;
	while (first) {
		if (first->next!=first) { // �ж��Ƿ������һ�����
			q = first->next;
			first->next = q->next;
			delete q;
		}
		else {
			head->next = nullptr; // �Ͽ�ͷ���(dummy node)������
			delete first; // ɾ����һ�����
			break; // ֱ������ѭ��
		}
	}
	cout << "list cleared!" << endl;
}

template<typename T>
void CircleLinkedList<T>::Print() {
	Node<T>* first=head->next,*p=first;
	if (!first) {
		cout << "none list!" << endl;
		return;
	}
	cout << "head->";
	while (p) {
		if (p->next != first) {
			cout << p->data << "->";
			p = p->next;
		}
		else {
			cout << p->data <<"->"<< first->data << endl;
			break;
		}
	}
}

// β�巨����
template<typename T>
void CircleLinkedList<T>::InputBack(const T endTag) {
	Node<T>* newNode,* r = head;
	T temp;
	Clear();
	cout << "please input:";
	cin >> temp;
	while (temp != endTag) {
		newNode = new Node<T>(temp);
		if (newNode == nullptr) {
			return;
		}
		r->next = newNode;
		r = newNode;
		cin >> temp;
	}
	r->next = head->next; // ָ���һ����㣬����ѭ��
}

template <typename T>
Node<T>* CircleLinkedList<T>::Locate(int pos) {
	int count = 0;
	Node<T>* p = head->next;
	while (p&&count<pos) {
		p = p->next;
		count++;
	}
	return p;
}

// ��������β��ָ��
template<typename T>
Node<T>* CircleLinkedList<T>::Tail() {
	Node<T> *p = this->GetHead()->next;
	if (p==nullptr) {
		cout << "none list!" << endl;
		return head; // �ձ�
	}
	while (p!=nullptr) {
		if (p->next == head->next) {
			return p;
		}
		p = p->next;
	}
	return head;
}

// ���ر�
template<typename T>
int CircleLinkedList<T>::Length() {
	Node<T>* p = this->GetHead()->next;
	if (!p) {
		return 0; // �ձ���ͷָ��
	}
	int count=0;
	while (p != this->Tail()) {
		p = p->next;
		count++;
	}
	return count+1;
}

// ���뵽pos��λ��
template<typename T>
bool CircleLinkedList<T>::Insert(const T& item, const int pos) {
	// ֻ�����������һ�����ݵ�����������Ӧ��ʹ��InputBack()��������
	if (this->Length()==0|| pos<0 || pos > this->Length()) {
		return false;
	}
	Node<T>* newNode = new Node<T>(item), *cur, *r;
	if (!newNode)
		return false;
	// �����һ��λ�ñȽ����⣬Ҫ����β�����ָ��
	if (pos == 0) { 
		cur = head;
		r = this->Tail();
		newNode->next = cur->next;
		cur->next = newNode;
		r->next = cur->next;
	}
	else {
		cur = this->Locate(pos - 1);
		newNode->next = cur->next;
		cur->next = newNode;
	}
	return true;
}

template<typename T>
bool CircleLinkedList<T>::Delete(const int pos, T& item) {
	if (pos < 0 || pos>this->Length() - 1||this->Length()==0) {
		return false;
	}
	Node<T>* cur, *q;
	if (pos == 0) {
		q = head->next;
		item = q->data;
		this->Tail()->next = q->next;
		if (q->next != nullptr) {
			head->next = q->next;
		}
		else{
			head->next = nullptr;
		}
		delete q;
	}
	else {
		cur = this->Locate(pos - 1);
		q = cur->next;
		item = q->data;
		cur->next = q->next;
		delete q;
	}	
	return true;
}