#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public: 
    int findMin(vector<int>& nums) {
        auto ele_it = min_element(nums.begin(), nums.end());
        return *ele_it;
    }
    
    // 顺序查找，查找第一个变小的值，它就是最小值
    // 时间复杂度为 O(n)
    int findMin_seq(vector<int>& nums) {
        int n = nums.size();
        // 只有一个元素
        if(n == 1) {
            return nums[0];
        }
        // 从头到尾遍历，寻找转折点
        for(int i=0; i<nums.size()-1; ++i) {
            if(nums[i] > nums[i+1]) {
                return nums[i+1];
            }
        }
        // 都是一样大
        return nums[0];
    }

    // 使用二分查找法，查找旋转数组的最小元素
    int findMin_bin(vector<int>& nums) {
        int n = nums.size();
        // 只有一个元素, return nums[0]
        if(n  == 1) {
            return nums[0];
        }
        int l {0}, r{n - 1};
        while(l<r) {
            int mid = l + (r-l)/2;
            // 左半部分有序，右半部分无序
            // 最小值应该在 右半部分
            // mid不可能是最小值，去(mid, r] 区间查找
            if(nums[mid] > nums[r]) {
                l = mid + 1;
                // 两个边界值相等，不知道哪边有序，哪边无序
                // 直接 --r，继续处理
            } else if(nums[mid] == nums[r]) {
                --r;
                // nums[mid] < nums[right]，右边有序，最小值在左边
                // 最小值可能是mid，为什么呢？ 因为mid比right小
                // 有机会成为最小值
                // 去 [left, mid] 区间继续查找
            } else {
                r = mid;
            }
        }
        return nums[l];
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}