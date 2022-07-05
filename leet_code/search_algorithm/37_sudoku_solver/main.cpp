#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
    // 9*9 line 记录每一行是否放置过 1-9 9个数
    vector<vector<bool>> line;
    // 9*9 column 记录每一列是否放置过 1-9 9个数
    vector<vector<bool>> column;
    // 3*3*9  记录每一个九宫格是否放置过 1-9 9个数
    vector<vector<vector<bool>>> block;
    // 是否所有空位都已填充完成的标记
    bool valid;
    // 所有空位的索引记录
    vector<pair<int, int>> spaces;
 
    void dfs(vector<vector<char>>& board, int pos) {
        // 说明空位已经填完了
        if(pos == spaces.size()) {
            valid = true;
            return;
        }

        // 取出第pos个空格对应的索引位置
        auto [i, j] = spaces[pos];
        for(int digit=0; digit<9&&!valid; ++digit) {
            if(!line[i][digit] && !column[j][digit] && !block[i/3][j/3][digit]) {
                line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = true; // 设置标志位
                board[i][j] = digit + '0' + 1;
                dfs(board, pos+1); 
                line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = false; // 回溯
            }
        }

    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        line = {9, vector<bool>(9, false)};
        column = {9, vector<bool>(9, false)};
        block = {3, vector<vector<bool>>(3, vector<bool>(9, false))};
        valid = false;

        // 填充空值索引位置
        // 已经填充值的位置，标志位记为 true
        for(int i=0; i<9; ++i) {
            for(int j=0; j<9; ++j) {
                if(board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                } else {
                    // 减1适配到 [0-8]
                    int digit = board[i][j] - '0' - 1;
                    line[i][digit] = column[j][digit] = block[i/3][j/3][digit] = true; 
                }   
            }
        }

        dfs(board, 0);
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}