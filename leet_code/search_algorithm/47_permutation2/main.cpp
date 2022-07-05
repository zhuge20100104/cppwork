#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

class Solution {
    vector<int> vis;
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        // 说明我们已经找到一个全排了
        if(idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }

        // 回溯nums， 查找其他全排
        for(int i=0; i<nums.size(); ++i) {
            // 两种情况，vis[i]访问过了，不用再访问，跳过
            // 第二种情况是， vis[i-1] == vis[i] 并且vis[i-1]没访问过
            // 有一种 a 1, b1的情况
            // 为避免 a1, b1 和 b1, a1
            // 被当作两种情况
            // 强制要求先访问a1, 再访问b1
            if(vis[i] || (i>0 && nums[i-1]==nums[i] && !vis[i-1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx+1, perm);
            vis[i] = 0;      // 这一级 找完以后，回溯到原始状态
            perm.pop_back(); // 这一级 找完以后，回溯到原始状态
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // 所有可行的全排列答案
        vector<vector<int>> ans;
        // 当前答案
        vector<int> perm;
        // 是否已经访问过的记录，访问过置为1，没访问过是0
        // 默认为全0
        vis.resize(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}