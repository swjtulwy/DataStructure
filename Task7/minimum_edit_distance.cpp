#include "minimum_edit_distance.h"


void TestMED() {
	std::string word1 = "intention";
	std::string word2 = "execution";
	std::cout << "单词 "<<word1<<" 和 "<<word2<<" 的莱文斯坦编辑距离为: "
		<<MinDistance(word1, word2)<<std::endl;
}

int MinDistance(std::string word1, std::string word2) {
	int n1 = word1.length();
	int n2 = word2.length();
	if (n1 * n2 == 0) { // 任何一个单词为0，则距离为两个单词长度之和
		return n1 + n2;
	}
	std::vector<std::vector<int>> dp(n1+1, std::vector<int>(n2+1, 0));
	for (int i = 1; i < n1 + 1; i++) {  // 第一列初始化
		dp[i][0] = i;
	}
	for (int i = 1; i < n2 + 1; i++) {  // 第一行初始化
		dp[0][i] = i;
	}

	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (word1.at(i - 1) == word2.at(j - 1)) {  // 子串最后一个字符相等
				dp[i][j] = dp[i - 1][j - 1];
			}
			else{
				dp[i][j] = std::min(std::min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1]) + 1;
			}
		}
	}
	return dp[n1][n2];
}