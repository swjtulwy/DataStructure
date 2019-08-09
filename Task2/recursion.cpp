#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 本文件中函数全部采用递归实现

//编程实现斐波那契数列求值 f(n) = f(n-1) + f(n-2)
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


//编程实现求阶乘 n!
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

//编程实现一组数据集合的全排列
// 包含begin 不包含end,[begin,end)
void FullPermutation(vector<int> v, int begin, int end) {
	
}

// 测试函数
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