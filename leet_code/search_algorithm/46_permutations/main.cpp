#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>


using namespace std;


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> res {};
        if(!len) {
            // 返回空链表，没有排列
            return res;
        }
        deque<int> path{};

        vector<bool> used(len, false);
        dfs(nums, len, 0, path, used, res);
        return res;
    }

    void dfs(vector<int>& nums, int len, int depth, deque<int>& path, vector<bool>& used, vector<vector<int>>& res) {
        if(depth == len) {
            vector<int> sub_res;
            copy(path.begin(), path.end(), back_insert_iterator(sub_res));
            res.emplace_back(std::move(sub_res));
            return;
        }

        for(int i=0; i<len; ++i) {
            if(used[i]) {
                continue;
            }

            path.emplace_back(nums[i]);
            used[i] = true;
            dfs(nums, len, depth + 1, path, used, res);
            path.pop_back();
            used[i] = false;
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums{1, 2, 3};
    auto res = s.permute(nums);
    cout << res << "\n";
    return EXIT_SUCCESS;
}