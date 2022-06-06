#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 方法1，线性查找，时间复杂度为 O(n)
    bool search(vector<int>& nums, int target) {
       auto ele_it = search_n(nums.begin(), nums.end(), 1, target);
       return ele_it != nums.end();
    }
    // 方法2, 二分查找，时间复杂度为 O(lg(n))
    bool search_bin(vector<int>& nums, int target) {
        int n {(int)nums.size()};
        // 空向量, 不可能包含target
        if(!n) {
            return false;
        } 
        
        // 单一元素向量，直接检查nums[0] 是否等于target
        if(n==1) {
            return (nums[0] == target);
        }

        // 设定左右双指针，准备开始循环
        int l{0}, r{n-1};

        while(l<=r) {
            int mid = (l+r) >> 1;
            if(nums[mid] == target) {
                return true;
            } 

            // 应对一种特殊情况.
            // nums=[3,1,2,3,3,3,3]，target=2
            // nums[l] == nums[mid] == nums[r] 
            // 这种情况无法预知 左边有序还是右边有序，左++，右--
            // 跳过相等的情况
            if(nums[l] == nums[mid] && nums[mid] == nums[r]) {
                // 此处注意 ++l的好处，复用了l，如果用 l++, 将产生一个临时变量
                ++l;
                --r;
                // 说明左边有序
                // 这边的几个等号是坑，得一个一个调 才知道
            } else if(nums[l] <= nums[mid]) {
                // target 在左半边, 在左半边有序区间接着找
                // [l, mid)
                if(nums[l] <= target && target < nums[mid]) {
                    r = mid - 1; 
                } else {
                    // 在右半边无序区间接着找
                    // (mid, right]
                    l = mid + 1;
                }
                // 说明右半边有序
            } else {
                // target 在右半边有序区间，在右半边有序区间内查找
                // (mid, right]
                if(nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                    // target 在左半边 无序区间，去左半边无序区间查找
                    // [l, mid)
                } else {
                    r = mid - 1;
                }
            }
        }
        return false;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {2,5,6,0,0,1,2};
    int target {0};
    auto contains = s.search_bin(nums, target);
    if(contains) {
        cout << nums << " contains " << target;
    } else {
        cout << nums << " not contains " << target;
    }
    cout << "\n";
    return EXIT_SUCCESS;
}