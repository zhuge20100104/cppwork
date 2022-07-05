#include "printer/printer.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    int n, m;
    void dfs(vector<vector<char>>& board, int i, int j) {
        if(i<0 || i>=n || j<0 || j>=m || board[i][j] != 'O') {
            return;
        }

        // 先把搜索到的'O'置为 'A'
        board[i][j] = 'A';
        // 深度优先搜索上下左右四个方向
        dfs(board, i-1, j); // 上
        dfs(board, i, j+1); // 右
        dfs(board, i+1, j); //下
        dfs(board, i, j-1); //左
    }
    
public:
    // 有两类‘O’字符，一类是挨着边的，或者和挨着边的O相连的
    // 这种不能填充。
    // 另一种是不挨边的，这种可以填充，
    // 我们可以把挨着边的标记为'A'
    // 不挨边的不标记
    // 挨着边的可以到时候回退为'O'
    // 不挨边的'O'直接标记为'X'
    void solve(vector<vector<char>>& board) {
        // 当前矩阵的行数
        n = board.size();
        if(!n) {
            // 空矩阵，直接return
            return;
        }
        // 矩阵的列数
        m = board[0].size();
        // 第1列和最后一列
        // 深度优先搜索，把边缘‘O’置'A'
        for(int i=0; i<n; ++i) {
            dfs(board, i, 0);
            dfs(board, i, m-1);
        }

        // 第一行和最后一行
        for(int i=1; i<m-1; ++i) {
            dfs(board, 0, i);
            dfs(board, n-1, i);
        }

        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                if(board[i][j] == 'A') {
                    // 边缘'O'，还原
                    board[i][j] ='O';
                }else if(board[i][j] == 'O') {
                    // 非边缘'O', 设置成'X'
                    board[i][j] = 'X';
                }
            }
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    return EXIT_SUCCESS;
}