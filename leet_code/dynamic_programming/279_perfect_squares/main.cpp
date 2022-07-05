#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, 0);

        for(int i=1; i<=n; ++i) {
            // 默认初始化为i，表示i个1的平方相加
            dp[i] = i;
            for(int j=1; j*j<=i; ++j) {
                dp[i] = min(dp[i], dp[i-j*j] + 1);
            }
        }
        return dp[n];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    int n;
    while(cin >> n) {
        auto res = s.numSquares(n);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}