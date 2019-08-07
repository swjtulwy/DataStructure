#pragma once
#include <iostream>
#include "single_linked_list.h"
using namespace std;

void TestCircleLinkedList();

// 采用dummy node作为头结点，即头结点不存储实际数据
template <typename T>
class CircleLinkedList {
public:
	// 默认构造函数
	CircleLinkedList() { head = new Node<T>; };
	// 有参构造函数
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
		if (first->next!=first) { // 判断是否是最后一个结点
			q = first->next;
			first->next = q->next;
			delete q;
		}
		else {
			head->next = nullptr; // 断开头结点(dummy node)的链接
			delete first; // 删除第一个结点
			break; // 直接跳出循环
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

// 尾插法输入
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
	r->next = head->next; // 指向第一个结点，构成循环
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

// 返回链表尾部指针
template<typename T>
Node<T>* CircleLinkedList<T>::Tail() {
	Node<T> *p = this->GetHead()->next;
	if (p==nullptr) {
		cout << "none list!" << endl;
		return head; // 空表
	}
	while (p!=nullptr) {
		if (p->next == head->next) {
			return p;
		}
		p = p->next;
	}
	return head;
}

// 返回表长
template<typename T>
int CircleLinkedList<T>::Length() {
	Node<T>* p = this->GetHead()->next;
	if (!p) {
		return 0; // 空表返回头指针
	}
	int count=0;
	while (p != this->Tail()) {
		p = p->next;
		count++;
	}
	return count+1;
}

// 插入到pos的位置
template<typename T>
bool CircleLinkedList<T>::Insert(const T& item, const int pos) {
	// 只允许插入至少一个数据的链表，空链表应该使用InputBack()处理输入
	if (this->Length()==0|| pos<0 || pos > this->Length()) {
		return false;
	}
	Node<T>* newNode = new Node<T>(item), *cur, *r;
	if (!newNode)
		return false;
	// 插入第一个位置比较特殊，要更改尾部结点指向
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