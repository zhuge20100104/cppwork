#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty()) {
            return false;
        }

        int m{(int)board.size()}, n{(int)board[0].size()};
        // m 行 n列的false数组，表示没有被访问过
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        bool find{false};
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                backtracking(i, j, board, word, find, visited, 0);
            }
        }
        return find;
    }

    void backtracking(int i, int j, vector<vector<char>>& board, string& word, bool& find, vector<vector<bool>>& visited, int pos) {
        // 检查是否越界
        if(i<0 || i>=board.size() || j<0 || j>=board[0].size()) {
            return;
        }

        if(visited[i][j] || find || board[i][j] != word[pos]) {
            return;
        }
        // 说明找完了，刚好找到整个单词
        if(pos == word.size() - 1) {
            find = true;
            return;
        }

        visited[i][j] = true; // 修改当前节点状态
        // 递归子结点
        backtracking(i+1, j, board, word, find, visited, pos+1); // 下面
        backtracking(i-1, j, board, word, find, visited, pos+1); // 上面
        backtracking(i, j+1, board, word, find, visited, pos+1); // 右边
        backtracking(i, j-1, board, word, find, visited, pos+1); // 左面 
        visited[i][j] = false; // 回溯到上一次的状态
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<vector<char>> board {{'A','B','C', 'E'},{'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word{"ABCCED"};
    auto exist = s.exist(board, word);
    if(exist) {
        cout << word << " exist in: " << board << "\n"; 
    } else {
        cout << word << " not exist in: " << board << "\n";
    }
    return EXIT_SUCCESS;
}