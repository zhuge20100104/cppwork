#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        for(long i=0; i*i<=c; ++i) {
            double b = sqrt(c-i*i);
            if(b==static_cast<int>(b)) {
                return true;
            }
        }
        return false;
    }

    // 使用双向指针法
    bool judgeSquareSum2(int c) {
        long l = 0, r = static_cast<long>(sqrt(c));
        while(l<=r) {
            long sum = l*l + r*r;
            if(sum == c) return true;
            else if(sum > c) --r;
            else ++l; 
        }
        return false;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    int number = 5;
    bool can_square_sum = s.judgeSquareSum2(number);
    if(can_square_sum) 
        cout << number << " can be square sum\n";
    else 
        cout << number << " can't be square sum\n"; 
    return EXIT_SUCCESS;
}