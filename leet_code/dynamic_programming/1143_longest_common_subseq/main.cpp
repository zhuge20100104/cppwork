#include "printer/printer.hpp"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        // 第一行是 dp[0: j]， 其中 text1[0:0]长度为0，最长公共子串为0
        // 第一列是 dp[i: 0],  其中 text2[0:0]长度为0，最长公共子串为0
        vector<vector<int>> dp (m+1, vector<int>(n+1, 0));

        for(int i=1; i<=m; ++i) {
            for(int j=1; j<=n; ++j) {
                if(text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[m][n];
    }
};

int main(int argc, char** argv) {
    Solution s;
    string text1, text2;
    while(cin >> text1 >> text2) {
        auto res = s.longestCommonSubsequence(text1, text2);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}