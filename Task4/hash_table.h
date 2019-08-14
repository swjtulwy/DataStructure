#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//散列表（哈希表）
//实现一个基于链表法解决冲突问题的散列表

// 哈希函数处理冲突的方法有：开放定址法和链表法
// 下文采用拉链法，结点内存储键值对
// 哈希函数采用除余法，除的数为模板参数中哈希表大小
// 对键进行散列，值为键的附属
// 对于Hash的实现有两种，一种是HashMap一种是HashSet
// 区别在于HashMap存储键值对，并散列键。HashSet存储对象，散列对象。
// 下面实现的是HashMap，键唯一，值不唯一


void TestHashTable();

// 著名的ELFHash字符串哈希算法，用于将字符串唯一映射成unsigned int
inline unsigned int ELFHash(const char* str, unsigned int len)
{
	unsigned int hash = 0;
	unsigned int g = 0;
	for (unsigned int i = 0; i < len; ++i)
	{
		char temp = str[i];
		hash = (hash << 4) + (temp * 13);
		g = hash & 0xf0000000;  // 32位
		if (g)
		{
			hash ^= (g >> 24);
			hash ^= g;
		}
	}
	return hash;
}

// 将类型为K形式的键转为无符号int
template<typename K>
inline unsigned int HashKey(const K& key) {
	return (unsigned int)key;
}

// 将字符串形式的键转为无符号int
template<>
inline unsigned int HashKey<string>(const string& key) {
	return ELFHash(key.c_str(), key.length());
}

// 将长整型形式的键转为无符号int
template<>
inline unsigned int HashKey<unsigned long long>(const unsigned long long& key)
{
	return ELFHash((const char*)& key, sizeof(unsigned long long));
}

// 哈希表的类
template<typename K, typename V>
class HashTable
{
	struct Node;
public:
	void Insert(const K& key, const V& value);
	bool Delete(const K& key);
	bool Find(const K& key, V* val = 0);
	void Clear();
	void Print();
	unsigned int getSize() { return m_size; }
	V& operator[](const K& key);
	HashTable() :m_table(0), m_slotSize(10), m_size(0) {
		m_table = new Node * [m_slotSize];
		memset(m_table, 0, sizeof(Node*) * m_slotSize);
	};
	// 带散列表长度的初始化
	HashTable(unsigned int slotSize) {
		m_slotSize = slotSize;
		m_table = new Node * [m_slotSize];
		memset(m_table, 0, sizeof(Node*) * m_slotSize);
	}
	~HashTable() {
		Clear();
		delete[] m_table;
	}
private:
	// 存放键值对的结构体
	struct Node {
		K key;
		V val;
		Node* next;
	};
	// 存放指向键值对的指针数组
	Node** m_table;
	unsigned int m_slotSize; // 散列表长度
	unsigned int m_size;  // 存储的键值对数量
};

// 查找对应的键是否存在
template<typename K, typename V>
bool HashTable<K, V>::Find(const K& key, V* val) {
	unsigned int pos = HashKey(key) % m_slotSize;
	Node* node = m_table[pos];  // 遍历指针
	while (node != 0) {
		if (node->key == key) {
			// 找到键了，如果val不为0，返回对应的值
			if (val != 0) {
				*val = node->val; // val为指向值得指针
			}
			return true;
		}
		node = node->next;
	}
	return false;
}

// 插入键值对
template<typename K, typename V>
void HashTable<K, V>::Insert(const K& key, const V& value) {
	// 没有发现同样的键存在
	if (!Find(key)) {
		unsigned int pos = HashKey(key) % m_slotSize;
		// 头插法
		Node* node = new Node;
		node->key = key;
		node->val = value;
		node->next = m_table[pos];
		m_table[pos] = node;
		m_size++;
	}
}

// 根据键删除
template<typename K, typename V>
bool HashTable<K, V>::Delete(const K& key) {
	unsigned int pos = HashKey(key) % m_slotSize;
	Node* node = m_table[pos];
	Node* node_prev = 0;
	while (node != 0) {
		// 找到该键
		if (node->key == key) {
			// 链表中就这一个
			if (node_prev == 0) {
				m_table[pos] = node->next;
			}
			else {
				node_prev->next = node->next;
			}
			delete node;
			m_size--;
			return true;
		}
		node_prev = node;
		node = node->next;
	}
	return false;
}

// 清空链表
template<typename K, typename V>
void HashTable<K, V>::Clear() {
	for (unsigned int i = 0; i < m_slotSize; i++) {
		Node* node = m_table[i];
		while (node != 0) {
			Node* temp = node;
			node = node->next;
			delete temp;
		}
	}
	m_size = 0;
	memset(m_table, 0, sizeof(Node*) * m_slotSize);
}

// 打印哈希表
template<typename K, typename V>
void HashTable<K, V>::Print() {
	cout << "{ ";
	for (unsigned int i = 0; i < m_slotSize; i++) {
		Node* node = m_table[i];
		while (node != 0) {
			cout << node->key << ":" << node->val << " ";
			node = node->next;
		}
	}
	cout << "} " << endl;
}

template<typename K, typename V>
V& HashTable<K, V>::operator[](const K& key) {
	unsigned int pos = HashKey(key) % m_slotSize;
	Node* node = m_table[pos];  // 遍历指针
	while (node != 0) {
		if (node->key == key) {
			return node->val;
		}
		node = node->next;
	}
	cout << "input error!" << endl;
	exit(1);
}
