#pragma once
#include "hash_table.h"

void TestLRUCache();

// ˫������+HashMap��ʵ��LRU���������㷨

// ��ʾ�����Ľ��,��ֵ�������ͱ�ʾ
struct CacheNode
{
	unsigned int key;
	unsigned int value;
	CacheNode* prev, * next;
	CacheNode() :prev(nullptr), next(nullptr) {}
	CacheNode(unsigned int k, unsigned int v) :key(k),value(v),prev(nullptr),next(nullptr){}
};


// ��
class LRUCache
{
public:
	// ��capacity��ʼ�������������
	LRUCache(unsigned int capacity) {
		m_size = capacity;
		m_head = nullptr;
		m_tail = nullptr;
	};
	~LRUCache();
	// ֱ��ͨ���ж�Map�Ƿ���keyֵ���ɣ�������ҵ�key���򷵻ض�Ӧ��value�����򷵻�-1;
	int GetCache(int key);
	// �����ǰ��keyֵ��Ӧ�Ľڵ��Ѿ����ڣ�������ڵ�ȡ����������ɾ���ڵ�������ԭ�е�λ�ã�
	// ����ͷ������ýڵ㣻����ڵ㲻���ڽڵ��У����ʱ����Ҫ�������ͷ�������½ڵ㣬
	// �����½ڵ���ܵ���������������������������������Ҫɾ������β���Ľڵ㡣
	void SetCache(int key, int value);
	// ���������˫������β��ɾ��
	void Remove(CacheNode* node);
	// �������뵽˫�������ͷ��
	void SetHead(CacheNode* node);
	void Print();
private:
	CacheNode* m_head, * m_tail;   // �������ͷβָ��
	unsigned int m_size;  // ��¼�����������
	HashTable<int,CacheNode*> m_map;  // ������ѯ�����л������Ϣ��Map
};

