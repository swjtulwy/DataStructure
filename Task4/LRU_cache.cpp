#include "LRU_cache.h"


// ���Ժ���
void TestLRUCache() {
	LRUCache* lruCache = new LRUCache(4); // ���û�����д�СΪ4
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

// �Ƴ�������
void LRUCache::Remove(CacheNode* node) {
	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	else {
		m_head = node->next; // ����ͷ
	}
	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}
	else {
		m_tail = node->prev; // ����β
	}
}

// ������ͷ�����������㣬�����������뵽�����λ��
void LRUCache::SetHead(CacheNode* node) {
	node->next = m_head;
	node->prev = nullptr;
	if (m_head != nullptr) { // ͷ���ǿ�
		m_head->prev = node;
	}
	m_head = node;  
	if (m_tail == nullptr) {
		m_tail = m_head;
	}
}

// ������飬��ȡ�仺������
int LRUCache::GetCache(int key) {
	CacheNode* node = new CacheNode;
	if (m_map.Find(key)) {  // ���hashmap���иÿ�
		node = m_map[key];
		Remove(node);     // ��ô���ÿ�ӻ������(һ��˫������)���ᵽ����
		SetHead(node);    // ��Ϊ���ձ������ˣ���һ�θ����ʱ�����
 		return node->value;
	}
	else {
		return -1; // ���û�ҵ�����
	}
}

// д�����
void LRUCache::SetCache(int key, int value) {
	CacheNode* node = new CacheNode;
	if ( m_map.getSize()!=0 &&  m_map.Find(key, &node)) { // ���ԭ����hashmap�����ҵ��û����
		node->value = value;  // ��ô���¸û���������
		Remove(node);
		SetHead(node);
	}
	else {   // ���ԭ��û����������
		CacheNode* newNode = new CacheNode(key, value);
		if (m_map.getSize() >= m_size) {  // ��������������������̭��β�Ļ����
			m_map.Delete(m_tail->key);
			Remove(m_tail);
		}
		SetHead(newNode);  // ��ô���û����ŵ�����
		m_map.Insert(key, newNode);  // ͬʱhashmap��Ҳ��¼�û������Ϣ
	}
}


// ��ӡ������С�hashmap��ϵ����Ϣ
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