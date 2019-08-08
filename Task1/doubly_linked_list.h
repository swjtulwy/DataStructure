#pragma once
#include<iostream>

using namespace std;

void TestDoublyLinkedList();

template<typename T>
struct DNode
{
	T data;
	DNode<T>* prev;
	DNode<T>* next;
	DNode() :prev(nullptr),next(nullptr){};
	DNode(T& item) :data(item), prev(nullptr), next(nullptr) {};
};

template<typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList() :head(new DNode<T>){};
	DoublyLinkedList(const T& item) :head(new DNode<T>(item)) {};
	void InputBack(const T endTag);
	void Clear();
	void Print();
	DNode<T>* Locate(const int pos);
	int Length();
	bool Insert(T item, const int pos);
	bool Delete(const int pos, T& item);
	~DoublyLinkedList() { Clear(); };

private:
	DNode<T>* head;
};

// 后插法输入
template<typename T>
void DoublyLinkedList<T>::InputBack(const T endTag) {
	DNode<T>* newNode, * r = head;
	T data;
	cout << "please input: ";
	cin >> data;
	while (data!=endTag) {
		newNode = new DNode<T>(data);
		if (newNode == nullptr) {
			return;
		}
		r->next = newNode;
		newNode->prev = r;
		r = r->next;
		cin >> data;
	}
}

// 清空
template<typename T>
void DoublyLinkedList<T>::Clear() {
	DNode <T>* q;
	while (head->next!=nullptr){
		q = head->next; 
		if (q->next != nullptr) { // 中间结点
			head->next = q->next;
			q->next->prev = head;
			delete q;
		}
		else{
			head->next = nullptr; // 剩最后一个结点了，尾部指向空
			delete q;
		}
	}
}

// 输出
template<typename T>
void DoublyLinkedList<T>::Print() {
	DNode<T>* p = head->next;
	if (!p) {
		cout << "none list!" << endl;
		return;
	}
	cout << "head<-->";
	while (p){
		if (!p->next) {
			cout << p->data<<endl;
		}
		else{
			cout << p->data << "<-->";
		}
		p = p->next;
	}
}

// 获取长度
template<typename T>
int DoublyLinkedList<T>::Length() {
	int count = 0;
	DNode<T>* p = head->next;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}

template <typename T>
DNode<T>* DoublyLinkedList<T>::Locate(const int pos) {
	if (pos<0 || pos>this->Length() - 1) {
		return head;
	}
	DNode<T>* p = head->next;
	int count = 0;
	while (count<pos){
		p = p->next;
		count++;
	}
	return p;
}

template<typename T>
bool DoublyLinkedList<T>::Insert(T item, const int pos) {
	if (pos<0 || pos>this->Length() || !head->next) { // 允许在最后面插,不能插入空链表
		return false;
	}
	DNode<T>* newNode=new DNode<T>(item);
	if (pos == 0) { // 插在头部
		newNode->next = head->next;
		newNode->prev = head;
		head->next = newNode;
		newNode->next->prev = newNode;
	}
	else{
		DNode<T>* cur = this->Locate(pos - 1);
		newNode->next = cur->next;
		newNode->prev = cur;
		cur->next = newNode;
		if (!newNode->next) {
			return true;
		}
		newNode->next->prev = newNode;
	}
	return true;
}


template<typename T>
bool DoublyLinkedList<T>::Delete(const int pos, T& item) {
	if (pos<0 || pos>this->Length()-1 || !head->next) { 
		return false;
	}
	DNode<T>* q = this->Locate(pos);
	item = q->data;
	if (!q->next) {
		q->prev->next = nullptr;
	}
	else{
		q->prev->next = q->next;
		q->next->prev = q->prev;
	}
	delete q;
	return true;
}