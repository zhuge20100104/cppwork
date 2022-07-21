#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Solution {
    // 大顶堆  存储左边部分的值 例如: 1, 2 , 3, 4, 5  
    // 最先弹出的是 5，最大值
    priority_queue<int, vector<int>, less<int>> max_queue;
    // 小顶堆 存储右边部分的值 例如: 9, 8, 7, 6
    // 最先弹出的是 6，最小值
    priority_queue<int, vector<int>, greater<int>> min_queue;
public:

    void Insert(int num) {
        if(max_queue.size() == min_queue.size()) {
            min_queue.push(num);
            auto ele = min_queue.top();
            min_queue.pop();
            // 最终奇数个元素被放在了max_queue那边，后面要从max_queue取
            max_queue.push(ele);
        } else {
            // 不等的话，说明max_queue比min_queue多，应该放在min_queue里面，让两个相等
            max_queue.push(num);
            auto ele = max_queue.top();
            max_queue.pop();
            min_queue.push(ele);
        } 
    }

    double GetMedian() { 
        double ele {0.0};
        if(max_queue.size() == min_queue.size()) {
            ele = (max_queue.top() + min_queue.top()) * 1.0 /2;
        } else {
            ele = max_queue.top() * 1.0;
        }
        return ele;
    }
};


// 题目: https://www.nowcoder.com/practice/9be0172896bd43948f8a32fb954e1be1?tpId=295&tqId=23457&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    return EXIT_SUCCESS;
}