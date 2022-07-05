#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m{(int)grid.size()}, n{(int)grid[0].size()};

        vector<vector<int>> dp(m, vector<int>(n, 0));
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                // 原点，第一个数据
                if(i==0 && j==0) {
                    dp[i][j] = grid[i][j];
                    // 第一行
                } else if(i==0) {
                    dp[i][j] = dp[i][j-1] + grid[i][j];
                    // 第一列
                } else if(j==0) {
                    dp[i][j] = dp[i-1][j] + grid[i][j];
                    // i,j都不为0，中间的数字
                } else {
                    // 取上边或者左边的最小值
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
                }   
            }
        }
        return dp[m-1][n-1];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}