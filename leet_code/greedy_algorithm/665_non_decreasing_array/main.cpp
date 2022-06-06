#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int n = nums.size();
        for(int i=0; i<n-1; ++i) {
            int x = nums[i], y = nums[i+1];
            // 出现非增序
            if(x>y) {
                // 先nums[i] = nums[i+1]
                nums[i] = y;
                // 如果是增序，直接return true
                if(is_sorted(nums.begin(), nums.end())){
                    return true;
                }
                // 如果不行，换下nums[i+1] = nums[i]
                nums[i] = x;
                nums[i+1] = x;  
                // 如果这两个都不行就是真不行了
                return is_sorted(nums.begin(), nums.end());
            }
        }  
        // 如果没有倒序，return true;
        return true; 
    }

    bool checkPossibilityEnhanced(vector<int>& nums) {
        int n = nums.size(), cnt = 0;
        for(int i=0; i<n-1; ++i) {
            int x = nums[i], y = nums[i+1];
            if(x > y) {
                ++ cnt;
                // 两次倒序， return false
                if(cnt > 1) {
                    return false;
                }
                // 如果后面的数字比前面的数字要小，倒序了
                // 注意能走到这里，说明nums[i-1] < nums[i]成立了
                // 这样我们把 nums[i+1] = nums[i]
                // 看后面是否升序就行了
                // 如果还有倒序，就是超过两次倒序
                // 说明不能通过一步改成升序，直接return false了
                if(i>0 && y < nums[i-1]) {
                    nums[i+1] = x;
                }
            }
        }
        return true;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums {4,2,3};
    auto can_increase = s.checkPossibilityEnhanced(nums);
    cout << nums;
    if(can_increase) {
        cout << " can ";
    }else {
        cout << " can't ";
    }

    cout << " be changed to increased array by one replace\n";
    return EXIT_SUCCESS;
}