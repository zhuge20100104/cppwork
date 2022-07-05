#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>


using namespace std;


class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res {};
        vector<int> path{};
        helper(1, n, k, path, res);
        return res;
    }

    void helper(int start_idx, int n, int k, vector<int>& path, vector<vector<int>>& res) {
        // 说明已经选了k个了
        if(path.size() == k) {
            auto tmp_path(path);
            res.emplace_back(std::move(tmp_path));
            return;
        }

        // 这个题目和排列数不一样，需要剪枝
        // n =4 k=2 path.size() = 0 
        // i<= 4 -(2-0) + 1 = 3
        // 刚好到3， 4是一个空集合，没有元素，
        // 4需要被剪枝
        for(int i=start_idx; i<= n -(k-path.size())+1; ++i) { //剪枝    
            path.emplace_back(i);
            helper(i+1, n, k, path, res);
            path.pop_back(); // 回溯，加进去的元素要重新吐出来，回溯到上一层
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    return EXIT_SUCCESS;
}