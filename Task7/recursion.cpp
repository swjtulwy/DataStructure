#include "recursion.h"
#include <iostream>
using namespace std;


//���ݹ顿
// �ݹ�ʹһЩ���ӵ����⴦�����������ˣ�������ѧϰ�㷨��ơ����ݽṹʱ������ᵽ��һ�㡣
// ���ǣ��ݹ���ÿһ��ִ��ʱ��ҪΪ�ֲ����������ص�ַ����ջ�ռ䣨�Է�����ÿ�εݹ���ö��������µľֲ������;ֲ�������
// ����ݹ���̫��Ļ����ͻ�����̫���stack������ͽ���������Ч�ʣ�Ҳ�����˵ݹ����ȡ�
// ��ˣ��ڱ�Ҫ��ʱ�����ֻʹ�õݹ��˼������⣬��������ת�÷ǵݹ�ķ�ʽ��д
int ClimbStairs1(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	return ClimbStairs1(n - 1) + ClimbStairs1(n - 2);
}

int ClimbStairs2(int n) {
	int step1 = 1, step2 = 1, tmp = 0;
	for (int i = 2; i < n + 1; i++) {
		tmp = step1 + step2;
		step1 = step2;
		step2 = tmp;
	}
	return step2;
}

void TestClimbstairs() {
	int n;
	cout << "������¥�ݽ���:";
	cin >> n;
	cout << "�ݹ���ʽ�����е��﷽����" << ClimbStairs1(n) << endl;
	cout << "������ʽ�����е��﷽����" << ClimbStairs2(n) << endl;
}