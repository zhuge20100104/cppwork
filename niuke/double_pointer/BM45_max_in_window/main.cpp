#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Solution {
   
public:
    /**
     * 解法1： 暴力解法，时间超限
    */
    vector<int> maxInWindows(const vector<int>& nums, int size) {
        if(size > nums.size()) {
            return {};
        }

        vector<int> res{};
        for(int i=0; i+size <= nums.size(); ++i) {
            auto cur_max = *max_element(nums.begin()+i, nums.begin()+i + size);
            res.push_back(cur_max);
        }

        return res;
    }
};


// 题目: https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=295&tqId=23458&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    string arr_str;
    string size_str;
    Solution sol;
    int size{0};
    while(getline(cin, arr_str)) {
        stringstream ss{arr_str};
        string temp;
        vector<int> nums;
        while(getline(ss, temp, ',')) {
            auto num = stoi(temp);
            nums.push_back(num);
        }

        cout << "size: ";

        getline(cin, size_str);
        size = stoi(size_str);
        auto maxs = sol.maxInWindows(nums, size);

        stringstream res_ss;
        res_ss << "[";
        for(auto const& ele: maxs) {
            res_ss << ele << ',';
        }
        auto str = res_ss.str();
        str = str.substr(0, str.size()-1);
        cout << str << "]\n";
    }
    return EXIT_SUCCESS;
}