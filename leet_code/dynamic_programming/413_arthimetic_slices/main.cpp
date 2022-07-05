#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        // 必须大于等于3个数，才能组成等差数列
        if(n < 3) return 0;
        vector<int> dp(n, 0);
        for(int i=2; i<n; ++i) {
            // nums[i-2] nums[i-1] nums[i]构成三个数的等差数列
            if(nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                // 以i 结尾的数列个数，是以i-1结尾的数列个数  + 1
                // 这是一个递推公式，自己看一下就知道了
                dp[i] = dp[i-1] + 1;
            }
        }
        // 需要累加所有可能的数列，不管是以多少结尾的。
        return accumulate(dp.begin(), dp.end(), 0);
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}