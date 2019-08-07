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
	~DoublyLinkedList() { Clear(); };

private:
	DNode<T>* head;
};

// ��巨����
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

// ���
template<typename T>
void DoublyLinkedList<T>::Clear() {
	DNode <T>* q;
	while (head->next!=nullptr){
		q = head->next; 
		if (q->next != nullptr) { // �м���
			head->next = q->next;
			q->next->prev = head;
			delete q;
		}
		else{
			head->next = nullptr; // ʣ���һ������ˣ�β��ָ���
			delete q;
		}
	}
}

// ���
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


