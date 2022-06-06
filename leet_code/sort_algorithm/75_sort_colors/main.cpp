#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;


class Solution {
public:
    // 方法1：直接使用std::sort进行排序，但是不符合题目要求
    void sortColors(vector<int>& nums) {
        sort(nums.begin(), nums.end());
    }
    
    // 方法2: 使用哈希表统计数字出现的次数，然后再还原
    void sortColors_hash_table(vector<int>& nums) {
        array<int, 3> res {0};
        for(auto num: nums) {
            ++ res[num];
        }

        int cnt {0};
        for(int i=0; i<res.size(); ++i) {
            for(int j=0; j<res[i]; ++j) {
                nums[cnt++] = i;
            }
        }
    }
    
    // 方法3: 双指针快排扫描法
    void sortColors_quick_sort(vector<int>& nums) {
        int len = nums.size();
        // 只有一个元素，直接返回
        if(len < 2) {
            return;
        }
        // 分界点
        // all in [0, p0) == 0
        // all in [p0, i) == 1
        // all in (p2, len-1] == 2
        int p0{0};
        int i{0};
        int p2{len - 1};

        // 因为上面区间 i p2都是开区间，所以需要  <= p2
        while(i <= p2) {
            // 把等于0 的元素放到p0位置，p0往后移
            if(nums[i] == 0) {
                swap(nums[i++], nums[p0++]);
            } else if(nums[i] == 1) {
                ++i;
                // nums[i] == 2
                // 把nums[i] 和 nums[p2]进行交换
                // 把2放到右边去
            } else {
                swap(nums[i], nums[p2--]);
            }
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {2,0,2,1,1,0};

    cout << "Before sort: " << nums << "\n";
    s.sortColors_hash_table(nums);
    cout << "After sort: " << nums << "\n";

    return EXIT_SUCCESS;
}