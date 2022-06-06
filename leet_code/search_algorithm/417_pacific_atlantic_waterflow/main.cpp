#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

// 左右下上 四个方向数组
static int const dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(); // 行数
        int n = heights[0].size(); // 列数
        // 流进太平洋的海水数组
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        // 流进大西洋的海水数组
        vector<vector<bool>> atlantic(m, vector<bool>(n, false)); 
        // 左侧能流进太平洋的海水
        for(int i=0; i<m; ++i) {
            dfs(i, 0, pacific, heights);
        }
        // 遍历上侧能流进太平洋的海水
        for(int j=0; j<n; ++j) {
            dfs(0, j, pacific, heights);
        }

        // 右侧能流进大西洋的海水
        for(int i=0; i<m; ++i) {
            dfs(i, n-1, atlantic, heights);
        }

        // 下侧能流进大西洋的海水
        for(int j=0; j<n; ++j) {
            dfs(m-1, j, atlantic, heights);
        }

        // 求两者的交集，就是既能流进太平洋，又能流进大西洋的海水集合
        vector<vector<int>> result;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(pacific[i][j] && atlantic[i][j]) {
                    vector<int> cell;
                    cell.emplace_back(i);
                    cell.emplace_back(j);
                    result.emplace_back(std::move(cell));
                }
            }
        }
        return result;
    } 

    void dfs(int row, int col, vector<vector<bool>>& ocean, vector<vector<int>>& heights) {
        // m,n 总行数，总列数
        int m{(int)ocean.size()};
        int n{(int)ocean[0].size()};
        // 说明已经 能流通了，不用再标记了
        if(ocean[row][col]) {
            return;
        }
        // 第一个在太平洋或者大西洋边上，肯定能进太平洋，或者大西洋
        // 后面的就要看 是不是具有>=关系了
        // 必须 >=才能流进去
        ocean[row][col] = true;
        // 从左右下上4个方向看，有没有能流进太平洋/大西洋的海水，
        // 如果有递归标记为true
        for(int i=0; i<4; ++i) {
            int newRow = row + dirs[i][0], newCol = col + dirs[i][1];
            if(newRow>=0 && newRow<m && newCol>=0 && newCol<n && heights[newRow][newCol]>=heights[row][col]) {
                dfs(newRow, newCol, ocean, heights);
            }
        }

    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    
    return EXIT_SUCCESS;
}