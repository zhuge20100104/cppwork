#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>


using namespace std;


/**
 * (0,0) (0,1) (0,2) (0,3)
 * (1,0) (1,1) (1,2) (1,3)
 * (2,0) (2,1) (2,2) (2,3)
 * (3,0) (3,1) (3,2) (3,3)
 * 
 *  左对角线是 row-col
 *  右对角线是 row+col相等
*/
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res{};
        // 表示第n行的皇后放在第几位的数组
        vector<int> queens (n, -1);
        // 表示哪些列已经用过了，不能再用了 
        set<int> cols;
        // 左对角线 row-col相等
        set<int> diag1;
        // 右对角线 row+col相等
        set<int> diag2;
        backtrack(res, queens, n, 0, cols, diag1, diag2);
        return res;
    }

private:
    void backtrack(vector<vector<string>>& res, vector<int>& queens, int n, int row, set<int>& cols, set<int>& diag1, set<int>& diag2) {
        // 刚好到了n行了，可以加了
        if(row == n) {
            auto board = generateBoard(queens, n);
            res.emplace_back(std::move(board));
        } else {
            // 按列遍历
            for(int i=0; i<n; ++i) {
                if(cols.find(i) != cols.end()) {
                    continue;
                }
                // 左对角线
                int diagonal1 = row - i;
                if(diag1.find(diagonal1) != diag1.end()) {
                    continue;
                }
                // 右对角线
                int diagonal2 = row + i;
                if(diag2.find(diagonal2) != diag2.end()) {
                    continue;
                }
                // 当前row的第i列是queen
                queens[row] = i;
                cols.insert(i);
                diag1.insert(diagonal1);
                diag2.insert(diagonal2);
                backtrack(res, queens, n, row+1, cols, diag1, diag2);
                // 回溯到前一个状态
                queens[row] = -1;
                cols.erase(i);
                diag1.erase(diagonal1);
                diag2.erase(diagonal2);
            }
        }
    }

    vector<string> generateBoard(vector<int>& queens, int n) {
        vector<string> board {};
        // 每行生成一个row,row里面的queens[i]个字符是Q
        for(int i=0; i<n; ++i) {
            string row (n, '.');
            row[queens[i]] = 'Q';
            board.emplace_back(std::move(row));
        }
        return board;
    }

};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}