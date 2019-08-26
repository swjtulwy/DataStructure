#include "0-1bag.h"
#include <iostream>
#include <vector>

using namespace std;

//�����ݡ�

// ���ݷ�����������������
// a����������⣬��������Ľ�ռ�
// bȷ�����������Ľ�ռ�ṹ
// c��������ȵķ�ʽ������ռ䣬���������������ü�֦����������Ч����

// https://blog.csdn.net/u010323330/article/details/80302227

int maxv = -9999;
int n = 3; // ��Ʒ����
int wMax = 30; // ��������
vector<int> w{0, 16,15,15};  // �����Ʒ����������
vector<int> v{0,45,25,25};  // �����Ʒ��ֵ������

int cw; // ��ǰ����
int cv; // ��ǰ��ֵ
vector<int> put(n+1);
int total = 1; // ��ռ�������


void DFS_Back(int i, int cw,int cv, int rw, vector<int> op) {
	// iΪ���ڼ���, cwΪ��ǰ��Ʒ��������cvΪ��ǰ�ܼ�ֵ,rwΪʣ����Ʒ������,opΪ�洢����
	// �ݹ��������
	if (i > n) { // �ҵ�һ��Ҷ�ӽ��
		if (cw == wMax && cv > maxv) { // �ҵ�һ�����������ĸ��Ž�
			maxv = cv;
			for (int j = 1; j <= n; j++) {
				put[j] = op[j];
			}
		}
	}
	else{ // ��δ����������Ʒ
		if (cw + w[i] < wMax) { // ���ӽ���֦
			op[i] = 1;   // ѡ��i����Ʒ
			DFS_Back(i + 1, cw + w[i], cv + v[i], rw - w[i], op);
		}
		op[i] = 0;  // ���ݣ���ѡ��i����Ʒ
		// ���ʣ�������ɵ�����С��ʣ�µ���Ʒ�����ͣ���֦�ұ�
		if (wMax - cw < rw) {  
			DFS_Back(i + 1, cw, cv, rw - w[i], op);
		}
	}
}

void Test01Bag() {
	vector<int> op(n + 1);
	int rw = 0;
	for (int i = 0; i < n; i++) {
		rw += w[i];  // ��ʼ��ʣ����Ʒ�ܼ�ֵ
	}
	DFS_Back(1, 0, 0, rw, op);
	for (int i = 0; i < n + 1; i++) {
		cout << put[i] << " ";
	}
}