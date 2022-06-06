#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 使用std::merge算子
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), back_inserter(res));
        int size = res.size();
        if(1==size) {
            return (double)res[0];
        }
        int mid_size = size>>1;
        return size % 2 == 0? (double)(res[mid_size - 1] + res[mid_size]) /2:  (double)res[mid_size];
    }

    double findMedianSortedArrays_custom_merge(vector<int>& nums1, vector<int>& nums2) {
        int size1{(int)nums1.size()}, size2 {(int)nums2.size()};
        int i {size1-1}, j{size2-1}, q{size1+size2-1};
        nums1.resize(size1+size2);
        int cur{0};

        while(i>=0 || j >=0) {
            // nums1完事儿了
            if(i==-1) {
                cur = nums2[j--];
                // nums2完事儿了
            }else if(j==-1) {
                cur = nums1[i--];
                // 两个都没完事儿
            } else if(nums1[i] > nums2[j]) {
                cur = nums1[i--];
            } else {
                cur = nums2[j--];
            }
            nums1[q--] = cur;
        }

        int size =  nums1.size();
        if(1==size) {
            return (double)nums1[0];
        }
        int mid_size = size>>1;
        return size % 2 == 0? (double)(nums1[mid_size - 1] + nums1[mid_size]) /2:  (double)nums1[mid_size];
    }


    double findMedianSortedArrays_bin_search(vector<int>& nums1, vector<int>& nums2) {
        // 交换，让nums1变为长度较小的序列
        if(nums1.size() > nums2.size()) {
            nums1.swap(nums2);
        }

        int m = nums1.size();
        int n = nums2.size();
        // 分割线左边所有元素需要满足的个数
        // 如果(m+n)为偶数，则为(m+n)/2
        // 如果(m+n)为奇数，则为(m+n+1)/2,我们给左边多划一个元素，便于计算
        // 无论为偶数或者奇数，多加个1都无伤大雅，因为 加的那个1，在偶数情况下，/2就没了
        int total_left = (m+n+1) / 2;
        // 在nums1的[0,m]的区间内寻找合适的分割线
        // 使得nums1[i-1] <= nums2[j] && nums2[j-1] <= nums1[i]
        int left {0};
        int right {m};

        // 跳出时 left == right
        while(left < right) {
            // 从数组1的中间区间开始查找
            int i = left + (right - left + 1) /2 ;
            // 数组2的左端点位置，为total_left -i ，因为数组1+数组2的左端点位置和为total_left
            int j = total_left - i;
            // 违背规则了，数组1的前半部分的最后一个值比数组2的后半部分的最小值大
            // 说明靠后了，需要在 [left, i)区间继续查找
            if(nums1[i-1] > nums2[j]) {
                // 因为这里减了1，所以会取不到右端点，上面的i值计算要加1
                right = i - 1;
            } else {
                // 数组1的前半部分的最大值，比数组2的前半部分的最小值要小
                // 说明可以向后查找,知道left == right
                // 区间为 [i,right]
                left = i;    
            }
        }

        int i {left};
        int j {total_left - i};
        // i =0 说明 左边没有值，设置为最小整数值，避免被取到最大值
        int nums1_left_max = (i ==0? std::numeric_limits<int>::min(): nums1[i-1]);
        // 如果i =m，说明右边没有值了，取最大整数值，避免 被取到最小值
        int nums1_right_min = (i==m ? std::numeric_limits<int>::max(): nums1[i]);
        int nums2_left_max = (j==0? std::numeric_limits<int>::min(): nums2[j-1]);
        int nums2_right_min = (j==n? std::numeric_limits<int>::max(): nums2[j]);

        // 奇数
        if((m+n)%2==1) {
            return (double)max(nums1_left_max, nums2_left_max);
        } else {
            return (double)(max(nums1_left_max, nums2_left_max) + min(nums1_right_min, nums2_right_min))/ 2; 
        } 
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> nums1{1, 3};
    vector<int> nums2{2};
    auto median_val = s.findMedianSortedArrays_custom_merge(nums1, nums2);
    cout << "Median value: " << median_val << endl;
    return EXIT_SUCCESS;
}