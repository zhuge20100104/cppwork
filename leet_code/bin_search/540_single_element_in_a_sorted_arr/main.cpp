#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 暴力法，时间复杂度为 O(n)
    int singleNonDuplicate_1(vector<int>& nums) {
        int n {(int)nums.size()};
        if(n == 1) return nums[0];
        int i {0};
        for(; i+2 < n; i+=2) {
            if(nums[i] != nums[i+1]) return nums[i];
        }

        // 此处最后一个元素是单一元素
        // 使用gdb进行调试就可以知道 以下事实
        // i = 2 nums.size() = 3
        // i = nums.size() - 1
        // 注意 i 已经加过2，变成 nums.size() - 1了，才会退出循环
        if(i == n - 1) {
            return *nums.rbegin();
        }
        return -1;
    }

    // 二分法，时间复杂度为O(lg(n))
    int singleNonDuplicate(vector<int>& nums) {
        int l {0}, r{(int)nums.size() - 1};
        // 二分法查找元素，这个标记位比较有意思
        while(l < r) {
            // 求元素中位
            auto mid = (l + r) >> 1;
            // 有两种情况，表示单一非重复元素不在前半部分
            // mid为偶数， a[mid] = a[mid + 1]
            // mid为奇数， a[mid - 1] = a[mid]
            // 这两种情况都可以概括为:
            // a[mid] = a[mid ^ 1], 所以不用区分奇偶 了
            // 当mid为偶数时 mid ^ 1 = mid + 1
            // 当mid为奇数时 mid ^ 1 = mid - 1
            // 所以上面一句就代表了两种情况
            // 另一个值的注意的点就是mid和它相邻的点相等了，说明mid位置的元素重复了，所以在
            // (m,r] 区间继续寻找
            if(nums[mid] == nums[mid ^ 1]) {
                l = mid + 1;
            } else {
                // 这里代表mid和它相邻的元素不等，说明不重复的元素在前半部分。
                // 因为mid和相邻的元素不等，所以有可能是单一元素，去
                // [l, mid] 区间寻找
                r = mid;
            }
        }
        return nums[l];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums{1, 1, 2};
    auto res = s.singleNonDuplicate_1(nums);
    cout << "Single element in vector " << nums << " is: ";
    cout << res << "\n";
    return EXIT_SUCCESS;
}