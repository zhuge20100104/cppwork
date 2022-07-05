#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        // n = 1 1种
        // n = 2 2种 1+1, 2 
        // n = 3 3种 1+2, 2+1, 1+1+1
        // n = 4 5种 2+2, 2+1+1, 1+1+2, 1+2+1, 1+1+1+1+1

        if(n<=2) return n;
        vector<int> dp(n+1, 1);
        for(int i=2; i<=n; ++i) {
            // dp[2] = dp[1] + dp[0] = 1+1 = 2
            // dp[3] = dp[2] + dp[1] = 2+1 = 3
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}