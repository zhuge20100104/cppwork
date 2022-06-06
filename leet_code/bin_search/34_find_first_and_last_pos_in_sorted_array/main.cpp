#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 线性查找法，时间复杂度为O(n),不满足条件
    // 空间复杂度为 O(1), 常量空间
    vector<int> searchRange(vector<int>& nums, int target) {
        // 设定左右边界初值
        int left {-1}, right{-1};

        for(int i=0; i<nums.size(); ++i) {
            // 如果找到左边界
            if(nums[i] == target) {
                // 记录左边界
                left = i;
                // 不越界的情况下寻找右边界
                // 直到找到第一个不是target的数
                while(++i<nums.size() && nums[i]==target);
                // 右边界往前移动1
                right = i-1;
                break;
            }
        }
        return {left, right};
    }
    
    // 手写std::lower_bound算子
    int findFirstPos(vector<int>& nums, int target) {
        int left{0}, right{(int)nums.size()-1};
        while(left < right) {
            int mid = (left + right) >> 1;
            if(nums[mid] > target) {
                // 继续搜索 [left，mid)区间，注意是左闭右开区间
                right = mid - 1;
            } else if(nums[mid] == target) {
                // 搜索到当前元素，
                // 继续往做搜索left bound
                // 区间为 [left, mid]
                right = mid;
            } else {
                // nums[mid] < target，
                // 继续搜索 (mid, right]区间，注意是左开右闭区间
                left = mid + 1;
            }
        }
        // 排除没有搜索到的情况
        if(nums[left] == target) {
            return left;
        }
        return -1;
    }  
    
    // 手写std::upper_bound算子
    int findLastPos(vector<int>& nums, int target) {
        int left{0}, right{(int)nums.size()-1};
        while(left < right) {
            // 这里这个加1 是个坑，题解也没说为啥。得自己试试，实际不加1无法退出循环
            // 可以自己debug看一下 (gdb)
            int mid = (left + right + 1) >> 1;
            if(nums[mid] > target) {
                // 继续搜索 [left，mid)区间，注意是左闭右开区间
                right = mid - 1;
            } else if(nums[mid] == target) {
                // 搜索到当前元素，
                // 继续往右搜索right bound
                // 区间为 [mid, right]
                left = mid;
            } else {
                // nums[mid] < target，
                // 继续搜索 (mid, right]区间，注意是左开右闭区间
                left = mid + 1;
            }
        }
        // 排除没有搜索到的情况
        if(nums[left] == target) {
            return left;
        }
        return -1;
    }  

    vector<int> searchRangeBinSearch(vector<int>& nums, int target) {
        if(!nums.data() || nums.empty()) {
            return {-1, -1};
        }

        int first = findFirstPos(nums, target);
        if(first == -1) {
            return {-1, -1};
        }

        int last = findLastPos(nums, target);
        return {first, last};
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    int target{2};
    vector<int> nums {2, 2};
    auto indexes = s.searchRange(nums, target);
    cout << indexes << "\n";
    return EXIT_SUCCESS;
}