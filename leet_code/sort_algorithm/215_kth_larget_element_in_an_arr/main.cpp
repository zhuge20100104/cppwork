#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

class Solution {
public: 
    // 暴力解法，排序数组，返回下标 k - 1 
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[k-1];
    }

    // 使用大顶堆
    // 大顶堆每个父节点都比子节点大
    int findKthLargest_priority_queue(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, less<int>> q;
        for(auto const& num: nums) {
            q.emplace(num);
        }
        for(int i=0; i<k-1; ++ i) {
            q.pop();
        }
        return q.top();
    }

    // 使用快速选择方法
    // 对数字进行快速排序
    // 第k大的元素一定在 nums.size() - k位置。
    // 我们只管中轴(pivot)元素的索引是否为 nums.size() - k，不管
    // 轴元素两侧是否有序
    int findKthLargest_quick_select(vector<int>& nums, int k) {
        // 初始化随机数种子
        srand(time(nullptr));
        return quick_select(nums, 0, nums.size()-1, nums.size() - k);
    }

    int quick_select(vector<int>& nums, int l, int r, int index) {
        int curr_idx = random_partition(nums, l, r);
        if(curr_idx == index) {
            return nums[curr_idx];
        } else {
            return curr_idx < index? quick_select(nums, curr_idx+1, r, index): quick_select(nums, l, curr_idx - 1, index);
        }
    }
    
    int random_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r-l+1) + l;
        // 将随机元素和最右边的轴元素调换
        swap(nums[i], nums[r]);
        return partition(nums, l, r);
    }

    int partition(vector<int>& nums, int l, int r) {
        int key = nums[r], i = l - 1;
        // 将最右侧元素作为pivot，从左向右扫描，只要有元素小于key，
        // 就将该元素放到轴元素的左侧，剩下的轴元素右侧的元素，自然大于
        // 轴元素
        for(int j=l; j<r; ++j) {
            if(nums[j] < key) {
                // 调换到最左侧
                swap(nums[++i], nums[j]);
            }
        }
        // 把轴元素放到它该放的位置
        swap(nums[i+1], nums[r]);
        return i+1;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {10, 9, 7, 8, 1, 2, 3, 4, 6, 5};
    int k {3};
    auto res = s.findKthLargest_quick_select(nums, k);
    cout << "The " << k << "th largest element is: " << res << "\n";
    return EXIT_SUCCESS;
}