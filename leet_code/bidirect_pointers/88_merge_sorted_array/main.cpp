#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 时间复杂度 (m+n)*log(m+n)
    // 空间复杂度 log(m + n)
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        nums1.erase(nums1.begin() + m, nums1.end());
        copy(nums2.begin(), nums2.end(), back_inserter(nums1));
        sort(nums1.begin(), nums1.end());
    }

    void merge_insert(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 {0}, p2{0}, cur{0};
        vector<int> sorted(m+n, 0);
        for(int i=0; i<m+n; ++i) {
            // 说明nums1搞完了
            if(p1==m) {
                cur = nums2[p2++];
                // 说明 nums2搞完了
            } else if(p2==n) {
                cur = nums1[p1++];
                // 都没搞完，nums1比较小
            } else if(nums1[p1] < nums2[p2] ){
                cur = nums1[p1++];
            } else {
                cur = nums2[p2++];
            }
            sorted[p1+p2-1] = cur;
        }
        sorted.swap(nums1);
    } 

    void merge_insert2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1{m-1}, p2{n-1};
        int tail {m+n-1};
        int cur{0};
        while(p1>=0 || p2>=0) {
            // 数组1 完事了
            if(p1 == -1) {
                cur = nums2[p2--];
                //数组2 完事了
            }else if(p2==-1) {
                cur = nums1[p1--];
                // 两个都还有，大的放后面
            } else if(nums1[p1] > nums2[p2]) {
                cur = nums1[p1--];
            } else {
                cur = nums2[p2--];
            }
            nums1[tail--] = cur;
        }
    }
};

auto main(int argc, char** argv) -> int {
    vector<int> nums1 {1,2,3,0,0,0};
    vector<int> nums2 {2,5,6};
    
    cout << "before merge: " << endl;
    cout << "nums1: " << nums1 << endl;
    cout << "nums2: " << nums2 << endl;

    Solution s;
    // s.merge(nums1, 3, nums2, nums2.size());
    // cout << "after merge, result is: " << nums1 << endl;

    // s.merge_insert(nums1, 3, nums2, nums2.size());
    // cout << "after merge_insert, result is: " << nums1 << endl;

    s.merge_insert2(nums1, 3, nums2, nums2.size());
    cout << "after merge_insert2, result is: " << nums1 << endl;

    return EXIT_SUCCESS;
}