#include "binary_search_tree.h"
#include "heap_array.h"
#include "priority_queue.h"

int main() {
	//TestBST(); // ����BST
	//TestHeapArray(); // ���Զ�
	//TestPriorityQueue(); // �������ȶ���

	// ���Ժϲ�n������
	extern vector<int> MergeKSortedArray(vector<vector<int>> & v);
	vector<vector<int>> a = { {6,3,0},{7,4,1},{8,5,2}};
	vector<int> m = MergeKSortedArray(a);
	for (int i = 0; i < m.size(); i++) {
		cout << m[i] << " ";
	}

	// ���Է���TopK
	//extern vector<int> TopK(vector<int> & v, int k);
	//vector<int> v = { 7,4,3,2,6,8,1,0 };
	//vector<int> res = TopK(v, 4);
	//for (int i = 0; i < res.size(); i++) {
	//	cout << res[i] << " ";
	//}
}
