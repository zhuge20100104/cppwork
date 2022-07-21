#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if(k > input.size()) {
            return {};
        }
        
        sort(input.begin(), input.end());
        vector<int> res{};
        copy(input.begin(), input.begin() + k, back_inserter(res));
        return res;
    }


    vector<int> GetLeastNumbers_Solution2(vector<int> input, int k) {
        if(k > input.size()) {
            return {};
        }

        priority_queue<int, vector<int>, greater<int>> qu;

        for(auto const& ele: input) {
            qu.emplace(ele);
        }

        vector<int> res{};
        int i {0};
        while(i < k) {
            res.push_back(qu.top());
            qu.pop();
            ++i;
        }

        return res;
    }
};

// 题目: https://www.nowcoder.com/practice/6a296eb82cf844ca8539b57c23e6e9bf?tpId=295&tqId=23263&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    return EXIT_SUCCESS;
}