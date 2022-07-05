#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) {
            return false;
        }

        int sum = accumulate(nums.begin(), nums.end(), 0);
        // 奇数
        if(sum & 1)  {
            return false;
        }

        int target = sum / 2;
        
        // target + 1列 是因为需要考虑 和为0的情况
        vector<vector<bool>> dp(n+1, vector<bool>(target+1, false));
        if(nums[0] <= target) {
            dp[0][nums[0]] = true;
        }
        

        for(int i=1; i<n; ++i) {
            for(int j=0; j<=target; ++j) {
                // 默认不考虑nums[i], 直接继承上一行的值
                dp[i][j] = dp[i-1][j];

                if(nums[i] == j) {
                    dp[i][j] = true;
                    continue;
                }

                if(nums[i] < j) {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
                }
            }
        }

        return dp[n-1][target];
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
        auto res = s.canPartition(nums);
        if(res) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return EXIT_SUCCESS;
}