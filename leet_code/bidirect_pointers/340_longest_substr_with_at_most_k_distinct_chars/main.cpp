#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        map<char, int> m;
        int left{0}, right{0}, cnt{0}, distance {0};
        // 滑动窗口右指针往右移， 遍历字符串
        while(right < s.size()) {
            char c = s[right];
            ++ m[c];
            // 首次出现
            // ++ cnt
            // cnt是用来统计k个不同的字符的
            if(m[c] == 1) {
                ++cnt; 
            } 
            // right 指针一直右移
            ++ right;
            // 说明已经有了k个字符了，开始移动左指针，直到 等于k个字符为止
            while(cnt > k) {
                auto tmp = s[left];
                // map中对应的值减少，减少到0时，表示减少了一个唯一字符，可以--cnt
                -- m[tmp];
                if(m[tmp] == 0) {
                    --cnt;
                }

                ++left;
            }

            distance = max(distance, right - left);
        }
        return distance;
    } 
};

void test_map() {
    map<char, int> m;
    ++m['a'];
    for(auto ele: m) {
        cout << "first: " << ele.first << " second: " << ele.second << "\n";
    }
}
auto main(int argc, char** argv) -> int {
    // test_map();
    Solution s;
    string str {"eceba"};
    int k {2};
    auto len_ = s.lengthOfLongestSubstringKDistinct(str, k);
    cout << "For string: " << str << "\n";
    cout << "Length of longest " << k << " distinct chars string is: " << len_ << "\n"; 
    return EXIT_SUCCESS;
}