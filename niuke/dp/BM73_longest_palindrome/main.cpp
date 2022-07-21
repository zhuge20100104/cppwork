#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    bool validatePalindrome(string str, int left, int right) {
        while(left < right) {
            if(str[left] != str[right]) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }

public:

    /**
     * 最长回文子串：解法二，动态规划 
     * 
     * */
    int getLongestPalindrome2(string A) {
        int len {(int)A.size()};
        if(len<2) {
            return 1;
        }

        int max_len{1};
        
        vector<vector<bool>> dp(len, vector<bool>(len, false));

        // 对角线上面的都是true， 因为从i -> i只有一个字符
        // 肯定是回文串
        for(int i=0; i<len; ++i) {
            dp[i][i] = true;
        }

        for(int j=1; j<len; ++j) {
            for(int i=0; i<j; ++i) {
                if(A[i] != A[j]) {
                    dp[i][j] = false;
                } else {
                    // j-1 -(i+1) + 1 <2
                    // j-1和 i+1的距离小于2了，说明回文无疑
                    if(j-i < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i+1][j-1];
                    }
                }

                if(j-i+1 > max_len && dp[i][j]) {
                    max_len = j-i+1;
                }
            }
        }
        
        return max_len;
    }

    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 最长回文子串： 解法一，暴力解法
     * 
     * @param A string字符串 
     * @return int整型
     */
    int getLongestPalindrome(string A) {
        int len {(int)A.size()};
        if(len == 1) {
            return 1;
        }

        int max_len{1};

        for(int i=0; i<len-1; ++i) {
            for(int j=i+1; j<len; ++j) {
                if(j-i+1>max_len && validatePalindrome(A, i, j)) {
                    max_len = j-i+1;
                }
            }
        }
        return max_len;
    }
};


// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string str;
    Solution sol;

    while(getline(cin, str)) {
        auto res = sol.getLongestPalindrome(str);
        cout << res << endl;
    }

    return EXIT_SUCCESS;
}