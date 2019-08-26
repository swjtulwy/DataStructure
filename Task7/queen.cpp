#include "queen.h"
#include<vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/bigmoyan/p/4521683.html


// 判断能不能放置皇后
// put 为记录每一行中存放皇后的列的临时数组
bool IsOk(int row, vector<int>& put) {
	// 从第一行开始遍历
	for (int i = 0; i < row; i++) {
		// 上下左右，及对角线不能放
		if (put[row] == put[i] || put[row] - put[i] == row - i || put[row] - put[i] == i - row) {
			return false;
		}
	}
	return true;
}


void NQueen(int row, int &n, int& total, vector<int>& put) {
	if (row == n) {
		total++; // 到达最下面的行，说明找到了一个解，递归退出
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (put[i]==j) {
					cout << "1 ";
				}
				else{
					cout << "0 ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	else {
		// 不行就往继续回溯到上一行下一列
		for (int col = 0; col < n; col++) {
			put[row] = col;
			if (IsOk(row, put)) { // 可以就往更深处
				NQueen(row + 1, n, total, put);
			}
		}
	}
}

void TestQueen() {
	int n;
	int total = 0;
	cout << "请输入皇后数量:";
	cin >> n;
	vector<int> put(n);
	NQueen(0, n, total, put);
	cout << "共有解法：" << total << "种" << endl;
}