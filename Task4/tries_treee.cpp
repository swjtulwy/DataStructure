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

// ʹ���ַ������齨���ֵ���
void TrieTree::BuildTree(const char* words[], int n) {
	for (int i = 0; i < n; i++) {
		Insert(words[i]);
	}
}

// �����ַ���
void TrieTree::Insert(const char* word) {
	TrieTreeNode* p = root;
	for (int i = 0; i < strlen(word); i++) {
		if (p->child[word[i] - 'a'] == 0) {
			// ���һ���µĽ���ָ�룬�ý����word[i]��ʼ��
			p->child[word[i] - 'a'] = new TrieTreeNode(word[i]); 
			p->childCnt++;  // ���Ӽ�����һ
		}
		p = p->child[word[i] - 'a']; // �����ӽ��
	}
	p->isEnd = true; //ѭ����ϣ������յ���
}

// �����ַ���
bool TrieTree::Find(const char* word) {
	TrieTreeNode* p = root;
	for (int i = 0; i < strlen(word); i++) {
		if (p->child[word[i] - 'a'] == NULL) {
			return false;
		}
		p = p->child[word[i] - 'a']; // �����ӽ��
	}
	// ѭ������������Ӧ�õ��������ַ�
	return p->isEnd;
}


// �ݹ�ɾ��
bool TrieTree::Delete(TrieTreeNode* treeNode, const char* word, int pos, int n) {
	if (pos == n) {
		treeNode->isEnd = false;  // ���ý��״̬�ı�Ϊ����ֹ���
		return treeNode->childCnt == 0; // ��������һ�������Ҷ�ӽ�㣬����Ҫɾ��
	}
	if (treeNode->child[word[pos] - 'a'] == NULL) {
		return false; //��;Ϊ��˵��û�иõ��ʣ�ֱ�ӷ���false
	}
	// �ӽ�㷵��true����Ҫɾ��
	if (Delete(treeNode->child[word[pos] - 'a'], word, pos + 1, n)) { // �ַ�λ��pos��һ
		delete treeNode->child[word[pos] - 'a'];   // �ͷŽ��ָ��ָ���ڴ�
		treeNode->child[word[pos] - 'a'] = NULL;   // ָ��ָ���
		// ���ӽ����Ϊ0��״̬Ϊ����ֹ���
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
		delete treeNode; // �ͷ�ָ����ڴ�
	}
	treeNode = NULL; // ָ��Ϊ��
}


// ǰ�����,�ݹ���ʽ
void TrieTree::PreOrderTraverse(TrieTreeNode* treeNode) {
	if (treeNode != NULL) {
		cout << treeNode->val << "(" << treeNode->childCnt << ") ";
		for (int i = 0; i < SIZE; i++) {
			PreOrderTraverse(treeNode->child[i]);
		}
	}
}

// �������,�ݹ���ʽ
void TrieTree::PostOrderTraverse(TrieTreeNode* treeNode) {
	if (treeNode != NULL) {
		for (int i = 0; i < SIZE; i++) {
			PostOrderTraverse(treeNode->child[i]);
		}
		cout << treeNode->val << "(" << treeNode->childCnt << ") ";
	}
}

// ��α���
void TrieTree::LevelOrderTraverse() {
	TrieTreeNode* treeNode = this->GetRoot();
	if (treeNode == NULL) {
		return;
	}
	queue<TrieTreeNode*> st;
	st.push(treeNode);
	while (!st.empty()) {
		TrieTreeNode* p = st.front();
		cout << p->val << "(" << p->childCnt << ") ";  // visit����,���滻��������
		for (int i = 0; i < SIZE; i++) {
			if (p->child[i] != NULL) {
				st.push(p->child[i]);
			}
		}
		st.pop();
	}
	cout << endl;
}