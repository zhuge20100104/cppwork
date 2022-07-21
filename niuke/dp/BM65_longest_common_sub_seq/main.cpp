#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

string const NO_COMMON_RESULT = "-1";
int constexpr LEFT_TOP = 1;
int constexpr LEFT_ = 2;
int constexpr TOP = 3;



class Solution {
   
    string x{""};
    string y{""};

public:

    string ans(int i, int j, vector<vector<int>>& b) {
        string res {""};
        // 递归终止条件
        if(i==0 || j==0) {
            return res;
        }

        // 按照不同的方向进行递归，获取结果
        // 从左上方来的
        if(b[i][j] == LEFT_TOP) {
            res += ans(i-1, j-1, b);
            res += x[i-1];
            // 从左边来的
        } else if(b[i][j] == LEFT_) {
            res += ans(i-1, j, b);
            // 从上边来的
        } else if(b[i][j] == TOP) {
            res += ans(i, j-1, b);
        }

        return res;
    }

    /**
     * longest common subsequence
     * @param s1 string字符串 the string
     * @param s2 string字符串 the string
     * @return string字符串
     */
    string LCS(string s1, string s2) {
        // write code here
        // 如果两个字符串中有空串，就没有通用子串
        if(s1.size() == 0 || s2.size() == 0) {
            return NO_COMMON_RESULT;
        }
        int len1 = s1.size();
        int len2 = s2.size();

        x = s1;
        y = s2;

        vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
        vector<vector<int>> b(len1+1, vector<int>(len2+1, 0));

        for(int i=1; i<=len1; ++i) {
            for(int j=1; j<=len2; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    // 从左上方来
                    b[i][j] = LEFT_TOP;
                }else {
                    if(dp[i-1][j] > dp[i][j-1]) {
                        // 从左边来
                        dp[i][j] = dp[i-1][j];
                        b[i][j] = LEFT_;
                    } else {
                        // 从上边来
                        dp[i][j] = dp[i][j-1];
                        b[i][j] = TOP;
                    }
                }
            }
        }

        auto res = ans(len1, len2, b);
        return res.empty()? NO_COMMON_RESULT: res;
    }
};


// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    string s1, s2;
    string temp;
    Solution sol;
    while(cin >> temp) {
        auto pos = temp.find(',');
        s1 = temp.substr(0, pos);
        s2 = temp.substr(pos+1);

        auto res = sol.LCS(s1, s2);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}