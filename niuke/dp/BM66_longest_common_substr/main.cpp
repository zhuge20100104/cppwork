#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    string LCS(string str1, string str2) {
        // write code here
        // 保存当前的最长子串长度
        int max_{0};
        // 保存当前最长子串的最终索引
        int idx {0}; 

        auto len1{(int)str1.size()}, len2{(int)str2.size()};

        // 动态规划数组
        vector<vector<int>> dp(len1 + 1, vector<int>(len2+1, 0));
        for(int i=0; i<len1; ++i) {
            for(int j=0; j<len2; ++j) {
                if(str1[i] == str2[j]) {
                    dp[i+1][j+1] = dp[i][j] + 1;
                    if(max_ < dp[i+1][j+1]) {   
                        max_ = dp[i+1][j+1];
                        idx = i+1; 
                    }
                }
            }
        }

        return str1.substr(idx-max_, max_);
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