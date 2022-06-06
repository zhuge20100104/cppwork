#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    void quick_sort(vector<int>& nums, int l, int r) {
        // 只有一个元素的情况
        // 0 + 1 >= 1
        // 或者左边界+1 大于右边界
        if(l+1>=r) {
            return;
        }
        int first {l}, last {r-1}, key = nums[first];
        // 指针仍在迭代的过程中，本轮迭代未完成
        // 左边元素仍未完全小于key，右边元素没有完全大于key
        while (first < last) {
            // 本来就比key大，应该在key的右边，那么往前移
            while(first < last && nums[last] >= key) {
                --last;
            }
            // 此处 nums[last] 比key 小,放在key左边，
            // 可以放在first所在位置，因为边界值nums[first]缓存在key中可
            nums[first] = nums[last];

            // 本来就应该比key小，那就不管它
            // first往后走
            while(first < last && nums[first] <= key) {
                ++first;
            }
            // 到这个时候nums[first]应该比key大了
            // 可以放到key右边，这时nums[last]已经缓存到之前first的位置了
            // 可以放到last所在位置
            nums[last] = nums[first];
        }   
        // 此处first == last
        // 是分界点了,把key放进去
        nums[first] = key;

        // 递归处理 当前元素的 左半部分和右半部分
        quick_sort(nums, l, first);
        quick_sort(nums, first + 1, r);
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {10, 9, 7, 8, 1, 2, 3, 4, 6, 5};

    cout << "Before sort, nums: " << nums << "\n";  
    s.quick_sort(nums, 0, nums.size());
    cout << "After sort, nums: " << nums << "\n";
    
    return EXIT_SUCCESS;
}