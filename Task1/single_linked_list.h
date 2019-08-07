#pragma once
#include<iostream>
using namespace std;

void TestSingleLinkedList();

// 链表结点的定义
template <typename T>
struct Node {
	T data;
	Node<T> *next;
	// 构造函数
	Node(Node<T>* ptr = nullptr) { next = ptr; };
	Node(const T& item, Node<T>* ptr = nullptr) {
		data = item;
		next = ptr;
	}
};

// 单链表类的定义和实现
template <typename T>
class LinkedList
{
public:
	// 无参构造函数
	LinkedList() { head = new Node<T>; };
	// 有参构造函数
	LinkedList(const T& item) { head = new Node<T>(item); }; // 初始化头结点
	// 析构函数
	~LinkedList() { Clear(); };
	// 重载函数：赋值
	LinkedList<T>& operator = (LinkedList<T>& List);
	// 链表清空
	void Clear();
	// 获取链表长度
	int Length() const;
	// 获取链表头结点
	Node<T>* GetHead() const { return head; };
	// 设置链表头结点
	void SetHead(Node<T>* p) { head = p; };
	// 查找值，返回满足条件的第一个结点指针
	Node<T>* Find(T& item);
	// 定位指定位置，返回该结点指针
	Node<T>* Locate(int pos);
	// 在指定位置pos上插入给定值的结点，失败则返回false
	bool Insert(T item, int pos);
	// 删除指定结点的值
	bool Delete(int pos, T& item);
	// 获取指定位置结点的值
	bool GetData(int pos, T& item);
	// 设置指定位置结点的值
	bool SetData(int pos, T& item);
	// 判断链表是否为空
	bool IsEmpty() const { return head->next == nullptr; };
	// 链表排序
	void Sort();
	// 前插法建立单链表
	void InputFront(T endTag);
	// 尾插法建立链表
	void InputBack(T endTag);
	// 打印链表
	void Print();
	// 翻转链表
	void Reverse();
	// 合并有序链表
	void Merge(LinkedList &List);
	// 求链表的中间结点
	Node<T>* GetMidNode();

private:
	// 指向头结点的指针为私有属性
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
		q = head->next; // 临时指向head的下一个结点
		head->next = q->next; // 改变head下一个结点指向，同时还保留了上次的指向q
		delete q; // 利用q逐个删除链表结点
	}
}

template<typename T>
int LinkedList<T>::Length() const {
	Node<T>* p = head->next; // p指向第一个结点，头结点不算在内
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
	int k = 0; // pos 从零开始计数
	while (p != nullptr && k < pos) {
		p = p->next;
		k++;
	}
	return p;
}

// 在第pos个位置插入结点
template<typename T>
bool LinkedList<T>::Insert(T item, int pos) {
	Node<T>* p = Locate(pos-1);
	if (p == nullptr) { // 无插入位置
		return false;
	}
	Node<T>* newNode = new Node<T>(item); // 创建新结点
	if (newNode == nullptr) {
		cout << "create new node error" << endl;
		return false;
	}
	newNode->next = p->next;
	p->next = newNode;
	return true;
}

//删除指定pos位置的结点, 通过引用参数item返回元素值
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

// 获取指定位置结点的值
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

// 设置指定位置结点的值
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


// 链表排序，冒泡法, 以后联系排序再改进吧..
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


// 头插法建立单链表
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

// 尾插法建立单链表
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

//打印链表
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

// 翻转链表
template<typename T>
void LinkedList<T>::Reverse() {
	Node<T>* pre = head->next;
	Node<T>* cur = pre->next;
	Node<T>* next = nullptr;
	head->next->next = nullptr; // 让链表的第一个结点的next指针指向空
	while (cur) {
		// 让next指向cur结点的下一个结点；
		// 再让cur结点的next指针指向pre。
		next = cur->next;
		cur->next = pre;
		// 让pre、cur结点都继续向后移位
		pre = cur;
		cur = next;
	}
	// 循环结束，让haed指针指向pre，此时的pre是翻转后的第一个结点
	head->next = pre;
}

// 合并有序链表
//void Merge(LinkedList& List);
template<typename T>
void LinkedList<T>::Merge(LinkedList& List) {
	this->Sort();
	List.Sort();
	Node<T>* p1, * p2, * q, * p;
	p1 = head->next;
	p2 = List.head->next; // 检测指针跳过表头结点
	head->next = nullptr; // 结果链表初始化
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->data >= p2->data) {
			q = p1; 
			p1 = p1->next; // 从p1中摘下
		}
		else{
			q = p2;
			p2 = p2->next; // 从p2中摘下
		}
		q->next = head->next;
		head->next = q; // 放入结果链表的链头,头插
	}
	p = (p1 != nullptr) ? p1 : p2;
	// 处理完剩余部分
	while (p != nullptr) {
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
	this->Sort();
}

// 求链表的中间结点,采用快慢指针法
template<typename T>
Node<T>* LinkedList<T>::GetMidNode() {
	Node<T>* fast = head, * slow = head;
	while (fast) {
		if (fast->next) { 
			fast = fast->next->next; // 一次跳两步步
		}
		else{
			break;
		}
		slow = slow->next; // 一次跳一步
	}
	return slow; // 两步的指针跳完了，慢指针应当停在中间
}