#pragma once
#include "hash_table.h"

void TestLRUCache();

// 双向链表+HashMap来实现LRU缓存块调度算法

// 表示缓存块的结点,键值都用整型表示
struct CacheNode
{
	unsigned int key;
	unsigned int value;
	CacheNode* prev, * next;
	CacheNode() :prev(nullptr), next(nullptr) {}
	CacheNode(unsigned int k, unsigned int v) :key(k),value(v),prev(nullptr),next(nullptr){}
};


// 类
class LRUCache
{
public:
	// 以capacity初始化缓存队列容量
	LRUCache(unsigned int capacity) {
		m_size = capacity;
		m_head = nullptr;
		m_tail = nullptr;
	};
	~LRUCache();
	// 直接通过判断Map是否含有key值即可，如果查找到key，则返回对应的value，否则返回-1;
	int GetCache(int key);
	// 如果当前的key值对应的节点已经存在，则将这个节点取出来，并且删除节点所处的原有的位置，
	// 并在头部插入该节点；如果节点不存在节点中，这个时候需要在链表的头部插入新节点，
	// 插入新节点可能导致容量溢出，如果出现溢出的情况，则需要删除链表尾部的节点。
	void SetCache(int key, int value);
	// 将缓存结点从双向链表尾部删除
	void Remove(CacheNode* node);
	// 将结点插入到双向链表的头部
	void SetHead(CacheNode* node);
	void Print();
private:
	CacheNode* m_head, * m_tail;   // 缓存队列头尾指针
	unsigned int m_size;  // 记录缓存队列容量
	HashTable<int,CacheNode*> m_map;  // 用来查询队列中缓存块信息的Map
};

