#pragma once
#include<iostream>
using namespace std;

void TestSingleLinkedList();

// ������Ķ���
template <typename T>
struct Node {
	T data;
	Node<T> *next;
	// ���캯��
	Node(Node<T>* ptr = nullptr) { next = ptr; };
	Node(const T& item, Node<T>* ptr = nullptr) {
		data = item;
		next = ptr;
	}
};

// ��������Ķ����ʵ��
template <typename T>
class LinkedList
{
public:
	// �޲ι��캯��
	LinkedList() { head = new Node<T>; };
	// �вι��캯��
	LinkedList(const T& item) { head = new Node<T>(item); }; // ��ʼ��ͷ���
	// ��������
	~LinkedList() { Clear(); };
	// ���غ�������ֵ
	LinkedList<T>& operator = (LinkedList<T>& List);
	// �������
	void Clear();
	// ��ȡ������
	int Length() const;
	// ��ȡ����ͷ���
	Node<T>* GetHead() const { return head; };
	// ��������ͷ���
	void SetHead(Node<T>* p) { head = p; };
	// ����ֵ���������������ĵ�һ�����ָ��
	Node<T>* Find(T& item);
	// ��λָ��λ�ã����ظý��ָ��
	Node<T>* Locate(int pos);
	// ��ָ��λ��pos�ϲ������ֵ�Ľ�㣬ʧ���򷵻�false
	bool Insert(T item, int pos);
	// ɾ��ָ������ֵ
	bool Delete(int pos, T& item);
	// ��ȡָ��λ�ý���ֵ
	bool GetData(int pos, T& item);
	// ����ָ��λ�ý���ֵ
	bool SetData(int pos, T& item);
	// �ж������Ƿ�Ϊ��
	bool IsEmpty() const { return head->next == nullptr; };
	// ��������
	void Sort();
	// ǰ�巨����������
	void InputFront(T endTag);
	// β�巨��������
	void InputBack(T endTag);
	// ��ӡ����
	void Print();
	// ��ת����
	void Reverse();
	// �ϲ���������
	void Merge(LinkedList &List);
	// ��������м���
	Node<T>* GetMidNode();

private:
	// ָ��ͷ����ָ��Ϊ˽������
	Node<T> *head; 
};

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList& List) {
	if (*this == List) {
		return *this;
	}
	T value;
	Node<T>* destptr = head, * srcptr = List.head;
	Clear();
	while (srcptr->next != nullptr) {
		value = srcptr->next->data;
		destptr->next = new Node<T>(value);
		destptr = destptr->next;
		srcptr = srcptr->next;
	}
	destptr->next = nullptr;
	return *this;
}

template<typename T>
void LinkedList<T>::Clear() {
	Node<T>* q;
	while (head->next != nullptr) {
		q = head->next; // ��ʱָ��head����һ�����
		head->next = q->next; // �ı�head��һ�����ָ��ͬʱ���������ϴε�ָ��q
		delete q; // ����q���ɾ��������
	}
}

template<typename T>
int LinkedList<T>::Length() const {
	Node<T>* p = head->next; // pָ���һ����㣬ͷ��㲻������
	int count = 0;
	while (p != nullptr) {
		p = p->next;
		count++;
	}
	return count;
}

template<typename T>
Node<T>* LinkedList<T>::Find(T& item) {
	Node<T>* p = head->next;
	while (p != nullptr && p->data!= item) {
		p = p->next;
	}
	return p;
}



template<typename T>
Node<T>* LinkedList<T>::Locate(int pos) {
	if (pos < 0)
		return nullptr;
	Node<T>* p = head->next;
	int k = 0; // pos ���㿪ʼ����
	while (p != nullptr && k < pos) {
		p = p->next;
		k++;
	}
	return p;
}

// �ڵ�pos��λ�ò�����
template<typename T>
bool LinkedList<T>::Insert(T item, int pos) {
	Node<T>* p = Locate(pos-1);
	if (p == nullptr) { // �޲���λ��
		return false;
	}
	Node<T>* newNode = new Node<T>(item); // �����½��
	if (newNode == nullptr) {
		cout << "create new node error" << endl;
		return false;
	}
	newNode->next = p->next;
	p->next = newNode;
	return true;
}

//ɾ��ָ��posλ�õĽ��, ͨ�����ò���item����Ԫ��ֵ
template<typename T>
bool LinkedList<T>::Delete(int pos, T& item) {
	Node<T>* p = Locate(pos-1);
	if (p == nullptr||p->next == nullptr) {
		return false;
	}
	Node<T>* del = p->next;
	p->next = del->next;
	item = del->data;
	delete del;
	return true;
}

// ��ȡָ��λ�ý���ֵ
template<typename T>
bool LinkedList<T>::GetData(int pos, T& item) {
	if (pos < 0) {
		return false;
	}
	Node<T>* p = Locate(pos);
	if (!p) {
		return false;
	}
	else {
		item = p->data;
		return true;
	}
}

// ����ָ��λ�ý���ֵ
template<typename T>
bool LinkedList<T>::SetData(int pos, T& item) {
	if (pos < 0) {
		return false;
	}
	Node<T>* p = Locate(pos);
	if (!p) {
		return false;
	}
	else{
		p->data = item;
		return true;
	}
}


// ��������ð�ݷ�, �Ժ���ϵ�����ٸĽ���..
template<typename T>
void LinkedList<T>::Sort() {
	if (head == nullptr) {
		return;
	}
	for (Node<T>* p1 = head; p1 != nullptr; p1 = p1->next) {
		for (Node<T>*  p2 = p1->next; p2!= nullptr; p2 = p2->next) {
			if (p1->data > p2->data) {
				T temp = p2->data;
				p2->data = p1->data;
				p1->data = temp;
			}
		}
	}
}


// ͷ�巨����������
template<typename T>
void LinkedList<T>::InputFront(T endTag){
	Node<T>* newNode;
	T data;
	Clear();
	cin >> data;
	while (data != endTag) {
		newNode = new Node<T>(data);
		if (newNode == nullptr) {
			return;
		}
		newNode->next = head->next;
		head->next = newNode;
		cin >> data;
	}
}

// β�巨����������
template<typename T>
void LinkedList<T>::InputBack(T endTag) {
	Node<T>* newNode, *r=head;
	T data;
	Clear();
	cin >> data;
	while (data != endTag) {
		newNode = new Node<T>(data);
		if (newNode == nullptr) {
			return;
		}
		r->next = newNode;
		r = newNode;
		cin >> data;
	}
}

//��ӡ����
template<typename T>
void LinkedList<T>::Print() {
	Node<T>* p = head->next;
	while (p)
	{
		if (p->next == nullptr) {
			cout << p->data << endl;
			return;
		}
		cout << p->data << "->";
		p = p->next;
	}
}

// ��ת����
template<typename T>
void LinkedList<T>::Reverse() {
	Node<T>* pre = head->next;
	Node<T>* cur = pre->next;
	Node<T>* next = nullptr;
	head->next->next = nullptr; // ������ĵ�һ������nextָ��ָ���
	while (cur) {
		// ��nextָ��cur������һ����㣻
		// ����cur����nextָ��ָ��pre��
		next = cur->next;
		cur->next = pre;
		// ��pre��cur��㶼���������λ
		pre = cur;
		cur = next;
	}
	// ѭ����������haedָ��ָ��pre����ʱ��pre�Ƿ�ת��ĵ�һ�����
	head->next = pre;
}

// �ϲ���������
//void Merge(LinkedList& List);
template<typename T>
void LinkedList<T>::Merge(LinkedList& List) {
	this->Sort();
	List.Sort();
	Node<T>* p1, * p2, * q, * p;
	p1 = head->next;
	p2 = List.head->next; // ���ָ��������ͷ���
	head->next = nullptr; // ��������ʼ��
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->data >= p2->data) {
			q = p1; 
			p1 = p1->next; // ��p1��ժ��
		}
		else{
			q = p2;
			p2 = p2->next; // ��p2��ժ��
		}
		q->next = head->next;
		head->next = q; // �������������ͷ,ͷ��
	}
	p = (p1 != nullptr) ? p1 : p2;
	// ������ʣ�ಿ��
	while (p != nullptr) {
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
	this->Sort();
}

// ��������м���,���ÿ���ָ�뷨
template<typename T>
Node<T>* LinkedList<T>::GetMidNode() {
	Node<T>* fast = head, * slow = head;
	while (fast) {
		if (fast->next) { 
			fast = fast->next->next; // һ����������
		}
		else{
			break;
		}
		slow = slow->next; // һ����һ��
	}
	return slow; // ������ָ�������ˣ���ָ��Ӧ��ͣ���м�
}