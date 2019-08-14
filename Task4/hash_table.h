#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//ɢ�б���ϣ��
//ʵ��һ���������������ͻ�����ɢ�б�

// ��ϣ���������ͻ�ķ����У����Ŷ�ַ��������
// ���Ĳ���������������ڴ洢��ֵ��
// ��ϣ�������ó��෨��������Ϊģ������й�ϣ���С
// �Լ�����ɢ�У�ֵΪ���ĸ���
// ����Hash��ʵ�������֣�һ����HashMapһ����HashSet
// ��������HashMap�洢��ֵ�ԣ���ɢ�м���HashSet�洢����ɢ�ж���
// ����ʵ�ֵ���HashMap����Ψһ��ֵ��Ψһ


void TestHashTable();

// ������ELFHash�ַ�����ϣ�㷨�����ڽ��ַ���Ψһӳ���unsigned int
inline unsigned int ELFHash(const char* str, unsigned int len)
{
	unsigned int hash = 0;
	unsigned int g = 0;
	for (unsigned int i = 0; i < len; ++i)
	{
		char temp = str[i];
		hash = (hash << 4) + (temp * 13);
		g = hash & 0xf0000000;  // 32λ
		if (g)
		{
			hash ^= (g >> 24);
			hash ^= g;
		}
	}
	return hash;
}

// ������ΪK��ʽ�ļ�תΪ�޷���int
template<typename K>
inline unsigned int HashKey(const K& key) {
	return (unsigned int)key;
}

// ���ַ�����ʽ�ļ�תΪ�޷���int
template<>
inline unsigned int HashKey<string>(const string& key) {
	return ELFHash(key.c_str(), key.length());
}

// ����������ʽ�ļ�תΪ�޷���int
template<>
inline unsigned int HashKey<unsigned long long>(const unsigned long long& key)
{
	return ELFHash((const char*)& key, sizeof(unsigned long long));
}

// ��ϣ�����
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
	// ��ɢ�б��ȵĳ�ʼ��
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
	// ��ż�ֵ�ԵĽṹ��
	struct Node {
		K key;
		V val;
		Node* next;
	};
	// ���ָ���ֵ�Ե�ָ������
	Node** m_table;
	unsigned int m_slotSize; // ɢ�б���
	unsigned int m_size;  // �洢�ļ�ֵ������
};

// ���Ҷ�Ӧ�ļ��Ƿ����
template<typename K, typename V>
bool HashTable<K, V>::Find(const K& key, V* val) {
	unsigned int pos = HashKey(key) % m_slotSize;
	Node* node = m_table[pos];  // ����ָ��
	while (node != 0) {
		if (node->key == key) {
			// �ҵ����ˣ����val��Ϊ0�����ض�Ӧ��ֵ
			if (val != 0) {
				*val = node->val; // valΪָ��ֵ��ָ��
			}
			return true;
		}
		node = node->next;
	}
	return false;
}

// �����ֵ��
template<typename K, typename V>
void HashTable<K, V>::Insert(const K& key, const V& value) {
	// û�з���ͬ���ļ�����
	if (!Find(key)) {
		unsigned int pos = HashKey(key) % m_slotSize;
		// ͷ�巨
		Node* node = new Node;
		node->key = key;
		node->val = value;
		node->next = m_table[pos];
		m_table[pos] = node;
		m_size++;
	}
}

// ���ݼ�ɾ��
template<typename K, typename V>
bool HashTable<K, V>::Delete(const K& key) {
	unsigned int pos = HashKey(key) % m_slotSize;
	Node* node = m_table[pos];
	Node* node_prev = 0;
	while (node != 0) {
		// �ҵ��ü�
		if (node->key == key) {
			// �����о���һ��
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

// �������
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

// ��ӡ��ϣ��
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
	Node* node = m_table[pos];  // ����ָ��
	while (node != 0) {
		if (node->key == key) {
			return node->val;
		}
		node = node->next;
	}
	cout << "input error!" << endl;
	exit(1);
}
