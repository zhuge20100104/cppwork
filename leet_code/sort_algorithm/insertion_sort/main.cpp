#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 插入排序算法 refers to: https://www.runoob.com/data-structures/insertion-sort.html
    void inserion_sort(vector<int>& nums) {
        int n {(int)nums.size()};
        for(int i=0; i<n; ++i) {
            for(int j=i; j>0; --j) {
                if(nums[j-1] > nums[j]) {
                    swap(nums[j-1], nums[j]);
                }
            }
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {10, 9, 7, 8, 1, 2, 3, 4, 6, 5};
    cout << "Before insertion sort: " << nums << "\n";
    s.inserion_sort(nums);
    cout << "After insersion sort: " << nums << "\n";
    return EXIT_SUCCESS;
}