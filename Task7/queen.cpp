#include "queen.h"
#include<vector>
#include <iostream>
using namespace std;

// https://www.cnblogs.com/bigmoyan/p/4521683.html


// �ж��ܲ��ܷ��ûʺ�
// put Ϊ��¼ÿһ���д�Żʺ���е���ʱ����
bool IsOk(int row, vector<int>& put) {
	// �ӵ�һ�п�ʼ����
	for (int i = 0; i < row; i++) {
		// �������ң����Խ��߲��ܷ�
		if (put[row] == put[i] || put[row] - put[i] == row - i || put[row] - put[i] == i - row) {
			return false;
		}
	}
	return true;
}


void NQueen(int row, int &n, int& total, vector<int>& put) {
	if (row == n) {
		total++; // ������������У�˵���ҵ���һ���⣬�ݹ��˳�
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
		// ���о����������ݵ���һ����һ��
		for (int col = 0; col < n; col++) {
			put[row] = col;
			if (IsOk(row, put)) { // ���Ծ������
				NQueen(row + 1, n, total, put);
			}
		}
	}
}

void TestQueen() {
	int n;
	int total = 0;
	cout << "������ʺ�����:";
	cin >> n;
	vector<int> put(n);
	NQueen(0, n, total, put);
	cout << "���нⷨ��" << total << "��" << endl;
}