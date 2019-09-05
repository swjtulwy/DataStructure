#include"divide_and_conquer.h"

//【分治】

//利用分治算法求一组数据的逆序对个数


void TestISP() {
	std::vector<int> s = { 6, 2, 1, 3, 4, 5, 1 };
	// 临时数组用于合并步骤，不在递归函数中开启数组，防止递归过程内存中同时存在大量数组
	std::vector<int> t(s.size()); 
	std::cout << "该数组的逆序列对数为:" << InverseSequencePair(s,t,0,s.size()-1) << std::endl; 
}

int InverseSequencePair(std::vector<int>& s, std::vector<int> temp, int l, int r) {
	if (l == r) {
		return 0;
	}
	int mid = (l + r) / 2;
	int ln = InverseSequencePair(s, temp, l, mid);  // 递归左边
	int rn = InverseSequencePair(s, temp, mid + 1, r); // 递归右边
	int mn = Merge(s, temp, l, mid, r);  // 计算一边一个的情况
	return ln + rn + mn;
}


// 边归并排序边计算
int Merge(std::vector<int>& s, std::vector<int> temp, int l, int m, int r) {
	int count = 0;
	int k = l;  // 最终数组的游标
	// 使用临时数组 
	for (int i = l; i <= r; i++) {
		temp[i] = s[i];
	}
	int i, j;
	for (i = l, j = m + 1; i <= m && j <= r; k++) {
		if (temp[i] > temp[j]) { // 左边发现一个大于右边的，那么排序后左边到中间的都必然都大于右边的该数
			count += m - i + 1;
			s[k] = temp[j]; // 归并，取小的
			j++;
		}
		else{
			s[k] = temp[i];
			i++;
		}
	}
	if (i > m) {  
		while (j <= r) {  // 右边还有剩余
			s[k++] = temp[j++];
		}
	}
	else{
		while (i <= m) { // 左边还有剩余
			s[k++] = temp[i++];
		}
	}
	return count;
}