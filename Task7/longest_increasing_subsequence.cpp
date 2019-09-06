#include"longest_increasing_subsequence.h"

void TestLIS() {
	//std::vector<int> s = {0,8,4,12,2};
	//std::vector<int> s = {6,5,4,2,3,1,4,5,12,2};
	std::vector<int> s = {3,5,6,5,4,2,3,1,4,5,12,2};
	//std::vector<int> s = {1,2,7,8,9,10,3,6,11,3,12};
	//std::cout << "最大的上升子序列长度为: "<<LongestIncresingSubsequence(s) << std::endl;
	std::cout << "实时dp数组为: " << std::endl;
	LongestIncresingSubsequence1(s);
}

int LongestIncresingSubsequence(std::vector<int> s) {
	int n = s.size();
	if (n == 0) {
		return 0;
	}
	std::vector<int> dp(n); // dp[i]代表以s[i]结尾的最大上升子序列的长度
	dp[0] = 1; 
	for (int i = 1; i < n; i++) {  // 外层遍历候选数
		int maxLength = 0;
		for (int j = 0; j < i; j++) {  
			if (s[j] < s[i]) {  
				maxLength = std::max(maxLength, dp[j]);  // 更新当前元素之前的最大上升序列长度
			}
		}
		// 尝试在每个可能的最长上升子序列中附加当前元素
		dp[i] = maxLength + 1; // 内层遍历完，更新当前长度，加一是因为附加当前元素
	}

	// 找出dp[]中的最大值即为数组的最大上升子序列长度
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (dp[i] > res) {
			res = dp[i];
		}
		std::cout << dp[i] << " ";
	}
	return res;
}

//6,5,4,2,3,1,4,5,12,2

// 改进版，采用二分搜索加动态规划，时间复杂度O(nlogn)
void LongestIncresingSubsequence1(std::vector<int> s) {
	std::vector<int> dp(s.size());
	auto len = dp.begin();	
	for (int i = 0; i < s.size();i++) {
		// 下面返回的是二分查找应该插入的位置
		auto low = std::lower_bound(dp.begin(), len, s[i]); 
		*low = s[i];  // 插入当前元素到查找到的位置
		if (low == len) {  // 如果查找的位置在最后，说明应该加入序列，长度加一
			len++;
		}
		for (int i = 0; i < low-dp.begin()+1; i++) {
			std::cout << dp[i] << " ";
		}
		std::cout <<std::endl;
	}
	std::cout<<std::endl<<"最大的上升子序列长度为: "<< len - dp.begin()<<std::endl;
}