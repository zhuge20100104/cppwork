#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit {0};
        for(int i=1; i<prices.size(); ++i) {
            profit += max(0, prices[i] - prices[i-1]);
        }

        return profit;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> prices {7,1,5,3,6,4};
    auto profit = s.maxProfit(prices);
    cout << "Can achieve a max profit of: " << profit << "\n";
    return EXIT_SUCCESS;
}