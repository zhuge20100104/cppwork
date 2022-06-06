#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 有两个条件:
    // 1. t是s的子串
    // 2. t是s的最长子串，或者t是s的字母序最小子串
    string findLongestWord(string s, vector<string>& dictionary) {
        string res {""};
        for(auto t: dictionary) {
            int i{0}, j{0};
            while(i<t.size() && j<s.size()) {
                if(t[i] == s[j]) {
                    ++i;
                }
                ++j;
            }
            if(i==t.size()) {
                // 两种情况，新出的t比res长
                // 新出的t和res一样长，但是字母序比较小
                // 此两种情况更新res
                if((t.size()> res.size()) || (t.size() == res.size() && (t < res))) {
                    res = t;
                }
            }
        }
        return res;
    }   
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string source_s {"abpcplea"};
    vector<string> dicts {"ale","apple","monkey","plea"};
    auto word = s.findLongestWord(source_s, dicts);
    cout << "Longest word in " << source_s << ": " << word << "\n";
    return EXIT_SUCCESS;
}