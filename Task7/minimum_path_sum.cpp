#include"minimum_path_sum.h"

void TestMPS() {
	std::vector<std::vector<int>> grid = { {1,3,8},{7,5,1},{4,2,1} };
	std::cout <<"��С·����Ϊ: "<< MinimumPathSum(grid) << std::endl;
}


// ����һ�������Ǹ������� m x n �������ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��
  
// ˵����ÿ��ֻ�����»��������ƶ�һ����

// ����:
// [
//	[1, 3, 1],
//	[1, 5, 1],
//	[4, 2, 1]
// ]
// ��� : 7
//	���� : ��Ϊ·�� 1��3��1��1��1 ���ܺ���С��

// ���ô����ϵ����±���
int MinimumPathSum(std::vector<std::vector<int>>& grid) {
	// ��ʼ��״̬����
	std::vector<std::vector<int>> dp(grid.size(), std::vector<int>(grid[0].size(),0));
	dp[0][0] = grid[0][0];
	// ��Կ���Ϳ��ϱߵĳ�ʼ��
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