#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;


class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans {0};
        for(int i=0; i<grid.size(); ++i) {
            for(int j=0; j<grid[0].size(); ++j) {
                // 使用std::max，逐次获取最大值
                ans = max(ans, islandDFS(grid, i, j));
            }
        }
        return ans;
    }

    // 递归返回有几块岛屿的函数
    int islandDFS(vector<vector<int>>& grid, int i, int j) {
        // 在边界范围之内
        if((i >= 0) && (i<grid.size()) && (j>=0) &&(j<grid[0].size())) {
            // 说明不是岛屿，返回0
            if(grid[i][j] == 0) {
                return 0;   
            } else { // 是岛屿，把当前位置置为0，避免重复计算
                grid[i][j] = 0;
                // 当前岛屿计数+1，再递归求其上下左右的岛屿数
                return 1 + islandDFS(grid, i-1,j) + islandDFS(grid, i+1, j) + islandDFS(grid, i, j-1) + islandDFS(grid, i, j+1); 
            }
        } else { // 已经越界，不在边界之内，return 0
            return 0;
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    
    return EXIT_SUCCESS;
}