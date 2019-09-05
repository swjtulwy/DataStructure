#include"longest_increasing_subsequence.h"

void TestLIS() {
	std::vector<int> s = {10,9,2,5,3,7,101};
	std::cout << "最大的上升子序列长度为: "<<LongestIncresingSubsequence(s) << std::endl;
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
	}
	return res;
}