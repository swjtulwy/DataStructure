#include "recursion.h"
#include <iostream>
using namespace std;


//【递归】
// 递归使一些复杂的问题处理起来简单明了，尤其在学习算法设计、数据结构时更能体会到这一点。
// 但是，递归在每一次执行时都要为局部变量、返回地址分配栈空间（对方法的每次递归调用都会生成新的局部变量和局部参数。
// 假如递归层次太多的话，就会消耗太多的stack），这就降低了运行效率，也限制了递归的深度。
// 因此，在必要的时候可以只使用递归的思想来求解，而程序则转用非递归的方式书写
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
	cout << "请输入楼梯阶数:";
	cin >> n;
	cout << "递归形式：共有到达方法：" << ClimbStairs1(n) << endl;
	cout << "递推形式：共有到达方法：" << ClimbStairs2(n) << endl;
}