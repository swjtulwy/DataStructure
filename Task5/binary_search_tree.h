#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// �����������bianry search tree���ֳƶ���������(binary sort tree)�����������
// ���BST

void TestBST();

// ����������Ľ��
template<typename T>
struct Node
{
	T data;
	Node<T>* lchild;
	Node<T>* rchild;
	Node() :lchild(nullptr),rchild(nullptr){}
	Node(const T& val) :data(val), lchild(nullptr), rchild(nullptr) {}
};


// �����������������
template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() :m_root(nullptr), m_length(0) {}
	~BinarySearchTree() { Clear(); }

	Node<T>* GetRoot() { return m_root; }  // ��ȡ�����
	
	void BuildTree(vector<T>& v); // ������
	void Clear(Node<T>* node);  // �����
	void Insert(const T& val);  // ������

	bool Delete(const T& val); // ɾ�����
	bool IsEmpty() { return m_root == nullptr; }   // �п�
	bool Find(const T& val);  // ����ָ�����
	int GetSize() { return m_length; }  // ��ȡ�������ݵĳ���

	void ClearTree() {   // �������������
		if (m_root == nullptr) {
			return;
		}
		Clear(m_root);
		m_root = nullptr;
	}

	Node<T>* Precursor(Node<T>* cur);  // ����ǰ�����
	Node<T>* Successor(Node<T>* cur);  // ���Һ�̽��
	Node<T>* LeftMaxNode(Node<T>* cur);  //  ���һ������������������
	Node<T>* RightMinNode(Node<T>* cur); //  ���һ���������������С�Ľ��
	Node<T>* GetParent(Node<T>* cur);   // ���һ�����ĸ����
	Node<T>* GetMin();   // ���������С���
	Node<T>* GetMax();    // ������������

	void PreOrderTraverse(Node<T>* treeNode);  // ǰ�����
	void InOrderTraverse(Node<T>* treeNode);  // �������
	void PostOrderTraverse(Node<T>* treeNode);  // �������
	void LevelOrderTraverse();  // ��α���



private:
	Node<T>* m_root;   // �����
	int m_length;  // ���н�����
};


// ͨ��ѭ��������
template<typename T>
void BinarySearchTree<T>::BuildTree(vector<T>& v) {
	for (int i = 0; i < v.size(); i++) {
		Insert(v[i]);
	}
}


// ����һ���½��
template<typename T>
void BinarySearchTree<T>::Insert(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	if (IsEmpty()) {  // ��Ϊ�����½��Ϊ�����
		m_root = newNode;
		m_length++;
	}
	else{
		Node<T>* p = m_root;
		while (p) { 
			if (val < p->data) {   // ���뵽������
				if (!p->lchild) {
					p->lchild = newNode;
					m_length++;
					return;
				}
				p = p->lchild; 
			}
			else {
				if (!p->rchild) {   // ���뵽������
					p->rchild = newNode;
					m_length++;
					return;
				}
				p = p->rchild; 
			}
		}
	}
}

// ���ҽ��
template <typename T>
bool BinarySearchTree<T>::Find(const T& val) {
	Node<T>* p = GetRoot();
	while (p!=nullptr) {
		if (val == p->data) {
			return true;
		}
		else if(val<p->data){
			p = p->lchild;
		}
		else{
			p = p->rchild;
		}
	}
	return false; // �������������ʧ��
}

// ɾ��ָ�����
// 1.Ҷ�ӽ��ֱ��ɾ��
// 2.ֻ��һ�����ӽ�㣬ֱ���ú��ӽ���滻��ǰ���
// 3.Ҫɾ���Ľ������������������ ����һ��������ɾ����㣺����������СԪ�� ���� �����������Ԫ��

template<typename T>
bool BinarySearchTree<T>::Delete(const T& val) {
	Node<T>* p = m_root,*parent = m_root;  // p denote the node to delete, parent is p's parent
	bool hand = true;
	while (p != nullptr) {
		if (val == p->data) {  
			// find the node whose data equal to val
			if (p == m_root) { // if the node is just root
				delete p;
				m_root = nullptr;  // delete root
				return true;
			}
			if (p->lchild == nullptr) {     // current node's left tree is null
				parent->lchild = hand ? p->rchild : parent->lchild;
				parent->rchild = hand ? parent->rchild : p->rchild;
				delete p;
			}
			else if(p->rchild == nullptr){  //current node's right tree is null
				parent->lchild = hand ? p->lchild : parent->lchild;
				parent->rchild = hand ? parent->rchild : p->lchild;
				delete p;
			}
			else{               //current node's left & right tree are all not null
				// use the max node of current node's left tree to swap current node			
				Node<T>* lmax = p->lchild,*tmp = p;
				while (lmax->rchild) {
					tmp = lmax;
					lmax = lmax->rchild;
				}
				p->data = lmax->data;
				if (tmp == p) {
					tmp->lchild = lmax->lchild;
				}
				else{
					tmp->rchild = lmax->lchild;
				}
				delete lmax;
			}
			return true;
		}
		else if (val < p->data) {  // find p in the left tree
			parent = p;
			hand = true; // denote p is left child of parent
			p = p->lchild;
		}
		else {   // find p in the right tree
			parent = p;
			hand = false; // denote p is right child of parent
			p = p->rchild;
		}
	}
	return false;
}

template<typename T>
Node<T>* BinarySearchTree<T>::GetParent(Node<T>* cur) {
	if (cur == m_root) {
		return nullptr;
	}
	// ˫ָ�������¼
	Node<T>* ptr = m_root;
	Node<T>* ptf = ptr;
	while (ptr) {
		if (ptr->data == cur->data) {
			return ptf;
		}
		if (ptr->data > cur->data) {
			ptf = ptr;
			ptr = ptr->lchild;
		}
		else{
			ptf = ptr;
			ptr = ptr->rchild;
		}
	}
}

// �������������ұߵĽ��
template<typename T>
Node<T>* BinarySearchTree<T>::LeftMaxNode(Node<T>* cur) {
	if (!cur->lchild) {
		cout << "no left child!, return nullptr" << endl;
		return nullptr;
	}
	Node<T>* p = cur->lchild;
	while (p->rchild) {
		p = p->rchild;
	}
	return p;
}

// ������������ߵĽ��
template<typename T>
Node<T>* BinarySearchTree<T>::RightMinNode(Node<T>* cur) {
	if (!cur->rchild) {
		cout << "no right child!, return nullptr" << endl;
		return nullptr;
	}
	Node<T>* p = cur->rchild;
	while (p->lchild) {
		p = p->lchild;
	}
	return p;
}

// Ѱ��һ������ǰ����㣨�����ϵ�ǰ����
template<typename T>
Node<T>* BinarySearchTree<T>::Precursor(Node<T>* cur) {
	if (cur == GetMin()) {
		cout << "no precursor!" << endl;
		return nullptr;
	}
	// ����������������������������㣬���򷵻ص�һ�����ڵ�ǰ�������Ƚ��
	if (cur->lchild) {
		return LeftMaxNode(cur);
	}
	else{
		Node<T>* res = GetParent(cur);
		while (cur->data < res->data) {
			res = GetParent(res);
		}
		return res;
	}
}

// Ѱ��һ�����ĺ�̽��
template<typename T>
Node<T>* BinarySearchTree<T>::Successor(Node<T>* cur) {
	if (cur == GetMax()) {
		cout << "no successor!" << endl;
		return nullptr;
	}
	if (cur->rchild) {
		return RightMinNode(cur);
	}
	else{
		Node<T>* res = GetParent(cur);
		while (cur->data > res->data) {
			res = GetParent(res);
		}
		return res;
	}
}

// �����������µĽ��
template<typename T>
Node<T>* BinarySearchTree<T>::GetMin() {
	Node<T>* p = m_root;
	if (!m_root->lchild) {
		return m_root;
	}
	while (p->lchild) {
		p = p->lchild;
	}
	return p;
}

// �����������½��
template<typename T>
Node<T>* BinarySearchTree<T>::GetMax() {
	Node<T>* p = m_root;
	if (!m_root->rchild) {
		return m_root;
	}
	while (p->rchild) {
		p = p->rchild;
	}
	return p;
}

// ��ն�����,�ݹ�
template<typename T>
void BinarySearchTree<T>::Clear(Node<T>* node) {
	if (node->lchild) {
		Clear(node->lchild);
		node->lchild = nullptr;
	}
	if (node->rchild) {
		Clear(node->rchild);
		node->rchild = nullptr;
	}
	delete node;
	node = nullptr;
	m_length--;
}

// ǰ�����
template<typename T>
void BinarySearchTree<T>::PreOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	cout << treeNode->data << " ";  // ǰ��������������ǰ��㣬��ȥ������������������
	PreOrderTraverse(treeNode->lchild);
	PreOrderTraverse(treeNode->rchild);
}

// �������
template<typename T>
void BinarySearchTree<T>::InOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	InOrderTraverse(treeNode->lchild);
	cout << treeNode->data << " ";  // �����������ȥ���������������ǰ��㣬����ȥ������
	InOrderTraverse(treeNode->rchild);
}

// �������
template<typename T>
void BinarySearchTree<T>::PostOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	PostOrderTraverse(treeNode->lchild);
	PostOrderTraverse(treeNode->rchild);
	cout << treeNode->data << " ";  // �����������ȥ����������ȥ�����������������ǰ���
}

// ��α���
template<typename T>
void BinarySearchTree<T>::LevelOrderTraverse() {
	if (IsEmpty()) {
		return;
	}
	queue<Node<T>*> Q;
	Q.push(m_root);
	while (!Q.empty()) {
		Node<T>* cur = Q.front();
		cout << cur->data << " ";
		if (cur->lchild) {
			Q.push(cur->lchild);
		}
		if (cur->rchild) {
			Q.push(cur->rchild);
		}
		Q.pop();
	}
	cout << endl;
}
