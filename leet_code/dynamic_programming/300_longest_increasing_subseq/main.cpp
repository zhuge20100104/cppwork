#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // 处理空数组情况
        if(nums.size() == 0) {
            return 0;
        }

        vector<int> dp(nums.size(), 1);
        for(int i=0; i<nums.size(); ++i) {
            for(int j=0; j<i; ++j) {
                // 后面比前面的大，需要更新当前最大子序列值
                if(nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string arr_str;
    while(getline(cin, arr_str)) {
        stringstream ss{arr_str};
        int temp;
        vector<int> nums;
        while(ss >> temp) {
            nums.push_back(temp);
        }

        auto res = s.lengthOfLIS(nums);
        cout << res << endl; 
    }
    return EXIT_SUCCESS;
}