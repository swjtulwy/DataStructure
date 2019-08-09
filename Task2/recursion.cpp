#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ���ļ��к���ȫ�����õݹ�ʵ��

//���ʵ��쳲�����������ֵ f(n) = f(n-1) + f(n-2)
int Fibonacci(int n) {
	if (n < 1) {
		cout << "number n must greater than 0!" << endl;
		exit(1);
	}
	if (n == 1 || n == 2) {
		return 1; 
	}
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}


//���ʵ����׳� n!
int Factorial(int n) {
	if (n < 0) {
		cout << "number n must greater than or equal to 0!" << endl;
		exit(1);
	}
	if (n == 0) {
		return 1;
	}
	return n * Factorial(n - 1);
}

//���ʵ��һ�����ݼ��ϵ�ȫ����
// ����begin ������end,[begin,end)
void FullPermutation(vector<int> v, int begin, int end) {
	//begin=endʱ����ʾ�ݹ�������ҵ���һ���������
	if (begin == end)
	{
		// ��ͷ�������������
		for (int i = 0; i < end; i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
		return; // ����ֱ�ӷ��أ��ڵ���ջ��ֱ�ӵ���
	}
	for (int i = begin; i < end; i++)
	{
		swap(v[begin], v[i]); // ÿ�ΰѺ���Ľ�������һ��λ��
		FullPermutation(v,begin + 1, end);
		swap(v[i], v[begin]);//����,��˳��ԭ
	}
}

// ���Ժ���
extern void TestFibonacci() {
	cout << "Fibonacci sequence from 1 to 9: ";
	for (int i = 1; i < 10; i++) {
		cout << Fibonacci(i) << " ";
	}
	cout << endl;
}

extern void TestFactorial() {
	cout << "Factorial sequence from 0 to 9: ";
	for (int i = 0; i < 10; i++) {
		cout << Factorial(i) << " ";
	}
	cout << endl;
}

extern void TestFullPermutation() {
	vector<int> v = { 4,3,7,9};
	FullPermutation(v, 0, v.size());
}