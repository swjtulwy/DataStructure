#include"longest_increasing_subsequence.h"

void TestLIS() {
	std::vector<int> s = {10,9,2,5,3,7,101};
	std::cout << "�������������г���Ϊ: "<<LongestIncresingSubsequence(s) << std::endl;
}

int LongestIncresingSubsequence(std::vector<int> s) {
	int n = s.size();
	if (n == 0) {
		return 0;
	}
	std::vector<int> dp(n); // dp[i]������s[i]��β��������������еĳ���
	dp[0] = 1; 
	for (int i = 1; i < n; i++) {  // ��������ѡ��
		int maxLength = 0;
		for (int j = 0; j < i; j++) {  
			if (s[j] < s[i]) {  
				maxLength = std::max(maxLength, dp[j]);  // ���µ�ǰԪ��֮ǰ������������г���
			}
		}
		// ������ÿ�����ܵ�������������и��ӵ�ǰԪ��
		dp[i] = maxLength + 1; // �ڲ�����꣬���µ�ǰ���ȣ���һ����Ϊ���ӵ�ǰԪ��
	}

	// �ҳ�dp[]�е����ֵ��Ϊ�����������������г���
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (dp[i] > res) {
			res = dp[i];
		}
	}
	return res;
}