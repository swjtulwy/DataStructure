#include "binary_search_tree.h"

// ≤‚ ‘BST
void TestBST() {
	BinarySearchTree<int>* B = new BinarySearchTree<int>;
	vector<int> v = { 9, 4, 17,6, 11, 5, 13 };
	B->BuildTree(v);
	cout << "we build a tree from data: 9 4 17 6 11 5 13" << endl;
	cout<< "the tree's root: " << B->GetRoot()->data << endl;
	Node<int>* p1 = B->GetRoot()->lchild->rchild;
	Node<int>* p2 = B->GetRoot()->rchild->lchild;
	cout << "the precursor of node whose data is 6: ";
	cout << B->Precursor(p1)->data << endl;
	cout << "the successor of node whose data is 6: ";
	cout << B->Successor(p1)->data << endl;
	cout << "the precursor of node whose data is 11: ";
	cout << B->Precursor(p2)->data << endl;
	cout << "the successor of node whose data is 11: ";
	cout << B->Successor(p2)->data << endl;
	cout << "PreOrderTraverse: ";
	B->PreOrderTraverse(B->GetRoot());
	cout << endl;
	cout << "InOrderTraverse: ";
	B->InOrderTraverse(B->GetRoot());
	cout << endl;
	cout << "PostOrderTraverse: ";
	B->PostOrderTraverse(B->GetRoot());
	cout << endl;
	cout << "LevelOrderTraverse: ";
	B->LevelOrderTraverse();

}