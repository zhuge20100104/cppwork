#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 特殊情况，区间为空，不需要移除
        if(intervals.empty()) {
            return 0;
        }
        int n = intervals.size();
        // 按照每个区间的后一个元素顺序排序，然后便于比较当前区间的后一个元素和下一区间的前一个元素是否相交，
        // 如果相交，移除区间个数加1
        sort(intervals.begin(), intervals.end(), [](std::vector<int>& a, std::vector<int>& b){
            return a[1] < b[1];
        });
        
        // Total 记录总共需要移除多少区间
        int total{0};
        // prev 记录 前一个 后值
        int prev = intervals[0][1];
        for(int i=1; i<intervals.size(); ++i) {
            // 后一个前值和前一个后值进行比较，如果较小，有相交，加1
            if(intervals[i][0] < prev) {
                ++ total;
            } else {
                // 更新 前一个后值
                prev = intervals[i][1];
            }
        }
        return total;
    }

};

auto main(int argc, char** argv) -> int {
    vector<vector<int>> intervals {{1, 2}, {2, 4}, {1, 3}};
    Solution s;
    auto erase_count = s.eraseOverlapIntervals(intervals);
    cout << "Need to erase: " << erase_count << " intervals\n"; 
    return EXIT_SUCCESS;
}