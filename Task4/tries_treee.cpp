#include "tries_tree.h"
#include <queue>
#include <string>

void TestTrieTree() {
	const char* str[] = {"love","peace","school","mom","dad","rather","hate","stupid"};
	const char* strtest[] = { "a", "ab", "ac","ad","abc","acb","ada", "acd","adc","abd"};
	const char* strtest1[] = {"a", "b","c","ab","abc","acd"};
	TrieTree *t = new TrieTree;
	t->BuildTree(strtest1, 6);
	t->PreOrderTraverse(t->GetRoot());
	cout << "find acd: " << t->Find("acd") << endl;
	t->Delete(t->GetRoot(), "a", 0, 1);
	t->PostOrderTraverse(t->GetRoot());
	cout << endl;
	t->Insert("bac");
	t->LevelOrderTraverse();

}

// 使用字符串数组建立字典树
void TrieTree::BuildTree(const char* words[], int n) {
	for (int i = 0; i < n; i++) {
		Insert(words[i]);
	}
}

// 插入字符串
void TrieTree::Insert(const char* word) {
	TrieTreeNode* p = root;
	for (int i = 0; i < strlen(word); i++) {
		if (p->child[word[i] - 'a'] == 0) {
			// 存放一个新的结点的指针，该结点用word[i]初始化
			p->child[word[i] - 'a'] = new TrieTreeNode(word[i]); 
			p->childCnt++;  // 孩子计数增一
		}
		p = p->child[word[i] - 'a']; // 进入子结点
	}
	p->isEnd = true; //循环完毕，设置终点标记
}

// 查找字符串
bool TrieTree::Find(const char* word) {
	TrieTreeNode* p = root;
	for (int i = 0; i < strlen(word); i++) {
		if (p->child[word[i] - 'a'] == NULL) {
			return false;
		}
		p = p->child[word[i] - 'a']; // 进入子结点
	}
	// 循环结束，正常应该到了最终字符
	return p->isEnd;
}


// 递归删除
bool TrieTree::Delete(TrieTreeNode* treeNode, const char* word, int pos, int n) {
	if (pos == n) {
		treeNode->isEnd = false;  // 将该结点状态改变为非终止结点
		return treeNode->childCnt == 0; // 如果这最后一个结点是叶子结点，则需要删除
	}
	if (treeNode->child[word[pos] - 'a'] == NULL) {
		return false; //中途为空说明没有该单词，直接返回false
	}
	// 子结点返回true，需要删除
	if (Delete(treeNode->child[word[pos] - 'a'], word, pos + 1, n)) { // 字符位置pos加一
		delete treeNode->child[word[pos] - 'a'];   // 释放结点指针指向内存
		treeNode->child[word[pos] - 'a'] = NULL;   // 指针指向空
		// 当子结点数为0且状态为非终止结点
		if (--treeNode->childCnt == 0 && treeNode->isEnd == false) {
			return true;
		}
	}
	return false;
}

void TrieTree::Clear(TrieTreeNode* treeNode) {
	if (treeNode != NULL) {
		for (int i = 0; i < SIZE; i++) {
			Clear(treeNode->child[i]);
		}
		delete treeNode; // 释放指向的内存
	}
	treeNode = NULL; // 指向为空
}


// 前序遍历,递归形式
void TrieTree::PreOrderTraverse(TrieTreeNode* treeNode) {
	if (treeNode != NULL) {
		cout << treeNode->val << "(" << treeNode->childCnt << ") ";
		for (int i = 0; i < SIZE; i++) {
			PreOrderTraverse(treeNode->child[i]);
		}
	}
}

// 后序遍历,递归形式
void TrieTree::PostOrderTraverse(TrieTreeNode* treeNode) {
	if (treeNode != NULL) {
		for (int i = 0; i < SIZE; i++) {
			PostOrderTraverse(treeNode->child[i]);
		}
		cout << treeNode->val << "(" << treeNode->childCnt << ") ";
	}
}

// 层次遍历
void TrieTree::LevelOrderTraverse() {
	TrieTreeNode* treeNode = this->GetRoot();
	if (treeNode == NULL) {
		return;
	}
	queue<TrieTreeNode*> st;
	st.push(treeNode);
	while (!st.empty()) {
		TrieTreeNode* p = st.front();
		cout << p->val << "(" << p->childCnt << ") ";  // visit部分,可替换其他函数
		for (int i = 0; i < SIZE; i++) {
			if (p->child[i] != NULL) {
				st.push(p->child[i]);
			}
		}
		st.pop();
	}
	cout << endl;
}