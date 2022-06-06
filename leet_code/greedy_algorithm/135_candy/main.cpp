#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int size = ratings.size();
        if(size < 2) {
            return size;
        }

        // 不能用初始化列表，用初始化列表被解析成 {3, 1}了
        vector<int> num(size, 1);

        for(int i=1; i<size; ++i) {
            if(ratings[i-1] < ratings[i]) {
                num[i] = num[i-1] + 1;
            }
        }

        for(int i=size-1; i>0; --i) {
            if(ratings[i-1]>ratings[i]) {
                num[i-1] = max(num[i-1], num[i]+1);
            }
        }

        return accumulate(num.begin(), num.end(), 0);
    }
};

auto main(int argc, char** argv) -> int {

    vector<int> ratings {1, 0, 2};
    Solution s;
    auto sum = s.candy(ratings);
    std::cout << "Candy's total count is: " << sum << "\n";

    return EXIT_SUCCESS;
}