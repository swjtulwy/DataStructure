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

int maxv = -9999;
int n = 3; // 物品数量
int wMax = 30; // 背包容量
vector<int> w{0, 16,15,15};  // 存放物品重量的数组
vector<int> v{0,45,25,25};  // 存放物品价值的数组

int cw; // 当前重量
int cv; // 当前价值
vector<int> put(n+1);
int total = 1; // 解空间结点数量


void DFS_Back(int i, int cw,int cv, int rw, vector<int> op) {
	// i为树第几层, cw为当前物品总重量，cv为当前总价值,rw为剩余物品总重量,op为存储数组
	// 递归结束条件
	if (i > n) { // 找到一个叶子结点
		if (cw == wMax && cv > maxv) { // 找到一个满足条件的更优解
			maxv = cv;
			for (int j = 1; j <= n; j++) {
				put[j] = op[j];
			}
		}
	}
	else{ // 尚未找完所有物品
		if (cw + w[i] < wMax) { // 左孩子结点剪枝
			op[i] = 1;   // 选第i个物品
			DFS_Back(i + 1, cw + w[i], cv + v[i], rw - w[i], op);
		}
		op[i] = 0;  // 回溯，不选第i个物品
		// 如果剩下能容纳的重量小于剩下的物品重量和，剪枝右边
		if (wMax - cw < rw) {  
			DFS_Back(i + 1, cw, cv, rw - w[i], op);
		}
	}
}

void Test01Bag() {
	vector<int> op(n + 1);
	int rw = 0;
	for (int i = 0; i < n; i++) {
		rw += w[i];  // 初始化剩余物品总价值
	}
	DFS_Back(1, 0, 0, rw, op);
	for (int i = 0; i < n + 1; i++) {
		cout << put[i] << " ";
	}
}