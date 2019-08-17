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

// 利用优先级队列合并 K 个有序数组，每个数组有n个元素
extern vector<int> MergeKSortedArray(vector<vector<int>>& v) {
	vector<int> res;
	PriorityQueue<MinHeapNode> q(v.size(),true);
	for (int i = 0; i < v.size(); i++) {
		q.Enqueue(MinHeapNode(v[i][0], i, 1)); // j必须从1开始
	}
	while (!q.IsEmpty()) {
		MinHeapNode temp = q.GetFront(); // 获取队列头结点
		q.Dequeue();
		res.push_back(temp.val);  // 放入结果数组
		if (temp.j < v[temp.i].size()) {  // 在其来源的那一个数组的遍历指针没有超过其容量
			temp.val = v[temp.i][temp.j]; // 取该数组中下一个的值
			temp.j++;   // 遍历指针更新
			q.Enqueue(temp); // 把这个放进优先队列
		}
	}
	return res;
}


// 求一组动态数据集合的最大 Top K
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