#pragma once
#include <iostream>

using namespace std;

//Tries树，又称键树，字典树或查找树。用来存储字符串的一种树形结构。它有三个基本性质：
//1 根节点不包含字符，除根节点外每一个节点都只包含一个字符。
//2 从根节点到某个一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
//3 每个节点的子节点包含的字符都不相同

//用于统计单词的频率，用于快速查找。比如字典查询、单词的自动补全和自动提示就可以使用类似的结构

//另外一些应用字典树解决的问题：
//1 有一个1G大小的一个文件，里面每一行是一个词，词的大小不超过16字节，内存限制大小是1M。返回频数最高的100个词。
//2 1000万字符串，其中有些是重复的，需要把重复的全部去掉，保留没有重复的字符串。请怎么设计和实现？
//3 一个文本文件，大约有一万行，每行一个词，要求统计出其中最频繁出现的前10个词，请给出思想，给出时间复杂度分析。
const int SIZE = 26;

void TestTrieTree();

struct TrieTreeNode {
	char val;
	bool isEnd;  // 布尔变量，用来判断该结点是不是一个字符串的最后一个字符
	int childCnt; // 孩子计数
	TrieTreeNode* child[SIZE]; // 存储孩子结点的结构体指针数组
	TrieTreeNode(char c) :val(c),isEnd(false),childCnt(0) {
		memset(child, 0, sizeof(child)); 
	}
};

class TrieTree
{
public:
	TrieTree() { root = new TrieTreeNode('*'); }; // 初始化根结点
	~TrieTree() { Clear(root); };
	void BuildTree(const char* words[], int n); //使用字符串数组建立树，n为数组长度
	void Insert(const char* word); // word是待插入字符串
	bool Find(const char* word);  // 查找该串是否存在于字典树中
	bool Delete(TrieTreeNode* treeNode, const char* word, int pos, int n);
	void PreOrderTraverse(TrieTreeNode* treeNode);  // 前序遍历
	void PostOrderTraverse(TrieTreeNode* treeNode); // 后序遍历
	void LevelOrderTraverse(); // 层次遍历
	void Clear(TrieTreeNode* treeNode);  // 清除函数
	void Print();  // 打印字符集
	TrieTreeNode* GetRoot() { return root; }  // 获取根结点
private:
	TrieTreeNode* root;
};
