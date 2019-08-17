#include "priority_queue.h"

void TestPriorityQueue() {
	PriorityQueue<int>* Q = new PriorityQueue<int>(8, false);
	vector<int> v = {3,1,6,4,9,2,0};
	for (int i = 0; i < v.size(); i++) {
		Q->Enqueue(v[i]);
		cout << Q->GetFront() << " ";
	}
	cout << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << Q->GetFront() << " ";
		Q->Dequeue();
	}

}

struct MinHeapNode
{
	int val;
	int i;
	int j;
	MinHeapNode() {}
	MinHeapNode(int a, int b, int c) :val(a), i(b), j(c) {}
	bool operator<(const MinHeapNode& m) {
		return this->val < m.val;
	}
	bool operator>(const MinHeapNode& m) {
		return this->val > m.val;
	}
	bool operator==(const MinHeapNode& m) {
		return this->val == m.val;
	}
};

// �������ȼ����кϲ� K ���������飬ÿ��������n��Ԫ��
extern vector<int> MergeKSortedArray(vector<vector<int>>& v) {
	vector<int> res;
	PriorityQueue<MinHeapNode> q(v.size(),true);
	for (int i = 0; i < v.size(); i++) {
		q.Enqueue(MinHeapNode(v[i][0], i, 1)); // j�����1��ʼ
	}
	while (!q.IsEmpty()) {
		MinHeapNode temp = q.GetFront(); // ��ȡ����ͷ���
		q.Dequeue();
		res.push_back(temp.val);  // ����������
		if (temp.j < v[temp.i].size()) {  // ������Դ����һ������ı���ָ��û�г���������
			temp.val = v[temp.i][temp.j]; // ȡ����������һ����ֵ
			temp.j++;   // ����ָ�����
			q.Enqueue(temp); // ������Ž����ȶ���
		}
	}
	return res;
}


// ��һ�鶯̬���ݼ��ϵ���� Top K
extern vector<int> TopK(vector<int>& v, int k) {
	PriorityQueue<int>* Q = new PriorityQueue<int>(v.size(),true);
	vector<int> res;
	for (int i = 0; i < v.size(); i++) {
		Q->Enqueue(v[i]);
	}
	for (int j = 0; j < k; j++) {
		res.push_back(Q->GetFront());
		Q->Dequeue();
	}
	return res;
}