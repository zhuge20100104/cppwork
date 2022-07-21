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
    string trans(string s, int n) {
        // write code here
        stack<string> st;
        // 最后一个字符串是一种特殊情况，也需要被计算进来，所以要预先加一个空格
        s += ' ';
        string str;
        // 现在字符串长度为n+1了，需要<=n
        for(int i=0; i<=n; ++i) {
            // 说明找到了某个单词，或者连续空格，
            // 连续空格也会插入一个空串
            if(s[i] == ' ') {
                st.push(str);
                // 清空当前串，连续空格将插入空串
                str = "";
            } else {
                if(s[i] >= 'a' && s[i] <= 'z') {
                    str += s[i] - 'a' + 'A';
                }

                if(s[i] >= 'A' && s[i] <= 'Z') {
                    str += s[i] - 'A' + 'a';
                }
            }
        }

        stringstream ss;
        while(!st.empty()) {
            ss << st.top(); 
            st.pop();
            ss << " ";
        }

        auto res = ss.str();
        return res.substr(0, res.size() - 1);
    }

};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string words;
    Solution sol;
    while(getline(cin, words)) {
        auto res = sol.trans(words, words.size());
        cout << res << endl;
    }

    return EXIT_SUCCESS;
}