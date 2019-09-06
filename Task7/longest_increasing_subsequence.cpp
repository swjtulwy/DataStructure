#include"longest_increasing_subsequence.h"

void TestLIS() {
	//std::vector<int> s = {0,8,4,12,2};
	std::vector<int> s = { 1,4,2,5,3};
	//std::cout << "�������������г���Ϊ: "<<LongestIncresingSubsequence(s) << std::endl;
	std::cout << "���׶ε��������������Ϊ: " << std::endl;
	LongestIncresingSubsequence1(s);
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
		std::cout << dp[i] << " ";
	}
	return res;
}

//1, 4, 2, 5, 3, 7, 4, 0

// �Ľ��棬���ö��������Ӷ�̬�滮��ʱ�临�Ӷ�O(nlogn)
void LongestIncresingSubsequence1(std::vector<int> s) {
	std::vector<int> dp(s.size());
	auto len = dp.begin();	
	for (int num : s) {
		// ���淵�ص��Ƕ��ֲ���Ӧ�ò����λ��
		auto low = std::lower_bound(dp.begin(), len, num); 
		*low = num;  // ���뵱ǰԪ�ص����ҵ���λ��
		if (low == len) {  // ������ҵ�λ�������˵��Ӧ�ü������У����ȼ�һ
			len++;
		}
		for (auto p = dp.begin(); p != low+1; p++) {
			std::cout << *p << " ";
		}
		std::cout << std::endl;
	}
	std::cout<<"�������������г���Ϊ: "<< len - dp.begin()<<std::endl;
}