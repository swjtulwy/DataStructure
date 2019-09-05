#include "longest_common_subsequence.h"


std::vector<std::vector<int>> flag;

void TestLCS() {
	std::string s1 = "helloworld";
	std::string s2 = "loopred";
	std::cout << "字符串 " << s1 << " 和 " << " 字符串" << s2 
		<< "的最长公共子序列长度为: " << LongestCommonSubsequence(s1, s2) << std::endl;
	std::cout << "走势图为:" << std::endl;
	std::cout << "   ";
	for (int i = 0; i < s2.size(); i++) {
		std::cout << s2[i]<<"  ";
	}
	std::cout << std::endl;
	for (int i = 1; i < s1.size() + 1; i++) {
		std::cout << s1[i-1]<<" ";
		for (int j = 1; j < s2.size() + 1; j++) {
			if (flag[i][j] == 1) {
				std::cout << "↖ ";
			}
			else if(flag[i][j] == 2){
				std::cout <<  "↑ ";
			}
			else if(flag[i][j] == 3){
				std::cout << "← ";
			}
			else {
				std::cout << flag[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	int i = s1.size(), j = s2.size();
	std::string res;
	while (true)
	{
		if (i == 0 || j == 0) {
			break;
		}
		if (flag[i][j] == 1) {
			res = s1[i - 1] + res;
			i--;
			j--;
		}
		else if(flag[i][j]==2){
			i--;
		}
		else if (flag[i][j] == 3) {
			j--;
		}
	}
	std::cout <<"最长的公共子序列为:"<< res<<std::endl;
}


int LongestCommonSubsequence(std::string s1, std::string s2) {
	int n1 = s1.length();
	int n2 = s2.length();
	if (n1 == 0 || n2 == 0) {
		return 0;
	}
	std::string res;
	std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2+1,0));
	flag = dp;
	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (s1[i - 1] == s2[j - 1]) {  // 相等说明找到一个
				dp[i][j] = dp[i - 1][j - 1] + 1;
				flag[i][j] = 1;
			}
			else {  // 不相等的情况
				dp[i][j] = std::max(dp[i-1][j],dp[i][j-1]);
				if (dp[i][j] == dp[i - 1][j]) {
					flag[i][j] = 2;
				}
				else{
					flag[i][j] = 3;
				}
			}
		}
	}
	return dp[n1][n2];
}

