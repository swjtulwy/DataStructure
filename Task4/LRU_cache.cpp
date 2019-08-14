#include "LRU_cache.h"


// 测试函数
void TestLRUCache() {
	LRUCache* lruCache = new LRUCache(4); // 设置缓存队列大小为4
	lruCache->SetCache(1, 1);
	lruCache->SetCache(2, 2);
	lruCache->SetCache(3, 3);
	lruCache->SetCache(4, 2);
	cout << "add 4 caches:<1,1>, <2,2>, <3,3>, <4,2>" << endl;
	lruCache->Print();
	cout << "visit cache 3: " << lruCache->GetCache(3)<< endl;
	lruCache->Print();
	cout << "visit cache 4: " << lruCache->GetCache(4) << endl;
	lruCache->Print();
	cout << "add 2 caches:<5,7>, <6,8>" << endl;
	lruCache->SetCache(5, 7);
	lruCache->SetCache(6, 8);
	lruCache->Print();
	cout << "visit cache 1: " << lruCache->GetCache(1) << endl;
	cout << "visit cache 5: " << lruCache->GetCache(5) << endl;
	lruCache->Print();
	cout << "add 1 caches:<7,8>" << endl;
	lruCache->SetCache(7, 8);
	lruCache->Print();
	cout << "visit cache 6: " << lruCache->GetCache(6) << endl;
	lruCache->Print();
	cout << "visit cache 4: " << lruCache->GetCache(4) << endl;
	lruCache->Print();

}

// 移除链表结点
void LRUCache::Remove(CacheNode* node) {
	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	else {
		m_head = node->next; // 链表头
	}
	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}
	else {
		m_tail = node->prev; // 链表尾
	}
}

// 从链表头部插入链表结点，即将缓存块加入到最近的位置
void LRUCache::SetHead(CacheNode* node) {
	node->next = m_head;
	node->prev = nullptr;
	if (m_head != nullptr) { // 头结点非空
		m_head->prev = node;
	}
	m_head = node;  
	if (m_tail == nullptr) {
		m_tail = m_head;
	}
}

// 读缓存块，获取其缓存内容
int LRUCache::GetCache(int key) {
	CacheNode* node = new CacheNode;
	if (m_map.Find(key)) {  // 如果hashmap里有该块
		node = m_map[key];
		Remove(node);     // 那么将该块从缓存队列(一个双向链表)中提到队首
		SetHead(node);    // 因为它刚被访问了，下一次更大几率被访问
 		return node->value;
	}
	else {
		return -1; // 如果没找到返回
	}
}

// 写缓存块
void LRUCache::SetCache(int key, int value) {
	CacheNode* node = new CacheNode;
	if ( m_map.getSize()!=0 &&  m_map.Find(key, &node)) { // 如果原来的hashmap中能找到该缓存块
		node->value = value;  // 那么更新该缓存块的内容
		Remove(node);
		SetHead(node);
	}
	else {   // 如果原来没有这个缓存块
		CacheNode* newNode = new CacheNode(key, value);
		if (m_map.getSize() >= m_size) {  // 如果缓存队列已满，则淘汰队尾的缓存块
			m_map.Delete(m_tail->key);
			Remove(m_tail);
		}
		SetHead(newNode);  // 那么将该缓存块放到队首
		m_map.Insert(key, newNode);  // 同时hashmap中也记录该缓存块信息
	}
}


// 打印缓存队列、hashmap的系列信息
void LRUCache::Print() {
	CacheNode* p = m_head;
	cout << "----------------------------" << endl;
	cout << "CacheQueue: ";
	while (p != m_tail && p) {
		cout << "|"<<p->key<<":"<<p->value<<"|-->";
		p = p->next;
	}
	cout << "|"<<p->key << ":" << p->value << "|"<<endl;
	cout << "HashMap: ";
	m_map.Print();
	cout << "CacheQueue Size: " << m_size <<" HashMap Size: "<<m_map.getSize()<< endl;
	cout << "----------------------------" << endl;
}