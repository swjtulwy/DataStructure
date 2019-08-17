#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// 二叉查找树（bianry search tree）又称二叉排序树(binary sort tree)或二叉搜索树
// 简称BST

void TestBST();

// 定义二叉树的结点
template<typename T>
struct Node
{
	T data;
	Node<T>* lchild;
	Node<T>* rchild;
	Node() :lchild(nullptr),rchild(nullptr){}
	Node(const T& val) :data(val), lchild(nullptr), rchild(nullptr) {}
};


// 定义二叉排序树的类
template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() :m_root(nullptr), m_length(0) {}
	~BinarySearchTree() { Clear(); }

	Node<T>* GetRoot() { return m_root; }  // 获取根结点
	
	void BuildTree(vector<T>& v); // 建立树
	void Clear(Node<T>* node);  // 清空树
	void Insert(const T& val);  // 插入结点

	bool Delete(const T& val); // 删除结点
	bool IsEmpty() { return m_root == nullptr; }   // 判空
	bool Find(const T& val);  // 查找指定结点
	int GetSize() { return m_length; }  // 获取树中数据的长度

	void ClearTree() {   // 清空整个二叉树
		if (m_root == nullptr) {
			return;
		}
		Clear(m_root);
		m_root = nullptr;
	}

	Node<T>* Precursor(Node<T>* cur);  // 查找前驱结点
	Node<T>* Successor(Node<T>* cur);  // 查找后继结点
	Node<T>* LeftMaxNode(Node<T>* cur);  //  获得一个结点左子树中最大结点
	Node<T>* RightMinNode(Node<T>* cur); //  获得一个结点右子树中最小的结点
	Node<T>* GetParent(Node<T>* cur);   // 获得一个结点的父结点
	Node<T>* GetMin();   // 获得树中最小结点
	Node<T>* GetMax();    // 获得树中最大结点

	void PreOrderTraverse(Node<T>* treeNode);  // 前序遍历
	void InOrderTraverse(Node<T>* treeNode);  // 中序遍历
	void PostOrderTraverse(Node<T>* treeNode);  // 后序遍历
	void LevelOrderTraverse();  // 层次遍历



private:
	Node<T>* m_root;   // 根结点
	int m_length;  // 树中结点个数
};


// 通过循环构建树
template<typename T>
void BinarySearchTree<T>::BuildTree(vector<T>& v) {
	for (int i = 0; i < v.size(); i++) {
		Insert(v[i]);
	}
}


// 插入一个新结点
template<typename T>
void BinarySearchTree<T>::Insert(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	if (IsEmpty()) {  // 树为空则新结点为根结点
		m_root = newNode;
		m_length++;
	}
	else{
		Node<T>* p = m_root;
		while (p) { 
			if (val < p->data) {   // 插入到左子树
				if (!p->lchild) {
					p->lchild = newNode;
					m_length++;
					return;
				}
				p = p->lchild; 
			}
			else {
				if (!p->rchild) {   // 插入到右子树
					p->rchild = newNode;
					m_length++;
					return;
				}
				p = p->rchild; 
			}
		}
	}
}

// 查找结点
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
	return false; // 其他情况，查找失败
}

// 删除指定结点
// 1.叶子结点直接删除
// 2.只有一个孩子结点，直接用孩子结点替换当前结点
// 3.要删除的结点有左、右两棵子树： 用另一结点替代被删除结点：右子树的最小元素 或者 左子树的最大元素

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
	// 双指针遍历记录
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

// 即最左子树最右边的结点
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

// 即右子树最左边的结点
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

// 寻找一个结点的前驱结点（排序上的前驱）
template<typename T>
Node<T>* BinarySearchTree<T>::Precursor(Node<T>* cur) {
	if (cur == GetMin()) {
		cout << "no precursor!" << endl;
		return nullptr;
	}
	// 若存在左子树，返回左子树最大结点，否则返回第一个大于当前结点的祖先结点
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

// 寻找一个结点的后继结点
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

// 即树的最左下的结点
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

// 即树的最右下结点
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

// 清空二叉树,递归
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

// 前序遍历
template<typename T>
void BinarySearchTree<T>::PreOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	cout << treeNode->data << " ";  // 前序遍历，先输出当前结点，再去左子树，接着右子树
	PreOrderTraverse(treeNode->lchild);
	PreOrderTraverse(treeNode->rchild);
}

// 中序遍历
template<typename T>
void BinarySearchTree<T>::InOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	InOrderTraverse(treeNode->lchild);
	cout << treeNode->data << " ";  // 中序遍历，先去左子树，再输出当前结点，接着去右子树
	InOrderTraverse(treeNode->rchild);
}

// 后序遍历
template<typename T>
void BinarySearchTree<T>::PostOrderTraverse(Node<T>* treeNode) {
	if (!treeNode) {
		return;
	}
	PostOrderTraverse(treeNode->lchild);
	PostOrderTraverse(treeNode->rchild);
	cout << treeNode->data << " ";  // 后序遍历，先去左子树，再去右子树，接着输出当前结点
}

// 层次遍历
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
