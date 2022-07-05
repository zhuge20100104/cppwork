#include "printer/printer.hpp"

#include <vector>
#include <string>
#include <queue>

using namespace std;


class Solution {
    // 四个方向
    // -1, 0  上
    // 0, 1   右
    // 1, 0  下
    // 0, -1 左
    vector<int> direction {-1, 0, 1, 0, -1};
public:
    int shortestBridge(vector<vector<int>>& grid) {
        //  行数和列数
        int m {(int)grid.size()}, n{(int)grid[0].size()};
        // 把第一个岛屿的边界0区域存储到queue里面
        // 便于第二步使用queue做广度优先遍历
        queue<pair<int, int>> points;

        // dfs寻找第一个岛屿，并把1全部赋值为2
        // 这样在广度优先遍历的时候，就可以区分是否找到第二个岛屿了
        // 第一个岛屿是2，第二个岛屿是1       
        bool flipped {false};
        for(int i=0; i<m; ++i) {
            // 如果已经完成了遍历，退出循环，
            // 包括将所有第一个岛屿的节点改为2，
            // 将所有第一个岛屿的边界点放入points
            if(flipped) break;

            for(int j=0; j<n; ++j) {
                // 说明是岛屿，深度优先遍历其周围所有的节点
                if(grid[i][j] == 1) {
                    dfs(points, grid, m, n, i, j);
                    flipped = true;
                    break;
                }
            }
        } 

        // 广度优先遍历寻找第二个岛屿，从第一个岛屿的边界点开始
        // 并把过程中经过的0赋值为2
        int x, y;
        int level {0};
        while(!points.empty()) {
            // 走一步就计数
            ++level; 
            int n_points = points.size();
            while(n_points--) {
                auto [r, c] = points.front();
                points.pop();
                // 寻找上右下左四个点
                for(int k=0; k<4; ++k) {
                    x = r+direction[k];
                    y = c+direction[k+1];
                    // 判断边界
                    if(x>=0 && y>=0 && x<m && y<n) {
                        // 说明遍历到第一个岛屿，或者已标记的节点
                        if(grid[x][y] == 2) {
                            continue;
                        }
                        // 说明遍历到第二个岛屿，达到目的，返回步数
                        if(grid[x][y] == 1) {
                            return level;
                        }
                        // 遍历到0，当前步没有找到岛屿
                        // 下一步接着对当前点做广度优先遍历
                        points.push({x, y}); 
                        // 把0点置为2，以免重复遍历
                        grid[x][y] = 2;
                    }
                }
            }
        }

        return 0;
    }

    void dfs(queue<pair<int, int>>& points, vector<vector<int>>& grid, int m, int n, int i, int j) {
        // 遇到边界，或者已经标记为2，就退出
        if(i<0 || j<0 || i==m || j==n || grid[i][j]==2) {
            return;
        }

        // 说明所有相连的岛屿都完成了，遇到岛屿边界了
        if(grid[i][j] == 0) {
            // 岛屿边界点放入 points
            points.push({i, j});
            return;
        }

        // 把第一座岛屿标为2
        grid[i][j] = 2;
        // 深度优先遍历上右下左 四个点
        dfs(points, grid, m, n, i-1, j);
        dfs(points, grid, m, n, i, j+1);
        dfs(points, grid, m, n, i+1, j);
        dfs(points, grid, m, n, i, j-1);
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    return EXIT_SUCCESS;
}