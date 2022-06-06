#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public: 
    // 方法1， unordered_map存储字符
    // std::sort排序
    // 连接字符
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for(auto const& ch: s) {
            ++mp[ch];
        }

        vector<pair<char, int>> vec;
        for(auto const& p: mp) {
            vec.emplace_back(p);
        }

        sort(vec.begin(), vec.end(), [](auto const& p1, auto const& p2) {
            return p1.second > p2.second;
        });

        stringstream ss;
        for(auto const& [ch, cnt]: vec) {
            for(int i=0; i<cnt; ++i) {
                ss << ch;
            }
        }
        return ss.str();
    }

    // 方法2， unordered_map 存储字符
    // 使用桶 装相同数量的字符在同一个桶内
    // 将桶中的字符还原，返回
    string frequencySort_buckets(string s) { 
        unordered_map<char, int> mp;
        int max_ch {0};
        for(auto const& ch: s) {
            max_ch = max(max_ch, ++mp[ch]);
        }

        vector<string> buckets (max_ch + 1);
        for(auto const& [ch, cnt]: mp) {
            buckets[cnt] += ch;
        }

        stringstream ss;
        for(int i=max_ch; i>0; --i) {
            for(auto const& ch: buckets[i]) {
                for(int cnt=0; cnt<i; ++cnt) {
                    ss << ch;
                }
            }
        }
        return ss.str();
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string str {"cccaaa"};

    cout << "Before frequency sort: " << str << "\n";
    auto res_str = s.frequencySort(str);
    cout << "After frequency sort: " << res_str << "\n";
    
    return EXIT_SUCCESS;
}