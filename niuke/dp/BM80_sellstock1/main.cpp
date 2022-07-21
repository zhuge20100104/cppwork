#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:

    /**
     * 方法2
     * 
     * @param prices int整型vector 
     * @return int整型
     */
    int maxProfit2(vector<int>& prices) {
        // write code here
        int min_prices = *max_element(prices.begin(), prices.end());
        int max_profit {0};

        for(auto const& p: prices) {
            if(p < min_prices) {
                min_prices = p;
            } else if(p - min_prices > max_profit) {
                max_profit = p - min_prices;
            }
        }

        return max_profit;
    }

    /**
     * 方法1： 暴力解法
     * 时间复杂度不满足要求，太慢了
     * 
     * @param prices int整型vector 
     * @return int整型
     */
    int maxProfit(vector<int>& prices) {
        // write code here
        int days = prices.size();
        int max_pro {0};
        for(int i=1; i<days; ++i) {
            for(int j=0; j<i; ++j) {
                max_pro = max(max_pro, prices[i]-prices[j]);
            }
        }
        return max_pro;
    }
};


// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {

    string arr_str;
    Solution sol;
    while(getline(cin, arr_str)) {
        stringstream ss{arr_str};
        string temp;
        vector<int> prices;
        while(getline(ss, temp, ',')) {
            auto num = stoi(temp);
            prices.push_back(num);
        }     

        auto max_pro = sol.maxProfit(prices);
        cout << max_pro << endl; 
    }
    return EXIT_SUCCESS;
}