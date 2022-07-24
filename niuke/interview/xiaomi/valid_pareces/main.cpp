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
    bool isValid(string s) {
        int len = s.size();
        // 奇数长度，无法配对成 括号序列
        if(len % 2) {
            return false;
        }

        unordered_map<char, char> pairs {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        stack<char> chs;
        for(auto const& ch: s) {
            if(pairs.count(ch)) {
                // 前一个没匹配上， 或者栈为空，无法匹配，return false
                if(chs.empty() || chs.top() != pairs[ch]) {
                    return false;
                } else {
                    chs.pop();
                }
            } else {
                chs.push(ch);
            }
        }

        return chs.empty();
    }
};

int main(int argc, char* argv[]) {
    vector<string> test_cases {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}"
    };

    Solution sol;
    for(auto const& test_case: test_cases) {
        cout << test_case << " ";
        bool valid = sol.isValid(test_case);
        if(valid) {
            cout << "is valid ";
        } else {
            cout << "is not valid ";
        }
        cout << "parencess\n";
    }
    return EXIT_SUCCESS;
}