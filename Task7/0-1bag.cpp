#include "0-1bag.h"
#include <iostream>
#include <vector>

using namespace std;

//【回溯】

// 回溯法解决问题的三个步骤
// a针对所给问题，定义问题的解空间
// b确定易于搜索的解空间结构
// c以深度优先的方式搜索解空间，并在搜索过程中用剪枝函数避免无效搜索

// https://blog.csdn.net/u010323330/article/details/80302227

int bestv = -1;  // 最优价值
int numObject = 5; // 物品数量
int wMax = 10; // 背包容量
vector<int> w{2,5,6,2,4};  // 存放物品重量的数组
vector<int> v{6,4,5,3,6};  // 存放物品价值的数组

int totalM = 0; // 可能的选法个数
int bestid = 0;
vector<int> bestx(numObject);  // 存储最好的选法


void Test01Bag() {
	vector<int> put(numObject);
	int rw = 0;
	for (int i = 0; i < numObject; i++) {
		rw += w[i];  // 初始化剩余物品总价值
	}
	DFS_Back(1, 0, 0, rw, put);
	cout << "选择方案共有上述" << totalM << "种" << endl;
	cout << "其中第"<<bestid<<"方案具有最大价值" << bestv <<endl;
	cout << "该方案为:";
	for (int j = 0; j < numObject; j++) {
		cout << bestx[j] << " ";
	}
	cout << endl;
}

void DFS_Back(int i, int cw, int cv, int rw, vector<int>& put) {
	// i 为树第几层, cw(current weight) 为当前物品总重量，cv(current value) 为当前总价值, 
	// rw (reserve weight) 为剩余物品总重量,op(option) 为选择数组
	// 递归结束条件
	if (i > numObject) { // 找到一个叶子结点
		for (int j = 0; j < numObject; j++) {
			cout << put[j] << " ";
		}
		cout << endl;
		++totalM;
		if (cw <= wMax && cv > bestv) { // 找到一个满足条件的更优解
			bestv = cv;
			bestid = totalM;
			for (int j = 0; j < numObject; j++) {
				bestx[j] = put[j];
			}
		}
	}
	else { // 尚未找完所有物品
		if (cw + w[i - 1] <= wMax) { // 左孩子
			put[i - 1] = 1;   // 选第i个物品
			DFS_Back(i + 1, cw + w[i - 1], cv + v[i - 1], rw - w[i - 1], put);
		}
		put[i - 1] = 0;  // 回溯，不选第i个物品
		// 如果剩下能容纳的重量小于剩下的物品重量和，右孩子
		//if (wMax - cw < rw) {  // 可选择剪枝
			DFS_Back(i + 1, cw, cv, rw - w[i - 1], put);
		//}
	}
}