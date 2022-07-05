#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n{(int)nums.size()};
        vector<int> dp(n+1, 0);
        dp[1] = nums[0];

        for(int i=2; i<=n; ++i) {
            // 打家劫舍有两种可能性
            // 1. 抢 dp[i-1]最多，那就不能抢劫nums[i-1]，因为两者是相邻的
            // 2. 抢 dp[i-2]最多，那就可以抢劫nums[i-1]，因为两者相隔一个
            // 两者取大者，就是最多的
            dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);
        }
        return dp[n];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}