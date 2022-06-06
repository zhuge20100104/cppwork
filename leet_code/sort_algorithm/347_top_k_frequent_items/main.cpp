#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;


class Solution {
public:

    // 先统计每个元素出现的频次
    // 然后使用priority_queue统计前k个频繁出现的元素 及其频次
    // 套路是，如果没有到k个，随便压入，
    // 如果到了k个，如果最下面一个最小的比 当前的count 要小，弹出最小的，
    // 压入最新的
    // 最后使用std::vector 弹出前k个结果
    // 注意，因为每次弹出要弹出最小的，所以需要使用小顶堆
    // 在C++ 中，compare 算子要使用greater算子
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> nums_counts;
        for(auto const& num: nums) {
            ++nums_counts[num];
        }

        // 小顶堆需要使用greater算子
        auto cmp = [](pair<int, int> const& ele1, pair<int, int> const& ele2) {
            return ele1.second > ele2.second;
        };
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> nums_queue(cmp);
        
       
        for(auto const& [num, count]: nums_counts) {
            // 说明已经到了k个了
            if(nums_queue.size()==k) {
                // 当前元素列表出现的最小次数 < count 
                if(nums_queue.top().second < count) {
                    nums_queue.pop();
                    nums_queue.emplace(num, count);
                }
                // 还没到k个，随便放
            } else {
                nums_queue.emplace(num, count);
            }   
        }

        vector<int> ret;
        while(!nums_queue.empty()) {
            ret.emplace_back(nums_queue.top().first);
            nums_queue.pop();
        }
        
        return ret;
    }


    // 方法2，基于快排做快速选择
    // 算法步骤如下，
    // 1. 先算出每个 元素出现的次数
    // 2. 转换成一个std::vector<pair<int, int>>对象
    // 3. 对上一部生成的vector做快排，如果 k < mid - start，那么只需要在  [start, mid -1)
    //  范围内继续做快排即可
    //  如果k > mid - start
    //  那么首先 要处理 0 -> mid - start的所有元素，放入到ret_value中。
    //  接着要处理 mid  + 1 ->  end中的所有元素，接着quick_sort，
    //  sort的 k 值范围是 k - (mid - start +1) ，因为前面范围内都已经放完了 mid-start + 1个元素了，所以 k改变了
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> nums_counts;
        for(auto const& num: nums) {
            ++ nums_counts[num];
        }

        vector<pair<int, int>> nums_vec;
        for(auto const& num_count: nums_counts) {
            nums_vec.emplace_back(num_count);
        }

        vector<int> res;
        qsort(nums_vec, 0, nums_vec.size()-1, res, k);
        return res;
    }

    void qsort(vector<pair<int, int>>& nums, int start, int end, vector<int>& res, int k) {
        int picked = rand() % (end - start + 1)+ start;
        // 交换 随机位置和 轴位置的值
        swap(nums[picked], nums[start]);
        // 设置中轴值，key值
        int pivot = nums[start].second;
        // 记录当前搬运到最左侧的最大值的索引
        int index {start};

        for(int i = start+1; i<=end; ++i) {
            // 把大于pivot的值，放到pivot的左边
            // 那么小于pivot的值，自然放在了pivot的右边
            if(nums[i].second >= pivot) {
                swap(nums[++index], nums[i]);
            }
        }
        // 将pivot放到中位去
        // 快排的倒序算法
        swap(nums[start], nums[index]);

        // k在排序的左半部分，直接 继续在 start, index-1区间排
        if(k < index - start) {
            qsort(nums, start, index - 1, res, k);
        } else {
            // 现保存左半部分已经排序好的index - start个元素值
            for(int i=start; i<=index; ++i) {
                res.emplace_back(nums[i].first);
            }
            if(k > index - start + 1) {
                // 注意此处k的值变小了，因为已经处理了index-start +1 个元素了
                qsort(nums, index + 1, end, res, k-(index - start + 1));
            }
        }
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;

    return EXIT_SUCCESS;
}