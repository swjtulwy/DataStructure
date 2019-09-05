#include"minimum_path_sum.h"

void TestMPS() {
	std::vector<std::vector<int>> grid = { {1,3,8},{7,5,1},{4,2,1} };
	std::cout <<"最小路径和为: "<< MinimumPathSum(grid) << std::endl;
}


// 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
  
// 说明：每次只能向下或者向右移动一步。

// 输入:
// [
//	[1, 3, 1],
//	[1, 5, 1],
//	[4, 2, 1]
// ]
// 输出 : 7
//	解释 : 因为路径 1→3→1→1→1 的总和最小。

// 采用从左上到右下遍历
int MinimumPathSum(std::vector<std::vector<int>>& grid) {
	// 初始化状态数组
	std::vector<std::vector<int>> dp(grid.size(), std::vector<int>(grid[0].size(),0));
	dp[0][0] = grid[0][0];
	// 针对靠左和靠上边的初始化
	for (int i = 1; i < grid.size(); i++) {
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int i = 1; i < grid[0].size(); i++) {
		dp[0][i] = dp[0][i - 1] + grid[0][i];
	}
	for (int i = 1; i < grid.size(); i++) {
		for (int j = 1; j < grid[0].size(); j++) {
			if (dp[i - 1][j] > dp[i][j - 1]) {
				dp[i][j] = dp[i][j - 1] + grid[i][j];
			}
			else{
				dp[i][j] = dp[i - 1][j] + grid[i][j];
			}
		}
	}
	return dp[grid.size() - 1][grid[0].size() - 1];
}