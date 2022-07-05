#include "printer/printer.hpp"

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> res;

    void backtrack(vector<int>& candidates,
                   vector<int> tem,
                   int target,
                   int startindex) {
        int zhx;
        
        cout << "tem: " << tem << "\n";

        for (int i = startindex; i < candidates.size();) {
            tem.emplace_back(candidates[i]);
            zhx = target - candidates[i];
            if (zhx < 0) {
                tem.pop_back();
                break;
            } else if (zhx == 0) {
                cout << "Final tem:" << tem << "\n";
                res.emplace_back(tem);
            } else if (zhx > 0) {
                backtrack(candidates, tem, zhx, i + 1);
            }
            tem.pop_back();
            //去重
            i++;
            cout << "Before: " << i << "\n";
            cout << "Start index: " << startindex << "\n";
            while (i < candidates.size() && candidates[i] == candidates[i - 1])
                i++;
            cout << "After: " << i << "\n";
        }
    }

   public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        //排序用来剪枝、去重
        sort(candidates.begin(), candidates.end());
        vector<int> tem;
        backtrack(candidates, tem, target, 0);
        return res;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    // 1, 1, 2, 5, 6, 7, 10 
    // 把第1轮中相同的1去掉，就避免重复了
    vector<int> candidates{10, 1, 2, 7, 6, 1, 5};
    int target{8};
    auto res = s.combinationSum2(candidates, target);
    cout << res << "\n";
    return EXIT_SUCCESS;
}