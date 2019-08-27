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

int bestv = -1;  // ���ż�ֵ
int numObject = 5; // ��Ʒ����
int wMax = 10; // ��������
vector<int> w{2,5,6,2,4};  // �����Ʒ����������
vector<int> v{6,4,5,3,6};  // �����Ʒ��ֵ������

int totalM = 0; // ���ܵ�ѡ������
int bestid = 0;
vector<int> bestx(numObject);  // �洢��õ�ѡ��


void Test01Bag() {
	vector<int> put(numObject);
	int rw = 0;
	for (int i = 0; i < numObject; i++) {
		rw += w[i];  // ��ʼ��ʣ����Ʒ�ܼ�ֵ
	}
	DFS_Back(1, 0, 0, rw, put);
	cout << "ѡ�񷽰���������" << totalM << "��" << endl;
	cout << "���е�"<<bestid<<"������������ֵ" << bestv <<endl;
	cout << "�÷���Ϊ:";
	for (int j = 0; j < numObject; j++) {
		cout << bestx[j] << " ";
	}
	cout << endl;
}

void DFS_Back(int i, int cw, int cv, int rw, vector<int>& put) {
	// i Ϊ���ڼ���, cw(current weight) Ϊ��ǰ��Ʒ��������cv(current value) Ϊ��ǰ�ܼ�ֵ, 
	// rw (reserve weight) Ϊʣ����Ʒ������,op(option) Ϊѡ������
	// �ݹ��������
	if (i > numObject) { // �ҵ�һ��Ҷ�ӽ��
		for (int j = 0; j < numObject; j++) {
			cout << put[j] << " ";
		}
		cout << endl;
		++totalM;
		if (cw <= wMax && cv > bestv) { // �ҵ�һ�����������ĸ��Ž�
			bestv = cv;
			bestid = totalM;
			for (int j = 0; j < numObject; j++) {
				bestx[j] = put[j];
			}
		}
	}
	else { // ��δ����������Ʒ
		if (cw + w[i - 1] <= wMax) { // ����
			put[i - 1] = 1;   // ѡ��i����Ʒ
			DFS_Back(i + 1, cw + w[i - 1], cv + v[i - 1], rw - w[i - 1], put);
		}
		put[i - 1] = 0;  // ���ݣ���ѡ��i����Ʒ
		// ���ʣ�������ɵ�����С��ʣ�µ���Ʒ�����ͣ��Һ���
		//if (wMax - cw < rw) {  // ��ѡ���֦
			DFS_Back(i + 1, cw, cv, rw - w[i - 1], put);
		//}
	}
}