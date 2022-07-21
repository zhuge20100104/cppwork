#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算最大收益
     * @param prices int整型vector 股票每一天的价格
     * @return int整型
     */
    int maxProfit(vector<int>& prices) {
        // write code here
        int profit {0};
        for(int i=1; i<prices.size(); ++i) {
            if(prices[i] > prices[i-1]) {
                profit += (prices[i] - prices[i-1]);
            }
        }
        return profit;
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