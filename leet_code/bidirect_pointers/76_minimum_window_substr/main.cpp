#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        // chars 记录t中每个字符的数量
        vector<int> chars(128, 0);
        // flag表示每个字符是否在t中存在
        vector<bool> flag(128, false);

        for(int i=0; i<t.size(); ++i) {
            flag[t[i]] = true;
            ++chars[t[i]];
        }

        // 移动滑动窗口，不断更改统计数据
        // 统计窗口中字符的个数
        int cnt{0};
        // 滑动窗口的左栅栏
        int l{0};
        // 最终最小字符串的起始位置
        int min_l {0};
        // 最终最小字符串的长度，初始化为一个不可能达到的值，如果最后没有改变，
        // 就说明没有找到，
        // 否则最后改变了，小于这个值，就说明找到了
        int min_size {(int)s.size() + 1};
        // 从左向右扫描， 优先移动右窗口位置
        for(int r=0; r<s.size(); ++r) {
            // 说明s中的当前字符在t中存在
            if(flag[s[r]]) {
                // 注意统计的时候，只统计 t中的字符个数那么多次，多于t中的字符个数的，不计入cnt的统计范围内，cnt不++
                // 例如t中的a出现3次，那么而s中的a出现4次，那么cnt ++到3就不加了。
                // 但是 chars数组中的a的统计数还是要减，这样最终会减到-1 [3-4=-1]
                // 这个多出来的-1可以用来在向右滑动l的过程中使用，说明多统计了一次a，
                // 我们滑动l窗口的时候只有当++chars[a] > 0的时候才说明已经到达了a本身出现的次数，3次
                // 如果这个时候再看到char a，那就需要 -- cnt了，表示再向右滑动就会少一个字符a了 
                if(--chars[s[r]] >= 0) {
                    ++ cnt;
                }
                // 若目前滑动窗口中已经包含t的全部字符
                // 尝试将l右移，在不影响结果的情况下，获得最短子字符串
                while(cnt == t.size()) {
                    // 更新字符串起始位置和最小长度
                    if(r-l+1 < min_size) {
                        min_l = l;
                        min_size = r - l + 1;
                    }

                    if(flag[s[l]] && ++chars[s[l]]>0) {
                        -- cnt;
                    }

                    ++l;
                }
            }   
        }
        return min_size > s.size() ? "": s.substr(min_l, min_size);
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string source = "ADOBECODEBANC";
    string t = "ABC";
    auto res = s.minWindow(source, t);
    cout << "Source string: " << source << "\n";
    cout << "Dest string: " << t << "\n";
    cout << "Min window: " << res << "\n";
    return EXIT_SUCCESS;
}